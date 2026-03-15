#pragma once

#include <QWidget>
#include <QVariantList>
#include <QVector>

class QTreeWidget;
class QTabWidget;

// Debug panel: variable watch, call stack, breakpoints.
class DebugPanel : public QWidget {
    Q_OBJECT

public:
    explicit DebugPanel(QWidget *parent = nullptr);

public slots:
    void updateVariables(const QVariantList &variables);
    void updateCallStack(const QVariantList &frames);
    void updateBreakpoints(const QString &filePath, const QVector<int> &lines);

signals:
    /// Emitted when a call-stack frame is activated (double-clicked).
    void frameActivated(int lineNumber);

private:
    QTabWidget  *tabs_;
    QTreeWidget *variables_;
    QTreeWidget *callStack_;
    QTreeWidget *breakpoints_;
};
