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

#include <cmath>
#include <algorithm>
#include <memory>
#include <future>

namespace comal::sound {

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

void Engine::stop() {
    // If Qt's QCoreApplication has already been destroyed (static
    // teardown ordering), avoid calling into Qt multimedia APIs as
    // they may access torn-down global state and crash. In that
    // case just join background threads and clear bookkeeping.
    if (!QCoreApplication::instance()) {
        std::unique_lock<std::mutex> lk(play_mutex_);
        for (auto *b : active_buffers_) {
            if (b) {
                QIODevice* dev = reinterpret_cast<QIODevice*>(b);
                if (dev->isOpen()) dev->close();
                dev->deleteLater();
            }
        }
        active_buffers_.clear();
        return;
    }

    std::unique_lock<std::mutex> lk(play_mutex_);
    for (auto *b : active_buffers_) {
        if (b) {
            QIODevice* dev = reinterpret_cast<QIODevice*>(b);
            if (dev->isOpen()) dev->close();
            dev->deleteLater();
        }
    }
    if (persistent_audio_) {
        QAudioSink* sink = reinterpret_cast<QAudioSink*>(persistent_audio_);
        sink->stop();
        delete sink;
        persistent_audio_ = nullptr;
    }
    lk.unlock();

    std::unique_lock<std::mutex> lk2(play_mutex_);
    active_buffers_.clear();
}

void Engine::init() {
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

std::shared_ptr<std::shared_future<void>> Engine::play(const PlaySpec& spec) {
    auto prom = std::make_shared<std::promise<void>>();
    auto fut = std::make_shared<std::shared_future<void>>(prom->get_future().share());

    if (spec.name != "tone") {
        // unsupported play type for now — signal completion immediately
        try { prom->set_value(); } catch (...) {}
        return fut;
    }

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

    int wait_ms = static_cast<int>(std::lround(dur_ms)) + 50;
    // Use a background thread to wait and then post cleanup to the Qt event loop.
    std::thread([this, tone, wait_ms, completion]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(wait_ms));
        bool queued = false;
        if (QCoreApplication::instance()) {
            // Try to post cleanup to Qt event loop to safely manipulate QObjects.
            // If the event loop isn't running the queued call may never execute; therefore
            // we still set the completion promise here so callers don't block indefinitely.
            queued = QMetaObject::invokeMethod(QCoreApplication::instance(), [this, tone]() {
                tone->close();
                tone->deleteLater();
                std::unique_lock<std::mutex> lk(play_mutex_);
                auto it = std::find(active_buffers_.begin(), active_buffers_.end(), reinterpret_cast<void*>(tone));
                if (it != active_buffers_.end()) active_buffers_.erase(it);
            }, Qt::QueuedConnection);
        }

        if (!queued) {
            // No event loop or invokeMethod failed — perform cleanup here.
            try {
                tone->close();
            } catch(...){}
            try {
                delete tone;
            } catch(...){}
            std::unique_lock<std::mutex> lk(play_mutex_);
            auto it = std::find(active_buffers_.begin(), active_buffers_.end(), reinterpret_cast<void*>(tone));
            if (it != active_buffers_.end()) active_buffers_.erase(it);
            lk.unlock();
        }

        if (completion) {
            try { completion->set_value(); } catch (...) {}
        }
    }).detach();

    {
        std::unique_lock<std::mutex> lk(play_mutex_);
        active_buffers_.push_back(reinterpret_cast<void*>(tone));
    }
}

} // namespace comal::sound

#endif // USE_QTMULTIMEDIA
