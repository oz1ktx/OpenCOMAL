/// @file comal_run.cpp
/// CLI tool: load and execute a COMAL .lst program.
/// Usage: comal-run <filename.lst>

#include "comal_interpreter.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: comal-run <program.lst>\n";
        return 1;
    }

    std::string filename = argv[1];

    comal::runtime::Interpreter interp;

    try {
        interp.loadFile(filename);
        interp.run();
    } catch (const comal::runtime::ComalError& e) {
        std::cerr << "Runtime error";
        if (e.line() > 0)
            std::cerr << " at line " << e.line();
        std::cerr << ": " << e.what() << "\n";
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
