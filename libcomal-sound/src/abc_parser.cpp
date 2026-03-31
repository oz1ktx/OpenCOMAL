#include "../include/comal_abc.h"
#include <sstream>
#include <cctype>
#include <cmath>
#include <optional>
#include <cstdlib>

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

std::vector<ToneEvent> parseABCToTones(const std::string& abc,
                                       double defaultTempoBpm,
                                       double defaultLengthBeats) {
    std::vector<ToneEvent> out;
    std::istringstream ss(abc);
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

        // Parse optional length (integer multiplier or /n fraction)
        double lengthBeats = defaultLen;
        if (pos < tok.size()) {
            if (tok[pos] == '/') {
                pos++;
                if (pos < tok.size() && std::isdigit(static_cast<unsigned char>(tok[pos]))) {
                    int denom = std::atoi(tok.c_str()+pos);
                    if (denom > 0) lengthBeats = defaultLen / denom;
                } else {
                    lengthBeats = defaultLen / 2.0;
                }
            } else if (std::isdigit(static_cast<unsigned char>(tok[pos]))) {
                int mult = std::atoi(tok.c_str()+pos);
                if (mult > 0) lengthBeats = static_cast<double>(mult);
            }
        }

        midi += acc;
        ToneEvent ev; ev.midiNote = midi; ev.frequencyHz = midiToFreq(midi);
        ev.durationMs = (60000.0 / tempo) * lengthBeats;
        return ev;
    };

    while (ss >> tok) {
        if (tok.empty()) continue;
        // Uppercase copy for directive matching
        std::string t = tok;
        for (auto &c : t) c = std::toupper(static_cast<unsigned char>(c));

        if ((t.rfind("L=", 0) == 0) || (t.rfind("L:", 0) == 0)) {
            std::string val = t.substr(2);
            try { defaultLen = std::stod(val); } catch(...) {}
            continue;
        }
        if (t.rfind("Q=", 0) == 0) {
            std::string val = t.substr(2);
            try { tempo = std::stod(val); } catch(...) {}
            continue;
        }

        // Rest token (z/Z)
        if (t == "Z") {
            ToneEvent e; e.frequencyHz = 0.0; e.durationMs = (60000.0 / tempo) * defaultLen; out.push_back(e); continue;
        }

        auto maybe = parseNoteToken(tok);
        if (maybe) out.push_back(*maybe);
    }

    return out;
}

} // namespace comal::sound::abc
