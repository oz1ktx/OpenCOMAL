#pragma once

#include <QThread>
#include <QString>
#include <QVariantList>
#include <memory>

namespace comal::runtime { class Interpreter; }
namespace comal::graphics { class Scene; }
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

    /// Set a single direct command to execute (call before start()).
    void setDirectCommand(const QString &command);

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

protected:
    void run() override;

private:
    std::unique_ptr<comal::runtime::Interpreter> interp_;
    QtIO    *io_;       // owned by interp_ via setIO()
    QString  source_;
    QString  directCmd_;
};
