#include "../include/comal_abc.h"
#include <sstream>
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

static bool isBarSeparatorToken(const std::string& token) {
    if (token.empty()) return false;
    return std::all_of(token.begin(), token.end(), [](unsigned char c) {
        return c == '|' || c == '[' || c == ']';
    });
}

std::vector<ToneEvent> parseABCToTones(const std::string& abc,
                                       double defaultTempoBpm,
                                       double defaultLengthBeats) {
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
    
    std::istringstream ss(processed);
    std::string tok;
    double tempo = defaultTempoBpm;
    double defaultLen = defaultLengthBeats; // in beats

    // Local helper: parse a single note token into a ToneEvent.
    auto parseNoteToken = [&](const std::string &tok)->std::optional<ToneEvent> {
        if (tok.empty()) return std::nullopt;
        size_t pos = 0;

        // Parse accidentals (^ = sharp, _ = flat, = natural)
        int acc = 0;
        while (pos < tok.size()) {
            if (tok[pos] == '^') { acc += 1; pos++; }
            else if (tok[pos] == '_') { acc -= 1; pos++; }
            else if (tok[pos] == '=') { /* natural: reset accidental */ pos++; }
            else break;
        }
        if (pos >= tok.size()) return std::nullopt;

        char rawLetter = tok[pos];
        char letter = std::toupper(static_cast<unsigned char>(rawLetter));
        if (letter < 'A' || letter > 'G') return std::nullopt;
        pos++;

        // Start with base MIDI for octave 4
        int midi = noteBaseMidi(letter);
        // lowercase letter => one octave up
        if (std::islower(static_cast<unsigned char>(rawLetter))) midi += 12;

        // Comma/apostrophe modifiers adjust octave relative to current
        while (pos < tok.size()) {
            if (tok[pos] == ',') { midi -= 12; pos++; }
            else if (tok[pos] == '\'') { midi += 12; pos++; }
            else break;
        }

        // Optional explicit octave digits override previous octave shifts: C4, c5
        if (pos < tok.size() && std::isdigit(static_cast<unsigned char>(tok[pos]))) {
            size_t start = pos;
            while (pos < tok.size() && std::isdigit(static_cast<unsigned char>(tok[pos]))) pos++;
            int oct = std::atoi(tok.c_str() + start);
            if (oct != 0) midi = noteBaseMidi(letter) + (oct - 4) * 12;
        }

        // Parse optional length (integer multiplier or fraction)
        double lengthBeats = defaultLen;
        if (pos < tok.size()) {
            const auto maybeLen = parsePositiveNumberOrFraction(tok.substr(pos));
            if (maybeLen) {
                lengthBeats = defaultLen * *maybeLen;
            }
        }

        midi += acc;
        ToneEvent ev; ev.midiNote = midi; ev.frequencyHz = midiToFreq(midi);
        ev.durationMs = (60000.0 / tempo) * lengthBeats;
        return ev;
    };

    while (ss >> tok) {
        if (tok.empty()) continue;

        // Ignore note-tie connector (ties join note durations, not important for simple playback)
        if (tok == "-") {
            continue;
        }

        if (isBarSeparatorToken(tok)) {
            continue;
        }

        // Uppercase copy for directive matching (handles both uppercase and lowercase input)
        std::string t = tok;
        for (auto &c : t) c = std::toupper(static_cast<unsigned char>(c));

        if ((t.rfind("L=", 0) == 0) || (t.rfind("L:", 0) == 0)) {
            std::string val = tok.substr(2);
            if (auto parsed = parsePositiveNumberOrFraction(val)) {
                defaultLen = *parsed;
            }
            continue;
        }
        if ((t.rfind("Q=", 0) == 0) || (t.rfind("Q:", 0) == 0)) {
            std::string val = tok.substr(2);
            if (auto parsed = parsePositiveNumberOrFraction(val)) {
                tempo = *parsed;
            }
            continue;
        }

        // Rest token (z/Z) with optional length suffix.
        if (!t.empty() && t[0] == 'Z') {
            double lengthBeats = defaultLen;
            if (tok.size() > 1) {
                if (auto parsed = parsePositiveNumberOrFraction(tok.substr(1))) {
                    lengthBeats = defaultLen * *parsed;
                }
            }
            ToneEvent e;
            e.frequencyHz = 0.0;
            e.midiNote = -1;
            e.durationMs = (60000.0 / tempo) * lengthBeats;
            out.push_back(e);
            continue;
        }

        auto maybe = parseNoteToken(tok);
        if (maybe) out.push_back(*maybe);
    }

    return out;
}

} // namespace comal::sound::abc
