/// Simple ABC subset parser for converting short ABC/MML-like strings
/// into tone events (frequency + duration). Intended as a lightweight
/// starter parser used by the Engine to drive tone playback.
#pragma once

#include <string>
#include <vector>

namespace comal::sound::abc {

struct ToneEvent {
    double frequencyHz{0.0}; // 0.0 for rest
    int midiNote{-1}; // -1 for rest
    double durationMs{0.0};
};

// Persistent parser state carried across successive parseABCToTones calls.
// Allows multi-segment playback (DATA/READ + PLAY loop) without re-sending
// the ABC header directives (L:, Q:) each time.
// Reset to defaults via resetABCState(), or by PLAY "STOP".
struct ABCState {
    double tempoBpm        = 120.0; // Q: tempo in BPM
    double defaultLen      = 1.0;   // L: default note length in beats
    double beatUnit        = 0.25;  // Q: beat unit (e.g. 0.25 for Q:1/4=123); default is quarter note
};

// Parse a simple ABC/MML-like string into a sequence of ToneEvent.
// State (tempo, note length, beat unit) is read from AND written back to
// `state`, so a subsequent call picks up where the previous one left off.
//
// Supported constructs (initial subset):
// - Notes A-G (upper/lowercase). Accidentals ^ (sharp) and _ (flat).
// - Rests: z or Z, with optional lengths (z2, z/2)
// - Inline directives: L=/L: (default length in beats), Q=/Q: (tempo)
//   Q:<unit>=<bpm> beat-unit form (e.g. Q:1/4=123) is fully supported.
// - Length tokens accept number or fraction (e.g. A2, A/2, A3/2, L=1/4)
// - Common bar separators (|, ||, |], [|) are ignored
// - Comments starting with % are stripped (ignored to end of line)
// - Note ties (-) are ignored (not needed for simple playback)
// The parser is intentionally small and forgiving.
std::vector<ToneEvent> parseABCToTones(const std::string& abc, ABCState& state);

// Convenience overload starting from default state (stateless call).
inline std::vector<ToneEvent> parseABCToTones(const std::string& abc,
                                               double defaultTempoBpm = 120.0,
                                               double defaultLengthBeats = 1.0) {
    ABCState st;
    st.tempoBpm   = defaultTempoBpm;
    st.defaultLen = defaultLengthBeats;
    st.beatUnit   = 0.25;
    return parseABCToTones(abc, st);
}

} // namespace comal::sound::abc
