#include "../include/comal_sound.h"
#include <iostream>

int main() {
    comal::sound::Engine e;
    e.init();
    comal::sound::PlaySpec p;
    p.name = "test-tone";
    p.duration = 0.1;
    e.play(p);
    std::cout << "sound commands test OK\n";
    return 0;
}
