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
#include "comal_graphics_commands.h"
#include "comal_scene_model.h"
#include "comal_sound.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <thread>
#include <chrono>

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
static void execDraw(Interpreter& interp, ComalLine* line);
static void execTone(Interpreter& interp, ComalLine* line);
static void execPlay(Interpreter& interp, ComalLine* line);
static void execRestore(Interpreter& interp, ComalLine* line);

// Lvalue assignment helpers
static void assignToLval(Interpreter& interp, const Expression* lval,
                         const Value& val, int op);
static Value& resolveLval(Interpreter& interp, const Expression* lval);

// Helper used by step-mode: suspend after each executed statement.
static void stepPause(Interpreter& interp) {
    if (!interp.isSingleStep())
        return;
    interp.suspend();
    interp.waitWhileSuspended();
}

// ── execSeq — main execution loop ──────────────────────────────────────

void execSeq(Interpreter& interp, ComalLine* start) {
    interp.curline = start;

    while (interp.curline) {
        interp.checkInterrupt();
        if (interp.isSuspended()) {
            interp.waitWhileSuspended();
        }
        ComalLine* line = interp.curline;

        // Breakpoint support: pause before executing a statement if a
        // breakpoint is set on this line.
        interp.checkBreakpoint();

        // Trace mode
        if (interp.trace && line->lineNumber() > 0) {
            interp.print("[" + std::to_string(line->lineNumber()) + "] ");
        }

        // Single-step mode: pause before executing the current statement.
        // This ensures stepping lands on the first line inside a PROC/FUNC.
        stepPause(interp);

        // Default next line (in case execLine doesn't modify curline)
        ComalLine* next = line->next();

        execLine(interp, line);

        // If execLine didn't change curline (normal straight-line flow),
        // advance to the next line.
        if (interp.curline == line)
            interp.curline = next;
    }
}

// ── execLine — dispatch one statement ───────────────────────────────────

void execLine(Interpreter& interp, ComalLine* line) {

    switch (line->command()) {
    // ── SLEEP ─────────────────────────────────────────────────────────────
    case StatementType::Sleep: {
        auto* elist = std::get_if<ExpList*>(&line->contents());
        if (!elist || !*elist)
            break; // no args -> no-op

        auto* node = *elist;
        if (!node || !node->exp())
            break;

        Value v = evaluate(interp, node->exp());
        int64_t ms = v.toInt();
        if (ms > 0)
            std::this_thread::sleep_for(std::chrono::milliseconds(ms));
        break;
    }

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

    case StatementType::Trace: {
        auto* expr = std::get_if<Expression*>(&line->contents());
        if (expr && *expr) {
            // Unwrap ExpIsNum/ExpIsString wrapper if present
            const Expression* e = *expr;
            if (e->opType() == OpType::ExpIsNum || e->opType() == OpType::ExpIsString)
                e = e->asExp();
            if (e->opType() == OpType::Id) {
                std::string name = std::get<ExpId>(e->data()).id->name;
                for (auto& c : name) c = std::toupper(c);
                interp.trace = (name == "ON");
            }
        }
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
    case StatementType::Trap: {
        const auto& tr = line->asTrap();
        if (tr.esc != 0) {
            // TRAP ESC+/- : simple statement, no-op in batch mode
            break;
        }
        execTrap(interp, line);
        break;
    }

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
        interp.clearScreen();
        break;

    // ── CURSOR row, col ─────────────────────────────────────────────────
    case StatementType::Cursor: {
        const auto& te = line->asTwoExp();
        int64_t row = evalInt(interp, te.exp1);
        int64_t col = evalInt(interp, te.exp2);
        interp.setCursor(static_cast<int>(row), static_cast<int>(col));
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
        auto* expr = std::get_if<Expression*>(&line->contents());
        if (expr && *expr) {
            std::string cmd = evalString(interp, *expr);
            if (!cmd.empty())
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
        auto* expr = std::get_if<Expression*>(&line->contents());
        if (expr && *expr) {
            Value v = evaluate(interp, *expr);
            if (v.isString()) {
                const std::string& fname = v.asString();
                if (fname.empty()) {
                    // Restore default output
                    interp.selOutputFile_.reset();
                } else {
                    // Redirect output to file
                    auto ofs = std::make_unique<std::ofstream>(fname);
                    if (!ofs->is_open()) {
                        throw ComalError(ErrorCode::Open,
                            "Cannot open '" + fname + "' for output");
                    }
                    interp.selOutputFile_ = std::move(ofs);
                }
            } else {
                interp.selOutput = v.toInt();
            }
        }
        break;
    }

    case StatementType::Select_Input: {
        auto* expr = std::get_if<Expression*>(&line->contents());
        if (expr && *expr) {
            Value v = evaluate(interp, *expr);
            if (v.isString()) {
                const std::string& fname = v.asString();
                if (fname.empty()) {
                    // Restore default input
                    interp.selInputFile_.reset();
                } else {
                    // Redirect input from file
                    auto ifs = std::make_unique<std::ifstream>(fname);
                    if (!ifs->is_open()) {
                        throw ComalError(ErrorCode::Open,
                            "Cannot open '" + fname + "' for input");
                    }
                    interp.selInputFile_ = std::move(ifs);
                }
            } else {
                interp.selInput = v.toInt();
            }
        }
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
    case StatementType::Draw:
        execDraw(interp, line);
        break;

    case StatementType::Tone:
        execTone(interp, line);
        break;

    case StatementType::Play:
        execPlay(interp, line);
        break;

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

// ── File read helper (handles arrays) ───────────────────────────────────

// Read one lvalue from a binary file, handling whole-array reads.
// Legacy do_readfile() reads N elements when lvalue is an array.
static void readFileLval(Interpreter& interp, int64_t fno, const Expression* lval) {
    // Determine expected type from the lvalue (unwrap wrappers)
    const Expression* inner = lval;
    while (inner && (inner->opType() == OpType::ExpIsNum ||
                     inner->opType() == OpType::ExpIsString))
        inner = inner->asExp();

    Value::Type expected = Value::Type::Int;
    if (inner->opType() == OpType::Sid || inner->opType() == OpType::Sarray)
        expected = Value::Type::String;
    else if (inner->opType() == OpType::Id) {
        const auto& eid = std::get<ExpId>(inner->data());
        if (eid.id && eid.id->type == V_STRING)
            expected = Value::Type::String;
        else if (eid.id && eid.id->type == V_FLOAT)
            expected = Value::Type::Float;
    }

    // Resolve the lvalue to check if it's an array
    Value& target = resolveLval(interp, lval);
    if (target.isArray()) {
        // Read one element per array slot (matches legacy do_readfile)
        auto& arr = target.asArray();
        for (auto& elem : arr.elements) {
            Value val = interp.files.readValue(fno, expected);
            elem.assignFrom(val);
        }
    } else {
        Value val = interp.files.readValue(fno, expected);
        assignToLval(interp, lval, val, becomesSYM);
    }
}

// ── PRINT ───────────────────────────────────────────────────────────────

// PRINT FILE — binary write to file (same format as WRITE FILE)
static void printFile(Interpreter& interp, const TwoExp& te,
                      const PrintList* printroot) {
    int64_t fno = evaluate(interp, te.exp1).toInt();
    if (te.exp2) {
        int64_t pos = evaluate(interp, te.exp2).toInt();
        interp.files.seek(fno, pos);
    }

    for (auto* node = printroot; node; node = node->next()) {
        if (node->exp()) {
            Value val = evaluate(interp, node->exp());
            if (val.isArray()) {
                // Legacy behavior: PRINT FILE rejects whole arrays
                // Unwrap ExpIsNum/ExpIsString wrappers to get the actual Id/Sid
                const Expression* inner = node->exp();
                while (inner && (inner->opType() == OpType::ExpIsNum ||
                                 inner->opType() == OpType::ExpIsString))
                    inner = inner->asExp();
                std::string varname = "array";
                if (inner && inner->opType() == OpType::Id) {
                    auto& eid = std::get<ExpId>(inner->data());
                    if (eid.id) varname = eid.id->name;
                } else if (inner && inner->opType() == OpType::Sid) {
                    auto& esid = std::get<ExpSid>(inner->data());
                    if (esid.id) varname = esid.id->name;
                }
                throw ComalError(ErrorCode::Array,
                    "Missing string array indices on " + varname);
            }
            interp.files.writeValue(fno, val);
        }
    }
}

// PRINT USING — formatted numeric output
// Format string uses '#' for digits, '.' for decimal point.
// e.g. "####" → width 4, 0 decimals; "##.##" → width 5, 2 decimals.
static void printUsing(Interpreter& interp, const Expression* fmtExpr,
                       const PrintList* printroot, int pr_sep) {
    Value fmtVal = evaluate(interp, fmtExpr);
    if (!fmtVal.isString())
        throw ComalError(ErrorCode::Using, "USING format must be a string");
    const std::string& fmt = fmtVal.asString();

    // Parse USING format: count total width and decimal precision
    int width = 0, prec = 0;
    bool decpoint = false;
    for (char c : fmt) {
        width++;
        if (c == '#') {
            if (decpoint) prec++;
        } else if (c == '.') {
            if (decpoint)
                throw ComalError(ErrorCode::Using, "USING string format error");
            decpoint = true;
        } else {
            throw ComalError(ErrorCode::Using, "USING string format error");
        }
    }

    char spec[32];
    std::snprintf(spec, sizeof(spec), "%%%d.%dlf", width, prec);

    for (auto* node = printroot; node; node = node->next()) {
        if (node->exp()) {
            double d = evaluate(interp, node->exp()).toDouble();
            char buf[64];
            std::snprintf(buf, sizeof(buf), spec, d);
            interp.print(buf);
        }

        int sep = node->separator();
        if (sep == commaSYM)
            interp.print("\t");
    }

    if (pr_sep == 0)
        interp.newline();
    else if (pr_sep == commaSYM)
        interp.print("\t");
}

static void execPrint(Interpreter& interp, ComalLine* line) {
    const auto& pr = line->asPrint();

    if (pr.modifier) {
        if (pr.modifier->type == fileSYM) {
            if (auto* te = std::get_if<TwoExp>(&pr.modifier->data)) {
                printFile(interp, *te, pr.printroot);
                return;
            }
        } else if (pr.modifier->type == usingSYM) {
            if (auto* fmtExpr = std::get_if<Expression*>(&pr.modifier->data)) {
                printUsing(interp, *fmtExpr, pr.printroot, pr.pr_sep);
                return;
            }
        }
    }

    for (auto* node = pr.printroot; node; node = node->next()) {
        // Separator precedes this item (stored on node from parser grammar)
        int sep = node->separator();
        if (sep == commaSYM) {
            interp.print("\t");
        }
        // semicolonSYM = concatenate (no space)

        if (node->exp()) {
            Value v = evaluate(interp, node->exp());
            interp.print(v.printStr());
        }
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

    // Check for INPUT FILE modifier — binary read, same as READ FILE
    if (inp.modifier) {
        if (auto* te = std::get_if<TwoExp>(&inp.modifier->data)) {
            int64_t fno = evaluate(interp, te->exp1).toInt();

            for (auto* node = inp.lvalroot; node; node = node->next()) {
                readFileLval(interp, fno, node->exp());
            }
            return;
        }
    }

    std::string prompt = "? ";

    // Handle AT modifier (prompt string)
    if (inp.modifier) {
        if (auto* s = std::get_if<string*>(&inp.modifier->data)) {
            if (*s) prompt = std::string((*s)->s, (*s)->len);
        }
    }

    // Read one line, then parse fields from it
    std::string input_line = interp.readLine(prompt);
    size_t pos = 0;

    for (auto* node = inp.lvalroot; node; node = node->next()) {
        const Expression* lval = node->exp();

        // Skip whitespace
        while (pos < input_line.size() && (input_line[pos] == ' ' || input_line[pos] == '\t'))
            pos++;

        // If we exhausted the line, read another
        if (pos >= input_line.size()) {
            input_line = interp.readLine("?? ");
            pos = 0;
            while (pos < input_line.size() && (input_line[pos] == ' ' || input_line[pos] == '\t'))
                pos++;
        }

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

        Value val;
        if (is_string) {
            // Parse string field
            std::string field;
            if (pos < input_line.size() && input_line[pos] == '"') {
                // Quoted string — read until closing quote
                pos++;  // skip opening quote
                while (pos < input_line.size() && input_line[pos] != '"') {
                    field += input_line[pos++];
                }
                if (pos < input_line.size()) pos++;  // skip closing quote
            } else {
                // Unquoted string — read until comma or end of line, trim trailing space
                size_t start = pos;
                while (pos < input_line.size() && input_line[pos] != ',') {
                    pos++;
                }
                field = input_line.substr(start, pos - start);
                // Trim trailing whitespace
                while (!field.empty() && (field.back() == ' ' || field.back() == '\t'))
                    field.pop_back();
            }
            val = Value(std::move(field));
        } else {
            // Parse numeric field
            size_t start = pos;
            // Extract until comma or end
            while (pos < input_line.size() && input_line[pos] != ',') {
                pos++;
            }
            std::string numstr = input_line.substr(start, pos - start);
            // Trim trailing whitespace
            while (!numstr.empty() && (numstr.back() == ' ' || numstr.back() == '\t'))
                numstr.pop_back();
            // Trim leading whitespace
            size_t fpos = numstr.find_first_not_of(" \t");
            if (fpos != std::string::npos) numstr = numstr.substr(fpos);
            try {
                size_t ppos;
                long long ll = std::stoll(numstr, &ppos);
                if (ppos == numstr.size()) {
                    val = Value(static_cast<int64_t>(ll));
                } else {
                    double d = std::stod(numstr, &ppos);
                    val = Value(d);
                }
            } catch (...) {
                throw ComalError(ErrorCode::Input,
                    "Cannot parse '" + numstr + "' as a number");
            }
        }

        // Skip comma separator
        while (pos < input_line.size() && (input_line[pos] == ' ' || input_line[pos] == '\t'))
            pos++;
        if (pos < input_line.size() && input_line[pos] == ',')
            pos++;

        assignToLval(interp, lval, val, becomesSYM);
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
    // Unwrap ExpIsNum/ExpIsString wrappers
    while (lval->opType() == OpType::ExpIsNum || lval->opType() == OpType::ExpIsString)
        lval = lval->asExp();

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
    // Unwrap ExpIsNum/ExpIsString wrappers
    while (lval->opType() == OpType::ExpIsNum || lval->opType() == OpType::ExpIsString)
        lval = lval->asExp();

    std::string name = lvalName(lval);

    Symbol* sym = interp.scopes.current().find(name);
    if (!sym) {
        // Auto-create in the nearest CLOSED scope (or global), matching legacy behavior
        Value init;
        switch (lval->opType()) {
        case OpType::Sid:
        case OpType::Sarray:
            init = Value(std::string{});
            break;
        default: {
            // Check id_rec type for V_FLOAT variables
            bool is_float = false;
            if (auto* eid = std::get_if<ExpId>(&lval->data()))
                is_float = (eid->id && eid->id->type == V_FLOAT);
            init = is_float ? Value(0.0) : Value(int64_t{0});
            break;
        }
        }
        // Walk up to nearest CLOSED scope for variable creation
        Scope* target = &interp.scopes.current();
        while (target->parent && !target->closed)
            target = target->parent;
        sym = &target->define(name, std::move(init));
    }

    // Array element?
    if (sym->resolve().isArray()) {
        // Extract subscript expressions — check both ExpId and ExpSid
        const ExpList* exproot = nullptr;
        if (lval->opType() == OpType::Array || lval->opType() == OpType::Sarray ||
            lval->opType() == OpType::Id) {
            if (auto* eidp = std::get_if<ExpId>(&lval->data()))
                exproot = eidp->exproot;
        } else if (lval->opType() == OpType::Sid) {
            auto& esid = std::get<ExpSid>(lval->data());
            exproot = esid.exproot;
        }
        if (exproot) {
            std::vector<int64_t> idx;
            for (auto* node = exproot; node; node = node->next())
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

    // Whole-array assignment: fill all elements with the scalar value
    if (target.isArray() && !val.isArray()) {
        auto& arr = target.asArray();
        for (auto& elem : arr.elements) {
            switch (op) {
            case becomesSYM: elem.assignFrom(val); break;
            case becplusSYM: elem = elem + val; break;
            case becminusSYM: elem = elem - val; break;
            default: elem.assignFrom(val); break;
            }
        }
        return;
    }

    // Whole-array to whole-array copy (a():=b())
    if (target.isArray() && val.isArray()) {
        auto& tarr = target.asArray();
        const auto& sarr = val.asArray();
        size_t n = std::min(tarr.elements.size(), sarr.elements.size());
        for (size_t i = 0; i < n; ++i)
            tarr.elements[i].assignFrom(sarr.elements[i]);
        return;
    }

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

    // If any of from/to/step is float, promote from_val to float so
    // the loop variable is created as float (prevents int truncation of step)
    if (to_val.isNumeric() && step_val.isNumeric()) {
        bool needs_float = to_val.isFloat() || step_val.isFloat() || from_val.isFloat();
        if (needs_float && !from_val.isFloat()) {
            from_val = Value(from_val.toDouble());
        }
    }

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
            interp.checkInterrupt();
            Value cur = evaluate(interp, fr.lval);
            if (pastEnd(cur.toDouble(), to_val.toDouble())) break;
            execLine(interp, fr.stat);
            stepPause(interp);
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
        interp.checkInterrupt();
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
                stepPause(interp);
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
            interp.checkInterrupt();
            Value cond = evaluate(interp, iw.exp);
            if (cond.toInt() == 0) break;
            execLine(interp, iw.stat);
            stepPause(interp);
        }
        return;
    }

    // Block WHILE — lineptr points to ENDWHILE
    ComalLine* endwhile = line->linePtr();
    if (!endwhile) throw ComalError(ErrorCode::Scan, "WHILE without ENDWHILE");

    while (true) {
        interp.checkInterrupt();
        Value cond = evaluate(interp, iw.exp);
        if (cond.toInt() == 0) break;

        try {
            ComalLine* saved = interp.curline;
            interp.curline = line->next();
            while (interp.curline && interp.curline != endwhile) {
                ComalLine* cur_line = interp.curline;
                interp.curline = cur_line->next();
                execLine(interp, cur_line);
                stepPause(interp);
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
            interp.checkInterrupt();
            execLine(interp, iw->stat);
            stepPause(interp);
        } while (iw->exp && evaluate(interp, iw->exp).toInt() == 0);
        return;
    }

    // Block REPEAT — lineptr points to UNTIL
    ComalLine* until_line = line->linePtr();
    if (!until_line) throw ComalError(ErrorCode::Scan, "REPEAT without UNTIL");

    while (true) {
        interp.checkInterrupt();
        try {
            ComalLine* saved = interp.curline;
            interp.curline = line->next();
            while (interp.curline && interp.curline != until_line) {
                ComalLine* cur_line = interp.curline;
                interp.curline = cur_line->next();
                execLine(interp, cur_line);
                stepPause(interp);
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
        interp.checkInterrupt();
        try {
            ComalLine* saved = interp.curline;
            interp.curline = line->next();
            while (interp.curline && interp.curline != endloop) {
                ComalLine* cur_line = interp.curline;
                interp.curline = cur_line->next();
                execLine(interp, cur_line);
                stepPause(interp);
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
        if (cond.toInt() != 0) {
            execLine(interp, iw.stat);
            stepPause(interp);
        }
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
            stepPause(interp);
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
                    stepPause(interp);
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
                stepPause(interp);
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
    // CLOSE can be: monostate (close all), Expression* (close one),
    // or ExpList* (close multiple files)
    auto* elist = std::get_if<ExpList*>(&line->contents());
    if (elist && *elist) {
        for (auto* node = *elist; node; node = node->next()) {
            int64_t fno = evalInt(interp, node->exp());
            interp.files.close(fno);
        }
        return;
    }
    auto* expr = std::get_if<Expression*>(&line->contents());
    if (expr && *expr) {
        int64_t fno = evalInt(interp, *expr);
        interp.files.close(fno);
        return;
    }
    // No arguments: close all files
    interp.files.closeAll();
}

// ── READ (from DATA or file) ────────────────────────────────────────────

static void execRead(Interpreter& interp, ComalLine* line) {
    const auto& rr = line->asRead();

    if (rr.modifier) {
        // File READ — uses binary format with type tags
        int64_t fno = evalInt(interp, rr.modifier->exp1);
        for (auto* node = rr.lvalroot; node; node = node->next()) {
            readFileLval(interp, fno, node->exp());
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
        if (val.isArray()) {
            // Write each element individually (matches legacy behavior)
            for (auto& elem : val.asArray().elements) {
                interp.files.writeValue(fno, elem);
            }
        } else {
            interp.files.writeValue(fno, val);
        }
    }
}

// ── TRAP..HANDLER..ENDTRAP ──────────────────────────────────────────────

static void execTrap(Interpreter& interp, ComalLine* line) {
    ComalLine* linked = line->linePtr();
    if (!linked)
        throw ComalError(ErrorCode::Scan, "TRAP without HANDLER/ENDTRAP");

    // Determine if this is TRAP..HANDLER..ENDTRAP or TRAP..ENDTRAP (no handler).
    // linePtr from TRAP points to HANDLER if present, otherwise to ENDTRAP.
    ComalLine* handler = nullptr;
    ComalLine* endtrap = nullptr;
    if (linked->command() == StatementType::Handler) {
        handler = linked;
        endtrap = handler->linePtr();  // HANDLER→ENDTRAP
    } else {
        // TRAP..ENDTRAP with no HANDLER — errors are silently swallowed
        endtrap = linked;
    }

    ComalLine* body_end = handler ? handler : endtrap;

    bool retry;
    do {
        retry = false;
        try {
            // Execute TRAP body
            interp.curline = line->next();
            while (interp.curline && interp.curline != body_end) {
                ComalLine* cur_line = interp.curline;
                interp.curline = cur_line->next();
                execLine(interp, cur_line);
            }
        } catch (ComalError& e) {
            // Save error info
            interp.lastError = e.code();
            interp.lastErrorMsg = e.what();
            interp.lastErrorLine = e.line();

            if (handler) {
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
            // else: no HANDLER — error is silently swallowed
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
    // Check if this is a PROC/FUNC variable call
    ComalLine* proc_line = nullptr;
    Symbol* proc_sym = interp.scopes.current().find(name);
    if (proc_sym && (proc_sym->kind == SymbolKind::ProcRef || proc_sym->kind == SymbolKind::FuncRef)) {
        proc_line = proc_sym->routine_line;
    } else {
        proc_line = interp.findRoutine(name);
    }
    const auto& pf = proc_line->asProcFunc();

    // EXTERNAL procs/funcs are not loadable — treat as no-op
    if (pf.external) {
        if (isFunc) {
            interp.returnValue = Value(int64_t{0});
        }
        return;
    }

    // Evaluate arguments in the CALLER's scope before pushing new scope
    struct BoundArg {
        std::string name;
        enum { Val, Ref, Name, Proc, Func } kind;
        Value val;                        // for value params
        Value* ref_target{nullptr};       // for REF params
        const Expression* name_expr{nullptr}; // for NAME params
    };
    std::vector<BoundArg> bound;

    auto* parm = pf.parmroot;
    auto* arg = args;
    while (parm && arg) {
        BoundArg ba;
        ba.name = parm->id()->name;
        ba.kind = BoundArg::Val;

        if (parm->isRef()) {
            ba.kind = BoundArg::Ref;
            ba.ref_target = &resolveLval(interp, arg->exp());
        } else if (parm->isName()) {
            ba.kind = BoundArg::Name;
            ba.name_expr = arg->exp();
        } else if (parm->isProc()) {
            ba.kind = BoundArg::Proc;
            ba.name_expr = arg->exp();  // store expr for lookup
        } else if (parm->isFunc()) {
            ba.kind = BoundArg::Func;
            ba.name_expr = arg->exp();
        } else {
            ba.val = evaluate(interp, arg->exp());
        }

        bound.push_back(std::move(ba));
        parm = parm->next();
        arg = arg->next();
    }

    // Save caller scope for NAME thunks
    Scope* caller_scope = &interp.scopes.current();

    // Create new scope
    Scope& scope = interp.scopes.push(
        name, pf.closed != 0, proc_line, pf.level);

    // Bind pre-evaluated parameters
    for (auto& ba : bound) {
        switch (ba.kind) {
        case BoundArg::Ref:
            scope.defineRef(ba.name, ba.ref_target);
            break;
        case BoundArg::Name:
            scope.defineName(ba.name, ba.name_expr, caller_scope);
            break;
        case BoundArg::Proc: {
            // PROC parameter: find the routine by name from the expression
            const Expression* pexpr = ba.name_expr;
            while (pexpr && (pexpr->opType() == OpType::ExpIsNum || pexpr->opType() == OpType::ExpIsString))
                pexpr = pexpr->asExp();
            std::string pname;
            if (pexpr) {
                if (auto* eidp = std::get_if<ExpId>(&pexpr->data()))
                    pname = eidp->id ? eidp->id->name : "";
                else if (auto* esidp = std::get_if<ExpSid>(&pexpr->data()))
                    pname = esidp->id ? esidp->id->name : "";
            }
            ComalLine* rline = interp.findRoutine(pname);
            scope.defineProcFunc(ba.name, SymbolKind::ProcRef, rline);
            break;
        }
        case BoundArg::Func: {
            const Expression* fexpr = ba.name_expr;
            while (fexpr && (fexpr->opType() == OpType::ExpIsNum || fexpr->opType() == OpType::ExpIsString))
                fexpr = fexpr->asExp();
            std::string fname;
            if (fexpr) {
                if (auto* eidp = std::get_if<ExpId>(&fexpr->data()))
                    fname = eidp->id ? eidp->id->name : "";
                else if (auto* esidp = std::get_if<ExpSid>(&fexpr->data()))
                    fname = esidp->id ? esidp->id->name : "";
            }
            ComalLine* rline = interp.findRoutine(fname);
            scope.defineProcFunc(ba.name, SymbolKind::FuncRef, rline);
            break;
        }
        default:
            scope.define(ba.name, std::move(ba.val));
            break;
        }
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

// ── DRAW (graphics commands) ────────────────────────────────────────────

static void execDraw(Interpreter& interp, ComalLine* line) {
    // DRAW supports two forms:
    //   DRAW "circle 100 200 50"              — full command as single string
    //   DRAW "circle", 100, 200, 50           — command name + separate args
    //   DRAW "Spaceship.rect", x, y, w, h     — grouped, with variables
    //
    // In the multi-arg form, all expressions are evaluated and joined
    // into a single command string for parsing.
    auto* elist = std::get_if<ExpList*>(&line->contents());
    if (!elist || !*elist) return;

    auto& scene = interp.graphicsScene();
    const auto& registry = interp.graphicsRegistry();

    // Build command string by joining all expression values
    std::string cmdStr;
    for (auto* node = *elist; node; node = node->next()) {
        Value v = evaluate(interp, node->exp());
        if (!cmdStr.empty()) cmdStr += ' ';
        cmdStr += v.printStr();
    }

    comal::graphics::ParsedCommand cmd;
    comal::graphics::ParseError err;
    if (!comal::graphics::parseLine(cmdStr, static_cast<int>(line->lineNumber()),
                                    registry, cmd, err)) {
        throw ComalError(ErrorCode::Parm, "DRAW: " + err.message);
    }

    if (cmd.command.empty())
        return;  // blank or comment — skip

    std::string execErr = comal::graphics::executeCommand(scene, cmd);
    if (!execErr.empty()) {
        throw ComalError(ErrorCode::Parm, "DRAW: " + execErr);
    }

    interp.notifySceneChanged();
}

// ── TONE / PLAY (sound) ───────────────────────────────────────────────

static void execTone(Interpreter& interp, ComalLine* line) {
    auto* elist = std::get_if<ExpList*>(&line->contents());
    if (!elist || !*elist)
        throw ComalError(ErrorCode::Parm, "TONE requires two integer arguments: frequency, duration");

    // Expect exactly two numeric arguments: frequency (Hz), duration (ms)
    std::vector<double> args;
    bool async = false;
    for (auto* node = *elist; node; node = node->next()) {
        const comal::Expression* e = node->exp();
        if (!e) continue;
        
        // Unwrap ExpIsNum/ExpIsString wrappers so modifiers (Id/String) are visible
        const comal::Expression* inner = e;
        while (inner && (inner->opType() == comal::OpType::ExpIsNum || inner->opType() == comal::OpType::ExpIsString))
            inner = inner->asExp();

        // First handle bare identifier/string modifiers like ASYNC/NOWAIT
        if (inner->opType() == comal::OpType::Id) {
            const auto &eid = std::get<comal::ExpId>(inner->data());
            const char* idn = eid.id ? eid.id->name : "";
            std::string iname(idn);
            for (auto &c : iname) c = std::toupper(static_cast<unsigned char>(c));
            if (iname == "ASYNC" || iname == "NOWAIT") {
                async = true;
                continue;
            }
            // Not a known modifier — fall through to evaluate (may be a variable containing a number)
        }
        if (inner->opType() == comal::OpType::String) {
            auto *s = inner->asString();
            std::string ss(s->s, s->len);
            std::string up = ss;
            for (auto &c : up) c = std::toupper(static_cast<unsigned char>(c));
            if (up == "ASYNC" || up == "NOWAIT") {
                async = true;
                continue;
            }
            // Otherwise treat as an expression (may evaluate to a number)
        }

        // Evaluate expression for numeric arguments (evaluate original expression to honor wrappers)
        Value v = evaluate(interp, e);
        if (v.isNumeric()) {
            args.push_back(v.toDouble());
            continue;
        }
        throw ComalError(ErrorCode::Parm, "TONE arguments must be numeric or ASYNC/NOWAIT");
    }

    if (args.size() < 2)
        throw ComalError(ErrorCode::Parm, "TONE requires two arguments: frequency (Hz), duration (ms)");

    comal::sound::PlaySpec spec;
    spec.name = "tone";
    spec.params.push_back(args[0]);
    spec.params.push_back(args[1]);
    spec.duration = args[1];
    spec.async = async;

    static comal::sound::Engine* engine = [](){
        auto *e = new comal::sound::Engine();
        e->init();
        comal::sound::registerEngine(e);
        return e;
    }();
    auto fut = engine->play(spec);
    // Blocking behaviour by default: wait on engine completion unless async requested
    if (!spec.async && fut) {
        try {
            fut->wait();
        } catch (...) {
            // ignore wait errors
        }
    }

}

static void execPlay(Interpreter& interp, ComalLine* line) {
    auto* elist = std::get_if<ExpList*>(&line->contents());
    if (!elist || !*elist)
        throw ComalError(ErrorCode::Parm, "PLAY requires a string argument");
    // PLAY supports a string argument followed by optional parameters.
    // First element must be a string describing the source/command.
    auto* node = *elist;
    Value firstVal = evaluate(interp, node->exp());
    if (!firstVal.isString())
        throw ComalError(ErrorCode::Parm, "PLAY requires a string argument as the first parameter");

    comal::sound::PlaySpec spec;
    spec.name = firstVal.asString();
    spec.duration = 0;
    spec.async = false;

    // parse remaining parameters (if any)
    for (auto *n = node->next(); n; n = n->next()) {
        const comal::Expression* e = n->exp();
        if (!e) continue;
        // If it's a string, allow key=value forms (e.g. "VOL=80", "SF2=/path")
        if (e->opType() == comal::OpType::String) {
            auto *s = e->asString();
            std::string ss(s->s, s->len);
            std::string up = ss;
            for (auto &c : up) c = std::toupper(static_cast<unsigned char>(c));
            if (up.rfind("VOL=", 0) == 0) {
                try {
                    int vnum = std::stoi(ss.substr(4));
                    // set engine volume immediately
                    static comal::sound::Engine* engine = [](){ auto *e = new comal::sound::Engine(); e->init(); comal::sound::registerEngine(e); return e; }();
                    engine->setVolume(vnum);
                } catch (...) {
                    throw ComalError(ErrorCode::Parm, "PLAY VOL requires an integer value");
                }
            } else if (up.rfind("DUR=", 0) == 0) {
                try {
                    spec.duration = std::stod(ss.substr(4));
                } catch (...) {
                    throw ComalError(ErrorCode::Parm, "PLAY DUR requires a numeric value (ms)");
                }
            } else if (up == "ASYNC" || up == "NOWAIT") {
                spec.async = true;
            }
            continue;
        }

        // If it's an identifier (Id/Sid), inspect the id name without evaluating
        if (e->opType() == comal::OpType::Id) {
            const auto &eid = std::get<comal::ExpId>(e->data());
            const char* idn = eid.id ? eid.id->name : "";
            std::string iname(idn);
            for (auto &c : iname) c = std::toupper(static_cast<unsigned char>(c));
            if (iname == "ASYNC" || iname == "NOWAIT") {
                spec.async = true;
                continue;
            }
            if (iname == "VOL") {
                // expect next node to be numeric
                if (!n->next()) throw ComalError(ErrorCode::Parm, "PLAY VOL requires a numeric value");
                Value vv = evaluate(interp, n->next()->exp());
                if (!vv.isNumeric()) throw ComalError(ErrorCode::Parm, "PLAY VOL requires a numeric value");
                static comal::sound::Engine* engine = [](){ auto *e = new comal::sound::Engine(); e->init(); comal::sound::registerEngine(e); return e; }();
                engine->setVolume(static_cast<int>(vv.toDouble()));
                n = n->next(); // skip value
                continue;
            }
            if (iname == "DUR") {
                if (!n->next()) throw ComalError(ErrorCode::Parm, "PLAY DUR requires a numeric value (ms)");
                Value dv = evaluate(interp, n->next()->exp());
                if (!dv.isNumeric()) throw ComalError(ErrorCode::Parm, "PLAY DUR requires a numeric value (ms)");
                spec.duration = dv.toDouble();
                n = n->next();
                continue;
            }
        }

        // If it's numeric, append to params (e.g., PLAY "tone", freq, dur)
        Value vv = evaluate(interp, e);
        if (vv.isNumeric()) {
            spec.params.push_back(vv.toDouble());
            continue;
        }
        // Unknown parameter form — ignore or raise error; choose to ignore silently
    }

    static comal::sound::Engine* engine = [](){
        auto *e = new comal::sound::Engine();
        e->init();
        return e;
    }();

    auto pfut = engine->play(spec);
    if (!spec.async && pfut) {
        try { pfut->wait(); } catch (...) {}
    }
}

// ── FUNC call from expression ───────────────────────────────────────────

Value execFuncCall(Interpreter& interp, const std::string& name,
                   const ExpList* args) {
    interp.returnValue = Value{};  // clear previous return
    execCall(interp, name, args, true);
    return std::move(interp.returnValue);
}

} // namespace comal::runtime
