#pragma once

#include "comal_io.h"

#include <QObject>
#include <QString>
#include <QMutex>
#include <QWaitCondition>
#include <string>

/// Qt-signal-based I/O backend for the GUI.
///
/// The interpreter runs on a worker thread.  This class emits signals
/// (queued connection → GUI thread) for output and blocks the worker
/// thread on a QWaitCondition when input is needed.
///
/// The GUI connects to the signals and calls provideInput() when the
/// user enters a line in the Direct Command panel.
class QtIO : public QObject, public comal::runtime::IOInterface {
    Q_OBJECT

public:
    explicit QtIO(QObject *parent = nullptr);

    // -- IOInterface (called on the worker thread) --------------------
    void print(const std::string& text) override;
    std::string readLine() override;
    void clearScreen() override;
    void setCursor(int row, int col) override;

    // -- Called from the GUI thread -----------------------------------
    /// Supply the input line that readLine() is waiting for.
    void provideInput(const QString &line);

signals:
    /// Emitted when the runtime calls print().
    void textOutput(const QString &text);

    /// Emitted when the runtime calls clearScreen() (PAGE).
    void screenCleared();

    /// Emitted when the runtime calls setCursor() (CURSOR).
    void cursorMoved(int row, int col);

    /// Emitted when the runtime needs a line of input.
    void inputRequested();

private:
    QMutex          inputMutex_;
    QWaitCondition  inputReady_;
    QString         inputLine_;
    bool            inputAvailable_{false};
};
