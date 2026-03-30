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
// - Rests: z or Z
// - Inline directives: L= (default length in beats), Q= (tempo in BPM)
// - Note lengths: e.g. A2 (2 beats), A/2 (0.5 beat)
// The parser is intentionally small and forgiving: whitespace separates tokens.
std::vector<ToneEvent> parseABCToTones(const std::string& abc,
                                       double defaultTempoBpm = 120.0,
                                       double defaultLengthBeats = 1.0);

} // namespace comal::sound::abc
