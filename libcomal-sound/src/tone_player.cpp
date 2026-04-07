#ifdef USE_QTMULTIMEDIA
#include "comal_sound.h"

#include <QAudioFormat>
#include <QAudioSink>
#include <QAudioDevice>
#include <QIODevice>
#include <QTimer>
#include <QCoreApplication>
#include <QThread>
#include <QMediaDevices>
#include <QMetaObject>

#include <cmath>
#include <algorithm>
#include <memory>
#include <future>

namespace comal::sound {

#ifdef USE_FLUIDSYNTH
// Forward declaration of fluidsynth wrapper implemented in midi_player.cpp
std::shared_ptr<std::shared_future<void>> playABCWithSynth(const std::string& abc);
#endif


// A QIODevice that generates a sine wave on demand. Generates interleaved
// samples for the requested channel count (duplicates mono into all channels).
class ToneIODevice : public QIODevice {
public:
    ToneIODevice(int freq, qint64 samples, int sampleRate, int channels, double amp)
        : frequency(freq), remainingSamples(samples), sampleRate(sampleRate), channelCount(channels), amplitude(amp) {
        phase = 0.0;
    }
    bool isSequential() const override { return true; }
    qint64 bytesAvailable() const override {
        return QIODevice::bytesAvailable() + remainingSamples * channelCount * 2;
    }
protected:
    qint64 readData(char* data, qint64 maxlen) override {
        qint64 bytesPerFrame = channelCount * 2; // 2 bytes per sample
        qint64 framesAvailable = remainingSamples;
        qint64 maxFrames = maxlen / bytesPerFrame;
        qint64 framesToWrite = std::min(maxFrames, framesAvailable);
        if (framesToWrite <= 0) return 0;
        const double twoPiF = 2.0 * M_PI * frequency;
        const double phaseStep = twoPiF / static_cast<double>(sampleRate);
        for (qint64 f = 0; f < framesToWrite; ++f) {
            double v = std::sin(phase);
            int16_t s = static_cast<int16_t>(v * 32767.0 * amplitude);
            for (int ch = 0; ch < channelCount; ++ch) {
                qint64 idx = f * bytesPerFrame + ch * 2;
                data[idx] = static_cast<char>(s & 0xff);
                data[idx+1] = static_cast<char>((s >> 8) & 0xff);
            }
            phase += phaseStep;
            if (phase > 2.0 * M_PI) phase -= 2.0 * M_PI;
        }
        totalSamplesWritten += framesToWrite;
        remainingSamples -= framesToWrite;
        return framesToWrite * bytesPerFrame;
    }
    qint64 writeData(const char*, qint64) override { return -1; }
private:
    int frequency;
    qint64 remainingSamples;
    int sampleRate;
    int channelCount{1};
    double amplitude;
    double phase{0.0};
    qint64 totalSamplesWritten{0};
};

void Engine::stopActiveImpl() {
    // If Qt's QCoreApplication has already been destroyed (static
    // teardown ordering), avoid calling into Qt multimedia APIs as
    // they may access torn-down global state and crash. In that
    // case just join background threads and clear bookkeeping.
    if (!QCoreApplication::instance()) {
        std::unordered_map<std::uint64_t, PlaybackEntry> pending;
        std::unique_lock<std::mutex> lk(play_mutex_);
        pending.swap(active_playbacks_);
        lk.unlock();

        for (auto &kv : pending) {
            QIODevice* dev = reinterpret_cast<QIODevice*>(kv.second.device);
            if (dev) {
                if (dev->isOpen()) dev->close();
                delete dev;
            }
            if (kv.second.completion) {
                try { kv.second.completion->set_value(); } catch (...) {}
            }
        }
        return;
    }

    std::unordered_map<std::uint64_t, PlaybackEntry> pending;
    std::unique_lock<std::mutex> lk(play_mutex_);
    pending.swap(active_playbacks_);
    lk.unlock();

    for (auto &kv : pending) {
        QIODevice* dev = reinterpret_cast<QIODevice*>(kv.second.device);
        if (dev) {
            if (dev->isOpen()) dev->close();
            dev->deleteLater();
        }
        if (kv.second.completion) {
            try { kv.second.completion->set_value(); } catch (...) {}
        }
    }

    if (persistent_audio_) {
        QAudioSink* sink = reinterpret_cast<QAudioSink*>(persistent_audio_);
        sink->stop();
    }
}

void Engine::stopImpl() {
    stopActiveImpl();
    std::unique_lock<std::mutex> lk(play_mutex_);
    if (persistent_audio_) {
        QAudioSink* sink = reinterpret_cast<QAudioSink*>(persistent_audio_);
        delete sink;
        persistent_audio_ = nullptr;
    }
}

void Engine::initImpl() {
    if (!QCoreApplication::instance()) {
        static int argc = 1;
        static char arg0[] = "comal-sound";
        static char* argv[] = { arg0, nullptr };
        new QCoreApplication(argc, argv);
    }
    try {
        (void)QMediaDevices::defaultAudioOutput();
        (void)QMediaDevices::audioOutputs();
    } catch (...) {
        // ignore
    }
    try {
        auto dev = QMediaDevices::defaultAudioOutput();
        QAudioSink* sink = new QAudioSink(dev);
        std::unique_lock<std::mutex> lk(play_mutex_);
        persistent_audio_ = reinterpret_cast<void*>(sink);
    } catch (...) {
        // ignore failures here; initialization is best-effort
    }
}

std::shared_ptr<std::shared_future<void>> Engine::playImpl(const PlaySpec& spec) {
    auto prom = std::make_shared<std::promise<void>>();
    auto fut = std::make_shared<std::shared_future<void>>(prom->get_future().share());

#ifdef USE_FLUIDSYNTH
    if (spec.name != "tone") {
        // If FluidSynth is available, forward ABC/MML strings to the synth
        try {
            return playABCWithSynth(spec.name);
        } catch (...) {
            try { prom->set_value(); } catch (...) {}
            return fut;
        }
    }
#else
    if (spec.name != "tone") {
        // unsupported play type for now — signal completion immediately
        try { prom->set_value(); } catch (...) {}
        return fut;
    }
#endif

    if (spec.params.empty()) {
        try { prom->set_value(); } catch (...) {}
        return fut;
    }
    int freq = static_cast<int>(spec.params[0]);
    double dur_ms_d = spec.duration;
    if (dur_ms_d <= 0.0 && spec.params.size() >= 2)
        dur_ms_d = spec.params[1];
    if (dur_ms_d <= 0.0)
        dur_ms_d = 200.0; // fallback

    const int sampleRate = 44100;
    const int sampleCount = static_cast<int>(std::round(sampleRate * dur_ms_d / 1000.0));

    double ampScale = 0.5; // default
    try {
        ampScale = static_cast<double>(this->volume()) / 100.0;
    } catch (...) {
        ampScale = 0.5;
    }

    if (QCoreApplication::instance() && QCoreApplication::instance()->thread() != QThread::currentThread()) {
        QTimer::singleShot(0, QCoreApplication::instance(), [this, freq, sampleCount, sampleRate, ampScale, dur_ms_d, prom]() {
            this->startToneOnQtThread(freq, sampleCount, sampleRate, ampScale, dur_ms_d, prom);
        });
    } else {
        this->startToneOnQtThread(freq, sampleCount, sampleRate, ampScale, dur_ms_d, prom);
    }

    return fut;
}

void Engine::startToneOnQtThread(int freq, int sampleCount, int sampleRate, double ampScale, double dur_ms,
                                 std::shared_ptr<std::promise<void>> completion) {
    QAudioFormat fmt;
    fmt.setSampleRate(sampleRate);
    fmt.setChannelCount(2);
    fmt.setSampleFormat(QAudioFormat::Int16);

    ToneIODevice* tone = new ToneIODevice(freq, sampleCount, sampleRate, 2, ampScale);
    tone->open(QIODevice::ReadOnly);

    QAudioSink* sink = nullptr;
    {
        std::unique_lock<std::mutex> lk(play_mutex_);
        if (persistent_audio_) sink = reinterpret_cast<QAudioSink*>(persistent_audio_);
    }
    if (!sink) {
        auto dev = QMediaDevices::defaultAudioOutput();
        sink = new QAudioSink(dev, fmt);
        std::unique_lock<std::mutex> lk(play_mutex_);
        persistent_audio_ = reinterpret_cast<void*>(sink);
    }

    if (sink->format() != fmt) {
        auto dev = QMediaDevices::defaultAudioOutput();
        delete sink;
        sink = new QAudioSink(dev, fmt);
        std::unique_lock<std::mutex> lk(play_mutex_);
        persistent_audio_ = reinterpret_cast<void*>(sink);
    }

    sink->stop();
    sink->start(tone);

    const std::uint64_t playbackId = next_playback_id_.fetch_add(1);
    {
        std::unique_lock<std::mutex> lk(play_mutex_);
        active_playbacks_[playbackId] = PlaybackEntry{reinterpret_cast<void*>(tone), completion};
    }

    int wait_ms = static_cast<int>(std::lround(dur_ms)) + 50;
    // Wait on a helper thread, then complete cleanup by playback id.
    std::thread([this, playbackId, wait_ms]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(wait_ms));

        auto cleanupOnQtThread = [this, playbackId]() {
            QIODevice* dev = nullptr;
            std::shared_ptr<std::promise<void>> done;
            {
                std::unique_lock<std::mutex> lk(play_mutex_);
                auto it = active_playbacks_.find(playbackId);
                if (it == active_playbacks_.end())
                    return;
                dev = reinterpret_cast<QIODevice*>(it->second.device);
                done = it->second.completion;
                active_playbacks_.erase(it);
            }

            if (dev) {
                dev->close();
                if (QCoreApplication::instance()) dev->deleteLater();
                else delete dev;
            }
            if (done) {
                try { done->set_value(); } catch (...) {}
            }
        };

        bool queued = false;
        if (QCoreApplication::instance()) {
            queued = QMetaObject::invokeMethod(QCoreApplication::instance(), cleanupOnQtThread, Qt::QueuedConnection);
        }

        if (!queued) {
            // No event loop available: resolve safely in this thread by id.
            QIODevice* dev = nullptr;
            std::shared_ptr<std::promise<void>> done;
            {
                std::unique_lock<std::mutex> lk(play_mutex_);
                auto it = active_playbacks_.find(playbackId);
                if (it == active_playbacks_.end())
                    return;
                dev = reinterpret_cast<QIODevice*>(it->second.device);
                done = it->second.completion;
                active_playbacks_.erase(it);
            }

            if (dev) {
                try { dev->close(); } catch (...) {}
                try { delete dev; } catch (...) {}
            }
            if (done) {
                try { done->set_value(); } catch (...) {}
            }
        }
    }).detach();
}

} // namespace comal::sound

#endif // USE_QTMULTIMEDIA
