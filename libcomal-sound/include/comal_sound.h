/// Minimal header for libcomal-sound (stub)
#pragma once

#include <string>
#include <vector>
#include <atomic>
#include <algorithm>
#include <mutex>
#include <thread>
#include <memory>
#include <future>

namespace comal::sound {

struct PlaySpec {
    std::string name;
    double duration = 0.0;
    std::vector<double> params;
    bool async = false;
};

class Engine {
public:
    Engine();
    ~Engine();
    void init();
    // Returns a shared_future handle that will be set when playback finishes.
    std::shared_ptr<std::shared_future<void>> play(const PlaySpec& spec);
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
    // store opaque pointers to QAudioSink to avoid requiring the Qt headers
    // persistent audio output owned by the Engine (opaque QAudioSink*)
    void* persistent_audio_ = nullptr;
    // track active QIODevice pointers used for playback so we can close them
    std::vector<void*> active_buffers_;
    // Qt-specific helper to start a tone on the Qt event loop
    // The optional `completion` promise will be fulfilled when playback finishes.
    void startToneOnQtThread(int freq, int sampleCount, int sampleRate, double ampScale, double dur_ms,
                              std::shared_ptr<std::promise<void>> completion = nullptr);
#else
    // no-op when Qt multimedia is not available
#endif
};

// Register a created Engine so it can be shutdown on process exit.
void registerEngine(Engine* e);
// Stop and destroy all registered engines. Safe to call multiple times.
void shutdownAllEngines();

} // namespace comal::sound
