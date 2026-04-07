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
#include <deque>
#include <condition_variable>
#include <unordered_map>
#include <cstdint>

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
    // Stop active playback without shutting down the service thread.
    void stopActive();
    // Stop any active playback and join background threads.
    void stop();
    // Volume 0-100
    void setVolume(int v) { volume_.store(std::clamp(v, 0, 100)); }
    int volume() const { return volume_.load(); }

private:
    struct QueuedPlay {
        PlaySpec spec;
        std::shared_ptr<std::promise<void>> completion;
    };

    enum class ServiceCommandType {
        Play,
        StopAll,
    };

    struct ServiceCommand {
        ServiceCommandType type = ServiceCommandType::Play;
        QueuedPlay play;
        std::shared_ptr<std::promise<void>> completion;
    };

    void ensureServiceThread();
    void serviceLoop();

    // Backend-specific implementations (Qt / fallback)
    void initImpl();
    void stopActiveImpl();
    void stopImpl();
    std::shared_ptr<std::shared_future<void>> playImpl(const PlaySpec& spec);

    std::mutex service_mutex_;
    std::condition_variable service_cv_;
    std::deque<ServiceCommand> service_queue_;
    std::thread service_thread_;
    bool service_running_ = false;
    bool service_stopping_ = false;

    std::atomic<int> volume_{50};
    // Playback bookkeeping for graceful shutdown
#ifdef USE_QTMULTIMEDIA
    std::mutex play_mutex_;
    struct PlaybackEntry {
        void* device = nullptr; // opaque QIODevice*
        std::shared_ptr<std::promise<void>> completion;
    };
    // store opaque pointers to QAudioSink to avoid requiring the Qt headers
    // persistent audio output owned by the Engine (opaque QAudioSink*)
    void* persistent_audio_ = nullptr;
    // track active playbacks by stable id so stop/callback paths cannot race
    std::unordered_map<std::uint64_t, PlaybackEntry> active_playbacks_;
    std::atomic<std::uint64_t> next_playback_id_{1};
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
