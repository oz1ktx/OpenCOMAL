#include "run_worker.h"
#include "qt_io.h"
#include "comal_interpreter.h"
#include "comal_error.h"

using namespace comal::runtime;

RunWorker::RunWorker(QObject *parent)
    : QThread(parent)
    , interp_(std::make_unique<Interpreter>())
    , io_(new QtIO)          // will be owned by Interpreter via unique_ptr
{
    // Hand the QtIO to the interpreter (transfers ownership)
    interp_->setIO(std::unique_ptr<IOInterface>(io_));
}

RunWorker::~RunWorker()
{
    requestStop();
    wait();
}

void RunWorker::setSource(const QString &source)
{
    source_ = source;
}

void RunWorker::requestStop()
{
    interp_->interrupt().request();
}

void RunWorker::run()
{
    try {
        // Reset state for a fresh run
        interp_->resetRunState();

        // Load program from source text
        interp_->loadSource(source_.toStdString());

        interp_->run();
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
