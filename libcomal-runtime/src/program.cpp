/// @file program.cpp
/// Interpreter: program loading, structure scanning, and execution entry.

#include "comal_interpreter.h"
#include "comal_executor.h"
#include "comal_evaluator.h"
#include "comal_parser_api.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <stack>

namespace comal::runtime {

// ── Constructor / Destructor ────────────────────────────────────────────

Interpreter::Interpreter() {
    std::random_device rd;
    rng.seed(rd());
}

Interpreter::~Interpreter() = default;

// ── loadFile ────────────────────────────────────────────────────────────

void Interpreter::loadFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open())
        throw ComalError(ErrorCode::Open, "Cannot open file: " + path);

    // Parse each line and build the program linked list
    ComalLine* tail = nullptr;
    std::string text;
    int line_count = 0;

    while (std::getline(file, text)) {
        line_count++;

        // Skip empty lines
        if (text.empty() || text.find_first_not_of(" \t\r\n") == std::string::npos)
            continue;

        char errbuf[256] = {};
        int errpos = 0;

        ComalLine* cl = comal_parse_line_modern(text.c_str(),
                                                 errbuf, sizeof(errbuf), &errpos);
        if (!cl) {
            std::string msg = "Parse error at file line " +
                              std::to_string(line_count) + ": " + errbuf;
            throw ComalError(ErrorCode::Scan, msg);
        }

        // Build linked list
        if (!progroot) {
            progroot = cl;
        } else if (tail) {
            tail->setNext(cl);
        }
        tail = cl;
    }

    // Run structure scan
    structureScan();
}

// ── addLine ─────────────────────────────────────────────────────────────

void Interpreter::addLine(const std::string& text) {
    char errbuf[256] = {};
    int errpos = 0;

    ComalLine* cl = comal_parse_line_modern(text.c_str(),
                                             errbuf, sizeof(errbuf), &errpos);
    if (!cl) {
        throw ComalError(ErrorCode::Scan,
            std::string("Parse error: ") + errbuf);
    }

    // Append to end of program
    if (!progroot) {
        progroot = cl;
    } else {
        ComalLine* tail = progroot;
        while (tail->next()) tail = tail->next();
        tail->setNext(cl);
    }
}

// ── structureScan ───────────────────────────────────────────────────────

/// Structure scan table: maps statement types to their expected end markers.
struct ScanRule {
    StatementType cmd;
    StatementType pushes;     // what we push on the stack (the end we expect)
    StatementType expects1;   // what must be on the stack
    StatementType expects2;   // alternate expected (or Empty)
    bool short_form;          // can have inline body (FOR x DO ..., IF THEN ...)
    bool is_proc;             // PROC/FUNC definition
};

static const ScanRule scan_rules[] = {
    { StatementType::For,       StatementType::EndFor,   StatementType::Empty,   StatementType::Empty,    true,  false },
    { StatementType::If,        StatementType::Elif,     StatementType::Empty,   StatementType::Empty,    true,  false },
    { StatementType::Elif,      StatementType::Elif,     StatementType::Elif,    StatementType::Empty,    false, false },
    { StatementType::Else,      StatementType::EndIf,    StatementType::Elif,    StatementType::Empty,    false, false },
    { StatementType::While,     StatementType::EndWhile, StatementType::Empty,   StatementType::Empty,    true,  false },
    { StatementType::Repeat,    StatementType::Until,    StatementType::Empty,   StatementType::Empty,    true,  false },
    { StatementType::Loop,      StatementType::EndLoop,  StatementType::Empty,   StatementType::Empty,    false, false },
    { StatementType::Case,      StatementType::When,     StatementType::Empty,   StatementType::Empty,    false, false },
    { StatementType::When,      StatementType::When,     StatementType::When,    StatementType::Empty,    false, false },
    { StatementType::Otherwise, StatementType::EndCase,  StatementType::When,    StatementType::Empty,    false, false },
    { StatementType::Trap,      StatementType::Handler,  StatementType::Empty,   StatementType::Empty,    false, false },
    { StatementType::Handler,   StatementType::EndTrap,  StatementType::Handler, StatementType::Empty,    false, false },
    { StatementType::Proc,      StatementType::EndProc,  StatementType::Empty,   StatementType::Empty,    false, true  },
    { StatementType::Func,      StatementType::EndFunc,  StatementType::Empty,   StatementType::Empty,    false, true  },

    // End markers: they pop from the stack
    { StatementType::EndFor,    StatementType::Empty,    StatementType::EndFor,  StatementType::Empty,    false, false },
    { StatementType::EndIf,     StatementType::Empty,    StatementType::EndIf,   StatementType::Elif,     false, false },
    { StatementType::EndWhile,  StatementType::Empty,    StatementType::EndWhile,StatementType::Empty,    false, false },
    { StatementType::Until,     StatementType::Empty,    StatementType::Until,   StatementType::Empty,    false, false },
    { StatementType::EndLoop,   StatementType::Empty,    StatementType::EndLoop, StatementType::Empty,    false, false },
    { StatementType::EndCase,   StatementType::Empty,    StatementType::EndCase, StatementType::When,     false, false },
    { StatementType::EndTrap,   StatementType::Empty,    StatementType::EndTrap, StatementType::Handler,  false, false },
    { StatementType::EndProc,   StatementType::Empty,    StatementType::EndProc, StatementType::Empty,    false, false },
    { StatementType::EndFunc,   StatementType::Empty,    StatementType::EndFunc, StatementType::Empty,    false, false },
};

static const ScanRule* findScanRule(StatementType cmd) {
    for (auto& r : scan_rules) {
        if (r.cmd == cmd) return &r;
    }
    return nullptr;
}

void Interpreter::structureScan() {
    // Stack: pairs of (expected-end-type, opening-line)
    struct StackEntry {
        StatementType expected;
        ComalLine* opener;
    };
    std::stack<StackEntry> stk;

    for (ComalLine* line = progroot; line; line = line->next()) {
        StatementType cmd = line->command();
        const ScanRule* rule = findScanRule(cmd);
        if (!rule) continue;

        // If this statement expects something on the stack (it's an end-marker
        // or a mid-block keyword like ELIF, ELSE, WHEN, OTHERWISE, HANDLER)
        if (rule->expects1 != StatementType::Empty) {
            if (stk.empty())
                throw ComalError(ErrorCode::Scan,
                    "Unexpected " + std::string(statement_type_name(cmd)) +
                    " at line " + std::to_string(line->lineNumber()));

            StackEntry& top = stk.top();
            if (top.expected != rule->expects1 && top.expected != rule->expects2)
                throw ComalError(ErrorCode::Scan,
                    "Mismatched " + std::string(statement_type_name(cmd)) +
                    " at line " + std::to_string(line->lineNumber()) +
                    "; expected " + std::string(statement_type_name(top.expected)));

            // Link the opener's lineptr to this line
            top.opener->setLinePtr(line);

            stk.pop();
        }

        // If this statement pushes a new expectation
        if (rule->pushes != StatementType::Empty) {
            // Short-form check: if the statement has an inline body,
            // it's self-contained and doesn't push
            bool is_short = false;
            if (rule->short_form) {
                switch (cmd) {
                case StatementType::For: {
                    const auto& fr = line->asFor();
                    if (fr.stat) is_short = true;
                    break;
                }
                case StatementType::If: {
                    const auto& iw = line->asIfWhile();
                    if (iw.stat) is_short = true;
                    break;
                }
                case StatementType::While: {
                    const auto& iw = line->asIfWhile();
                    if (iw.stat) is_short = true;
                    break;
                }
                case StatementType::Repeat: {
                    const auto* iw = std::get_if<IfWhileRec>(&line->contents());
                    if (iw && iw->stat) is_short = true;
                    break;
                }
                default: break;
                }
            }

            if (!is_short)
                stk.push({rule->pushes, line});
        }
    }

    if (!stk.empty()) {
        auto& top = stk.top();
        throw ComalError(ErrorCode::Scan,
            "Unterminated " + std::string(statement_type_name(top.opener->command())) +
            " at line " + std::to_string(top.opener->lineNumber()));
    }

    // Build procedure table
    buildProcTable();

    // Initialize DATA pointer
    initDataPointer();
}

// ── buildProcTable ──────────────────────────────────────────────────────

void Interpreter::buildProcTable() {
    procTable.clear();
    for (ComalLine* line = progroot; line; line = line->next()) {
        if (line->command() == StatementType::Proc ||
            line->command() == StatementType::Func) {
            const auto& pf = line->asProcFunc();
            if (pf.id) {
                procTable[pf.id->name] = line;
            }
        }
    }
}

// ── initDataPointer ─────────────────────────────────────────────────────

void Interpreter::initDataPointer() {
    dataLine = nullptr;
    dataExp = nullptr;

    for (ComalLine* line = progroot; line; line = line->next()) {
        if (line->command() == StatementType::Data) {
            dataLine = line;
            auto* el = std::get_if<ExpList*>(&line->contents());
            if (el) dataExp = *el;
            return;
        }
    }
}

// ── advanceData ─────────────────────────────────────────────────────────

void Interpreter::advanceData() {
    if (!dataLine) return;

    // Walk forward from current DATA line to find the next one
    for (ComalLine* line = dataLine->next(); line; line = line->next()) {
        if (line->command() == StatementType::Data) {
            dataLine = line;
            auto* el = std::get_if<ExpList*>(&line->contents());
            if (el) dataExp = *el;
            return;
        }
    }

    // No more DATA lines
    dataLine = nullptr;
    dataExp = nullptr;
}

// ── findRoutine ─────────────────────────────────────────────────────────

ComalLine* Interpreter::findRoutine(const std::string& name) {
    auto it = procTable.find(name);
    if (it == procTable.end())
        throw ComalError(ErrorCode::Label,
            "PROC/FUNC '" + name + "' not found");
    return it->second;
}

// ── resetRunState ───────────────────────────────────────────────────────

void Interpreter::resetRunState() {
    // Reset scopes (clear everything except global, then clear global)
    while (scopes.depth() > 1)
        scopes.pop();
    scopes.global().clear();

    // Close all files
    files.closeAll();

    // Reset DATA pointer
    initDataPointer();

    // Clear error state
    lastError = ErrorCode::None;
    lastErrorMsg.clear();
    lastErrorLine = 0;

    // Clear return value
    returnValue = Value{};

    // Reset I/O selection
    selOutput = 0;
    selInput = 0;

    trace = false;
    curline = nullptr;
}

// ── run ─────────────────────────────────────────────────────────────────

void Interpreter::run() {
    if (!progroot)
        throw ComalError(ErrorCode::Run, "No program loaded");

    resetRunState();

    try {
        execSeq(*this, progroot);
    } catch (EndSignal&) {
        // Normal termination via END statement
    } catch (StopSignal&) {
        print("STOP at line " +
              std::to_string(curline ? curline->lineNumber() : 0) + "\n");
    }

    // Clean up
    files.closeAll();
}

// ── I/O ─────────────────────────────────────────────────────────────────

void Interpreter::print(const std::string& s) {
    if (selOutput != 0 && files.isOpen(selOutput)) {
        files.writeValue(selOutput, Value(s));
    } else {
        *out << s;
        out->flush();
    }
}

void Interpreter::newline() {
    print("\n");
}

std::string Interpreter::readLine(const std::string& prompt) {
    if (!prompt.empty()) print(prompt);

    if (selInput != 0 && files.isOpen(selInput)) {
        Value v = files.readValue(selInput, Value::Type::String);
        return v.asString();
    }

    std::string line;
    if (!std::getline(*in, line))
        throw ComalError(ErrorCode::Eof, "End of input");
    return line;
}

} // namespace comal::runtime
