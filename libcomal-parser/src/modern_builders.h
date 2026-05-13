/// @file modern_builders.h
/// Bison grammar semantic actions for building modern ComalLine AST directly.
///
/// Used by parser.y to construct ComalLine* nodes instead of legacy
/// struct comal_line. Part of Phase 3 AST modernization.

#pragma once

#include "comal_ast_modern.h"

namespace comal {

// Forward declarations
class ComalLine;
class Expression;
class ExpList;
class DimList;
class ParmList;
class ImportList;
class PrintList;
class WhenList;
class AssignList;

// ============================================================================
// Token symbol conversion
// ============================================================================

/// Convert legacy token symbol to modern StatementType
StatementType token_to_statement_type(int token_symbol);

/// Create simple keyword statement from token symbol (e.g., NULL, END, RETRY, PAGE, etc.)
ComalLine* build_simple_keyword_from_token(int token_symbol);

// ============================================================================
// Builder functions for modern AST nodes (return ComalLine* or component types)
// These replace the corresponding legacy struct-based builders.
// ============================================================================

// Simple statement builders
ComalLine* build_empty_line();
ComalLine* build_print_line(PrintRec&& prec);
ComalLine* build_input_line(InputRec&& irec);
ComalLine* build_close_line(ExpList* exproot);
ComalLine* build_dim_line(DimList* dimlist);
ComalLine* build_assign_line(AssignList* assignroot);
ComalLine* build_for_line(ForRec&& forrec);
ComalLine* build_if_line(IfWhileRec&& ifrec);
ComalLine* build_while_line(IfWhileRec&& whilerec);
ComalLine* build_repeat_line(IfWhileRec&& repeatrec);
ComalLine* build_case_line(Expression* caseexp);
ComalLine* build_exec_line(Expression* procexp);
ComalLine* build_spawn_line(Expression* procexp);
ComalLine* build_spawn_handle_line(Expression* handleExp, Expression* procexp);
ComalLine* build_open_line(OpenRec&& openrec);
ComalLine* build_read_line(ReadRec&& readrec);
ComalLine* build_write_line(WriteRec&& writerec);
ComalLine* build_draw_line(ExpList* drawargs);
ComalLine* build_tone_line(ExpList* toneargs);
ComalLine* build_play_line(ExpList* playargs);
ComalLine* build_sleep_line(ExpList* sleepargs);
ComalLine* build_data_line(ExpList* dataroot);
ComalLine* build_cursor_line(Expression* row, Expression* col);
ComalLine* build_single_exp_line(StatementType cmd, Expression* exp);
ComalLine* build_single_id_line(StatementType cmd, id_rec* id);
ComalLine* build_label_line(id_rec* id);
ComalLine* build_restore_line(id_rec* id);
ComalLine* build_proc_line(ProcFuncRec&& pfrec);
ComalLine* build_func_line(ProcFuncRec&& pfrec);
ComalLine* build_import_line(ImportRec&& importrec);
ComalLine* build_trap_line(TrapRec traprec);
ComalLine* build_when_line(WhenList* whenroot);
ComalLine* build_local_line(DimList* dimlist);
ComalLine* build_simple_keyword_line(StatementType cmd);

} // namespace comal
