#pragma once

#include <string>
#include <vector>

#include "comal_lsp_protocol.h"
#include "comal_graphics_commands.h"

namespace comal::lsp {

std::vector<Diagnostic> computeDiagnostics(const std::string& text,
                                           const comal::graphics::CommandRegistry& graphicsRegistry);

}  // namespace comal::lsp
