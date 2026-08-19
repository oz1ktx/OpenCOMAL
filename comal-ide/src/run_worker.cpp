#include "run_worker.h"
#include "qt_io.h"
#include "language_backend.h"
#include "comal_interpreter.h"
#include "comal_error.h"
#include "comal_scene_model.h"
#include <QVariantMap>
#include <algorithm>
#include <cctype>

using namespace comal::runtime;

namespace {

QString formatHex(std::uint16_t value, int width)
{
    return QString("%1").arg(value, width, 16, QChar('0')).toUpper();
}

QVariantList makeRegisterList(const Z80DebugSnapshot& snapshot)
{
    QVariantList list;
    for (const Z80DebugRegister& reg : snapshot.registers) {
        QVariantMap map;
        map["name"] = QString::fromStdString(reg.name);
        map["value"] = QString("%1h").arg(formatHex(reg.value, reg.width));
        list.append(map);
    }
    return list;
}

QVariantList makeFlagList(const Z80DebugSnapshot& snapshot)
{
    QVariantList list;
    for (const Z80DebugFlag& flag : snapshot.flags) {
        QVariantMap map;
        map["name"] = QString::fromStdString(flag.name);
        map["value"] = flag.value ? "1" : "0";
        list.append(map);
    }
    return list;
}

QVariantList makeMemoryRows(const Z80DebugSnapshot& snapshot)
{
    QVariantList rows;
    for (std::size_t offset = 0; offset < snapshot.memory.size(); offset += 16) {
        QString hexBytes;
        QString ascii;
        const std::uint16_t address =
            static_cast<std::uint16_t>(snapshot.memoryStart + static_cast<std::uint16_t>(offset));
        for (std::size_t i = 0; i < 16 && offset + i < snapshot.memory.size(); ++i) {
            const std::uint8_t byte = snapshot.memory[offset + i];
            if (!hexBytes.isEmpty()) {
                hexBytes += ' ';
            }
            hexBytes += formatHex(byte, 2);
            ascii += std::isprint(byte) ? QChar(byte) : QChar('.');
        }

        QVariantMap map;
        map["address"] = QString("%1h").arg(formatHex(address, 4));
        map["hex"] = hexBytes;
        map["ascii"] = ascii;
        rows.append(map);
    }
    return rows;
}

QVariantList makeDisassemblyRows(const Z80DebugSnapshot& snapshot)
{
    QVariantList rows;
    for (const Z80DisassemblyLine& line : snapshot.disassembly) {
        QStringList byteParts;
        for (std::uint8_t byte : line.bytes) {
            byteParts.push_back(formatHex(byte, 2));
        }
        QVariantMap map;
        map["address"] = QString("%1h").arg(formatHex(line.address, 4));
        map["bytes"] = byteParts.join(' ');
        map["instruction"] = QString::fromStdString(line.instruction);
        map["source"] = line.sourceLine > 0 ? QString("line %1").arg(line.sourceLine) : QString();
        map["current"] = line.current;
        rows.append(map);
    }
    return rows;
}

} // namespace

RunWorker::RunWorker(QObject *parent)
    : QThread(parent)
    , interp_(std::make_unique<Interpreter>())
    , io_(new QtIO)          // will be owned by Interpreter via unique_ptr
{
    // Hand the QtIO to the internal interpreter (transfers ownership)
    interp_->setIO(std::unique_ptr<IOInterface>(io_));

    // Scene-change callback: coalesced signal to prevent render flooding.
    interp_->setSceneChangedCallback([this]() {
        queueSceneChanged();
    });

    // Suspended callback: emitted when the interpreter pauses (BREAK/step)
    interp_->setSuspendCallback([this]() {
        int line = 0;
        if (getInterp()->curline)
            line = getInterp()->curline->lineNumber();
        emit suspended(line);

        // Collect variables for debug panel
        auto vars = getInterp()->getVariables();
        QVariantList varList;
        for (const auto& var : vars) {
            QVariantMap varMap;
            varMap["name"] = QString::fromStdString(var.name);
            varMap["type"] = QString::fromStdString(var.type);
            varMap["value"] = QString::fromStdString(var.value);
            varMap["scope"] = QString::fromStdString(var.scope);
            varList.append(varMap);
        }
        emit variablesChanged(varList);

        // Collect call stack for debug panel
        auto stack = getInterp()->getCallStack();
        QVariantList stackList;
        for (const auto &frame : stack) {
            QVariantMap frameMap;
            frameMap["name"] = QString::fromStdString(frame.name);
            frameMap["line"] = frame.line;
            stackList.append(frameMap);
        }
        emit callStackChanged(stackList);
    });
}

RunWorker::~RunWorker()
{
    if (isRunning()) {
        requestStop();
        wait();
    }
}

void RunWorker::setExternalInterpreter(std::shared_ptr<comal::runtime::Interpreter> interp)
{
    externalInterp_ = interp;
    if (externalInterp_) {
        externalInterp_->setSceneChangedCallback([this]() {
            queueSceneChanged();
        });
    }
    // Note: The external interpreter should already have a QtIO backend
    // configured by MainWindow before being passed here.
}

void RunWorker::queueSceneChanged()
{
    if (sceneSignalPending_.exchange(true, std::memory_order_acq_rel)) {
        sceneSignalDirty_.store(true, std::memory_order_release);
        return;
    }
    emit sceneChanged();
}

void RunWorker::onSceneRendered()
{
    if (sceneSignalDirty_.exchange(false, std::memory_order_acq_rel)) {
        emit sceneChanged();
        return;
    }
    sceneSignalPending_.store(false, std::memory_order_release);
}

void RunWorker::setSource(const QString &source)
{
    source_ = source;
    directCmd_.clear();
    resetZ80ExecutionState();
    sceneSignalPending_.store(false, std::memory_order_release);
    sceneSignalDirty_.store(false, std::memory_order_release);
}

void RunWorker::setDirectCommand(const QString &command)
{
    directCmd_ = command;
    source_.clear();
    resetZ80ExecutionState();
    sceneSignalPending_.store(false, std::memory_order_release);
    sceneSignalDirty_.store(false, std::memory_order_release);
}

void RunWorker::setLanguage(LanguageId language)
{
    language_ = language;
}

void RunWorker::setProgramPath(const QString &programPath)
{
    programPath_ = programPath;
}

void RunWorker::setCpmDrivePath(const QString &cpmDrivePath)
{
    cpmDrivePath_ = cpmDrivePath;
}

void RunWorker::setGraphicsScene(comal::graphics::Scene* scene)
{
    getInterp()->setGraphicsScene(scene);
}

void RunWorker::requestStop()
{
    if (language_ == LanguageId::Z80Assembly) {
        z80StopRequested_.store(true, std::memory_order_release);
        {
            std::lock_guard<std::mutex> lock(z80DebugMutex_);
            z80Paused_ = false;
        }
        z80DebugCv_.notify_all();
        return;
    }

    // If we're in single-step mode, stop stepping so we don't re-enter suspend.
    getInterp()->setSingleStep(false);

    // Ensure we wake up if suspended (break mode) so the interrupt can be processed.
    getInterp()->resume();
    if (io_)
        io_->provideInput("");
    getInterp()->interrupt().request();
}

void RunWorker::requestBreak()
{
    if (language_ == LanguageId::Z80Assembly) {
        z80BreakRequested_.store(true, std::memory_order_release);
        return;
    }

    // Request a cooperative pause. If the interpreter is currently blocked
    // waiting for input, wake it so it can reach the suspend point and pause.
    getInterp()->suspend();
    if (io_)
        io_->provideInput("");
}

void RunWorker::requestContinue()
{
    if (language_ == LanguageId::Z80Assembly) {
        {
            std::lock_guard<std::mutex> lock(z80DebugMutex_);
            if (!z80Paused_) {
                return;
            }
            z80Paused_ = false;
            z80AllowOneInstruction_ = true;
        }
        z80DebugCv_.notify_all();
        return;
    }

    getInterp()->resume();
}

void RunWorker::setSingleStep(bool enable)
{
    if (language_ == LanguageId::Z80Assembly) {
        z80SingleStepRequested_.store(enable, std::memory_order_release);
        return;
    }

    getInterp()->setSingleStep(enable);
}

void RunWorker::setBreakpoints(const std::vector<int> &lines)
{
    if (language_ == LanguageId::Z80Assembly) {
        std::lock_guard<std::mutex> lock(z80DebugMutex_);
        z80Breakpoints_ = lines;
        std::sort(z80Breakpoints_.begin(), z80Breakpoints_.end());
        z80Breakpoints_.erase(std::unique(z80Breakpoints_.begin(), z80Breakpoints_.end()),
                              z80Breakpoints_.end());
        return;
    }

    getInterp()->setBreakpoints(lines);
}

bool RunWorker::isSuspended() const
{
    if (language_ == LanguageId::Z80Assembly) {
        std::lock_guard<std::mutex> lock(z80DebugMutex_);
        return z80Paused_;
    }

    return getInterp()->isSuspended();
}

const comal::graphics::Scene& RunWorker::graphicsScene() const
{
    return getInterp()->graphicsScene();
}

void RunWorker::run()
{
    // Create backend using the factory based on language ID
    const auto backend = BackendFactory::createBackend(language_);
    if (!backend) {
        emit errorOccurred("Unsupported language selected.", 0);
        return;
    }

    // Emit assemblyStarted signal for Z80 assembly files
    const QString lowerPath = programPath_.toLower();
    if ((lowerPath.endsWith(".asm") || lowerPath.endsWith(".z80") || lowerPath.endsWith(".s")) 
        && language_ == LanguageId::Z80Assembly) {
        emit assemblyStarted(programPath_);
    }

    const BackendRunResult result = backend->run(
        BackendRunContext{getInterp(), source_, directCmd_, programPath_, cpmDrivePath_,
                          language_ == LanguageId::Z80Assembly ? this : nullptr});

    // Emit assembly signals if assembly was attempted (Z80 only)
    if (result.assemblyAttempted) {
        if (!result.assemblyOk) {
            emit assemblyFailed(result.errorMessage, result.errorLine, result.assemblyConsoleOutput);
            if (!result.ok) {
                emit errorOccurred(result.errorMessage, result.errorLine);
                return;
            }
        } else {
            emit assemblySucceeded(result.assemblyOutputPath, result.assemblyListingPath, 
                                   result.assemblyElapsedSeconds, result.assemblyConsoleOutput);
        }
    }

    if (result.finished) {
        // Emit Z80 runtime output if present
        if (!result.z80RuntimeOutput.isEmpty()) {
            emit z80RuntimeOutput(result.z80RuntimeOutput);
        }
        emit finished();
        return;
    }

    if (!result.ok) {
        emit errorOccurred(result.errorMessage, result.errorLine);
        return;
    }

    // Emit Z80 runtime output if present
    if (!result.z80RuntimeOutput.isEmpty()) {
        emit z80RuntimeOutput(result.z80RuntimeOutput);
    }

    emit finished();
}

bool RunWorker::stopRequested() const
{
    return z80StopRequested_.load(std::memory_order_acquire);
}

bool RunWorker::shouldPause(std::uint16_t programCounter, int sourceLine)
{
    std::lock_guard<std::mutex> lock(z80DebugMutex_);

    if (z80AllowOneInstruction_) {
        z80AllowOneInstruction_ = false;
        z80SkipBreakpointAddress_ = std::nullopt;
        return false;
    }

    if (z80BreakRequested_.exchange(false, std::memory_order_acq_rel)) {
        return true;
    }

    if (z80SingleStepRequested_.load(std::memory_order_acquire)) {
        return true;
    }

    if (sourceLine <= 0) {
        return false;
    }

    if (z80SkipBreakpointAddress_ && *z80SkipBreakpointAddress_ == programCounter) {
        z80SkipBreakpointAddress_ = std::nullopt;
        return false;
    }
    z80SkipBreakpointAddress_ = std::nullopt;

    return std::binary_search(z80Breakpoints_.begin(), z80Breakpoints_.end(), sourceLine);
}

void RunWorker::waitUntilResumed(std::uint16_t programCounter,
                                 int sourceLine,
                                 const Z80DebugSnapshot& snapshot)
{
    {
        std::unique_lock<std::mutex> lock(z80DebugMutex_);
        z80Paused_ = true;
        z80PausedAddress_ = programCounter;
        z80PausedLine_ = sourceLine;
        z80AllowOneInstruction_ = false;
    }

    emit suspended(sourceLine);
    emit variablesChanged({});
    emit callStackChanged({});
    emit z80RegistersChanged(makeRegisterList(snapshot));
    emit z80FlagsChanged(makeFlagList(snapshot));
    emit z80MemoryChanged(makeMemoryRows(snapshot));
    emit z80DisassemblyChanged(makeDisassemblyRows(snapshot));

    std::unique_lock<std::mutex> lock(z80DebugMutex_);
    z80DebugCv_.wait(lock, [this] {
        return !z80Paused_ || z80StopRequested_.load(std::memory_order_acquire);
    });
    if (!z80StopRequested_.load(std::memory_order_acquire)) {
        z80SkipBreakpointAddress_ = z80PausedAddress_;
    }
}

void RunWorker::resetZ80ExecutionState()
{
    z80StopRequested_.store(false, std::memory_order_release);
    z80BreakRequested_.store(false, std::memory_order_release);
    z80SingleStepRequested_.store(false, std::memory_order_release);
    {
        std::lock_guard<std::mutex> lock(z80DebugMutex_);
        z80Paused_ = false;
        z80AllowOneInstruction_ = false;
        z80PausedLine_ = 0;
        z80PausedAddress_ = 0;
        z80SkipBreakpointAddress_ = std::nullopt;
    }
    z80DebugCv_.notify_all();
}
