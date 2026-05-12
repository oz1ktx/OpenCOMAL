/// @file ast_compat.h
/// Internal parser declarations for legacy↔modern AST expression conversion.
///
/// Phase 5 (Legacy AST Decommissioning): These are parser-internal only — no
/// code outside libcomal-parser should call them. The modern parser API
/// (comal_parse_line_modern()) produces modern ComalLine* directly without
/// needing these conversion functions. However, the grammar still constructs
/// legacy struct expressions during parsing (from Bison semantic actions in
/// parser_support.cpp), which must be converted to modern variants before
/// being passed to build_*_line() functions.
///
/// These conversion functions exist because rewriting the grammar itself to
/// build modern AST directly would be a major undertaking (Phase 6+).
/// Until then, this compatibility layer is necessary and correct.

#pragma once

#include "comal_ast.h"
#include "comal_ast_modern.h"

namespace comal {

/// Convert a legacy expression struct to a modern Expression*.
/// Used by grammar actions in parser.y (Phase 4 rule migration).
/// Caller owns the returned pointer.
Expression* convert_expression(const struct expression* old_exp);

// ── List conversion helpers ────────────────────────────────────────────────
// Used by grammar actions (parser.y) during Phase 4 rule migration.
// Each converts a legacy linked-list to a modern managed vector.
// The input list must already be in correct order (reversed if necessary).
//
// These are necessary until the Bison grammar is rewritten to build modern
// AST directly (currently it builds legacy structs for performance/compatibility).

ExpList*    convert_exp_list(const struct exp_list* list);
DimList*    convert_dim_list(const struct dim_list* list);
ParmList*   convert_parm_list(const struct parm_list* list);
ImportList* convert_import_list(const struct import_list* list);
PrintList*  convert_print_list(const struct print_list* list);
WhenList*   convert_when_list(const struct when_list* list);
AssignList* convert_assign_list(const struct assign_list* list);

// ── Record / sub-struct conversion helpers ─────────────────────────────────
// Convert supporting record types used by statement rules.

ExtRec* convert_ext_rec(const struct ext_rec* er);

} // namespace comal
