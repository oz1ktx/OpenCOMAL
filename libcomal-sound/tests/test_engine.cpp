#include "../include/comal_sound.h"
#include <cassert>

int main() {
    comal::sound::Engine e;
    e.init();
    comal::sound::PlaySpec spec{"unit", 0.05, {440.0}};
    e.play(spec);
    return 0;
}
