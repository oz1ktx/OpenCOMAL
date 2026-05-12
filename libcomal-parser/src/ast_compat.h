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
/// Caller owns the returned pointer.
Expression* convert_expression(const struct expression* old_exp);

// ── List conversion helpers ────────────────────────────────────────────────
// Used by grammar actions (parser.y) during Phase 4 rule migration.
// The input list must already be in correct order (reversed if necessary).

ExpList*    convert_exp_list(const struct exp_list* list);
DimList*    convert_dim_list(const struct dim_list* list);
ParmList*   convert_parm_list(const struct parm_list* list);
ImportList* convert_import_list(const struct import_list* list);
PrintList*  convert_print_list(const struct print_list* list);
WhenList*   convert_when_list(const struct when_list* list);
AssignList* convert_assign_list(const struct assign_list* list);

// ── Record / sub-struct conversion helpers ─────────────────────────────────

ExtRec*   convert_ext_rec(const struct ext_rec* er);

} // namespace comal
