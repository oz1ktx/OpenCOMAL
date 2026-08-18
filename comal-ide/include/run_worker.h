#pragma once

#include <QThread>
#include <QString>
#include <QVariantList>
#include <memory>
#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <mutex>
#include <optional>
#include "language_profile.h"
#include "language_backend.h"

namespace comal::runtime { class Interpreter; }
namespace comal::graphics { class Scene; }
class QtIO;

/// Worker thread that executes source through the selected language backend.
/// Owns the Interpreter instance and its QtIO backend for COMAL mode.
class RunWorker : public QThread, public IBackendExecutionControl {
    Q_OBJECT

public:
    explicit RunWorker(QObject *parent = nullptr);
    ~RunWorker() override;

    /// Set an external (persistent) interpreter to use instead of creating a new one.
    /// If set before start(), this interpreter will be reused across multiple runs.
    void setExternalInterpreter(std::shared_ptr<comal::runtime::Interpreter> interp);

    /// Set the source code to execute (call before start()).
    void setSource(const QString &source);

    /// Set a single direct command to execute (call before start()).
    void setDirectCommand(const QString &command);

    /// Set the source language for execution mode selection.
    void setLanguage(LanguageId language);

    /// Set the current program path (used by non-COMAL backends).
    void setProgramPath(const QString &programPath);

    /// Use an external (persistent) graphics scene.
    void setGraphicsScene(comal::graphics::Scene* scene);

    /// Access the QtIO backend (for signal/slot wiring).
    QtIO *io() const { return io_; }

    /// Access the interpreter's graphics scene (for rendering after signals).
    const comal::graphics::Scene& graphicsScene() const;

    /// Request the interpreter to stop (thread-safe).
    void requestStop();

    /// Request the interpreter to break (pause execution).
    void requestBreak();

    /// Request the interpreter to continue after a break.
    void requestContinue();

    /// Return true if the interpreter is currently suspended.
    bool isSuspended() const;

    /// Enable or disable single-step mode.
    void setSingleStep(bool enable);

    /// Set line-number breakpoints for the next run.
    void setBreakpoints(const std::vector<int> &lines);

    /// Queue a coalesced scene-changed signal (thread-safe).
    void queueSceneChanged();

    /// Called by the GUI thread after rendering a sceneChanged notification.
    void onSceneRendered();

signals:
    /// Emitted when execution finishes normally.
    void finished();

    /// Emitted when execution ends with an error.
    void errorOccurred(const QString &message, int lineNumber);

    /// Emitted when the graphics scene has changed (DRAW executed).
    void sceneChanged();

    /// Emitted when execution is suspended (break/step).
    void suspended(int lineNumber);

    /// Emitted when execution is suspended, with current variables.
    void variablesChanged(const QVariantList &variables);

    /// Emitted when execution is suspended, with current call stack.
    void callStackChanged(const QVariantList &frames);

    /// Emitted when Z80 execution is suspended, with current register values.
    void z80RegistersChanged(const QVariantList &registers);

    /// Emitted when Z80 execution is suspended, with current flag values.
    void z80FlagsChanged(const QVariantList &flags);

    /// Emitted when Z80 execution is suspended, with a memory window.
    void z80MemoryChanged(const QVariantList &memoryRows);

    /// Emitted when Z80 execution is suspended, with disassembly around the PC.
    void z80DisassemblyChanged(const QVariantList &lines);

    // ── Assembly workflow signals (Z80Assembly only) ──
    
    /// Emitted when assembly phase begins for Z80 source.
    /// Parameter: source file path
    void assemblyStarted(const QString &sourcePath);

    /// Emitted when assembly phase completes successfully.
    /// Parameters: output (.COM) file path, listing file path, elapsed seconds, console output
    void assemblySucceeded(const QString &outputPath, const QString &listingPath, double elapsedSeconds, const QString &consoleOutput);

    /// Emitted when assembly phase fails.
    /// Parameters: error message, error line number (0 if unknown), console output
    void assemblyFailed(const QString &errorMessage, int errorLine, const QString &consoleOutput);

    /// Emitted when Z80 program produces runtime output (BDOS function 9, etc.)
    void z80RuntimeOutput(const QString &output);

protected:
    void run() override;

private:
    bool stopRequested() const override;
    bool shouldPause(std::uint16_t programCounter, int sourceLine) override;
    void waitUntilResumed(std::uint16_t programCounter,
                          int sourceLine,
                          const Z80DebugSnapshot& snapshot) override;
    void resetZ80ExecutionState();

    std::unique_ptr<comal::runtime::Interpreter> interp_;
    std::shared_ptr<comal::runtime::Interpreter> externalInterp_;
    QtIO    *io_;       // owned by interp_ via setIO()
    QString  source_;
    QString  directCmd_;
    QString  programPath_;
    LanguageId language_{LanguageId::Comal};
    std::atomic<bool> sceneSignalPending_{false};
    std::atomic<bool> sceneSignalDirty_{false};
    std::atomic<bool> z80StopRequested_{false};
    std::atomic<bool> z80BreakRequested_{false};
    std::atomic<bool> z80SingleStepRequested_{false};
    mutable std::mutex z80DebugMutex_;
    std::condition_variable z80DebugCv_;
    std::vector<int> z80Breakpoints_;
    bool z80Paused_{false};
    bool z80AllowOneInstruction_{false};
    int z80PausedLine_{0};
    std::uint16_t z80PausedAddress_{0};
    std::optional<std::uint16_t> z80SkipBreakpointAddress_;

    /// Get the active interpreter (external if set, otherwise default internal one).
    comal::runtime::Interpreter* getInterp() const {
        return externalInterp_ ? externalInterp_.get() : interp_.get();
    }
};
