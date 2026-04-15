#include "../include/comal_abc.h"
#include <iostream>
#include <cassert>
#include <vector>

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

    // Real-world compact ABC body, ingested line-by-line (like DATA/READ + PLAY).
    const std::vector<std::string> pinkPantherLines = {
        "z4 z3/2^D/2 E/2z^E/2|F8-|F4- F/2z^D/2 =E/2z^E/2|F8-|F4- F/2z^E/2 =E/2z^D/2|=D8-|D4- D/2z^D/2 E/2z^E/2|F8-|",
        "F4- F/2z3^A,/2|B,/2z3C/2 =D/2z3^A,/2|B,/2zC/2 D/2zG/2 F/2zB,/2 D/2zF/2|^E4- ^E/2(3=EDB,=A,B,/2-|B,3z4z/2^A,/2|",
        "B,3/2z2C/2 D3/2z2^A,/2|B,3/2C/2 D3/2G/2 F3/2D/2 F3/2B/2|^A8-|^A4 z3z/2^A,/2|B,3/2z2C/2 D3/2z2^A,/2|B,3/2C/2 D3/2G/2 F3/2B,/2 D3/2F/2|",
        "^E4- ^E/2(3=EDB,=A,B,/2-|B,3z4z|z2 B3/2=A/2 F3/2E/2 D3/2B,/2|^E/2=E3/2 ^E/2=E3/2 ^E/2=E3/2 ^E/2=E3/2|(3DB,A, B,B,4-B,-|",
        "B,2- B,/2z4z3/2|(3DB,A, B,B,4-B,-|B,2- B,/2z4z3/2|(3DB,A, B,B,4-B,-|B,2- B,/2z4z^A/2|B/2z3c/2 d/2z3^A/2|",
        "B/2zc/2 d/2zg/2 f/2zB/2 d/2zf/2|^e4- ^e/2(3=edB=AB/2-|B3z4z/2^A/2|B3/2z2c/2 d3/2z2^A/2|B3/2c/2 d3/2g/2 f3/2d/2 f3/2b/2|^a8-|",
        "^a4 z3z/2^A/2|B3/2z2c/2 d3/2z2^A/2|B3/2c/2 d3/2g/2 f3/2B/2 d3/2f/2|^e4- ^e/2(3=edB=AB/2-|B3z4z|z2 B3/2A/2 F3/2E/2 D3/2B,/2|",
        "^E/2=E3/2 ^E/2=E3/2 ^E/2=E3/2 ^E/2=E3/2|(3DB,A, B,B,4-B,-|B,4- B,z3|(3DB,A, B,B,4-B,-|B,4- B,z3|",
        "(3DB,A, B,B,3- B,/2z3/2|z6 c'2-|c'4- c'3/2|]"
    };

    std::string stitched = "L:1/8\nQ:1/4=123\nK:C\n";
    for (const auto& line : pinkPantherLines) {
        stitched += line;
        stitched += "\n";
    }

    auto pev = comal::sound::abc::parseABCToTones(stitched, 120.0, 1.0);    if (pev.empty()) {
        std::cerr << "Pink Panther compact body produced no events\n";
        return 17;
    }
    if (pev[0].midiNote != -1) {
        std::cerr << "Expected first event to be rest from z4\n";
        return 18;
    }
    // With Q:1/4=123: beatUnit=0.25, L:1/8: defaultLen=0.125
    // z4 => (60000/123) * (0.125/0.25) * 4 = 487.8 * 0.5 * 4 = 975.6ms
    if (!(pev[0].durationMs > 960.0 && pev[0].durationMs < 990.0)) {
        std::cerr << "Unexpected z4 duration at Q:1/4=123 L:1/8 => "
                  << pev[0].durationMs << "\n";
        return 19;
    }

    // Inline directive + music on same line should not drop notes.
    auto iev = comal::sound::abc::parseABCToTones("L:1/8 Q:1/4=123 z4 ^D/2 E/2", 120.0, 1.0);
    if (iev.size() < 3) {
        std::cerr << "Inline L:/Q: line lost note/rest events: " << iev.size() << "\n";
        return 20;
    }
    if (iev[0].midiNote != -1) {
        std::cerr << "Expected first inline event to be rest z4\n";
        return 21;
    }

    // Regression: in ABC, digits after octave marks are lengths, not octave overrides.
    // B,4 should be a long note (4x default length) at lowered octave.
    auto l1 = comal::sound::abc::parseABCToTones("L:1/8 Q:1/4=120 B,4", 120.0, 1.0);
    if (l1.size() != 1) {
        std::cerr << "Expected one event for B,4, got " << l1.size() << "\n";
        return 28;
    }
    if (!(l1[0].durationMs > 980.0 && l1[0].durationMs < 1020.0)) {
        std::cerr << "Expected B,4 duration ~1000ms, got " << l1[0].durationMs << "\n";
        return 29;
    }

    // c'2 should keep octave from apostrophe and use 2x length.
    auto l2 = comal::sound::abc::parseABCToTones("L:1/8 Q:1/4=120 c'2", 120.0, 1.0);
    if (l2.size() != 1) {
        std::cerr << "Expected one event for c'2, got " << l2.size() << "\n";
        return 30;
    }
    if (!(l2[0].durationMs > 480.0 && l2[0].durationMs < 520.0)) {
        std::cerr << "Expected c'2 duration ~500ms, got " << l2[0].durationMs << "\n";
        return 31;
    }

    std::cout << "ABC parser test OK (" << ev.size() << " events)\n";

    // ── Stateful multi-call test ──────────────────────────────────────────
    // Send header in first call; body-only in subsequent calls. State should
    // carry tempo and note length across calls without re-sending the header.
    {
        using namespace comal::sound::abc;
        ABCState st;
        // First call: header only (no notes)
        auto h = parseABCToTones("L:1/8 Q:1/4=123", st);
        if (!h.empty()) {
            std::cerr << "Header-only call should produce no events, got " << h.size() << "\n";
            return 22;
        }
        if (!(st.tempoBpm > 122.0 && st.tempoBpm < 124.0)) {
            std::cerr << "State tempoBpm should be ~123, got " << st.tempoBpm << "\n";
            return 23;
        }
        if (!(st.beatUnit > 0.24 && st.beatUnit < 0.26)) {
            std::cerr << "State beatUnit should be ~0.25, got " << st.beatUnit << "\n";
            return 24;
        }

        // Second call: body only — must use inherited L:1/8 Q:1/4=123 state
        auto b = parseABCToTones("z4", st);
        if (b.size() != 1 || b[0].midiNote != -1) {
            std::cerr << "Stateful body call should produce 1 rest, got " << b.size() << "\n";
            return 25;
        }
        // z4 at L:1/8 Q:1/4=123 => 975ms (same as Pink Panther test above)
        if (!(b[0].durationMs > 960.0 && b[0].durationMs < 990.0)) {
            std::cerr << "Stateful z4 duration wrong: " << b[0].durationMs << "\n";
            return 26;
        }

        // Resetting state brings back to defaults
        st = ABCState{};
        auto r = parseABCToTones("z4", st);
        // Default: L=1.0 Q=120 beatUnit=1.0 => (60000/120)*1*4 = 2000ms
        if (!(r[0].durationMs > 1990.0 && r[0].durationMs < 2010.0)) {
            std::cerr << "After reset z4 duration wrong: " << r[0].durationMs << "\n";
            return 27;
        }
    }

    return 0;
}
