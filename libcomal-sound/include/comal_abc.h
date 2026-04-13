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

// Parse a simple, space-separated ABC/MML-like string into a sequence
// of ToneEvent. Supported constructs (initial subset):
// - Notes A-G (uppercase). Accidentals ^ (sharp) and _ (flat) supported.
// - Rests: z or Z, with optional lengths (z2, z/2)
// - Inline directives: L=/L: (default length in beats), Q=/Q: (tempo in BPM)
// - Length tokens accept number or fraction (e.g. A2, A/2, A3/2, L=1/4)
// - Common bar separators (|, ||, |], [|) are ignored
// - Comments starting with % are stripped (ignored to end of line)
// - Note ties (-) are ignored (not needed for simple playback)
// The parser is intentionally small and forgiving: whitespace separates tokens.
std::vector<ToneEvent> parseABCToTones(const std::string& abc,
                                       double defaultTempoBpm = 120.0,
                                       double defaultLengthBeats = 1.0);

} // namespace comal::sound::abc
