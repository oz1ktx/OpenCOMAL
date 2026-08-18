/// @file comal_run.cpp
/// CLI tool: load and execute a COMAL .lst program.
/// Usage: comal-run <filename.lst>

#include "comal_interpreter.h"
#include <iostream>
#include <string>
#include <csignal>
#include <cstdlib>

// Global pointer for signal handler → interpreter bridge.
static comal::runtime::Interpreter* g_interp = nullptr;

static void sigintHandler(int /*sig*/) {
    if (g_interp)
        g_interp->interrupt().request();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: comal-run <program.lst>\n";
        return 1;
    }

    std::string filename = argv[1];

    comal::runtime::Interpreter interp;

    // Install SIGINT handler so Ctrl-C triggers cooperative interrupt.
    g_interp = &interp;
    struct sigaction sa{};
    sa.sa_handler = sigintHandler;
    sa.sa_flags = 0;   // no SA_RESTART — interrupt blocking reads too
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, nullptr);

    int exit_code = 0;
    try {
        interp.loadFile(filename);
        interp.run();
    } catch (const comal::runtime::EscapeSignal&) {
        std::cerr << "Escape\n";
        exit_code = 0;
    } catch (const comal::runtime::StopSignal&) {
        exit_code = 0;
    } catch (const comal::runtime::ComalError& e) {
        std::cerr << "Runtime error";
        if (e.line() > 0)
            std::cerr << " at line " << e.line();
        std::cerr << ": " << e.what() << "\n";
        exit_code = 1;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        exit_code = 1;
    }

    // Use std::_Exit() to bypass destructors and avoid crashes during Qt/audio cleanup.
    // This prevents the Interpreter destructor from running, which would otherwise
    // destroy the sound engine and trigger crashes in Qt's audio infrastructure
    // during static shutdown.
    std::_Exit(exit_code);
    return exit_code;  // unreachable
}
