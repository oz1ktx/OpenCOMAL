#pragma once

#include <QWidget>

class QTreeWidget;
class QTabWidget;

// Debug panel: variable watch, call stack, breakpoints.
class DebugPanel : public QWidget {
    Q_OBJECT

public:
    explicit DebugPanel(QWidget *parent = nullptr);

private:
    QTabWidget  *tabs_;
    QTreeWidget *variables_;
    QTreeWidget *callStack_;
    QTreeWidget *breakpoints_;
};
