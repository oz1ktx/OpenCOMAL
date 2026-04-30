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
#include <unordered_set>
#include <condition_variable>
#include <mutex>
#include <thread>

#include "comal_value.h"
#include "comal_scope.h"
#include "comal_file_io.h"
#include "comal_error.h"
#include "comal_interrupt.h"
#include "comal_io.h"
#include "comal_ast_modern.h"
#include "comal_scene_model.h"
#include "comal_graphics_commands.h"

namespace comal::sound { class Engine; }

namespace comal::runtime {

// ── Variable info for debugging ─────────────────────────────────────────

/// Information about a variable for the debug panel.
struct VariableInfo {
    std::string name;
    std::string type;      // "INTEGER", "REAL", "STRING", "ARRAY", etc.
    std::string value;     // string representation of the value
    std::string scope;     // scope name (e.g. "GLOBAL", "MAIN", procedure name)
};

/// One frame in the call stack (for the debug panel).
struct CallStackFrame {
    std::string name;      // e.g. PROC/FUNC name or "GLOBAL"
    int line{0};           // line number of proc definition (or current line)
};

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

    // Suspend/Resume support
    void suspend();
    void resume();
    bool isSuspended() const;
    // Wait while suspended (for use in execSeq)
    void waitWhileSuspended();

    /// Get all current variables for debugging (collects from scope stack).
    std::vector<VariableInfo> getVariables() const;

    /// Get the current call stack for debugging (top frame first).
    std::vector<CallStackFrame> getCallStack() const;

    // ── I/O interface (replaceable) ─────────────────────────────────────

    /// The pluggable I/O backend.  Defaults to TerminalIO (stdout/stdin).
    /// The GUI replaces this with a Qt-signal-based implementation.
    IOInterface& io() { return *io_; }

    /// Replace the I/O backend.  Takes ownership.
    void setIO(std::unique_ptr<IOInterface> io) { io_ = std::move(io); }

    // ── Graphics scene (for DRAW commands) ───────────────────────────────

    /// The graphics scene model.  DRAW commands modify this.
    comal::graphics::Scene& graphicsScene() { return *gfxScene_; }
    const comal::graphics::Scene& graphicsScene() const { return *gfxScene_; }

    /// Use an external scene (e.g. persistent across direct commands).
    /// The caller retains ownership.  Pass nullptr to revert to internal.
    void setGraphicsScene(comal::graphics::Scene* s) {
        gfxScene_ = s ? s : &defaultScene_;
    }

    /// The graphics command registry.
    const comal::graphics::CommandRegistry& graphicsRegistry() const { return gfxRegistry_; }

    /// Set a callback to be invoked after each DRAW command executes.
    /// The GUI uses this to trigger re-rendering of the graphics panel.
    void setSceneChangedCallback(std::function<void()> cb) { sceneChangedCb_ = std::move(cb); }

    /// Get the current scene-changed callback (e.g. to forward to spawn workers).
    const std::function<void()>& sceneChangedCallback() const { return sceneChangedCb_; }

    /// Set a callback to be invoked when execution is suspended (BREAK / step).
    void setSuspendCallback(std::function<void()> cb) { suspendCallback_ = std::move(cb); }

    /// Notify that the scene has changed (called by executor after DRAW).
    void notifySceneChanged() { if (sceneChangedCb_) sceneChangedCb_(); }

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
    ///
    /// This also supports the IDE "Break" button by waiting while the
    /// interpreter is suspended.
    void checkInterrupt() {
        interrupt_.check();
        if (isSuspended())
            waitWhileSuspended();
    }

    /// Single-step mode: pause after each statement execution.
    /// Used by IDE "Step Into" for debugging.
    void setSingleStep(bool enable) { singleStep_ = enable; }
    bool isSingleStep() const { return singleStep_; }

    /// Breakpoints (line numbers) for debugging.
    void setBreakpoints(const std::vector<int>& lines);
    void addBreakpoint(int line);
    void removeBreakpoint(int line);
    bool hasBreakpoint(int line) const;
    std::vector<int> breakpoints() const;

    /// Called from execSeq to check for a breakpoint on the current line.
    /// If a breakpoint is hit, this suspends execution once (until resume).
    void checkBreakpoint();

    /// Mark this interpreter as running in SPAWN-restricted mode.
    /// In this mode, routine calls are limited to CLOSED PROC/FUNC routines.
    void setSpawnRestricted(bool enabled) { spawnRestricted_ = enabled; }
    bool isSpawnRestricted() const { return spawnRestricted_; }

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

    /// Register a spawned worker thread for lifecycle management.
    void registerSpawnWorker(std::shared_ptr<Interpreter> worker,
                             std::thread thread);

    /// Join all spawned workers.
    ///
    /// When requestInterrupt is true, workers are first asked to cancel via
    /// interrupt() and queue shutdown notification. Use false for graceful
    /// shutdown at normal program completion.
    void stopSpawnedWorkers(bool requestInterrupt = true);

    /// Get this interpreter's sound engine, creating it on first use.
    comal::sound::Engine& soundEngine();

private:
    /// Interrupt controller instance.
    InterruptController interrupt_;

    // Suspend state (atomic for thread safety)
    std::atomic<bool> suspended_{false};
    std::condition_variable suspendCv_;
    mutable std::mutex suspendMutex_;

    /// Single-step mode flag.
    bool singleStep_{false};

    /// True when this interpreter is a SPAWN worker.
    bool spawnRestricted_{false};

    /// Breakpoints (line numbers).
    std::unordered_set<int> breakpoints_;
    /// The last line that caused a breakpoint suspension.
    int lastBreakpointLine_{0};

    /// I/O backend (owned).  Defaults to TerminalIO.
    std::unique_ptr<IOInterface> io_;

    /// Storage for parsed lines (owns the ParseTree objects).
    std::vector<std::unique_ptr<ParseTree>> trees_;

    /// Graphics scene model and command registry.
    comal::graphics::Scene defaultScene_;       // internal default (CLI use)
    comal::graphics::Scene* gfxScene_{&defaultScene_};  // active scene
    comal::graphics::CommandRegistry gfxRegistry_;
    std::function<void()> sceneChangedCb_;

    /// Called when execution is suspended (break/step).
    std::function<void()> suspendCallback_;

    struct SpawnWorker {
        std::shared_ptr<Interpreter> interp;
        std::thread thread;
    };
    std::mutex spawnedWorkersMutex_;
    std::vector<SpawnWorker> spawnedWorkers_;

    /// Interpreter-owned sound engine (lazy initialized).
    std::unique_ptr<comal::sound::Engine> soundEngine_;

    /// Build the global procedure table from the program.
    void buildProcTable();
};

} // namespace comal::runtime

#endif // COMAL_INTERPRETER_H
