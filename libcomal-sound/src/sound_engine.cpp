#include "comal_sound.h"

#include <iostream>

#ifdef USE_QTMULTIMEDIA
#include <QAudioFormat>
#include <QAudioSink>
#include <QAudioDevice>
#include <QBuffer>
#include <QIODevice>
#include <QTimer>
#include <QCoreApplication>
#include <QThread>
#include <QByteArray>
#include <QMediaDevices>
#include <cmath>
#include <thread>
#include <chrono>
#include <memory>
#endif

namespace comal::sound {

Engine::Engine() = default;
Engine::~Engine() {
    // Avoid calling into Qt multimedia subsystems during static
    // teardown — QCoreApplication and platform backends may already
    // be partially destroyed which can cause crashes. Do not call
    // `stop()` from the destructor; rely on process teardown to
    // release remaining resources.
}

#ifdef USE_QTMULTIMEDIA
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
        // Generate samples using a phase accumulator to ensure continuity
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
            // write interleaved channels (duplicate mono)
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
#endif

void Engine::stop() {
#ifdef USE_QTMULTIMEDIA
    // If Qt's QCoreApplication has already been destroyed (static
    // teardown ordering), avoid calling into Qt multimedia APIs as
    // they may access torn-down global state and crash. In that
    // case just join background threads and clear bookkeeping.
    if (!QCoreApplication::instance()) {
        // Qt not available; ensure queued QIODevices are cleared.
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
    // Close and release any active QIODevice buffers
    for (auto *b : active_buffers_) {
        if (b) {
            QIODevice* dev = reinterpret_cast<QIODevice*>(b);
            if (dev->isOpen()) dev->close();
            // schedule deletion on Qt event loop
            dev->deleteLater();
        }
    }
    // Stop and delete persistent audio sink if present
    if (persistent_audio_) {
        QAudioSink* sink = reinterpret_cast<QAudioSink*>(persistent_audio_);
        sink->stop();
        delete sink;
        persistent_audio_ = nullptr;
    }
    lk.unlock();

    // Clear bookkeeping
    std::unique_lock<std::mutex> lk2(play_mutex_);
    active_buffers_.clear();
#else
    // nothing to do when multimedia unavailable
#endif
}

void Engine::init() {
#ifdef USE_QTMULTIMEDIA
    if (!QCoreApplication::instance()) {
        static int argc = 1;
        static char arg0[] = "comal-sound";
        static char* argv[] = { arg0, nullptr };
        // Keep QCoreApplication alive for process lifetime
        new QCoreApplication(argc, argv);
    }
    // Report available audio outputs
    // Querying available audio outputs is harmless but avoid printing
    // diagnostic messages here; leave device selection to QMediaDevices.
    try {
        (void)QMediaDevices::defaultAudioOutput();
        (void)QMediaDevices::audioOutputs();
    } catch (...) {
        // ignore
    }
    // Create a persistent audio sink for the lifetime of the Engine.
    try {
        auto dev = QMediaDevices::defaultAudioOutput();
        QAudioSink* sink = new QAudioSink(dev);
        std::unique_lock<std::mutex> lk(play_mutex_);
        persistent_audio_ = reinterpret_cast<void*>(sink);
    } catch (...) {
        // ignore failures here; initialization is best-effort
    }
#else
    std::cout << "[sound] init\n";
#endif
}

void Engine::play(const PlaySpec& spec) {
#ifdef USE_QTMULTIMEDIA
    if (spec.name != "tone") {
        // unsupported play type for now
        return;
    }

    if (spec.params.empty()) return;
    int freq = static_cast<int>(spec.params[0]);
    // Determine duration in milliseconds. Accept either `spec.duration`
    // or the second parameter in `spec.params`. Treat the value as
    // milliseconds (no heuristics for seconds vs ms).
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

    QAudioFormat fmt;
    fmt.setSampleRate(sampleRate);
    fmt.setChannelCount(2);
    fmt.setSampleFormat(QAudioFormat::Int16);

    // Dispatch to Qt thread or call directly
    if (QCoreApplication::instance() && QCoreApplication::instance()->thread() != QThread::currentThread()) {
        QTimer::singleShot(0, QCoreApplication::instance(), [this, freq, sampleCount, sampleRate, ampScale, dur_ms_d]() {
            this->startToneOnQtThread(freq, sampleCount, sampleRate, ampScale, dur_ms_d);
        });
    } else {
        this->startToneOnQtThread(freq, sampleCount, sampleRate, ampScale, dur_ms_d);
    }
#else
    // Fallback when Qt Multimedia is unavailable
    // fallback: no-op when Qt Multimedia is unavailable
#endif
}

#ifdef USE_QTMULTIMEDIA
void Engine::startToneOnQtThread(int freq, int sampleCount, int sampleRate, double ampScale, double dur_ms) {
    QAudioFormat fmt;
    fmt.setSampleRate(sampleRate);
    fmt.setChannelCount(2);
    fmt.setSampleFormat(QAudioFormat::Int16);

    // Create tone IO in Qt thread
        ToneIODevice* tone = new ToneIODevice(freq, sampleCount, sampleRate, 2, ampScale);
    tone->open(QIODevice::ReadOnly);

    // Obtain or create persistent sink
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

    // Ensure the sink uses the requested format. QAudioSink doesn't
    // provide a `setFormat()` API, so recreate the sink when the
    // format differs.
    if (sink->format() != fmt) {
        auto dev = QMediaDevices::defaultAudioOutput();
        delete sink;
        sink = new QAudioSink(dev, fmt);
        std::unique_lock<std::mutex> lk(play_mutex_);
        persistent_audio_ = reinterpret_cast<void*>(sink);
    }

    sink->stop();
    sink->start(tone);

    // Schedule cleanup via Qt singleShot (runs in Qt event loop)
    int wait_ms = static_cast<int>(std::lround(dur_ms)) + 50;
    QTimer::singleShot(wait_ms, tone, [this, tone]() {
        // Let the sink drain naturally; just delete the tone device after
        // the expected duration. Avoid calling sink->stop() here which
        // can introduce discontinuities.
        tone->close();
        tone->deleteLater();
        std::unique_lock<std::mutex> lk(play_mutex_);
        auto it = std::find(active_buffers_.begin(), active_buffers_.end(), reinterpret_cast<void*>(tone));
        if (it != active_buffers_.end()) active_buffers_.erase(it);
    });

    // record bookkeeping
    {
        std::unique_lock<std::mutex> lk(play_mutex_);
        active_buffers_.push_back(reinterpret_cast<void*>(tone));
    }
}
#endif

} // namespace comal::sound
