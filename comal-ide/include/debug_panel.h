#pragma once

#include <QWidget>
#include <QVariantList>

class QTreeWidget;
class QTabWidget;

// Debug panel: variable watch, call stack, breakpoints.
class DebugPanel : public QWidget {
    Q_OBJECT

public:
    explicit DebugPanel(QWidget *parent = nullptr);

public slots:
    void updateVariables(const QVariantList &variables);

private:
    QTabWidget  *tabs_;
    QTreeWidget *variables_;
    QTreeWidget *callStack_;
    QTreeWidget *breakpoints_;
};
