/// Very small command registry stub for sound commands.
#include "comal_sound.h"
#include <iostream>

namespace comal::sound {

// Example thin wrapper that would parse "play" commands in future.
void run_example_command(Engine& e) {
    PlaySpec p;
    p.name = "beep";
    p.duration = 0.25;
    e.play(p);
}

} // namespace comal::sound
