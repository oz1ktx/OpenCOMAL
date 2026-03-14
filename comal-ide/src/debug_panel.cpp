#include "debug_panel.h"

#include <QVBoxLayout>
#include <QTabWidget>
#include <QTreeWidget>
#include <QHeaderView>
#include <QVariantMap>

DebugPanel::DebugPanel(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    tabs_ = new QTabWidget(this);

    // Variables / Watch tab
    variables_ = new QTreeWidget;
    variables_->setHeaderLabels({tr("Name"), tr("Type"), tr("Value"), tr("Scope")});
    variables_->header()->setStretchLastSection(true);
    // Remove placeholder data - will be populated dynamically
    tabs_->addTab(variables_, tr("Variables"));

    // Call Stack tab
    callStack_ = new QTreeWidget;
    callStack_->setHeaderLabels({tr("Frame"), tr("Location")});
    callStack_->header()->setStretchLastSection(true);
    auto *frame0 = new QTreeWidgetItem({"#0", "calculate_sum (line 25)"});
    auto *frame1 = new QTreeWidgetItem({"#1", "main (line 10)"});
    callStack_->addTopLevelItem(frame0);
    callStack_->addTopLevelItem(frame1);
    tabs_->addTab(callStack_, tr("Call Stack"));

    // Breakpoints tab
    breakpoints_ = new QTreeWidget;
    breakpoints_->setHeaderLabels({tr("File"), tr("Line"), tr("Condition")});
    breakpoints_->header()->setStretchLastSection(true);
    auto *bp1 = new QTreeWidgetItem({"sample.lst", "25", ""});
    auto *bp2 = new QTreeWidgetItem({"sample.lst", "42", "i > 5"});
    breakpoints_->addTopLevelItem(bp1);
    breakpoints_->addTopLevelItem(bp2);
    tabs_->addTab(breakpoints_, tr("Breakpoints"));

    layout->addWidget(tabs_);
}

void DebugPanel::updateVariables(const QVariantList &variables)
{
    variables_->clear();
    for (const QVariant &var : variables) {
        QVariantMap varMap = var.toMap();
        QString name = varMap["name"].toString();
        QString type = varMap["type"].toString();
        QString value = varMap["value"].toString();
        QString scope = varMap["scope"].toString();
        auto *item = new QTreeWidgetItem({name, type, value, scope});
        variables_->addTopLevelItem(item);
    }
}
