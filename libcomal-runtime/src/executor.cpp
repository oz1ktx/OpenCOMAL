/// @file executor.cpp
/// Statement executor — walks ComalLine linked list and dispatches
/// each statement type.  Replaces legacy exec_seq/exec_line.

#include "comal_executor.h"
#include "comal_evaluator.h"
#include "comal_interpreter.h"
#include "comal_ast.h"           // full definitions: id_rec, string, VAL_TYPE, etc.
#include "comal_ast_modern.h"
#include "comal_functions.h"
#include "comal_parser_api.h"    // statement_type_name()
#include "parser.tab.h"          // token constants

#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <filesystem>

namespace comal::runtime {

// ── Forward declarations of exec helpers ────────────────────────────────

static void execPrint(Interpreter& interp, ComalLine* line);
static void execInput(Interpreter& interp, ComalLine* line);
static void execAssign(Interpreter& interp, ComalLine* line);
static void execFor(Interpreter& interp, ComalLine* line);
static void execWhile(Interpreter& interp, ComalLine* line);
static void execRepeat(Interpreter& interp, ComalLine* line);
static void execLoop(Interpreter& interp, ComalLine* line);
static void execIf(Interpreter& interp, ComalLine* line);
static void execCase(Interpreter& interp, ComalLine* line);
static void execDim(Interpreter& interp, ComalLine* line);
static void execOpen(Interpreter& interp, ComalLine* line);
static void execClose(Interpreter& interp, ComalLine* line);
static void execRead(Interpreter& interp, ComalLine* line);
static void execWrite(Interpreter& interp, ComalLine* line);
static void execTrap(Interpreter& interp, ComalLine* line);
static void execImport(Interpreter& interp, ComalLine* line);
static void execCall(Interpreter& interp, const std::string& name,
                     const ExpList* args, bool isFunc);
static void execRestore(Interpreter& interp, ComalLine* line);

// Lvalue assignment helpers
static void assignToLval(Interpreter& interp, const Expression* lval,
                         const Value& val, int op);
static Value& resolveLval(Interpreter& interp, const Expression* lval);

// ── execSeq — main execution loop ──────────────────────────────────────

void execSeq(Interpreter& interp, ComalLine* start) {
    interp.curline = start;

    while (interp.curline) {
        ComalLine* line = interp.curline;

        // Trace mode
        if (interp.trace && line->lineNumber() > 0) {
            interp.print("[" + std::to_string(line->lineNumber()) + "] ");
        }

        // Advance to next line before executing (some stmts change curline)
        interp.curline = line->next();

        execLine(interp, line);
    }
}

// ── execLine — dispatch one statement ───────────────────────────────────

void execLine(Interpreter& interp, ComalLine* line) {
    switch (line->command()) {

    // ── No-ops ──────────────────────────────────────────────────────────
    case StatementType::Empty:
    case StatementType::Null:
    case StatementType::Data:       // DATA is consumed by READ at runtime
    case StatementType::EndCase:
    case StatementType::EndIf:
    case StatementType::Label:
        break;


    // ── PRINT ───────────────────────────────────────────────────────────
    case StatementType::Print:
        execPrint(interp, line);
        break;

    // ── INPUT ───────────────────────────────────────────────────────────
    case StatementType::Input:
        execInput(interp, line);
        break;

    // ── Assignment (:=, :+, :-) ─────────────────────────────────────────
    case StatementType::Assign:
        execAssign(interp, line);
        break;

    // ── Control flow ────────────────────────────────────────────────────
    case StatementType::For:
        execFor(interp, line);
        break;

    case StatementType::While:
        execWhile(interp, line);
        break;

    case StatementType::Repeat:
        execRepeat(interp, line);
        break;

    case StatementType::Loop:
        execLoop(interp, line);
        break;

    case StatementType::If:
        execIf(interp, line);
        break;

    case StatementType::Case:
        execCase(interp, line);
        break;

    // ── Skip-over for ELSE/ELIF/ENDWHILE/OTHERWISE ──────────────────────
    case StatementType::Else:
    case StatementType::EndWhile:
    case StatementType::Otherwise:
        // lineptr points to the end of the block — skip to it
        if (line->linePtr())
            interp.curline = line->linePtr()->next();
        break;

    case StatementType::Elif:
        // If we fall through to ELIF, skip to ENDIF
        if (line->linePtr())
            interp.curline = line->linePtr()->next();
        break;

    case StatementType::EndLoop:
        // Sentinel: shouldn't reach here except via LOOP body
        break;

    case StatementType::Until: {
        // Evaluate condition; if false, jump back to REPEAT
        // UNTIL stores Expression* (not IfWhileRec)
        auto* exp = std::get_if<Expression*>(&line->contents());
        Value cond = evaluate(interp, exp ? *exp : nullptr);
        if (cond.toInt() == 0 && line->linePtr())
            interp.curline = line->linePtr()->next();  // back to first line after REPEAT
        break;
    }

    // ── DIM / LOCAL ─────────────────────────────────────────────────────
    case StatementType::Dim:
    case StatementType::Local:
        execDim(interp, line);
        break;

    // ── PROC/FUNC definitions — skip over body at runtime ───────────────
    case StatementType::Proc:
    case StatementType::Func:
        // Jump past the ENDPROC/ENDFUNC
        if (line->linePtr())
            interp.curline = line->linePtr()->next();
        break;

    case StatementType::EndProc:
    case StatementType::EndFunc:
        // End of a procedure/function body — signal return
        throw ReturnSignal{};

    case StatementType::Return: {
        // RETURN [expr] — evaluate the expression and stash the result
        if (auto* expr = std::get_if<Expression*>(&line->contents())) {
            if (*expr)
                interp.returnValue = evaluate(interp, *expr);
        }
        throw ReturnSignal{};
    }

    // ── EXEC (call a PROC) ──────────────────────────────────────────────
    case StatementType::Exec: {
        auto* expr = std::get_if<Expression*>(&line->contents());
        if (!expr || !*expr)
            throw ComalError(ErrorCode::Parm, "EXEC requires an expression");
        // The expression should be an Id pointing to the procedure
        const auto& eid = std::get<ExpId>((*expr)->data());
        execCall(interp, eid.id->name, eid.exproot, false);
        break;
    }

    // ── File I/O ────────────────────────────────────────────────────────
    case StatementType::Open:
        execOpen(interp, line);
        break;

    case StatementType::Close:
        execClose(interp, line);
        break;

    case StatementType::Read:
        execRead(interp, line);
        break;

    case StatementType::Write:
        execWrite(interp, line);
        break;

    // ── DATA/RESTORE ────────────────────────────────────────────────────
    case StatementType::Restore:
        execRestore(interp, line);
        break;

    // ── TRAP/HANDLER ────────────────────────────────────────────────────
    case StatementType::Trap:
        execTrap(interp, line);
        break;

    case StatementType::Handler:
        // If we fall through to HANDLER, skip to ENDTRAP
        if (line->linePtr())
            interp.curline = line->linePtr()->next();
        break;

    case StatementType::EndTrap:
        break;

    // ── IMPORT ──────────────────────────────────────────────────────────
    case StatementType::Import:
        execImport(interp, line);
        break;

    // ── EXIT (from LOOP) ────────────────────────────────────────────────
    case StatementType::Exit: {
        // EXIT [WHEN condition]
        if (auto* iw = std::get_if<IfWhileRec>(&line->contents())) {
            if (iw->exp) {
                Value cond = evaluate(interp, iw->exp);
                if (cond.toInt() == 0)
                    break;  // condition false, don't exit
            }
        }
        throw ExitSignal{};
    }

    // ── STOP / END ──────────────────────────────────────────────────────
    case StatementType::Stop:
        throw StopSignal{};

    case StatementType::End:
        throw EndSignal{};

    // ── PAGE (clear screen) ─────────────────────────────────────────────
    case StatementType::Page:
        interp.print("\033[2J\033[H");  // ANSI clear
        break;

    // ── CURSOR row, col ─────────────────────────────────────────────────
    case StatementType::Cursor: {
        const auto& te = line->asTwoExp();
        int64_t row = evalInt(interp, te.exp1);
        int64_t col = evalInt(interp, te.exp2);
        interp.print("\033[" + std::to_string(row) + ";" +
                     std::to_string(col) + "H");
        break;
    }

    // ── Directory operations ────────────────────────────────────────────
    case StatementType::Chdir: {
        auto* str = std::get_if<Expression*>(&line->contents());
        if (str && *str) {
            std::string dir = evalString(interp, *str);
            if (chdir(dir.c_str()) != 0)
                throw ComalError(ErrorCode::DirErr,
                    "CHDIR \"" + dir + "\" failed");
        }
        break;
    }

    case StatementType::Mkdir: {
        auto* str = std::get_if<Expression*>(&line->contents());
        if (str && *str) {
            std::string dir = evalString(interp, *str);
            std::filesystem::create_directory(dir);
        }
        break;
    }

    case StatementType::Rmdir: {
        auto* str = std::get_if<Expression*>(&line->contents());
        if (str && *str) {
            std::string dir = evalString(interp, *str);
            std::filesystem::remove(dir);
        }
        break;
    }

    case StatementType::Os: {
        auto* str = std::get_if<string*>(&line->contents());
        if (str && *str) {
            std::string cmd((*str)->s, (*str)->len);
            std::system(cmd.c_str());
        }
        break;
    }

    case StatementType::Del: {
        auto* expr = std::get_if<Expression*>(&line->contents());
        if (expr && *expr) {
            std::string fname = evalString(interp, *expr);
            std::filesystem::remove(fname);
        }
        break;
    }

    // ── SELECT OUTPUT / INPUT ───────────────────────────────────────────
    case StatementType::Select_Output: {
        const auto& te = line->asTwoExp();
        interp.selOutput = evalInt(interp, te.exp1);
        break;
    }

    case StatementType::Select_Input: {
        const auto& te = line->asTwoExp();
        interp.selInput = evalInt(interp, te.exp1);
        break;
    }

    // ── RETRY (in HANDLER) ──────────────────────────────────────────────
    case StatementType::Retry:
        throw RetrySignal{};

    // ── When/EndFor/EndLoop sentinels ───────────────────────────────────
    case StatementType::When:
        // If we hit WHEN during sequential execution, skip to ENDCASE
        if (line->linePtr())
            interp.curline = line->linePtr()->next();
        break;

    case StatementType::EndFor:
        // Should not be reached by sequential execution in well-structured code
        break;

    // ── Stubs for interactive-only commands ─────────────────────────────
    case StatementType::List:
    case StatementType::Save:
    case StatementType::Load:
    case StatementType::Enter:
    case StatementType::New:
    case StatementType::Scan:
    case StatementType::Auto:
    case StatementType::Cont:
    case StatementType::Edit:
    case StatementType::Renumber:
    case StatementType::Env:
    case StatementType::Quit:
    case StatementType::Run:
    case StatementType::Dir:
    case StatementType::Unit:
        // Not applicable in batch mode — ignore or warn
        break;

    default:
        throw ComalError(ErrorCode::NotImpl,
            "Statement type " + std::to_string(static_cast<int>(line->command())) +
            " not implemented");
    }
}

// ── PRINT ───────────────────────────────────────────────────────────────

static void execPrint(Interpreter& interp, ComalLine* line) {
    const auto& pr = line->asPrint();

    // TODO: handle FILE modifier (PRINT FILE#...)
    // TODO: handle USING modifier

    for (auto* node = pr.printroot; node; node = node->next()) {
        if (node->exp()) {
            Value v = evaluate(interp, node->exp());
            interp.print(v.printStr());
        }

        // Separators: comma = tab, semicolon = nothing
        int sep = node->separator();
        if (sep == commaSYM) {
            interp.print("\t");
        }
        // semicolonSYM = no space
    }

    // Trailing separator: if none, print newline
    if (pr.pr_sep == 0) {
        interp.newline();
    }
    // semicolonSYM trailing = no newline
    // commaSYM trailing = tab but no newline
    else if (pr.pr_sep == commaSYM) {
        interp.print("\t");
    }
}

// ── INPUT ───────────────────────────────────────────────────────────────

static void execInput(Interpreter& interp, ComalLine* line) {
    const auto& inp = line->asInput();

    std::string prompt = "? ";

    // Handle AT modifier (prompt string)
    if (inp.modifier) {
        if (auto* s = std::get_if<string*>(&inp.modifier->data)) {
            if (*s) prompt = std::string((*s)->s, (*s)->len);
        }
    }

    // Read values for each lvalue
    for (auto* node = inp.lvalroot; node; node = node->next()) {
        std::string input_str = interp.readLine(prompt);

        // Try to parse as number first, then use as string
        Value val;
        const Expression* lval = node->exp();

        // Determine target type from the lvalue
        bool is_string = false;
        if (lval->opType() == OpType::Sid ||
            lval->opType() == OpType::Sarray)
            is_string = true;
        else if (lval->opType() == OpType::Id) {
            const auto& eid = std::get<ExpId>(lval->data());
            if (eid.id && eid.id->type == V_STRING)
                is_string = true;
        }

        if (is_string) {
            val = Value(std::move(input_str));
        } else {
            // Try integer, then float
            try {
                size_t pos;
                long long ll = std::stoll(input_str, &pos);
                if (pos == input_str.size()) {
                    val = Value(static_cast<int64_t>(ll));
                } else {
                    double d = std::stod(input_str, &pos);
                    val = Value(d);
                }
            } catch (...) {
                throw ComalError(ErrorCode::Input,
                    "Cannot parse '" + input_str + "' as a number");
            }
        }

        assignToLval(interp, lval, val, becomesSYM);
        prompt = "? ";  // subsequent prompts
    }
}

// ── Assignment ──────────────────────────────────────────────────────────

static void execAssign(Interpreter& interp, ComalLine* line) {
    auto* list = line->asAssignList();
    for (auto* node = list; node; node = node->next()) {
        Value rhs = evaluate(interp, node->exp());
        assignToLval(interp, node->lval(), rhs, node->op());
    }
}

// ── Lvalue resolution ───────────────────────────────────────────────────

static std::string lvalName(const Expression* lval) {
    switch (lval->opType()) {
    case OpType::Id: {
        const auto& eid = std::get<ExpId>(lval->data());
        return eid.id ? eid.id->name : "";
    }
    case OpType::Sid: {
        const auto& esid = std::get<ExpSid>(lval->data());
        return esid.id ? esid.id->name : "";
    }
    case OpType::Array:
    case OpType::Sarray: {
        // Array element — same layout as ExpId
        const auto& eid = std::get<ExpId>(lval->data());
        return eid.id ? eid.id->name : "";
    }
    default:
        throw ComalError(ErrorCode::Lval, "Expression is not an lvalue");
    }
}

static Value& resolveLval(Interpreter& interp, const Expression* lval) {
    std::string name = lvalName(lval);

    Symbol* sym = interp.scopes.current().find(name);
    if (!sym) {
        // Auto-create
        Value init;
        switch (lval->opType()) {
        case OpType::Sid:
        case OpType::Sarray:
            init = Value(std::string{});
            break;
        default:
            init = Value(int64_t{0});
            break;
        }
        sym = &interp.scopes.current().define(name, std::move(init));
    }

    // Array element?
    if ((lval->opType() == OpType::Array || lval->opType() == OpType::Sarray) &&
        sym->resolve().isArray()) {
        const auto& eid = std::get<ExpId>(lval->data());
        if (eid.exproot) {
            std::vector<int64_t> idx;
            for (auto* node = eid.exproot; node; node = node->next())
                idx.push_back(evalInt(interp, node->exp()));
            auto& arr = sym->resolve().asArray();
            int64_t flat = arr.flatIndex(idx);
            return arr.elements[flat];
        }
    }

    // String variable with substring? (Sid with twoexp)
    // For substring assignment we need special handling — return the whole string
    return sym->resolve();
}

static void assignToLval(Interpreter& interp, const Expression* lval,
                         const Value& val, int op) {
    Value& target = resolveLval(interp, lval);

    switch (op) {
    case becomesSYM:
        target.assignFrom(val);
        break;
    case becplusSYM:
        if (target.isString() && val.isString())
            target = target + val;
        else
            target = target + val;
        break;
    case becminusSYM:
        target = target - val;
        break;
    default:
        target.assignFrom(val);
        break;
    }

    // Handle substring assignment for Sid
    if (lval->opType() == OpType::Sid) {
        const auto& esid = std::get<ExpSid>(lval->data());
        if (esid.twoexp && target.isString()) {
            // The target was already returned as the whole string
            // We need to do substring replacement
            std::string name = lvalName(lval);
            Symbol* sym = interp.scopes.current().find(name);
            if (sym) {
                std::string& s = sym->resolve().asString();
                int64_t from = 1, to = static_cast<int64_t>(s.size());
                if (esid.twoexp->exp1)
                    from = evalInt(interp, esid.twoexp->exp1);
                if (esid.twoexp->exp2)
                    to = evalInt(interp, esid.twoexp->exp2);
                if (from >= 1 && from <= static_cast<int64_t>(s.size()) + 1) {
                    s.replace(from - 1,
                              to - from + 1,
                              val.asString());
                }
            }
        }
    }
}

// ── FOR ─────────────────────────────────────────────────────────────────

static void execFor(Interpreter& interp, ComalLine* line) {
    const auto& fr = line->asFor();

    Value from_val = evaluate(interp, fr.from);
    Value to_val = evaluate(interp, fr.to);
    Value step_val = fr.step ? evaluate(interp, fr.step) : Value(int64_t{1});

    bool downto = (fr.mode == downtoSYM);

    // Compute the effective step direction:
    //   TO:     effective = +step
    //   DOWNTO: effective = -step  (we subtract step each iteration)
    double eff_step = downto ? -step_val.toDouble() : step_val.toDouble();

    // Helper: returns true when the loop variable has passed the target
    auto pastEnd = [&](double cur, double target) -> bool {
        if (eff_step > 0)
            return cur > target;
        else if (eff_step < 0)
            return cur < target;
        else
            return true; // step==0 → never execute
    };

    // Initialize loop variable
    assignToLval(interp, fr.lval, from_val, becomesSYM);

    // Short-form FOR x := a TO b DO stat
    if (fr.stat) {
        while (true) {
            Value cur = evaluate(interp, fr.lval);
            if (pastEnd(cur.toDouble(), to_val.toDouble())) break;
            execLine(interp, fr.stat);
            // DOWNTO subtracts the step; TO adds it
            Value next_val = downto ? (cur - step_val) : (cur + step_val);
            assignToLval(interp, fr.lval, next_val, becomesSYM);
        }
        return;
    }

    // Block FOR — body is lines from next to ENDFOR
    ComalLine* endfor = line->linePtr();  // lineptr points to ENDFOR
    if (!endfor) throw ComalError(ErrorCode::For, "FOR without ENDFOR");

    while (true) {
        Value cur = evaluate(interp, fr.lval);
        if (pastEnd(cur.toDouble(), to_val.toDouble())) break;

        // Execute body
        try {
            ComalLine* saved = interp.curline;
            interp.curline = line->next();
            while (interp.curline && interp.curline != endfor) {
                ComalLine* cur_line = interp.curline;
                interp.curline = cur_line->next();
                execLine(interp, cur_line);
            }
            interp.curline = saved;
        } catch (ExitSignal&) {
            interp.curline = endfor->next();
            return;
        }

        // Increment (DOWNTO subtracts, TO adds)
        Value next_val = downto
            ? (evaluate(interp, fr.lval) - step_val)
            : (evaluate(interp, fr.lval) + step_val);
        assignToLval(interp, fr.lval, next_val, becomesSYM);
    }

    // Skip past ENDFOR
    interp.curline = endfor->next();
}

// ── WHILE ───────────────────────────────────────────────────────────────

static void execWhile(Interpreter& interp, ComalLine* line) {
    const auto& iw = line->asIfWhile();

    // Short-form: WHILE cond DO stat
    if (iw.stat) {
        while (true) {
            Value cond = evaluate(interp, iw.exp);
            if (cond.toInt() == 0) break;
            execLine(interp, iw.stat);
        }
        return;
    }

    // Block WHILE — lineptr points to ENDWHILE
    ComalLine* endwhile = line->linePtr();
    if (!endwhile) throw ComalError(ErrorCode::Scan, "WHILE without ENDWHILE");

    while (true) {
        Value cond = evaluate(interp, iw.exp);
        if (cond.toInt() == 0) break;

        try {
            ComalLine* saved = interp.curline;
            interp.curline = line->next();
            while (interp.curline && interp.curline != endwhile) {
                ComalLine* cur_line = interp.curline;
                interp.curline = cur_line->next();
                execLine(interp, cur_line);
            }
            interp.curline = saved;
        } catch (ExitSignal&) {
            break;
        }
    }

    interp.curline = endwhile->next();
}

// ── REPEAT..UNTIL ───────────────────────────────────────────────────────

static void execRepeat(Interpreter& interp, ComalLine* line) {
    // Short-form: REPEAT stat UNTIL cond (on one line)
    const auto* iw = std::get_if<IfWhileRec>(&line->contents());
    if (iw && iw->stat) {
        do {
            execLine(interp, iw->stat);
        } while (iw->exp && evaluate(interp, iw->exp).toInt() == 0);
        return;
    }

    // Block REPEAT — lineptr points to UNTIL
    ComalLine* until_line = line->linePtr();
    if (!until_line) throw ComalError(ErrorCode::Scan, "REPEAT without UNTIL");

    while (true) {
        try {
            ComalLine* saved = interp.curline;
            interp.curline = line->next();
            while (interp.curline && interp.curline != until_line) {
                ComalLine* cur_line = interp.curline;
                interp.curline = cur_line->next();
                execLine(interp, cur_line);
            }
            interp.curline = saved;
        } catch (ExitSignal&) {
            interp.curline = until_line->next();
            return;
        }

        // Evaluate UNTIL condition (UNTIL stores Expression*, not IfWhileRec)
        auto* until_exp = std::get_if<Expression*>(&until_line->contents());
        Value cond = evaluate(interp, until_exp ? *until_exp : nullptr);
        if (cond.toInt() != 0) break;  // condition true → exit loop
    }

    interp.curline = until_line->next();
}

// ── LOOP..ENDLOOP ───────────────────────────────────────────────────────

static void execLoop(Interpreter& interp, ComalLine* line) {
    ComalLine* endloop = line->linePtr();
    if (!endloop) throw ComalError(ErrorCode::Scan, "LOOP without ENDLOOP");

    while (true) {
        try {
            ComalLine* saved = interp.curline;
            interp.curline = line->next();
            while (interp.curline && interp.curline != endloop) {
                ComalLine* cur_line = interp.curline;
                interp.curline = cur_line->next();
                execLine(interp, cur_line);
            }
            interp.curline = saved;
        } catch (ExitSignal&) {
            break;
        }
    }

    interp.curline = endloop->next();
}

// ── IF..ELIF..ELSE..ENDIF ───────────────────────────────────────────────

static void execIf(Interpreter& interp, ComalLine* line) {
    const auto& iw = line->asIfWhile();

    // Short-form: IF cond THEN stat
    if (iw.stat) {
        Value cond = evaluate(interp, iw.exp);
        if (cond.toInt() != 0)
            execLine(interp, iw.stat);
        return;
    }

    // Block IF — evaluate condition
    Value cond = evaluate(interp, iw.exp);
    if (cond.toInt() != 0) {
        // Execute true branch (lines until ELIF/ELSE/ENDIF)
        // The lineptr on IF points to the first ELIF (or ELSE, or ENDIF)
        ComalLine* branch_end = line->linePtr();
        ComalLine* saved = interp.curline;
        interp.curline = line->next();
        while (interp.curline && interp.curline != branch_end) {
            ComalLine* cur_line = interp.curline;
            interp.curline = cur_line->next();
            execLine(interp, cur_line);
        }
        // Now skip to ENDIF
        // branch_end could be ELIF, ELSE, or ENDIF
        // Walk forward to ENDIF
        ComalLine* scan = branch_end;
        while (scan && scan->command() != StatementType::EndIf) {
            if (scan->linePtr())
                scan = scan->linePtr();
            else
                scan = scan->next();
        }
        interp.curline = scan ? scan->next() : saved;
        return;
    }

    // Condition was false — walk ELIF/ELSE chain
    ComalLine* branch = line->linePtr();
    while (branch) {
        if (branch->command() == StatementType::Elif) {
            // ELIF stores Expression* (not IfWhileRec)
            auto* elif_exp = std::get_if<Expression*>(&branch->contents());
            Value elif_cond = evaluate(interp, elif_exp ? *elif_exp : nullptr);
            if (elif_cond.toInt() != 0) {
                // Execute this ELIF branch
                ComalLine* elif_end = branch->linePtr();
                interp.curline = branch->next();
                while (interp.curline && interp.curline != elif_end) {
                    ComalLine* cur_line = interp.curline;
                    interp.curline = cur_line->next();
                    execLine(interp, cur_line);
                }
                // Skip to ENDIF
                ComalLine* scan = elif_end;
                while (scan && scan->command() != StatementType::EndIf) {
                    if (scan->linePtr())
                        scan = scan->linePtr();
                    else
                        scan = scan->next();
                }
                interp.curline = scan ? scan->next() : nullptr;
                return;
            }
            branch = branch->linePtr();
        } else if (branch->command() == StatementType::Else) {
            // Execute ELSE branch (until ENDIF via lineptr)
            ComalLine* endif_line = branch->linePtr();
            interp.curline = branch->next();
            while (interp.curline && interp.curline != endif_line) {
                ComalLine* cur_line = interp.curline;
                interp.curline = cur_line->next();
                execLine(interp, cur_line);
            }
            interp.curline = endif_line ? endif_line->next() : nullptr;
            return;
        } else if (branch->command() == StatementType::EndIf) {
            interp.curline = branch->next();
            return;
        } else {
            break;
        }
    }
}

// ── CASE..WHEN..OTHERWISE..ENDCASE ──────────────────────────────────────

static void execCase(Interpreter& interp, ComalLine* line) {
    // CASE expr OF
    auto* expr = std::get_if<Expression*>(&line->contents());
    if (!expr || !*expr)
        throw ComalError(ErrorCode::Scan, "CASE without expression");

    Value selector = evaluate(interp, *expr);

    // Walk WHEN branches
    ComalLine* when = line->next();
    while (when) {
        if (when->command() == StatementType::When) {
            // Check if selector matches any value in the WHEN list
            WhenList* wl = when->asWhenList();
            bool matched = false;
            for (auto* w = wl; w; w = w->next()) {
                Value when_val = evaluate(interp, w->exp());
                int op = w->op();
                // op is the comparison operator (0 = equality, or relational)
                if (op == 0 || op == eqlSYM) {
                    if (selector == when_val) { matched = true; break; }
                } else if (op == lssSYM) {
                    if (selector < when_val) { matched = true; break; }
                } else if (op == leqSYM) {
                    if (selector <= when_val) { matched = true; break; }
                } else if (op == gtrSYM) {
                    if (selector > when_val) { matched = true; break; }
                } else if (op == geqSYM) {
                    if (selector >= when_val) { matched = true; break; }
                } else if (op == neqSYM) {
                    if (selector != when_val) { matched = true; break; }
                }
            }

            if (matched) {
                // Execute this WHEN branch
                ComalLine* when_end = when->linePtr();
                interp.curline = when->next();
                while (interp.curline && interp.curline != when_end) {
                    ComalLine* cur_line = interp.curline;
                    interp.curline = cur_line->next();
                    execLine(interp, cur_line);
                }
                // Skip to ENDCASE
                ComalLine* scan = when_end;
                while (scan && scan->command() != StatementType::EndCase)
                    scan = scan->next();
                interp.curline = scan ? scan->next() : nullptr;
                return;
            }

            // Move to the next WHEN (via lineptr)
            when = when->linePtr();
        } else if (when->command() == StatementType::Otherwise) {
            // Execute OTHERWISE branch
            ComalLine* endcase = when->linePtr();
            interp.curline = when->next();
            while (interp.curline && interp.curline != endcase) {
                ComalLine* cur_line = interp.curline;
                interp.curline = cur_line->next();
                execLine(interp, cur_line);
            }
            interp.curline = endcase ? endcase->next() : nullptr;
            return;
        } else if (when->command() == StatementType::EndCase) {
            interp.curline = when->next();
            return;
        } else {
            when = when->next();
        }
    }
}

// ── DIM / LOCAL ─────────────────────────────────────────────────────────

static void execDim(Interpreter& interp, ComalLine* line) {
    auto* dimlist = line->asDimList();
    bool is_local = (line->command() == StatementType::Local);

    for (auto* d = dimlist; d; d = d->next()) {
        std::string name = d->id()->name;
        Scope& scope = is_local ? interp.scopes.current() : interp.scopes.global();

        // Check if already defined
        if (scope.findLocal(name))
            continue;  // Re-DIM: skip (or could error)

        if (!d->dimensions()) {
            // Simple variable
            Value init;
            if (d->id()->type == V_STRING) {
                init = Value(std::string{});
            } else if (d->id()->type == V_FLOAT) {
                init = Value(0.0);
            } else {
                init = Value(int64_t{0});
            }
            scope.define(name, std::move(init));
        } else {
            // Array
            ArrayData arr;
            int64_t total = 1;
            for (auto* dim = d->dimensions(); dim; dim = dim->next()) {
                int64_t bottom = dim->bottom()
                    ? evalInt(interp, dim->bottom())
                    : 1;  // DEFAULT_DIMBOTTOM
                int64_t top = evalInt(interp, dim->top());
                if (top < bottom)
                    throw ComalError(ErrorCode::Dim,
                        "DIM: top < bottom for '" + name + "'");
                arr.dims.push_back({bottom, top});
                total *= (top - bottom + 1);
            }

            // String length
            if (d->strlen()) {
                arr.string_len = evalInt(interp, d->strlen());
            }

            // Initialize elements
            Value elem_init;
            if (d->id()->type == V_STRING)
                elem_init = Value(std::string{});
            else if (d->id()->type == V_FLOAT)
                elem_init = Value(0.0);
            else
                elem_init = Value(int64_t{0});

            arr.elements.resize(total, elem_init);
            scope.define(name, Value(std::move(arr)));
        }
    }
}

// ── OPEN ────────────────────────────────────────────────────────────────

static void execOpen(Interpreter& interp, ComalLine* line) {
    const auto& op = line->asOpen();

    int64_t fno = evalInt(interp, op.filenum);
    std::string fname = evalString(interp, op.filename);

    FileMode mode;
    switch (op.type) {
    case readSYM:   mode = FileMode::Read; break;
    case writeSYM:  mode = FileMode::Write; break;
    case appendSYM: mode = FileMode::Append; break;
    case randomSYM: mode = FileMode::Random; break;
    default:        mode = FileMode::Read; break;
    }

    int64_t reclen = op.reclen ? evalInt(interp, op.reclen) : 0;
    interp.files.open(fno, fname, mode, reclen, op.read_only != 0);
}

// ── CLOSE ───────────────────────────────────────────────────────────────

static void execClose(Interpreter& interp, ComalLine* line) {
    int fno = line->asInt();
    interp.files.close(fno);
}

// ── READ (from DATA or file) ────────────────────────────────────────────

static void execRead(Interpreter& interp, ComalLine* line) {
    const auto& rr = line->asRead();

    if (rr.modifier) {
        // File READ
        int64_t fno = evalInt(interp, rr.modifier->exp1);
        for (auto* node = rr.lvalroot; node; node = node->next()) {
            // Determine expected type from the lvalue
            Value::Type expected = Value::Type::Int;
            const Expression* lval = node->exp();
            if (lval->opType() == OpType::Sid || lval->opType() == OpType::Sarray)
                expected = Value::Type::String;

            Value val = interp.files.readValue(fno, expected);
            assignToLval(interp, lval, val, becomesSYM);
        }
        return;
    }

    // DATA read
    for (auto* node = rr.lvalroot; node; node = node->next()) {
        if (!interp.dataExp)
            throw ComalError(ErrorCode::Eod, "End of DATA");

        Value val = evaluate(interp, interp.dataExp->exp());
        assignToLval(interp, node->exp(), val, becomesSYM);

        // Advance DATA pointer
        interp.dataExp = interp.dataExp->next();
        if (!interp.dataExp)
            interp.advanceData();
    }
}

// ── WRITE (to file) ─────────────────────────────────────────────────────

static void execWrite(Interpreter& interp, ComalLine* line) {
    const auto& wr = line->asWrite();

    int64_t fno = evalInt(interp, wr.twoexp.exp1);
    // Optional record position
    if (wr.twoexp.exp2) {
        int64_t pos = evalInt(interp, wr.twoexp.exp2);
        interp.files.seek(fno, pos);
    }

    for (auto* node = wr.exproot; node; node = node->next()) {
        Value val = evaluate(interp, node->exp());
        interp.files.writeValue(fno, val);
    }
}

// ── TRAP..HANDLER..ENDTRAP ──────────────────────────────────────────────

static void execTrap(Interpreter& interp, ComalLine* line) {
    ComalLine* handler = line->linePtr();  // HANDLER line
    if (!handler)
        throw ComalError(ErrorCode::Scan, "TRAP without HANDLER");
    ComalLine* endtrap = handler->linePtr();  // ENDTRAP line

    bool retry;
    do {
        retry = false;
        try {
            // Execute TRAP body
            interp.curline = line->next();
            while (interp.curline && interp.curline != handler) {
                ComalLine* cur_line = interp.curline;
                interp.curline = cur_line->next();
                execLine(interp, cur_line);
            }
        } catch (ComalError& e) {
            // Save error info
            interp.lastError = e.code();
            interp.lastErrorMsg = e.what();
            interp.lastErrorLine = e.line();

            // Execute HANDLER body
            try {
                interp.curline = handler->next();
                while (interp.curline && interp.curline != endtrap) {
                    ComalLine* cur_line = interp.curline;
                    interp.curline = cur_line->next();
                    execLine(interp, cur_line);
                }
            } catch (RetrySignal&) {
                retry = true;
            }
        }
    } while (retry);

    interp.curline = endtrap ? endtrap->next() : nullptr;
}

// ── IMPORT ──────────────────────────────────────────────────────────────

static void execImport(Interpreter& interp, ComalLine* line) {
    const auto& imp = line->asImport();
    Scope& cur = interp.scopes.current();

    for (auto* node = imp.importroot; node; node = node->next()) {
        std::string name = node->id()->name;
        cur.importSymbol(name);
    }
}

// ── RESTORE ─────────────────────────────────────────────────────────────

static void execRestore(Interpreter& interp, ComalLine* line) {
    (void)line;
    // RESTORE without argument: reset to first DATA line
    interp.initDataPointer();
}

// ── PROC/FUNC call ──────────────────────────────────────────────────────

static void execCall(Interpreter& interp, const std::string& name,
                     const ExpList* args, bool isFunc) {
    ComalLine* proc_line = interp.findRoutine(name);
    const auto& pf = proc_line->asProcFunc();

    // Create new scope
    Scope& scope = interp.scopes.push(
        name, pf.closed != 0, proc_line, pf.level);

    // Bind parameters
    auto* parm = pf.parmroot;
    auto* arg = args;

    while (parm && arg) {
        std::string pname = parm->id()->name;

        if (parm->isRef()) {
            // REF parameter: alias the caller's variable
            Value& target = resolveLval(interp, arg->exp());
            // The resolveLval looked up in the old scope (before push)
            // — actually we need to resolve in the caller's scope.
            // Since we already pushed, we need the parent.
            // For now, this is a simplification.
            scope.defineRef(pname, &target);
        } else {
            // Value parameter: evaluate and copy
            Value val = evaluate(interp, arg->exp());
            scope.define(pname, std::move(val));
        }

        parm = parm->next();
        arg = arg->next();
    }

    // Execute body
    ComalLine* body_start = proc_line->next();
    ComalLine* saved = interp.curline;
    try {
        execSeq(interp, body_start);
    } catch (ReturnSignal&) {
        // Normal return from PROC/FUNC via ENDPROC/ENDFUNC
    }
    interp.curline = saved;

    // Pop scope
    interp.scopes.pop();
}

// ── FUNC call from expression ───────────────────────────────────────────

Value execFuncCall(Interpreter& interp, const std::string& name,
                   const ExpList* args) {
    interp.returnValue = Value{};  // clear previous return
    execCall(interp, name, args, true);
    return std::move(interp.returnValue);
}

} // namespace comal::runtime
