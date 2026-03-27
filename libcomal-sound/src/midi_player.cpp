#include "comal_sound.h"

#include <string>
#include <iostream>

namespace comal::sound {

// Minimal ABC/MIDI handling lives here. At the moment this is a
// lightweight stub so the codebase separates responsibilities; real
// parsing/playback implementations can be added here later.
class MidiHandler {
public:
    static void init() {
        // placeholder: initialize MIDI/ABC subsystems if present
        std::cout << "[sound] midi init (stub)\n";
    }

    static void playABC(const std::string& abc) {
        // placeholder: schedule/interpret ABC string
        std::cout << "[sound] playABC stub: " << abc << "\n";
    }
};

} // namespace comal::sound
