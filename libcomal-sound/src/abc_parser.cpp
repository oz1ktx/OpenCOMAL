#include "../include/comal_abc.h"
#include <sstream>
#include <cctype>
#include <cmath>

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

    while (ss >> tok) {
        if (tok.empty()) continue;
        // Normalize token
        std::string t = tok;
        // Uppercase for directives and notes
        for (auto &c : t) c = std::toupper(static_cast<unsigned char>(c));

        // Directives: L= or L: (length in beats), Q= (tempo)
        if ((t.rfind("L=", 0) == 0) || (t.rfind("L:", 0) == 0)) {
            std::string val = t.substr(2);
            try {
                defaultLen = std::stod(val);
            } catch(...) {}
            continue;
        }
        if (t.rfind("Q=", 0) == 0) {
            std::string val = t.substr(2);
            try { tempo = std::stod(val); } catch(...) {}
            continue;
        }

        // Rest
        if (t == "Z") {
            ToneEvent e; e.frequencyHz = 0.0; e.durationMs = (60000.0 / tempo) * defaultLen; out.push_back(e); continue;
        }

        // Parse accidentals (^ = sharp, _ = flat) at start
        int acc = 0;
        size_t pos = 0;
        while (pos < tok.size()) {
            if (tok[pos] == '^') { acc += 1; pos++; }
            else if (tok[pos] == '_') { acc -= 1; pos++; }
            else if (tok[pos] == '=') { /* natural: ignore */ pos++; }
            else break;
        }

        if (pos >= tok.size()) continue;

        char letter = std::toupper(static_cast<unsigned char>(tok[pos]));
        if (letter < 'A' || letter > 'G') continue;
        pos++;

        // Parse optional length (integer or /n)
        double lengthBeats = defaultLen;
        if (pos < tok.size()) {
            if (tok[pos] == '/') {
                // fraction 1/n
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

        int midi = noteBaseMidi(letter) + acc;
        double freq = midiToFreq(midi);
        ToneEvent ev; ev.frequencyHz = freq; ev.durationMs = (60000.0 / tempo) * lengthBeats; ev.midiNote = midi;
        out.push_back(ev);
    }

    return out;
}

} // namespace comal::sound::abc
