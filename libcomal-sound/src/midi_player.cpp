#include "../include/comal_sound.h"
#include "../include/comal_abc.h"

#ifdef USE_FLUIDSYNTH
#include <fluidsynth.h>
#endif

#include <thread>
#include <chrono>
#include <memory>
#include <future>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <unistd.h>
#include <cstring>

namespace comal::sound {

#ifdef USE_FLUIDSYNTH

namespace {

std::string trimCopy(const std::string& s) {
    const auto begin = s.find_first_not_of(" \t\n\r");
    if (begin == std::string::npos) return {};
    const auto end = s.find_last_not_of(" \t\n\r");
    return s.substr(begin, end - begin + 1);
}

void appendUnique(std::vector<std::string>& out, const std::string& value) {
    if (value.empty()) return;
    if (std::find(out.begin(), out.end(), value) == out.end()) {
        out.push_back(value);
    }
}

std::vector<std::string> parseDriverOverrideList(const char* value) {
    std::vector<std::string> out;
    if (!value || std::strlen(value) == 0) return out;

    std::string list(value);
    std::size_t pos = 0;
    while (true) {
        const std::size_t comma = list.find(',', pos);
        const std::string part = (comma == std::string::npos)
            ? list.substr(pos)
            : list.substr(pos, comma - pos);
        appendUnique(out, trimCopy(part));
        if (comma == std::string::npos) break;
        pos = comma + 1;
    }
    return out;
}

void collectFluidOption(void* data, const char* /*name*/, const char* option) {
    if (!data || !option || std::strlen(option) == 0) return;
    auto* out = static_cast<std::vector<std::string>*>(data);
    appendUnique(*out, option);
}

std::vector<std::string> listFluidAudioDriverOptions(fluid_settings_t* settings) {
    std::vector<std::string> out;
    if (!settings) return out;
    fluid_settings_foreach_option(settings, "audio.driver", &out, collectFluidOption);
    return out;
}

} // namespace

class FluidSynthPlayer {
public:
    FluidSynthPlayer() {
        settings = new_fluid_settings();

        // Reduce voice-allocation failures on dense passages.
        fluid_settings_setint(settings, "synth.polyphony", 512);

        // Use a non-invasive backend by default. Auto/backend default often
        // resolves to raw ALSA, which can interfere with desktop audio stacks.
        const char* driverOverride = std::getenv("COMAL_FLUID_AUDIO_DRIVER");
        std::vector<std::string> preferredDrivers = parseDriverOverrideList(driverOverride);
        appendUnique(preferredDrivers, "pipewire");
        appendUnique(preferredDrivers, "pulseaudio");
        appendUnique(preferredDrivers, "pulse");
        appendUnique(preferredDrivers, "jack");
        appendUnique(preferredDrivers, "alsa");
        appendUnique(preferredDrivers, "portaudio");
        appendUnique(preferredDrivers, "sdl2");
        appendUnique(preferredDrivers, "oss");

        const std::vector<std::string> availableDrivers = listFluidAudioDriverOptions(settings);
        std::vector<std::string> driverCandidates;
        if (!availableDrivers.empty()) {
            for (const auto& preferred : preferredDrivers) {
                if (std::find(availableDrivers.begin(), availableDrivers.end(), preferred) != availableDrivers.end()) {
                    appendUnique(driverCandidates, preferred);
                }
            }
            for (const auto& available : availableDrivers) {
                appendUnique(driverCandidates, available);
            }
        } else {
            driverCandidates = preferredDrivers;
        }

        synth = new_fluid_synth(settings);
        for (const auto& candidate : driverCandidates) {
            fluid_settings_setstr(settings, "audio.driver", candidate.c_str());
            driver = new_fluid_audio_driver(settings, synth);
            if (driver) {
                audioReady_ = true;
                selectedDriver_ = candidate;
                break;
            }
            appendUnique(attemptedDrivers_, candidate);
        }

        // Try to load SF2 from environment variable COMAL_SF2 or common path
        bool sfLoaded = false;
        const char* sfenv = std::getenv("COMAL_SF2");
        if (sfenv) {
            int r = fluid_synth_sfload(synth, sfenv, 1);
            if (r < 0) {
                std::cerr << "[sound] failed to load SF2: " << sfenv << "\n";
            } else {
                sfLoaded = true;
            }
        } else {
            // common locations (best-effort)
            const char* candidates[] = {
                // Common Debian/Ubuntu paths
                "/usr/share/sounds/sf2/FluidR3_GM.sf2",
                "/usr/share/sounds/sf2/GeneralUser_GS.sf2",
                "/usr/share/soundfonts/default.sf2",
                "/usr/share/soundfonts/FluidR3_GM.sf2",
                "/usr/share/sf2/FluidR3_GM.sf2",
                // Common /usr/local locations
                "/usr/local/share/sounds/sf2/FluidR3_GM.sf2",
                "/usr/local/share/soundfonts/default.sf2",
                // Fedora/other layouts
                "/usr/share/sounds/sf2/TimGM6mb.sf2",
                // Fallback null terminator
                nullptr
            };
            for (const char** p = candidates; *p; ++p) {
                if (access(*p, F_OK) == 0) {
                    int r = fluid_synth_sfload(synth, *p, 1);
                    if (r >= 0) {
                        sfLoaded = true;
                        break;
                    }
                }
            }
        }

        soundfontLoaded_ = sfLoaded;
        if (!audioReady_) {
            std::cerr << "[sound] FluidSynth audio driver not available";
            if (!attemptedDrivers_.empty()) {
                std::cerr << " (tried ";
                for (std::size_t i = 0; i < attemptedDrivers_.size(); ++i) {
                    if (i != 0) std::cerr << "/";
                    std::cerr << attemptedDrivers_[i];
                }
                std::cerr << ")";
            }
            std::cerr << "; PLAY will be silent in this session\n";
        } else {
            std::cerr << "[sound] FluidSynth audio driver: " << selectedDriver_ << "\n";
        }
        if (!soundfontLoaded_) {
            std::cerr << "[sound] No SoundFont loaded; PLAY will be silent in this session\n";
        }
    }

    ~FluidSynthPlayer() {
        if (driver) delete_fluid_audio_driver(driver);
        if (synth) delete_fluid_synth(synth);
        if (settings) delete_fluid_settings(settings);
    }

    std::shared_ptr<std::shared_future<void>> playABC(const std::string& abc) {
        auto prom = std::make_shared<std::promise<void>>();
        auto fut = std::make_shared<std::shared_future<void>>(prom->get_future().share());

        if (!synth || !audioReady_ || !soundfontLoaded_) {
            try { prom->set_value(); } catch (...) {}
            return fut;
        }

        // Parse using persistent state so tempo/length directives (L:, Q:)
        // carry over between successive PLAY calls.
        std::vector<comal::sound::abc::ToneEvent> events;
        {
            std::lock_guard<std::mutex> lk(state_mutex_);
            events = comal::sound::abc::parseABCToTones(abc, abcState_);
        }
        // Play asynchronously on a detached thread
        std::thread([this, events = std::move(events), prom]() mutable {
            try {
                // Prevent concurrent PLAY streams from flooding FluidSynth.
                std::lock_guard<std::mutex> playLock(playback_mutex_);

                // Prime the synthesizer and ALSA driver with extended silence to avoid
                // click artifacts. The ALSA driver needs time to initialize buffers properly.
                fluid_synth_noteon(synth, 0, 60, 0);   // Silent note to initialize pipeline
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                fluid_synth_noteoff(synth, 0, 60);
                std::this_thread::sleep_for(std::chrono::milliseconds(200));  // Extended silence

                for (const auto &ev : events) {
                    const int sleepMs = std::max(1, static_cast<int>(std::lround(ev.durationMs)));
                    if (ev.midiNote >= 0) {
                        const int on = fluid_synth_noteon(synth, 0, ev.midiNote, 100);
                        if (on != FLUID_OK) {
                            fluid_synth_all_notes_off(synth, 0);
                            std::this_thread::sleep_for(std::chrono::milliseconds(1));
                            continue;
                        }
                        std::this_thread::sleep_for(std::chrono::milliseconds(sleepMs));
                        fluid_synth_noteoff(synth, 0, ev.midiNote);
                    } else {
                        std::this_thread::sleep_for(std::chrono::milliseconds(sleepMs));
                    }
                }
            } catch (...) {
            }
            try { prom->set_value(); } catch(...) {}
        }).detach();

        return fut;
    }

    void resetABCState() {
        std::lock_guard<std::mutex> lk(state_mutex_);
        abcState_ = comal::sound::abc::ABCState{};
    }

    void stopPlayback() {
        if (synth) {
            // Hard-interrupt all active notes on all channels (0-15)
            for (int ch = 0; ch < 16; ++ch) {
                fluid_synth_all_notes_off(synth, ch);
            }
        }
    }

    bool canPlay() const {
        return synth && audioReady_ && soundfontLoaded_;
    }

private:
    fluid_settings_t* settings{nullptr};
    fluid_synth_t* synth{nullptr};
    fluid_audio_driver_t* driver{nullptr};
    bool audioReady_{false};
    bool soundfontLoaded_{false};
    std::string selectedDriver_;
    std::vector<std::string> attemptedDrivers_;
    std::mutex state_mutex_;
    std::mutex playback_mutex_;
    comal::sound::abc::ABCState abcState_;
};

void* createSynthPlayer() {
    return new FluidSynthPlayer();
}

void destroySynthPlayer(void* player) {
    auto* p = static_cast<FluidSynthPlayer*>(player);
    delete p;
}

#endif // USE_FLUIDSYNTH

// Public wrapper used by Engine::play
std::shared_ptr<std::shared_future<void>> playABCWithSynth(void* player, const std::string& abc) {
#ifdef USE_FLUIDSYNTH
    auto* p = static_cast<FluidSynthPlayer*>(player);
    if (p) return p->playABC(abc);
    // fallback ready future
    std::promise<void> pr; pr.set_value(); return std::make_shared<std::shared_future<void>>(pr.get_future().share());
#else
    (void)player;
    (void)abc;
    std::promise<void> pr; pr.set_value(); return std::make_shared<std::shared_future<void>>(pr.get_future().share());
#endif
}

// Reset persistent ABC parser state (called on PLAY "STOP").
void resetABCPlayerState(void* player) {
#ifdef USE_FLUIDSYNTH
    auto* p = static_cast<FluidSynthPlayer*>(player);
    if (p) p->resetABCState();
#else
    (void)player;
#endif
}

// Hard-interrupt all active MIDI notes on the synthesizer (called on PLAY "STOP").
void stopPlaybackWithSynth(void* player) {
#ifdef USE_FLUIDSYNTH
    auto* p = static_cast<FluidSynthPlayer*>(player);
    if (p) p->stopPlayback();
#else
    (void)player;
#endif
}

bool isABCWithSynthAvailable(void* player) {
#ifdef USE_FLUIDSYNTH
    auto* p = static_cast<FluidSynthPlayer*>(player);
    if (p) return p->canPlay();
    return false;
#else
    (void)player;
    return false;
#endif
}

} // namespace comal::sound
// end of file
