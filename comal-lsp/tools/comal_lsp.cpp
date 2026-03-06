#include "comal_lsp_server.h"
#include <iostream>

int main(int argc, char* argv[]) {
    try {
        comal::lsp::LspServer server;
        server.run();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "LSP Server error: " << e.what() << std::endl;
        return 1;
    }
}
