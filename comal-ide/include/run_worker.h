#pragma once

#include <QThread>
#include <QString>
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

signals:
    /// Emitted when execution finishes normally.
    void finished();

    /// Emitted when execution ends with an error.
    void errorOccurred(const QString &message, int lineNumber);

    /// Emitted when the graphics scene has changed (DRAW executed).
    void sceneChanged();

protected:
    void run() override;

private:
    std::unique_ptr<comal::runtime::Interpreter> interp_;
    QtIO    *io_;       // owned by interp_ via setIO()
    QString  source_;
    QString  directCmd_;
};
