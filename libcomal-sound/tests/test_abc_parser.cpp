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
    std::cout << "ABC parser test OK (" << ev.size() << " events)\n";
    return 0;
}
