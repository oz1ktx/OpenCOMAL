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
    std::cout << "\033[2J\033[H";
    std::cout.flush();
}

void TerminalIO::setCursor(int row, int col) {
    std::cout << "\033[" << row << ";" << col << "H";
    std::cout.flush();
}

} // namespace comal::runtime
