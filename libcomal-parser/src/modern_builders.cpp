/// @file modern_builders.cpp
/// Implementation of modern ComalLine builders for Bison grammar actions.
/// Phase 3: Bison semantic actions now build ComalLine* directly.

#include "modern_builders.h"
#include "comal_ast_modern.h"
#include "comal_legacy_shims.h"
#include "parser.tab.h"
#include <memory>

namespace comal {

// Helper: create line metadata (nullptr for now; line numbers added post-parse)
static ComalLineData* make_linedata() {
    return nullptr;
}

// ============================================================================
// Token symbol conversion
// ============================================================================

StatementType token_to_statement_type(int token_symbol) {
    switch (token_symbol) {
        case 0:                return StatementType::Empty;
        case becomesSYM:       return StatementType::Assign;
        case printSYM:         return StatementType::Print;
        case inputSYM:         return StatementType::Input;
        case openSYM:          return StatementType::Open;
        case closeSYM:         return StatementType::Close;
        case readSYM:          return StatementType::Read;
        case writeSYM:         return StatementType::Write;
        case dimSYM:           return StatementType::Dim;
        case dataSYM:          return StatementType::Data;
        case restoreSYM:       return StatementType::Restore;
        case execSYM:          return StatementType::Exec;
        case spawnSYM:         return StatementType::Spawn;
        case returnSYM:        return StatementType::Return;
        case stopSYM:          return StatementType::Stop;
        case endSYM:           return StatementType::End;
        case exitSYM:          return StatementType::Exit;
        case nullSYM:          return StatementType::Null;
        case delSYM:           return StatementType::Del;
        case pageSYM:          return StatementType::Page;
        case cursorSYM:        return StatementType::Cursor;
        case select_outputSYM: return StatementType::Select_Output;
        case select_inputSYM:  return StatementType::Select_Input;
        case dirSYM:           return StatementType::Dir;
        case drawSYM:          return StatementType::Draw;
        case toneSYM:          return StatementType::Tone;
        case playSYM:          return StatementType::Play;
        case sleepSYM:         return StatementType::Sleep;
        case unitSYM:          return StatementType::Unit;
        case chdirSYM:         return StatementType::Chdir;
        case mkdirSYM:         return StatementType::Mkdir;
        case rmdirSYM:         return StatementType::Rmdir;
        case osSYM:            return StatementType::Os;
        case retrySYM:         return StatementType::Retry;
        case idSYM:            return StatementType::Label;
        case localSYM:         return StatementType::Local;
        case forSYM:           return StatementType::For;
        case ifSYM:            return StatementType::If;
        case elifSYM:          return StatementType::Elif;
        case elseSYM:          return StatementType::Else;
        case whileSYM:         return StatementType::While;
        case repeatSYM:        return StatementType::Repeat;
        case untilSYM:         return StatementType::Until;
        case loopSYM:          return StatementType::Loop;
        case caseSYM:          return StatementType::Case;
        case whenSYM:          return StatementType::When;
        case otherwiseSYM:     return StatementType::Otherwise;
        case trapSYM:          return StatementType::Trap;
        case handlerSYM:       return StatementType::Handler;
        case procSYM:          return StatementType::Proc;
        case funcSYM:          return StatementType::Func;
        case importSYM:        return StatementType::Import;
        case endforSYM:        return StatementType::EndFor;
        case endifSYM:         return StatementType::EndIf;
        case endwhileSYM:      return StatementType::EndWhile;
        case endloopSYM:       return StatementType::EndLoop;
        case endcaseSYM:       return StatementType::EndCase;
        case endprocSYM:       return StatementType::EndProc;
        case endfuncSYM:       return StatementType::EndFunc;
        case endtrapSYM:       return StatementType::EndTrap;
        case sysSYM:           return StatementType::Os;
        default:               return StatementType::Empty;
    }
}

ComalLine* build_simple_keyword_from_token(int token_symbol) {
    StatementType cmd = token_to_statement_type(token_symbol);
    return build_simple_keyword_line(cmd);
}

// ============================================================================
// Simple builders
// ============================================================================

ComalLine* build_empty_line() {
    return new ComalLine(make_linedata(), StatementType::Empty, std::monostate{});
}

ComalLine* build_simple_keyword_line(StatementType cmd) {
    return new ComalLine(make_linedata(), cmd, std::monostate{});
}

ComalLine* build_single_exp_line(StatementType cmd, Expression* exp) {
    return new ComalLine(make_linedata(), cmd, exp);
}

ComalLine* build_single_id_line(StatementType cmd, id_rec* id) {
    return new ComalLine(make_linedata(), cmd, id);
}

ComalLine* build_label_line(id_rec* id) {
    return new ComalLine(make_linedata(), StatementType::Label, id);
}

ComalLine* build_restore_line(id_rec* id) {
    return new ComalLine(make_linedata(), StatementType::Restore, id);
}

ComalLine* build_cursor_line(Expression* row, Expression* col) {
    return new ComalLine(make_linedata(), StatementType::Cursor, TwoExp{row, col});
}

// ============================================================================
// Expression list builders
// ============================================================================

ComalLine* build_close_line(ExpList* exproot) {
    return new ComalLine(make_linedata(), StatementType::Close, exproot);
}

ComalLine* build_data_line(ExpList* dataroot) {
    return new ComalLine(make_linedata(), StatementType::Data, dataroot);
}

ComalLine* build_draw_line(ExpList* drawargs) {
    return new ComalLine(make_linedata(), StatementType::Draw, drawargs);
}

ComalLine* build_tone_line(ExpList* toneargs) {
    return new ComalLine(make_linedata(), StatementType::Tone, toneargs);
}

ComalLine* build_play_line(ExpList* playargs) {
    return new ComalLine(make_linedata(), StatementType::Play, playargs);
}

ComalLine* build_sleep_line(ExpList* sleepargs) {
    return new ComalLine(make_linedata(), StatementType::Sleep, sleepargs);
}

// ============================================================================
// Dimension list builders
// ============================================================================

ComalLine* build_dim_line(DimList* dimlist) {
    return new ComalLine(make_linedata(), StatementType::Dim, dimlist);
}

ComalLine* build_local_line(DimList* dimlist) {
    return new ComalLine(make_linedata(), StatementType::Local, dimlist);
}

// ============================================================================
// Complex record builders
// ============================================================================

ComalLine* build_print_line(PrintRec&& prec) {
    return new ComalLine(make_linedata(), StatementType::Print, std::move(prec));
}

ComalLine* build_input_line(InputRec&& irec) {
    return new ComalLine(make_linedata(), StatementType::Input, std::move(irec));
}

ComalLine* build_open_line(OpenRec&& openrec) {
    return new ComalLine(make_linedata(), StatementType::Open, std::move(openrec));
}

ComalLine* build_read_line(ReadRec&& readrec) {
    return new ComalLine(make_linedata(), StatementType::Read, std::move(readrec));
}

ComalLine* build_write_line(WriteRec&& writerec) {
    return new ComalLine(make_linedata(), StatementType::Write, std::move(writerec));
}

ComalLine* build_assign_line(AssignList* assignroot) {
    return new ComalLine(make_linedata(), StatementType::Assign, assignroot);
}

ComalLine* build_for_line(ForRec&& forrec) {
    return new ComalLine(make_linedata(), StatementType::For, std::move(forrec));
}

ComalLine* build_if_line(IfWhileRec&& ifrec) {
    return new ComalLine(make_linedata(), StatementType::If, std::move(ifrec));
}

ComalLine* build_while_line(IfWhileRec&& whilerec) {
    return new ComalLine(make_linedata(), StatementType::While, std::move(whilerec));
}

ComalLine* build_repeat_line(IfWhileRec&& repeatrec) {
    return new ComalLine(make_linedata(), StatementType::Repeat, std::move(repeatrec));
}

ComalLine* build_case_line(Expression* caseexp) {
    return new ComalLine(make_linedata(), StatementType::Case, caseexp);
}

ComalLine* build_proc_line(ProcFuncRec&& pfrec) {
    return new ComalLine(make_linedata(), StatementType::Proc, std::move(pfrec));
}

ComalLine* build_func_line(ProcFuncRec&& pfrec) {
    return new ComalLine(make_linedata(), StatementType::Func, std::move(pfrec));
}

ComalLine* build_import_line(ImportRec&& importrec) {
    return new ComalLine(make_linedata(), StatementType::Import, std::move(importrec));
}

ComalLine* build_trap_line(TrapRec traprec) {
    return new ComalLine(make_linedata(), StatementType::Trap, traprec);
}

ComalLine* build_when_line(WhenList* whenroot) {
    return new ComalLine(make_linedata(), StatementType::When, whenroot);
}

ComalLine* build_exec_line(Expression* procexp) {
    return new ComalLine(make_linedata(), StatementType::Exec, procexp);
}

ComalLine* build_spawn_line(Expression* procexp) {
    return new ComalLine(make_linedata(), StatementType::Spawn, procexp);
}

} // namespace comal
