#include "comal_sound.h"

#include <iostream>
#include <future>

namespace comal::sound {

static std::mutex& registry_mutex() {
    static std::mutex m;
    return m;
}

static std::vector<Engine*>& engine_registry() {
    static std::vector<Engine*> reg;
    return reg;
}

void registerEngine(Engine* e) {
    if (!e) return;
    std::lock_guard<std::mutex> lk(registry_mutex());
    auto &r = engine_registry();
    if (std::find(r.begin(), r.end(), e) != r.end())
        return;
    r.push_back(e);
}

void shutdownAllEngines() {
    std::vector<Engine*> engines;
    {
        std::lock_guard<std::mutex> lk(registry_mutex());
        auto &r = engine_registry();
        engines.swap(r);
    }

    for (Engine* e : engines) {
        try { e->stop(); } catch(...) {}
        try { delete e; } catch(...) {}
    }
}


Engine::Engine() = default;
Engine::~Engine() {
    try { stop(); } catch (...) {}
}

void Engine::ensureServiceThread() {
    std::lock_guard<std::mutex> lk(service_mutex_);
    if (service_running_)
        return;

    service_stopping_ = false;
    service_running_ = true;
    service_thread_ = std::thread(&Engine::serviceLoop, this);
}

void Engine::serviceLoop() {
    for (;;) {
        ServiceCommand cmd;
        {
            std::unique_lock<std::mutex> lk(service_mutex_);
            service_cv_.wait(lk, [this]() {
                return service_stopping_ || !service_queue_.empty();
            });

            if (service_stopping_ && service_queue_.empty())
                break;

            cmd = std::move(service_queue_.front());
            service_queue_.pop_front();
        }

        if (cmd.type == ServiceCommandType::Play) {
            try {
                auto inner = playImpl(cmd.play.spec);
                auto done = cmd.play.completion;
                std::thread([inner, done]() {
                    if (inner) {
                        try { inner->wait(); } catch (...) {}
                    }
                    if (done) {
                        try { done->set_value(); } catch (...) {}
                    }
                }).detach();
            } catch (...) {
                if (cmd.play.completion) {
                    try { cmd.play.completion->set_value(); } catch (...) {}
                }
            }
            continue;
        }

        if (cmd.type == ServiceCommandType::StopAll) {
            try { stopActiveImpl(); } catch (...) {}
            if (cmd.completion) {
                try { cmd.completion->set_value(); } catch (...) {}
            }
        }
    }

    std::lock_guard<std::mutex> lk(service_mutex_);
    service_running_ = false;
}

void Engine::init() {
    initImpl();
    ensureServiceThread();
}

std::shared_ptr<std::shared_future<void>> Engine::play(const PlaySpec& spec) {
    ensureServiceThread();

    auto prom = std::make_shared<std::promise<void>>();
    auto fut = std::make_shared<std::shared_future<void>>(prom->get_future().share());

    {
        std::lock_guard<std::mutex> lk(service_mutex_);
        if (service_stopping_) {
            try { prom->set_value(); } catch (...) {}
            return fut;
        }
        ServiceCommand cmd;
        cmd.type = ServiceCommandType::Play;
        cmd.play = QueuedPlay{spec, prom};
        service_queue_.push_back(std::move(cmd));
    }
    service_cv_.notify_one();
    return fut;
}

void Engine::stopActive() {
    ensureServiceThread();

    auto prom = std::make_shared<std::promise<void>>();
    auto fut = prom->get_future().share();
    {
        std::lock_guard<std::mutex> lk(service_mutex_);
        if (service_stopping_) {
            try { prom->set_value(); } catch (...) {}
        } else {
            ServiceCommand cmd;
            cmd.type = ServiceCommandType::StopAll;
            cmd.completion = prom;
            service_queue_.push_back(std::move(cmd));
        }
    }
    service_cv_.notify_one();
    try { fut.wait(); } catch (...) {}
}

void Engine::stop() {
    {
        std::lock_guard<std::mutex> lk(service_mutex_);
        if (!service_running_ && service_thread_.joinable() == false) {
            stopImpl();
            return;
        }
        service_stopping_ = true;
    }
    service_cv_.notify_all();

    if (service_thread_.joinable())
        service_thread_.join();

    std::deque<ServiceCommand> pending;
    {
        std::lock_guard<std::mutex> lk(service_mutex_);
        pending.swap(service_queue_);
    }
    for (auto &cmd : pending) {
        if (cmd.type == ServiceCommandType::Play) {
            if (cmd.play.completion) {
                try { cmd.play.completion->set_value(); } catch (...) {}
            }
            continue;
        }
        if (cmd.completion) {
            try { cmd.completion->set_value(); } catch (...) {}
        }
    }

    stopImpl();
}

// When Qt Multimedia is not available we provide small, self-contained
// fallback implementations here to keep this file minimal. Full Qt
// implementations live in `src/tone_player.cpp` and are compiled only
// when `USE_QTMULTIMEDIA` is defined.
#ifndef USE_QTMULTIMEDIA
void Engine::stopImpl() {
    // nothing to do when multimedia unavailable
}

void Engine::initImpl() {
    std::cout << "[sound] init\n";
}

void Engine::stopActiveImpl() {
    // nothing to do when multimedia unavailable
}

std::shared_ptr<std::shared_future<void>> Engine::playImpl(const PlaySpec& spec) {
    // Fallback: if FluidSynth is available, route ABC-like strings to it.
#ifdef USE_FLUIDSYNTH
    // If the spec encodes an ABC string in spec.name, forward to synth.
    // We expect the runtime to set spec.name to the ABC payload for PLAY.
    // The midi player will return a future that completes when playback ends.
    // Note: this minimal path ignores spec.params and spec.duration for now.
    try {
        // call into midi_player wrapper
        return comal::sound::playABCWithSynth(spec.name);
    } catch (...) {
        std::promise<void> pr; pr.set_value(); return std::make_shared<std::shared_future<void>>(pr.get_future().share());
    }
#else
    // No multimedia / no fluidsynth: return ready future (no-op)
    std::promise<void> pr;
    pr.set_value();
    auto sf = std::make_shared<std::shared_future<void>>(pr.get_future().share());
    return sf;
#endif
}
#else
// Backend implementations are in tone_player.cpp when Qt multimedia is enabled.
#endif

} // namespace comal::sound
