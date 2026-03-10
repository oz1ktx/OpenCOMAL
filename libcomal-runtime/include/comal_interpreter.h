#ifndef COMAL_INTERPRETER_H
#define COMAL_INTERPRETER_H

/// @file comal_interpreter.h
/// The central runtime object.  Owns program lines, scope stack,
/// file table, DATA pointers, and execution state.
///
/// Usage:
///   Interpreter interp;
///   interp.loadFile("hello.lst");
///   interp.run();

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <random>
#include <memory>
#include <functional>
#include <unordered_map>

#include "comal_value.h"
#include "comal_scope.h"
#include "comal_file_io.h"
#include "comal_error.h"
#include "comal_interrupt.h"
#include "comal_io.h"
#include "comal_ast_modern.h"

namespace comal::runtime {

// ── Structure scan table ────────────────────────────────────────────────

/// Pairs of matching statement types (FOR↔ENDFOR, IF↔ENDIF, etc.)
/// Used by the structure scanner to link lineptr between matching pairs.
struct ScanEntry {
    StatementType cmd;
    StatementType leaves;       // what this pushes (the "end" it expects)
    StatementType expects1;     // what must be on the stack to match
    StatementType expects2;     // alternate match (or Empty)
    enum Flag { None = 0, ShortForm = 1, ProcFunc = 2, EProcFunc = 4,
                DataStat = 8, CaseEntry = 16, ExitStat = 32,
                RetryStat = 64 } flags;
};

// ── Interpreter ─────────────────────────────────────────────────────────

class Interpreter {
public:
    Interpreter();
    ~Interpreter();

    // ── Program loading ─────────────────────────────────────────────────

    /// Load a .lst text file: parse each numbered line into the AST.
    void loadFile(const std::string& path);

    /// Load program from a source string (multi-line).
    void loadSource(const std::string& source);

    /// Parse and insert a single line (as if typed at the editor).
    void addLine(const std::string& text);

    // ── Execution ───────────────────────────────────────────────────────

    /// Run the loaded program from the beginning.
    void run();

    /// Parse and execute a single direct command (e.g. PRINT 2+2).
    void executeDirect(const std::string& command);

    // ── I/O interface (replaceable) ─────────────────────────────────────

    /// The pluggable I/O backend.  Defaults to TerminalIO (stdout/stdin).
    /// The GUI replaces this with a Qt-signal-based implementation.
    IOInterface& io() { return *io_; }

    /// Replace the I/O backend.  Takes ownership.
    void setIO(std::unique_ptr<IOInterface> io) { io_ = std::move(io); }

    /// Write to the currently selected output.
    void print(const std::string& s);

    /// Write newline.
    void newline();

    /// Read a line from the currently selected input.
    std::string readLine(const std::string& prompt = "");

    /// Clear screen (PAGE command).  Delegates to IO backend.
    void clearScreen();

    /// Position cursor (CURSOR command).  Delegates to IO backend.
    void setCursor(int row, int col);

    // ── State (public for evaluator / executor access) ──────────────────

    /// The program: linked list of ComalLine* (first line).
    ComalLine* progroot{nullptr};

    /// Current line pointer (advances during execution).
    ComalLine* curline{nullptr};

    /// Scope stack (global + call frames).
    ScopeStack scopes;

    /// Open files.
    FileTable files;

    /// DATA pointer: current line and expression position.
    ComalLine*  dataLine{nullptr};
    ExpList*    dataExp{nullptr};

    /// Procedure table: name → ComalLine* of the PROC/FUNC definition.
    /// Built by the structure scanner.
    std::unordered_map<std::string, ComalLine*> procTable;

    /// Random number generator (seeded once at startup).
    std::mt19937 rng;

    /// Trace mode flag.
    bool trace{false};

    /// Interrupt controller — signal-safe, GUI-safe cancellation.
    /// CLI installs a SIGINT handler; GUI connects a Stop button.
    InterruptController& interrupt() noexcept { return interrupt_; }

    /// Check for pending interrupt (convenience wrapper).
    /// Call at loop iteration boundaries and in execSeq.
    void checkInterrupt() { interrupt_.check(); }

    /// Last error info (for ERR, ERR$, ERRLINE).
    ErrorCode lastError{ErrorCode::None};
    std::string lastErrorMsg;
    long lastErrorLine{0};

    /// SELECT OUTPUT/INPUT file number redirection.
    int64_t selOutput{0};   // 0 = default (IO backend)
    int64_t selInput{0};    // 0 = default (IO backend)

    /// SELECT OUTPUT/INPUT to a named file (string argument).
    /// When set, print() / readLine() write/read from these instead.
    std::unique_ptr<std::ofstream> selOutputFile_;
    std::unique_ptr<std::ifstream> selInputFile_;

    /// Return value stash — set by RETURN expr inside a FUNC.
    Value returnValue;

    // ── Structure scanner ───────────────────────────────────────────────

    /// Scan the program for structural validity and link lineptr
    /// between matching statement pairs (FOR↔ENDFOR, etc.).
    /// Also builds the procTable and links DATA chains.
    void structureScan();

    /// Find the first DATA line and set dataLine/dataExp.
    void initDataPointer();

    // ── Helpers for the executor ────────────────────────────────────────

    /// Look up a PROC/FUNC by name. Throws if not found.
    ComalLine* findRoutine(const std::string& name);

    /// Navigate to the next DATA line from the current position.
    void advanceData();

    /// Clear all runtime state (scopes, files, DATA) for a fresh run.
    void resetRunState();

private:
    /// Interrupt controller instance.
    InterruptController interrupt_;

    /// I/O backend (owned).  Defaults to TerminalIO.
    std::unique_ptr<IOInterface> io_;

    /// Storage for parsed lines (owns the ParseTree objects).
    std::vector<std::unique_ptr<ParseTree>> trees_;

    /// Build the global procedure table from the program.
    void buildProcTable();
};

} // namespace comal::runtime

#endif // COMAL_INTERPRETER_H
