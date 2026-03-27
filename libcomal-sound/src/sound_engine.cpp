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
    // fallback: no-op when Qt Multimedia is unavailable — return an already-ready future
    std::promise<void> pr;
    pr.set_value();
    auto sf = std::make_shared<std::shared_future<void>>(pr.get_future().share());
    return sf;
}
#else
// silence - when USE_QTMULTIMEDIA is set the implementation is in tone_player.cpp
#endif

} // namespace comal::sound
