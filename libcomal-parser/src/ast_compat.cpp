#include "comal_ast_modern.h"
#include "comal_ast.h"
#include "comal_base.h"
#include <cstring>

// Pull in the generated token values (forSYM, printSYM, etc.)
#include "parser.tab.h"

// Compatibility layer: convert between legacy C structs and modern C++ classes
// This allows gradual migration of the parser

namespace comal {

// ── ParmList method implementations (need token constants) ──────────────

bool ParmList::isRef() const { return ref_type_ == refSYM; }
bool ParmList::isName() const { return ref_type_ == nameSYM; }
bool ParmList::isProc() const { return ref_type_ == procSYM; }
bool ParmList::isFunc() const { return ref_type_ == funcSYM; }

// ============================================================================
// Forward declarations of internal conversion helpers
// ============================================================================

static ExpList* convert_exp_list(const struct exp_list* old_list);
static DimList* convert_dim_list(const struct dim_list* old_list);
static ParmList* convert_parm_list(const struct parm_list* old_list);
static ImportList* convert_import_list(const struct import_list* old_list);
static PrintList* convert_print_list(const struct print_list* old_list);
static WhenList* convert_when_list(const struct when_list* old_list);
static AssignList* convert_assign_list(const struct assign_list* old_list);

// Forward declaration — convert_comal_line is defined later but needed
// for recursive conversion of short-form body statements (e.g. IF...THEN, FOR...DO).
ComalLine* convert_comal_line(const struct comal_line* old_line);

// ============================================================================
// Legacy struct -> Modern class conversion: Expressions
// ============================================================================

static OpType map_optype(enum optype old_type) {
    switch (old_type) {
        case T_UNUSED:        return OpType::Unused;
        case T_CONST:         return OpType::Const;
        case T_UNARY:         return OpType::Unary;
        case T_BINARY:        return OpType::Binary;
        case T_INTNUM:        return OpType::IntNum;
        case T_FLOAT:         return OpType::Float;
        case T_SUBSTR:        return OpType::Substr;
        case T_STRING:        return OpType::String;
        case T_ID:            return OpType::Id;
        case T_SID:           return OpType::Sid;
        case T_SYS:           return OpType::Sys;
        case T_SYSS:          return OpType::Syss;
        case T_EXP_IS_NUM:    return OpType::ExpIsNum;
        case T_EXP_IS_STRING: return OpType::ExpIsString;
        case T_ARRAY:         return OpType::Array;
        case T_SARRAY:        return OpType::Sarray;
        default:              return OpType::Unused;
    }
}

static enum optype unmap_optype(OpType new_type) {
    switch (new_type) {
        case OpType::Unused:      return T_UNUSED;
        case OpType::Const:       return T_CONST;
        case OpType::Unary:       return T_UNARY;
        case OpType::Binary:      return T_BINARY;
        case OpType::IntNum:      return T_INTNUM;
        case OpType::Float:       return T_FLOAT;
        case OpType::Substr:      return T_SUBSTR;
        case OpType::String:      return T_STRING;
        case OpType::Id:          return T_ID;
        case OpType::Sid:         return T_SID;
        case OpType::Sys:         return T_SYS;
        case OpType::Syss:        return T_SYSS;
        case OpType::ExpIsNum:    return T_EXP_IS_NUM;
        case OpType::ExpIsString: return T_EXP_IS_STRING;
        case OpType::Array:       return T_ARRAY;
        case OpType::Sarray:      return T_SARRAY;
    }
    return T_UNUSED;
}

Expression* convert_expression(const struct expression* old_exp) {
    if (!old_exp) return nullptr;
    
    OpType new_type = map_optype(old_exp->optype);
    
    // Create data variant based on type
    Expression::Data data;
    switch (new_type) {
        case OpType::IntNum:
            data = static_cast<int64_t>(old_exp->e.num);
            break;
        case OpType::Float:
            data = old_exp->e.fnum.val;  // drop legacy text, keep value only
            break;
        case OpType::String:
            data = old_exp->e.str;
            break;
        case OpType::Unary:
        case OpType::Const:
        case OpType::ExpIsNum:
        case OpType::ExpIsString:
            // Single sub-expression
            data = convert_expression(old_exp->e.exp);
            break;
        case OpType::Binary:
            data = TwoExp{
                convert_expression(old_exp->e.twoexp.exp1),
                convert_expression(old_exp->e.twoexp.exp2)
            };
            break;
        case OpType::Id:
            data = ExpId{
                old_exp->e.expid.id,
                convert_exp_list(old_exp->e.expid.exproot)
            };
            break;
        case OpType::Sid: {
            TwoExp* te = nullptr;
            if (old_exp->e.expsid.twoexp) {
                te = new TwoExp{
                    convert_expression(old_exp->e.expsid.twoexp->exp1),
                    convert_expression(old_exp->e.expsid.twoexp->exp2)
                };
            }
            data = ExpSid{
                old_exp->e.expsid.id,
                convert_exp_list(old_exp->e.expsid.exproot),
                te
            };
            break;
        }
        case OpType::Sys:
        case OpType::Syss:
            // SYS/SYS$ store only an exp_list in e.exproot (no id)
            data = convert_exp_list(old_exp->e.exproot);
            break;
        case OpType::Substr:
            data = ExpSubstr{
                convert_expression(old_exp->e.expsubstr.exp),
                TwoExp{
                    convert_expression(old_exp->e.expsubstr.twoexp.exp1),
                    convert_expression(old_exp->e.expsubstr.twoexp.exp2)
                }
            };
            break;
        case OpType::Array:
        case OpType::Sarray:
            // Arrays use same e.expid layout as T_ID (id + optional subscripts)
            data = ExpId{
                old_exp->e.expid.id,
                convert_exp_list(old_exp->e.expid.exproot)
            };
            break;
        default:
            data = std::monostate{};
            break;
    }
    
    return new Expression(new_type, old_exp->op, std::move(data));
}

// ============================================================================
// Modern class -> Legacy struct conversion (for compatibility during transition)
// ============================================================================

struct expression* convert_to_legacy_expression(const Expression* new_exp, int pool) {
    if (!new_exp) return nullptr;
    
    auto* old_exp = static_cast<struct expression*>(
        mem_alloc(pool, sizeof(struct expression))
    );
    
    old_exp->optype = unmap_optype(new_exp->opType());
    old_exp->op = new_exp->op();
    
    // Convert data based on type
    switch (new_exp->opType()) {
        case OpType::IntNum:
            old_exp->e.num = static_cast<long>(new_exp->asNum());
            break;
        case OpType::Float:
            old_exp->e.fnum.val = new_exp->asFloat();
            old_exp->e.fnum.text = nullptr;  // modern AST no longer carries source text
            break;
        case OpType::String:
            old_exp->e.str = new_exp->asString();
            break;
        // TODO: add more reverse-conversion cases as needed
        default:
            break;
    }
    
    return old_exp;
}

// ============================================================================
// List Conversion Helpers (Legacy -> Modern)
// ============================================================================

static ExpList* convert_exp_list(const struct exp_list* old_list) {
    if (!old_list) return nullptr;
    
    // Convert iteratively, then reverse to preserve order
    ExpList* result = nullptr;
    for (const struct exp_list* cur = old_list; cur; cur = cur->next) {
        auto* node = new ExpList(convert_expression(cur->exp), result);
        result = node;
    }
    return reverse_exp_list(result);
}

static DimEnsion* convert_dimensions(const struct dim_ension* old_dim) {
    if (!old_dim) return nullptr;
    
    DimEnsion* result = nullptr;
    // Build reversed, then reverse
    for (const struct dim_ension* cur = old_dim; cur; cur = cur->next) {
        auto* node = new DimEnsion(
            convert_expression(cur->bottom),
            convert_expression(cur->top),
            result
        );
        result = node;
    }
    // Reverse the list
    DimEnsion* prev = nullptr;
    DimEnsion* current = result;
    while (current) {
        DimEnsion* next = current->next();
        current->setNext(prev);
        prev = current;
        current = next;
    }
    return prev;
}

static DimList* convert_dim_list(const struct dim_list* old_list) {
    if (!old_list) return nullptr;
    
    DimList* result = nullptr;
    for (const struct dim_list* cur = old_list; cur; cur = cur->next) {
        auto* node = new DimList(
            cur->id,
            convert_dimensions(cur->dimensionroot),
            convert_expression(cur->strlen),
            result
        );
        result = node;
    }
    // Reverse to preserve order
    DimList* prev = nullptr;
    DimList* current = result;
    while (current) {
        DimList* next = current->next();
        current->setNext(prev);
        prev = current;
        current = next;
    }
    return prev;
}

static ParmList* convert_parm_list(const struct parm_list* old_list) {
    if (!old_list) return nullptr;
    
    ParmList* result = nullptr;
    for (const struct parm_list* cur = old_list; cur; cur = cur->next) {
        auto* node = new ParmList(
            cur->id,
            cur->ref,
            cur->array != 0,
            result
        );
        result = node;
    }
    // Reverse
    ParmList* prev = nullptr;
    ParmList* current = result;
    while (current) {
        ParmList* next = current->next();
        current->setNext(prev);
        prev = current;
        current = next;
    }
    return prev;
}

static ImportList* convert_import_list(const struct import_list* old_list) {
    if (!old_list) return nullptr;
    
    ImportList* result = nullptr;
    for (const struct import_list* cur = old_list; cur; cur = cur->next) {
        auto* node = new ImportList(
            cur->id,
            cur->array != 0,
            result
        );
        result = node;
    }
    // Reverse
    ImportList* prev = nullptr;
    ImportList* current = result;
    while (current) {
        ImportList* next = current->next();
        current->setNext(prev);
        prev = current;
        current = next;
    }
    return prev;
}

static PrintList* convert_print_list(const struct print_list* old_list) {
    if (!old_list) return nullptr;
    
    PrintList* result = nullptr;
    for (const struct print_list* cur = old_list; cur; cur = cur->next) {
        auto* node = new PrintList(
            convert_expression(cur->exp),
            cur->pr_sep,
            result
        );
        result = node;
    }
    // Reverse
    PrintList* prev = nullptr;
    PrintList* current = result;
    while (current) {
        PrintList* next = current->next();
        current->setNext(prev);
        prev = current;
        current = next;
    }
    return prev;
}

static WhenList* convert_when_list(const struct when_list* old_list) {
    if (!old_list) return nullptr;
    
    WhenList* result = nullptr;
    for (const struct when_list* cur = old_list; cur; cur = cur->next) {
        auto* node = new WhenList(
            cur->op,
            convert_expression(cur->exp),
            result
        );
        result = node;
    }
    // Reverse
    WhenList* prev = nullptr;
    WhenList* current = result;
    while (current) {
        WhenList* next = current->next();
        current->setNext(prev);
        prev = current;
        current = next;
    }
    return prev;
}

static AssignList* convert_assign_list(const struct assign_list* old_list) {
    if (!old_list) return nullptr;
    
    AssignList* result = nullptr;
    for (const struct assign_list* cur = old_list; cur; cur = cur->next) {
        auto* node = new AssignList(
            cur->op,
            convert_expression(cur->lval),
            convert_expression(cur->exp),
            result
        );
        result = node;
    }
    // Reverse
    AssignList* prev = nullptr;
    AssignList* current = result;
    while (current) {
        AssignList* next = current->next();
        current->setNext(prev);
        prev = current;
        current = next;
    }
    return prev;
}

// ============================================================================
// Statement-specific conversion helpers
// ============================================================================

static TwoExp convert_two_exp(const struct two_exp& old_te) {
    return TwoExp{
        convert_expression(old_te.exp1),
        convert_expression(old_te.exp2)
    };
}

static TwoNum convert_two_num(const struct two_num& old_tn) {
    return TwoNum{old_tn.num1, old_tn.num2};
}

static ForRec convert_for_rec(const struct for_rec& old_fr) {
    ForRec fr;
    fr.lval = convert_expression(old_fr.lval);
    fr.from = convert_expression(old_fr.from);
    fr.mode = old_fr.mode;
    fr.to   = convert_expression(old_fr.to);
    fr.step = convert_expression(old_fr.step);
    // Recursively convert the short-form body (e.g. FOR x:=1 TO 4 DO PRINT x)
    fr.stat = old_fr.stat ? convert_comal_line(old_fr.stat) : nullptr;
    return fr;
}

static IfWhileRec convert_ifwhile_rec(const struct ifwhile_rec& old_iw) {
    IfWhileRec iw;
    iw.exp = convert_expression(old_iw.exp);
    // Recursively convert the short-form body (e.g. IF x THEN STOP)
    iw.stat = old_iw.stat ? convert_comal_line(old_iw.stat) : nullptr;
    return iw;
}

static PrintModifier* convert_print_modifier(const struct print_modifier* old_mod) {
    if (!old_mod) return nullptr;
    
    auto* mod = new PrintModifier();
    mod->type = old_mod->type;
    if (old_mod->type == usingSYM) {
        mod->data = convert_expression(old_mod->data.str);
    } else if (old_mod->type == fileSYM) {
        mod->data = convert_two_exp(old_mod->data.twoexp);
    }
    return mod;
}

static PrintRec convert_print_rec(const struct print_rec& old_pr) {
    PrintRec pr;
    pr.modifier  = convert_print_modifier(old_pr.modifier);
    pr.printroot = convert_print_list(old_pr.printroot);
    pr.pr_sep    = old_pr.pr_sep;
    return pr;
}

static InputModifier* convert_input_modifier(const struct input_modifier* old_mod) {
    if (!old_mod) return nullptr;
    
    auto* mod = new InputModifier();
    mod->type = old_mod->type;
    if (old_mod->type == fileSYM) {
        mod->data = convert_two_exp(old_mod->data.twoexp);
    } else if (old_mod->type == stringSYM) {
        mod->data = old_mod->data.str;  // borrowed pointer
    }
    return mod;
}

static InputRec convert_input_rec(const struct input_rec& old_ir) {
    InputRec ir;
    ir.modifier = convert_input_modifier(old_ir.modifier);
    ir.lvalroot = convert_exp_list(old_ir.lvalroot);
    return ir;
}

static OpenRec convert_open_rec(const struct open_rec& old_or) {
    OpenRec orec;
    orec.filenum   = convert_expression(old_or.filenum);
    orec.filename  = convert_expression(old_or.filename);
    orec.type      = old_or.type;
    orec.reclen    = convert_expression(old_or.reclen);
    orec.read_only = old_or.read_only;
    return orec;
}

static ReadRec convert_read_rec(const struct read_rec& old_rr) {
    ReadRec rr;
    if (old_rr.modifier) {
        rr.modifier = new TwoExp{
            convert_expression(old_rr.modifier->exp1),
            convert_expression(old_rr.modifier->exp2)
        };
    } else {
        rr.modifier = nullptr;
    }
    rr.lvalroot = convert_exp_list(old_rr.lvalroot);
    return rr;
}

static WriteRec convert_write_rec(const struct write_rec& old_wr) {
    WriteRec wr;
    wr.twoexp  = convert_two_exp(old_wr.twoexp);
    wr.exproot = convert_exp_list(old_wr.exproot);
    return wr;
}

static ExtRec* convert_ext_rec(const struct ext_rec* old_er) {
    if (!old_er) return nullptr;
    
    auto* er = new ExtRec();
    er->dynamic  = old_er->dynamic;
    er->filename = convert_expression(old_er->filename);
    er->seg      = old_er->seg;  // borrowed
    return er;
}

static ProcFuncRec convert_pf_rec(const struct proc_func_rec& old_pf) {
    ProcFuncRec pf;
    pf.id        = old_pf.id;       // borrowed
    pf.closed    = old_pf.closed;
    pf.external  = convert_ext_rec(old_pf.external);
    pf.parmroot  = convert_parm_list(old_pf.parmroot);
    pf.level     = old_pf.level;
    pf.proclink  = nullptr;  // linked later
    pf.localproc = nullptr;
    pf.fatherproc = nullptr;
    pf.seg       = old_pf.seg;  // borrowed
    return pf;
}

static ImportRec convert_import_rec(const struct import_rec& old_ir) {
    ImportRec ir;
    ir.id         = old_ir.id;  // borrowed
    ir.importroot = convert_import_list(old_ir.importroot);
    return ir;
}

static TrapRec convert_trap_rec(const struct trap_rec& old_tr) {
    return TrapRec{old_tr.esc};
}

static ListCmd convert_list_cmd(const struct list_cmd& old_lc) {
    ListCmd lc;
    lc.str    = old_lc.str;  // borrowed
    lc.twonum = convert_two_num(old_lc.twonum);
    lc.id     = old_lc.id;   // borrowed
    return lc;
}

// ============================================================================
// map_cmd: legacy int cmd -> modern StatementType
// ============================================================================

static StatementType map_cmd(int cmd) {
    // Handle COMMAND(x) macro: interactive commands use (32767 - x)
    if (cmd == COMMAND(runSYM))   return StatementType::Run;
    if (cmd == COMMAND(delSYM))   return StatementType::Del;

    switch (cmd) {
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
        case returnSYM:        return StatementType::Return;
        case stopSYM:          return StatementType::Stop;
        case endSYM:           return StatementType::End;
        case exitSYM:          return StatementType::Exit;
        case nullSYM:          return StatementType::Null;
        case runSYM:           return StatementType::Run;
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
        case listSYM:          return StatementType::List;
        case saveSYM:          return StatementType::Save;
        case loadSYM:          return StatementType::Load;
        case enterSYM:         return StatementType::Enter;
        case newSYM:           return StatementType::New;
        case scanSYM:          return StatementType::Scan;
        case autoSYM:          return StatementType::Auto;
        case contSYM:          return StatementType::Cont;
        case editSYM:          return StatementType::Edit;
        case renumberSYM:      return StatementType::Renumber;
        case envSYM:           return StatementType::Env;
        case quitSYM:          return StatementType::Quit;
        case sysSYM:           return StatementType::Os;  // SYS — not impl, map to Os
        case traceSYM:         return StatementType::Trace;
        default:               return StatementType::Empty;
    }
}

// ============================================================================
// convert_comal_line: the main entry point for Phase 3
// ============================================================================

ComalLine* convert_comal_line(const struct comal_line* old_line) {
    if (!old_line) return nullptr;
    
    StatementType cmd = map_cmd(old_line->cmd);
    
    // Convert line metadata
    ComalLineData* ld = nullptr;
    if (old_line->ld) {
        ld = new ComalLineData(
            old_line->ld->lineno,
            old_line->ld->indent,
            old_line->ld->rem
        );
    }
    
    // Build the Contents variant based on the legacy cmd value
    ComalLine::Contents contents;
    
    switch (old_line->cmd) {
        // ---- No-data statements (monostate) ----
        case 0:  // empty
        case quitSYM:
        case newSYM:
        case scanSYM:
        case contSYM:
        case elseSYM:
        case endcaseSYM:
        case endfuncSYM:
        case endifSYM:
        case endloopSYM:
        case endprocSYM:
        case endwhileSYM:
        case endforSYM:
        case loopSYM:
        case handlerSYM:
        case endtrapSYM:
        case nullSYM:
        case endSYM:
        case pageSYM:
        case retrySYM:
        case otherwiseSYM:
            contents = std::monostate{};
            break;

        // ---- String data (lc.str) ----
        case saveSYM:
        case loadSYM:
        case enterSYM:
            contents = old_line->lc.str;
            break;

        // ---- ID data (lc.id) ----
        case envSYM:
        case restoreSYM:
        case idSYM:  // label
            contents = old_line->lc.id;
            break;

        // ---- TwoNum data (lc.twonum) ----
        case autoSYM:
        case editSYM:
        case renumberSYM:
            contents = convert_two_num(old_line->lc.twonum);
            break;

        // ---- TwoExp data (lc.twoexp) ----
        case cursorSYM:
            contents = convert_two_exp(old_line->lc.twoexp);
            break;

        // ---- LIST command (lc.listrec) ----
        case listSYM:
            contents = convert_list_cmd(old_line->lc.listrec);
            break;

        // ---- Single expression (lc.exp) ----
        case caseSYM:
        case execSYM:
        case delSYM:
        case chdirSYM:
        case rmdirSYM:
        case mkdirSYM:
        case dirSYM:
        case unitSYM:
        case osSYM:
        case elifSYM:
        case exitSYM:
        case returnSYM:
        case runSYM:
        case select_outputSYM:
        case select_inputSYM:
        case stopSYM:
        case untilSYM:
        case traceSYM:
            contents = convert_expression(old_line->lc.exp);
            break;

        // ---- Expression list (lc.exproot) ----
        case closeSYM:
        case dataSYM:
        case drawSYM:
        case toneSYM:
        case playSYM:
        case sleepSYM:
        case sysSYM:
            contents = convert_exp_list(old_line->lc.exproot);
            break;

        // ---- DIM list (lc.dimroot) ----
        case dimSYM:
        case localSYM:
            contents = convert_dim_list(old_line->lc.dimroot);
            break;

        // ---- FOR record (lc.forrec) ----
        case forSYM:
            contents = convert_for_rec(old_line->lc.forrec);
            break;

        // ---- IF/WHILE/REPEAT record (lc.ifwhilerec) ----
        case ifSYM:
        case whileSYM:
        case repeatSYM:
            contents = convert_ifwhile_rec(old_line->lc.ifwhilerec);
            break;

        // ---- IMPORT record (lc.importrec) ----
        case importSYM:
            contents = convert_import_rec(old_line->lc.importrec);
            break;

        // ---- INPUT record (lc.inputrec) ----
        case inputSYM:
            contents = convert_input_rec(old_line->lc.inputrec);
            break;

        // ---- OPEN record (lc.openrec) ----
        case openSYM:
            contents = convert_open_rec(old_line->lc.openrec);
            break;

        // ---- PRINT record (lc.printrec) ----
        case printSYM:
            contents = convert_print_rec(old_line->lc.printrec);
            break;

        // ---- PROC/FUNC record (lc.pfrec) ----
        case procSYM:
        case funcSYM:
            contents = convert_pf_rec(old_line->lc.pfrec);
            break;

        // ---- TRAP record (lc.traprec) ----
        case trapSYM:
            contents = convert_trap_rec(old_line->lc.traprec);
            break;

        // ---- READ record (lc.readrec) ----
        case readSYM:
            contents = convert_read_rec(old_line->lc.readrec);
            break;

        // ---- WHEN list (lc.whenroot) ----
        case whenSYM:
            contents = convert_when_list(old_line->lc.whenroot);
            break;

        // ---- WRITE record (lc.writerec) ----
        case writeSYM:
            contents = convert_write_rec(old_line->lc.writerec);
            break;

        // ---- Assignment list (lc.assignroot) ----
        case becomesSYM:
            contents = convert_assign_list(old_line->lc.assignroot);
            break;

        // ---- COMMAND() variants (interactive) ----
        default:
            if (old_line->cmd == COMMAND(runSYM)) {
                contents = old_line->lc.str;
            } else if (old_line->cmd == COMMAND(delSYM)) {
                contents = convert_two_num(old_line->lc.twonum);
            } else {
                contents = std::monostate{};
            }
            break;
    }
    
    auto* line = new ComalLine(ld, cmd, std::move(contents));
    line->setLinePtr(nullptr);  // linked later
    return line;
}

// ============================================================================
// Utility Functions
// ============================================================================

ExpList* reverse_exp_list(ExpList* list) {
    ExpList* prev = nullptr;
    ExpList* current = list;
    
    while (current != nullptr) {
        ExpList* next = current->next();
        current->setNext(prev);
        prev = current;
        current = next;
    }
    
    return prev;
}

} // namespace comal
