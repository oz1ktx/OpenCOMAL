#include "../include/comal_abc.h"
#include <iostream>
#include <cassert>

int main() {
    std::string melody = "L=1 Q=120 C D E F G A B";
    auto ev = comal::sound::abc::parseABCToTones(melody, 120.0, 1.0);
    // Expect 7 notes
    assert(ev.size() == 7);
    // Basic sanity: first event should be C (approx 261.6 Hz)
    double cFreq = ev[0].frequencyHz;
    if (!(cFreq > 250.0 && cFreq < 270.0)) {
        std::cerr << "Unexpected C frequency: " << cFreq << "\n";
        return 2;
    }
    // Additional octave tests: lowercase and explicit octave numbers
    auto oev = comal::sound::abc::parseABCToTones("L=1 Q=120 c C, c' C5 C3", 120.0, 1.0);
    // Expect 6 tokens: L=,Q= are directives so 5 notes (c, C,, c', C5, C3)
    if (oev.size() != 5) {
        std::cerr << "Unexpected octave parse count: " << oev.size() << "\n";
        return 3;
    }
    // midi numbers expected given parser rules:
    // noteBaseMidi('C') = 60; lowercase 'c' adds 12 -> 72
    if (oev[0].midiNote != 72) { std::cerr << "Expected midi 72 for c, got " << oev[0].midiNote << "\n"; return 4; }
    // 'C,' lowers octave by 12 -> 48
    if (oev[1].midiNote != 48) { std::cerr << "Expected midi 48 for C, got " << oev[1].midiNote << "\n"; return 5; }
    // "c'" -> lowercase 72 + apostrophe +12 = 84
    if (oev[2].midiNote != 84) { std::cerr << "Expected midi 84 for c' got " << oev[2].midiNote << "\n"; return 6; }
    // C5 -> explicit octave 5 -> 60 + 12 = 72
    if (oev[3].midiNote != 72) { std::cerr << "Expected midi 72 for C5 got " << oev[3].midiNote << "\n"; return 7; }
    // C3 -> explicit octave 3 -> 60 - 12 = 48
    if (oev[4].midiNote != 48) { std::cerr << "Expected midi 48 for C3 got " << oev[4].midiNote << "\n"; return 8; }

    // Rest lengths + directive aliases + bar separators
    auto rev = comal::sound::abc::parseABCToTones("L=1/2 Q:120 C z2 | D z/2 || E [| F |]", 120.0, 1.0);
    // Events: C, z2, D, z/2, E, F
    if (rev.size() != 6) {
        std::cerr << "Unexpected rest/bar parse count: " << rev.size() << "\n";
        return 9;
    }
    // C with L=1/2 at Q=120 => 250ms
    if (!(rev[0].durationMs > 240.0 && rev[0].durationMs < 260.0)) {
        std::cerr << "Unexpected C duration: " << rev[0].durationMs << "\n";
        return 10;
    }
    // z2 => 2 * defaultLen => 500ms
    if (!(rev[1].durationMs > 490.0 && rev[1].durationMs < 510.0)) {
        std::cerr << "Unexpected z2 duration: " << rev[1].durationMs << "\n";
        return 11;
    }
    // z/2 => 0.5 * defaultLen => 125ms
    if (!(rev[3].durationMs > 120.0 && rev[3].durationMs < 130.0)) {
        std::cerr << "Unexpected z/2 duration: " << rev[3].durationMs << "\n";
        return 12;
    }

    // Comments and ties
    auto cev = comal::sound::abc::parseABCToTones("L=1 Q=120 C D - E % comment at end", 120.0, 1.0);
    // Expect: C, D (tie - skipped), E (comment removed)
    if (cev.size() != 3) {
        std::cerr << "Unexpected comment/tie parse count: " << cev.size() << "\n";
        return 13;
    }
    // Verify C is parsed correctly
    if (!(cev[0].frequencyHz > 250.0 && cev[0].frequencyHz < 270.0)) {
        std::cerr << "Unexpected C frequency after comment handling\n";
        return 14;
    }
    // Verify D is second
    if (!(cev[1].frequencyHz > 290.0 && cev[1].frequencyHz < 310.0)) {
        std::cerr << "Unexpected D frequency after tie skipping\n";
        return 15;
    }
    // Verify E is third
    if (!(cev[2].frequencyHz > 320.0 && cev[2].frequencyHz < 340.0)) {
        std::cerr << "Unexpected E frequency after tie and comment\n";
        return 16;
    }

    std::cout << "ABC parser test OK (" << ev.size() << " events)\n";
    return 0;
}
