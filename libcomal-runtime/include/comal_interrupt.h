#ifndef COMAL_INTERRUPT_H
#define COMAL_INTERRUPT_H

/// @file comal_interrupt.h
/// Interrupt controller for cooperative cancellation.
///
/// The runtime checks this at loop iteration boundaries and in the
/// main execution loop.  Any external source (SIGINT handler, GUI
/// button, test harness) can call request() to ask for a stop.
///
/// The interrupt is tested via check(), which throws EscapeSignal
/// if the flag is set.  This integrates cleanly with TRAP/HANDLER.

#include <atomic>

namespace comal::runtime {

class EscapeSignal;  // forward — defined in comal_error.h

class InterruptController {
public:
    /// Request an interrupt from any thread / signal handler.
    /// This is safe to call from a signal handler (lock-free atomic).
    void request() noexcept {
        requested_.store(true, std::memory_order_release);
    }

    /// Clear the interrupt flag.
    void reset() noexcept {
        requested_.store(false, std::memory_order_release);
    }

    /// Returns true if an interrupt has been requested.
    bool pending() const noexcept {
        return requested_.load(std::memory_order_acquire);
    }

    /// Check and throw EscapeSignal if interrupt is pending.
    /// Call this at loop iteration boundaries in the executor.
    inline void check();   // defined after EscapeSignal is visible

private:
    std::atomic<bool> requested_{false};
};

} // namespace comal::runtime

// ── Inline definition (needs EscapeSignal) ──────────────────────────────
#include "comal_error.h"

inline void comal::runtime::InterruptController::check() {
    if (requested_.load(std::memory_order_acquire)) {
        requested_.store(false, std::memory_order_release);
        throw EscapeSignal{};
    }
}

#endif // COMAL_INTERRUPT_H
