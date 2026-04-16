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
#include <unordered_set>

namespace comal::runtime {

// ── Constructor / Destructor ────────────────────────────────────────────

Interpreter::Interpreter()
    : io_(std::make_unique<TerminalIO>())
{
    std::random_device rd;
    rng.seed(rd());
}

Interpreter::~Interpreter() {
    stopSpawnedWorkers();
}

void Interpreter::registerSpawnWorker(std::shared_ptr<Interpreter> worker,
                                      std::thread thread) {
    std::lock_guard<std::mutex> lock(spawnedWorkersMutex_);
    spawnedWorkers_.push_back(SpawnWorker{std::move(worker), std::move(thread)});
}

void Interpreter::stopSpawnedWorkers() {
    std::vector<SpawnWorker> workers;
    {
        std::lock_guard<std::mutex> lock(spawnedWorkersMutex_);
        if (spawnedWorkers_.empty()) {
            return;
        }
        workers = std::move(spawnedWorkers_);
        spawnedWorkers_.clear();
    }

    // Wake workers that might be blocked on queue INPUT.
    FileTable::requestQueueShutdown();

    for (auto& worker : workers) {
        if (worker.interp) {
            worker.interp->interrupt().request();
        }
    }

    for (auto& worker : workers) {
        if (worker.thread.joinable()) {
            worker.thread.join();
        }
    }

    FileTable::clearQueueShutdown();
}

void Interpreter::suspend() {
    {
        std::lock_guard<std::mutex> lock(suspendMutex_);
        suspended_ = true;
    }
    if (suspendCallback_)
        suspendCallback_();
}

void Interpreter::resume() {
    {
        std::lock_guard<std::mutex> lock(suspendMutex_);
        suspended_ = false;
    }
    suspendCv_.notify_all();
}

void Interpreter::waitWhileSuspended() {
    std::unique_lock<std::mutex> lock(suspendMutex_);
    suspendCv_.wait(lock, [&] { return !suspended_.load(); });
}

bool Interpreter::isSuspended() const {
    return suspended_.load();
}

std::vector<VariableInfo> Interpreter::getVariables() const {
    std::vector<VariableInfo> vars;

    // Walk the scope stack from current to global
    const Scope* scope = &scopes.current();
    while (scope) {
        for (const auto& [name, symbol] : scope->allSymbols()) {
            if (symbol.kind == SymbolKind::Variable || symbol.kind == SymbolKind::RefAlias) {
                VariableInfo info;
                info.name = name;
                info.scope = scope->name;

                const Value& val = symbol.resolve();
                if (val.isInt()) {
                    info.type = "INTEGER";
                    info.value = std::to_string(val.asInt());
                } else if (val.isFloat()) {
                    info.type = "REAL";
                    info.value = std::to_string(val.asFloat());
                } else if (val.isString()) {
                    info.type = "STRING";
                    info.value = "\"" + val.asString() + "\"";
                } else if (val.isArray()) {
                    const ArrayData& arr = val.asArray();
                    info.type = "ARRAY";
                    info.value = "[" + std::to_string(arr.elements.size()) + " elements]";
                } else {
                    info.type = "UNKNOWN";
                    info.value = "?";
                }

                vars.push_back(info);
            }
        }
        scope = scope->parent;
    }

    return vars;
}

std::vector<CallStackFrame> Interpreter::getCallStack() const {
    std::vector<CallStackFrame> stack;

    // Walk the scope stack from the current scope outward (top -> global)
    const Scope* scope = &scopes.current();
    while (scope) {
        CallStackFrame frame;
        frame.name = scope->name;
        if (scope->curproc) {
            frame.line = static_cast<int>(scope->curproc->lineNumber());
        } else if (curline) {
            frame.line = static_cast<int>(curline->lineNumber());
        }
        stack.push_back(std::move(frame));
        scope = scope->parent;
    }

    return stack;
}

void Interpreter::setBreakpoints(const std::vector<int>& lines) {
    breakpoints_.clear();
    for (int l : lines) {
        if (l > 0)
            breakpoints_.insert(l);
    }
}

void Interpreter::addBreakpoint(int line) {
    if (line > 0)
        breakpoints_.insert(line);
}

void Interpreter::removeBreakpoint(int line) {
    breakpoints_.erase(line);
}

bool Interpreter::hasBreakpoint(int line) const {
    return line > 0 && breakpoints_.count(line);
}

std::vector<int> Interpreter::breakpoints() const {
    std::vector<int> lines;
    lines.reserve(breakpoints_.size());
    for (int l : breakpoints_)
        lines.push_back(l);
    std::sort(lines.begin(), lines.end());
    return lines;
}

void Interpreter::checkBreakpoint() {
    if (isSingleStep())
        return;

    if (!curline)
        return;

    int ln = static_cast<int>(curline->lineNumber());
    if (ln <= 0)
        return;

    // Only suspend once per visit to a line.
    if (lastBreakpointLine_ != 0 && lastBreakpointLine_ != ln)
        lastBreakpointLine_ = 0;

    if (ln == lastBreakpointLine_)
        return;

    if (hasBreakpoint(ln)) {
        lastBreakpointLine_ = ln;
        suspend();
        waitWhileSuspended();
    }
}

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

        // Assign sequential file line number, stripping any legacy COMAL number
        if (!cl->lineData()) {
            cl->setLineData(new ComalLineData(line_count));
        } else {
            cl->lineData()->lineno = line_count;
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

// ── loadSource ──────────────────────────────────────────────────────────

void Interpreter::loadSource(const std::string& source) {
    std::istringstream stream(source);
    ComalLine* tail = nullptr;
    std::string text;
    int line_count = 0;

    while (std::getline(stream, text)) {
        line_count++;

        if (text.empty() || text.find_first_not_of(" \t\r\n") == std::string::npos)
            continue;

        char errbuf[256] = {};
        int errpos = 0;

        ComalLine* cl = comal_parse_line_modern(text.c_str(),
                                                 errbuf, sizeof(errbuf), &errpos);
        if (!cl) {
            std::string msg = "Parse error at line " +
                              std::to_string(line_count) + ": " + errbuf;
            throw ComalError(ErrorCode::Scan, msg);
        }

        if (!cl->lineData()) {
            cl->setLineData(new ComalLineData(line_count));
        } else {
            cl->lineData()->lineno = line_count;
        }

        if (!progroot) {
            progroot = cl;
        } else if (tail) {
            tail->setNext(cl);
        }
        tail = cl;
    }

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

            if (!is_short) {
                // EXTERNAL PROC/FUNC declarations have no body — don't push
                if (rule->is_proc) {
                    const auto& pf = line->asProcFunc();
                    if (pf.external) {
                        // No body to match — skip
                        continue;
                    }
                }
                // TRAP ESC+/- is a simple statement, not a block
                if (cmd == StatementType::Trap) {
                    const auto& tr = line->asTrap();
                    if (tr.esc != 0) continue;
                }
                stk.push({rule->pushes, line});
            }
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
    stopSpawnedWorkers();

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

    // A previous run or worker shutdown may have requested an interrupt.
    // Clear it here so each fresh run starts from a clean cancellation state.
    interrupt_.reset();
    FileTable::clearQueueShutdown();

    // Reset breakpoint tracking (line-based breakpoints persist but should
    // only trigger once per line visit).
    lastBreakpointLine_ = 0;
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
    stopSpawnedWorkers();
    files.closeAll();
}

// ── executeDirect ───────────────────────────────────────────────────────

void Interpreter::executeDirect(const std::string& command) {
    char errbuf[256] = {};
    int errpos = 0;

    ComalLine* cl = comal_parse_line_modern(command.c_str(),
                                             errbuf, sizeof(errbuf), &errpos);
    if (!cl) {
        throw ComalError(ErrorCode::Scan,
            std::string("Parse error: ") + errbuf);
    }

    execLine(*this, cl);
}

// ── I/O ─────────────────────────────────────────────────────────────────

void Interpreter::print(const std::string& s) {
    if (selOutput != 0 && files.isOpen(selOutput)) {
        files.writeValue(selOutput, Value(s));
    } else if (selOutputFile_) {
        *selOutputFile_ << s;
        selOutputFile_->flush();
    } else {
        io_->print(s);
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

    if (selInputFile_) {
        std::string line;
        if (!std::getline(*selInputFile_, line))
            return "";
        return line;
    }

    return io_->readLine();
}

void Interpreter::clearScreen() {
    io_->clearScreen();
}

void Interpreter::setCursor(int row, int col) {
    io_->setCursor(row, col);
}

} // namespace comal::runtime
