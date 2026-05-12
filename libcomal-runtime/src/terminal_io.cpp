// Terminal I/O implementation for console-based COMAL programs.
//
// PLATFORM LIMITATION: This implementation uses ANSI escape codes for cursor
// positioning and screen clearing, which are supported on Linux, macOS, and Unix.
// Windows console does not interpret these codes unless:
//  - Running under WSL2 (Windows Subsystem for Linux)
//  - Using a modern terminal that enables ANSI mode (Windows 10+)
//  - Running under Cygwin or MSYS2 with terminal support
//
// Future: A platform-specific abstraction (Qt-based or native Windows Console API)
// can replace this implementation for true Windows support.
//
#include "comal_io.h"
#include <iostream>

namespace comal::runtime {

void TerminalIO::print(const std::string& text) {
    std::cout << text;
    std::cout.flush();
}

std::string TerminalIO::readLine() {
    std::string line;
    if (!std::getline(std::cin, line))
        return "";
    return line;
}

void TerminalIO::clearScreen() {
    // ANSI escape: ESC[2J (clear screen) + ESC[H (move cursor to home)
    // Not supported on Windows console without ANSI mode enabled.
    std::cout << "\033[2J\033[H";
    std::cout.flush();
}

void TerminalIO::setCursor(int row, int col) {
    // ANSI escape: ESC[<row>;<col>H (move cursor to row,col)
    // Not supported on Windows console without ANSI mode enabled.
    std::cout << "\033[" << row << ";" << col << "H";
    std::cout.flush();
}

} // namespace comal::runtime
