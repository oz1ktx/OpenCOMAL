/// Minimal header for libcomal-sound (stub)
#pragma once

#include <string>
#include <vector>
#include <atomic>
#include <algorithm>
#include <mutex>
#include <thread>
#include <memory>

namespace comal::sound {

struct PlaySpec {
    std::string name;
    double duration = 0.0;
    std::vector<double> params;
};

class Engine {
public:
    Engine();
    ~Engine();
    void init();
    void play(const PlaySpec& spec);
    // Stop any active playback and join background threads.
    void stop();
    // Volume 0-100
    void setVolume(int v) { volume_.store(std::clamp(v, 0, 100)); }
    int volume() const { return volume_.load(); }

private:
    std::atomic<int> volume_{50};
    // Playback bookkeeping for graceful shutdown
#ifdef USE_QTMULTIMEDIA
    std::mutex play_mutex_;
    std::vector<std::thread> play_threads_;
    // store opaque pointers to QAudioSink to avoid requiring the Qt headers
    std::vector<void*> active_audios_;
#else
    // no-op when Qt multimedia is not available
#endif
};

} // namespace comal::sound
