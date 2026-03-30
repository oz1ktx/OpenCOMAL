#include "comal_sound.h"

#include <iostream>
#include <future>

namespace comal::sound {

static std::vector<Engine*>& engine_registry() {
    static std::vector<Engine*> reg;
    return reg;
}

void registerEngine(Engine* e) {
    if (!e) return;
    auto &r = engine_registry();
    r.push_back(e);
}

void shutdownAllEngines() {
    auto &r = engine_registry();
    for (Engine* e : r) {
        try { e->stop(); } catch(...) {}
        try { delete e; } catch(...) {}
    }
    r.clear();
}


Engine::Engine() = default;
Engine::~Engine() {
    // Avoid calling into Qt multimedia subsystems during static
    // teardown — QCoreApplication and platform backends may already
    // be partially destroyed which can cause crashes. Do not call
    // `stop()` from the destructor; rely on process teardown to
    // release remaining resources.
}

// When Qt Multimedia is not available we provide small, self-contained
// fallback implementations here to keep this file minimal. Full Qt
// implementations live in `src/tone_player.cpp` and are compiled only
// when `USE_QTMULTIMEDIA` is defined.
#ifndef USE_QTMULTIMEDIA
void Engine::stop() {
    // nothing to do when multimedia unavailable
}

void Engine::init() {
    std::cout << "[sound] init\n";
}

std::shared_ptr<std::shared_future<void>> Engine::play(const PlaySpec& /*spec*/) {
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
// silence - when USE_QTMULTIMEDIA is set the implementation is in tone_player.cpp
#endif

} // namespace comal::sound
