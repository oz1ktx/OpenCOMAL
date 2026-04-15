#include "../include/comal_abc.h"
#include <cctype>
#include <cmath>
#include <optional>
#include <cstdlib>
#include <algorithm>

namespace comal::sound::abc {

static int noteBaseMidi(char note) {
    // Map uppercase note letter to MIDI number in octave 4
    switch (note) {
        case 'C': return 60;
        case 'D': return 62;
        case 'E': return 64;
        case 'F': return 65;
        case 'G': return 67;
        case 'A': return 69;
        case 'B': return 71;
        default: return 60;
    }
}

static double midiToFreq(int midi) {
    return 440.0 * std::pow(2.0, (midi - 69) / 12.0);
}

static std::optional<double> parsePositiveNumberOrFraction(const std::string& text) {
    if (text.empty()) return std::nullopt;

    const auto slash = text.find('/');
    if (slash == std::string::npos) {
        try {
            const double value = std::stod(text);
            if (value > 0.0) return value;
        } catch (...) {
        }
        return std::nullopt;
    }

    const std::string num = text.substr(0, slash);
    const std::string den = text.substr(slash + 1);
    try {
        const double numerator = num.empty() ? 1.0 : std::stod(num);
        const double denominator = den.empty() ? 2.0 : std::stod(den);
        if (numerator > 0.0 && denominator > 0.0) {
            return numerator / denominator;
        }
    } catch (...) {
    }
    return std::nullopt;
}

static bool isSimpleHeaderKey(char c) {
    unsigned char uc = static_cast<unsigned char>(c);
    return std::isalpha(uc) != 0;
}

static bool parseLengthAt(const std::string& text, size_t& pos, double& ratioOut) {
    const size_t start = pos;

    const size_t numStart = pos;
    while (pos < text.size() && std::isdigit(static_cast<unsigned char>(text[pos]))) ++pos;
    const bool sawNum = (pos > numStart);

    if (pos < text.size() && text[pos] == '/') {
        const size_t slashPos = pos;
        ++pos;
        const size_t denStart = pos;
        while (pos < text.size() && std::isdigit(static_cast<unsigned char>(text[pos]))) ++pos;

        const std::string numeratorText = text.substr(start, slashPos - start);
        const std::string denominatorText = text.substr(denStart, pos - denStart);
        try {
            const double numerator = numeratorText.empty() ? 1.0 : std::stod(numeratorText);
            const double denominator = denominatorText.empty() ? 2.0 : std::stod(denominatorText);
            if (numerator > 0.0 && denominator > 0.0) {
                ratioOut = numerator / denominator;
                return true;
            }
        } catch (...) {
            pos = start;
            return false;
        }
        pos = start;
        return false;
    }

    if (sawNum) {
        try {
            ratioOut = std::stod(text.substr(start, pos - start));
            return ratioOut > 0.0;
        } catch (...) {
            pos = start;
            return false;
        }
    }

    pos = start;
    return false;
}

std::vector<ToneEvent> parseABCToTones(const std::string& abc,
                                       ABCState& state) {
    std::vector<ToneEvent> out;
    
    // Pre-process: remove comments and tokenize
    std::string processed;
    for (size_t i = 0; i < abc.size(); ++i) {
        if (abc[i] == '%') {
            while (i < abc.size() && abc[i] != '\n') ++i;
            if (i < abc.size()) processed += '\n';
        } else {
            processed += abc[i];
        }
    }
    
    double tempo      = state.tempoBpm;
    double defaultLen = state.defaultLen;
    double beatUnit   = state.beatUnit;
    size_t i = 0;
    bool lineStart = true;
    while (i < processed.size()) {
        const char c = processed[i];

        if (c == '\n') {
            ++i;
            lineStart = true;
            continue;
        }

        if (std::isspace(static_cast<unsigned char>(c))) {
            ++i;
            continue;
        }

        // ABC headers like "X:", "M:", "L:", "Q:", "K:" at line start.
        if (lineStart && isSimpleHeaderKey(c) && i + 1 < processed.size() && processed[i + 1] == ':') {
            const char key = std::toupper(static_cast<unsigned char>(c));
            i += 2;
            while (i < processed.size() && std::isspace(static_cast<unsigned char>(processed[i]))) ++i;

            if (key == 'L' || key == 'Q') {
                // Support both pure header lines (L:1/8) and inline use
                // (L:1/8 C D E): consume only directive value token.
                const size_t valueStart = i;
                while (i < processed.size() && !std::isspace(static_cast<unsigned char>(processed[i])) &&
                       processed[i] != '|' && processed[i] != '[' && processed[i] != ']') {
                    ++i;
                }
                std::string val = processed.substr(valueStart, i - valueStart);

                if (key == 'L') {
                    if (auto parsed = parsePositiveNumberOrFraction(val)) {
                        defaultLen = *parsed;
                    }
                } else {
                    // For Q headers like "Q:1/4=123", extract beat unit before '='
                    // (e.g. 1/4) and BPM after '='. Plain "Q:120" keeps beatUnit=1.
                    std::string qval = val;
                    const size_t eq = qval.find('=');
                    if (eq != std::string::npos && eq + 1 < qval.size()) {
                        const std::string buStr = qval.substr(0, eq);
                        if (auto bu = parsePositiveNumberOrFraction(buStr)) {
                            beatUnit = *bu;
                        }
                        qval = qval.substr(eq + 1);
                    }
                    if (auto parsed = parsePositiveNumberOrFraction(qval)) {
                        tempo = *parsed;
                    }
                }
            } else {
                while (i < processed.size() && processed[i] != '\n') ++i;
            }

            lineStart = true;
            continue;
        }

        lineStart = false;

        // Ignore common separators/punctuation and tuplet marker starts.
        if (c == '|' || c == '[' || c == ']' || c == '-' || c == '(' || c == ')' || c == ':') {
            ++i;
            continue;
        }

        // Parse L=/Q= directives that appear inline.
        const char uc = std::toupper(static_cast<unsigned char>(c));
        if ((uc == 'L' || uc == 'Q') && i + 1 < processed.size() && (processed[i + 1] == '=' || processed[i + 1] == ':')) {
            const char key = uc;
            i += 2;
            while (i < processed.size() && std::isspace(static_cast<unsigned char>(processed[i]))) ++i;

            const size_t start = i;
            while (i < processed.size() && !std::isspace(static_cast<unsigned char>(processed[i])) &&
                   processed[i] != '|' && processed[i] != '[' && processed[i] != ']') {
                ++i;
            }
            std::string val = processed.substr(start, i - start);
            if (key == 'Q') {
                const size_t eq = val.find('=');
                if (eq != std::string::npos && eq + 1 < val.size()) {
                    const std::string buStr = val.substr(0, eq);
                    if (auto bu = parsePositiveNumberOrFraction(buStr)) {
                        beatUnit = *bu;
                    }
                    val = val.substr(eq + 1);
                }
            }

            if (auto parsed = parsePositiveNumberOrFraction(val)) {
                if (key == 'L') defaultLen = *parsed;
                else tempo = *parsed;
            }
            continue;
        }

        // Rest token z/Z with optional length suffix.
        if (uc == 'Z') {
            ++i;
            double ratio = 1.0;
            size_t lenPos = i;
            if (parseLengthAt(processed, lenPos, ratio)) {
                i = lenPos;
            }
            ToneEvent e;
            e.frequencyHz = 0.0;
            e.midiNote = -1;
            e.durationMs = (60000.0 / tempo) * (defaultLen / beatUnit) * ratio;
            out.push_back(e);
            continue;
        }

        // Parse note with optional accidentals, octave marks, and length.
        if (c == '^' || c == '_' || c == '=' || (uc >= 'A' && uc <= 'G')) {
            size_t pos = i;

            int acc = 0;
            while (pos < processed.size()) {
                if (processed[pos] == '^') { acc += 1; ++pos; }
                else if (processed[pos] == '_') { acc -= 1; ++pos; }
                else if (processed[pos] == '=') { ++pos; }
                else break;
            }

            if (pos >= processed.size()) {
                ++i;
                continue;
            }

            const char rawLetter = processed[pos];
            const char letter = std::toupper(static_cast<unsigned char>(rawLetter));
            if (letter < 'A' || letter > 'G') {
                ++i;
                continue;
            }
            ++pos;

            int midi = noteBaseMidi(letter);
            if (std::islower(static_cast<unsigned char>(rawLetter))) midi += 12;

            while (pos < processed.size()) {
                if (processed[pos] == ',') { midi -= 12; ++pos; }
                else if (processed[pos] == '\'') { midi += 12; ++pos; }
                else break;
            }

            // In ABC, trailing digits are duration multipliers (e.g., F8),
            // not octave selectors. Octave is handled via case and ','/'\''.

            double ratio = 1.0;
            size_t lenPos = pos;
            if (parseLengthAt(processed, lenPos, ratio)) {
                pos = lenPos;
            }

            midi += acc;
            ToneEvent ev;
            ev.midiNote = midi;
            ev.frequencyHz = midiToFreq(midi);
            ev.durationMs = (60000.0 / tempo) * (defaultLen / beatUnit) * ratio;
            out.push_back(ev);

            i = pos;
            continue;
        }

        // Unknown token fragment: skip one character to stay resilient.
        ++i;
    }

    // Write back state so the next PLAY call continues from where we left off.
    state.tempoBpm   = tempo;
    state.defaultLen = defaultLen;
    state.beatUnit   = beatUnit;

    return out;
}

} // namespace comal::sound::abc
