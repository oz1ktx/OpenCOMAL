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

namespace comal::sound {

#ifdef USE_FLUIDSYNTH

class FluidSynthPlayer {
public:
    FluidSynthPlayer() {
        settings = new_fluid_settings();
        synth = new_fluid_synth(settings);
        // Try to create an audio driver; if it fails we'll still be able
        // to render via synth API or rely on app-level audio.
        driver = new_fluid_audio_driver(settings, synth);

        // Try to load SF2 from environment variable COMAL_SF2 or common path
        const char* sfenv = std::getenv("COMAL_SF2");
        if (sfenv) {
            int r = fluid_synth_sfload(synth, sfenv, 1);
            if (r <= 0) std::cerr << "[sound] failed to load SF2: " << sfenv << "\n";
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
                    if (r > 0) break;
                }
            }
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

        auto events = comal::sound::abc::parseABCToTones(abc);
        // Play asynchronously on a detached thread
        std::thread([this, events = std::move(events), prom]() mutable {
            try {
                for (const auto &ev : events) {
                    if (ev.midiNote >= 0) {
                        fluid_synth_noteon(synth, 0, ev.midiNote, 100);
                        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(std::lround(ev.durationMs))));
                        fluid_synth_noteoff(synth, 0, ev.midiNote);
                    } else {
                        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(std::lround(ev.durationMs))));
                    }
                }
            } catch (...) {
            }
            try { prom->set_value(); } catch(...) {}
        }).detach();

        return fut;
    }

private:
    fluid_settings_t* settings{nullptr};
    fluid_synth_t* synth{nullptr};
    fluid_audio_driver_t* driver{nullptr};
};

// Singleton helper
static FluidSynthPlayer* globalSynth() {
    static FluidSynthPlayer* inst = nullptr;
    if (!inst) inst = new FluidSynthPlayer();
    return inst;
}

#endif // USE_FLUIDSYNTH

// Public wrapper used by Engine::play
std::shared_ptr<std::shared_future<void>> playABCWithSynth(const std::string& abc) {
#ifdef USE_FLUIDSYNTH
    auto g = globalSynth();
    if (g) return g->playABC(abc);
    // fallback ready future
    std::promise<void> pr; pr.set_value(); return std::make_shared<std::shared_future<void>>(pr.get_future().share());
#else
    std::promise<void> pr; pr.set_value(); return std::make_shared<std::shared_future<void>>(pr.get_future().share());
#endif
}

} // namespace comal::sound
// end of file
