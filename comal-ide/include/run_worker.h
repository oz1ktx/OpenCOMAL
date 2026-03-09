#pragma once

#include <QThread>
#include <QString>
#include <memory>

namespace comal::runtime { class Interpreter; }
class QtIO;

/// Worker thread that runs the COMAL interpreter.
/// Owns the Interpreter instance and its QtIO backend.
class RunWorker : public QThread {
    Q_OBJECT

public:
    explicit RunWorker(QObject *parent = nullptr);
    ~RunWorker() override;

    /// Set the source code to execute (call before start()).
    void setSource(const QString &source);

    /// Access the QtIO backend (for signal/slot wiring).
    QtIO *io() const { return io_; }

    /// Request the interpreter to stop (thread-safe).
    void requestStop();

signals:
    /// Emitted when execution finishes normally.
    void finished();

    /// Emitted when execution ends with an error.
    void errorOccurred(const QString &message, int lineNumber);

protected:
    void run() override;

private:
    std::unique_ptr<comal::runtime::Interpreter> interp_;
    QtIO    *io_;       // owned by interp_ via setIO()
    QString  source_;
};
