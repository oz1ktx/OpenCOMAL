#include "run_worker.h"
#include "qt_io.h"
#include "language_backend.h"
#include "comal_interpreter.h"
#include "comal_error.h"
#include "comal_scene_model.h"
#include <QVariantMap>

using namespace comal::runtime;

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
    sceneSignalPending_.store(false, std::memory_order_release);
    sceneSignalDirty_.store(false, std::memory_order_release);
}

void RunWorker::setDirectCommand(const QString &command)
{
    directCmd_ = command;
    source_.clear();
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

void RunWorker::setGraphicsScene(comal::graphics::Scene* scene)
{
    getInterp()->setGraphicsScene(scene);
}

void RunWorker::requestStop()
{
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
    // Request a cooperative pause. If the interpreter is currently blocked
    // waiting for input, wake it so it can reach the suspend point and pause.
    getInterp()->suspend();
    if (io_)
        io_->provideInput("");
}

void RunWorker::requestContinue()
{
    getInterp()->resume();
}

void RunWorker::setSingleStep(bool enable)
{
    getInterp()->setSingleStep(enable);
}

void RunWorker::setBreakpoints(const std::vector<int> &lines)
{
    getInterp()->setBreakpoints(lines);
}

bool RunWorker::isSuspended() const
{
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
        BackendRunContext{getInterp(), source_, directCmd_, programPath_});

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
        emit finished();
        return;
    }

    if (!result.ok) {
        emit errorOccurred(result.errorMessage, result.errorLine);
        return;
    }

    emit finished();
}
