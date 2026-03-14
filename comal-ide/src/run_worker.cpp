#include "run_worker.h"
#include "qt_io.h"
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
    // Hand the QtIO to the interpreter (transfers ownership)
    interp_->setIO(std::unique_ptr<IOInterface>(io_));

    // Scene-change callback: emit signal (queued to GUI thread)
    interp_->setSceneChangedCallback([this]() {
        emit sceneChanged();
    });

    // Suspended callback: emitted when the interpreter pauses (BREAK/step)
    interp_->setSuspendCallback([this]() {
        int line = 0;
        if (interp_->curline)
            line = interp_->curline->lineNumber();
        emit suspended(line);

        // Collect variables for debug panel
        auto vars = interp_->getVariables();
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
        auto stack = interp_->getCallStack();
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
    requestStop();
    wait();
}

void RunWorker::setSource(const QString &source)
{
    source_ = source;
    directCmd_.clear();
}

void RunWorker::setDirectCommand(const QString &command)
{
    directCmd_ = command;
    source_.clear();
}

void RunWorker::setGraphicsScene(comal::graphics::Scene* scene)
{
    interp_->setGraphicsScene(scene);
}

void RunWorker::requestStop()
{
    // If we're in single-step mode, stop stepping so we don't re-enter suspend.
    interp_->setSingleStep(false);

    // Ensure we wake up if suspended (break mode) so the interrupt can be processed.
    interp_->resume();
    if (io_)
        io_->provideInput("");
    interp_->interrupt().request();
}

void RunWorker::requestBreak()
{
    // Request a cooperative pause. If the interpreter is currently blocked
    // waiting for input, wake it so it can reach the suspend point and pause.
    interp_->suspend();
    if (io_)
        io_->provideInput("");
}

void RunWorker::requestContinue()
{
    interp_->resume();
}

void RunWorker::setSingleStep(bool enable)
{
    interp_->setSingleStep(enable);
}

bool RunWorker::isSuspended() const
{
    return interp_->isSuspended();
}

const comal::graphics::Scene& RunWorker::graphicsScene() const
{
    return interp_->graphicsScene();
}

void RunWorker::run()
{
    try {
        if (!directCmd_.isEmpty()) {
            // Direct command mode: parse and execute a single line
            interp_->executeDirect(directCmd_.toStdString());
        } else {
            // Full program mode
            interp_->resetRunState();
            interp_->loadSource(source_.toStdString());
            interp_->run();
        }
        emit finished();
    } catch (const StopSignal&) {
        emit finished();
    } catch (const EndSignal&) {
        emit finished();
    } catch (const EscapeSignal&) {
        emit finished();
    } catch (const ComalError &e) {
        emit errorOccurred(QString::fromStdString(e.what()),
                           static_cast<int>(e.line()));
    } catch (const std::exception &e) {
        emit errorOccurred(QString::fromUtf8(e.what()), 0);
    }
}
