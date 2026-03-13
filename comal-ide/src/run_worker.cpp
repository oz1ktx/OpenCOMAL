#include "run_worker.h"
#include "qt_io.h"
#include "comal_interpreter.h"
#include "comal_error.h"
#include "comal_scene_model.h"

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
    interp_->interrupt().request();
}

void RunWorker::requestBreak()
{
    interp_->suspend();
}

void RunWorker::requestContinue()
{
    interp_->resume();
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
