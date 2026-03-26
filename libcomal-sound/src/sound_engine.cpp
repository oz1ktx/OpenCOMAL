#include "comal_sound.h"

#include <iostream>

#ifdef USE_QTMULTIMEDIA
#include <QAudioFormat>
#include <QAudioSink>
#include <QAudioDevice>
#include <QBuffer>
#include <QCoreApplication>
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
    stop();
}

void Engine::stop() {
#ifdef USE_QTMULTIMEDIA
    std::unique_lock<std::mutex> lk(play_mutex_);
    // Request stop on all active audio sinks
    for (auto *p : active_audios_) {
        if (p) {
            QAudioSink* a = reinterpret_cast<QAudioSink*>(p);
            a->stop();
        }
    }
    lk.unlock();

    // Join all threads
    for (auto &t : play_threads_) {
        if (t.joinable()) t.join();
    }

    // Clear bookkeeping
    std::unique_lock<std::mutex> lk2(play_mutex_);
    play_threads_.clear();
    active_audios_.clear();
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
    int dur_ms = static_cast<int>(spec.duration);
    if (dur_ms <= 0 && spec.params.size() >= 2) dur_ms = static_cast<int>(spec.params[1]);
    if (dur_ms <= 0) dur_ms = 200; // fallback

    const int sampleRate = 44100;
    const int sampleCount = (sampleRate * dur_ms) / 1000;

    QByteArray pcm;
    pcm.resize(sampleCount * 2);
    const double twoPiF = 2.0 * M_PI * freq;
    double ampScale = 0.5; // default
    try {
        ampScale = static_cast<double>(this->volume()) / 100.0;
    } catch (...) {
        ampScale = 0.5;
    }
    for (int i = 0; i < sampleCount; ++i) {
        double t = static_cast<double>(i) / sampleRate;
        double v = std::sin(twoPiF * t);
        int16_t s = static_cast<int16_t>(v * 32767.0 * ampScale);
        pcm[2*i] = static_cast<char>(s & 0xff);
        pcm[2*i+1] = static_cast<char>((s >> 8) & 0xff);
    }

    QAudioFormat fmt;
    fmt.setSampleRate(sampleRate);
    fmt.setChannelCount(1);
    fmt.setSampleFormat(QAudioFormat::Int16);

    QBuffer buffer(&pcm);
    buffer.open(QIODevice::ReadOnly);

    auto dev = QMediaDevices::defaultAudioOutput();
    // Start playback in a detached thread so caller is non-blocking.
    auto bufferPtr = std::make_shared<QBuffer>();
    bufferPtr->setData(pcm);
    bufferPtr->open(QIODevice::ReadOnly);

    QAudioSink* audio = new QAudioSink(dev);
    audio->start(bufferPtr.get());

    // Spawn a thread to stop and cleanup after playback finishes and
    // keep it joinable so the Engine can perform graceful shutdown.
    std::thread t([this, audio, bufferPtr, dur_ms]() {
        // allow audio to start
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        std::this_thread::sleep_for(std::chrono::milliseconds(dur_ms + 50));
        if (audio) audio->stop();
        bufferPtr->close();
        delete audio;
        // remove audio from active list
        std::unique_lock<std::mutex> lk(play_mutex_);
        auto it = std::find(active_audios_.begin(), active_audios_.end(), reinterpret_cast<void*>(audio));
        if (it != active_audios_.end()) active_audios_.erase(it);
    });

    // record bookkeeping
    {
        std::unique_lock<std::mutex> lk(play_mutex_);
        active_audios_.push_back(audio);
        play_threads_.push_back(std::move(t));
    }
#else
    // Fallback when Qt Multimedia is unavailable
    // fallback: no-op when Qt Multimedia is unavailable
#endif
}

} // namespace comal::sound
