/// @file ast_compat.h
/// Internal parser declarations for legacy↔modern AST conversion functions.
///
/// These are parser-internal only — no code outside libcomal-parser should
/// call them. External callers use comal_parse_line_modern() exclusively.

#pragma once

#include "comal_ast.h"
#include "comal_ast_modern.h"

namespace comal {

/// Convert a legacy comal_line to a modern ComalLine*.
/// Caller owns the returned pointer.
ComalLine* convert_comal_line(const struct comal_line* old_line);

/// Convert a legacy expression to a modern Expression*.
Expression* convert_expression(const struct expression* old_exp);

} // namespace comal
