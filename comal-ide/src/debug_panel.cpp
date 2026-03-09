#include "debug_panel.h"

#include <QVBoxLayout>
#include <QTabWidget>
#include <QTreeWidget>
#include <QHeaderView>

DebugPanel::DebugPanel(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    tabs_ = new QTabWidget(this);

    // Variables / Watch tab
    variables_ = new QTreeWidget;
    variables_->setHeaderLabels({tr("Name"), tr("Type"), tr("Value")});
    variables_->header()->setStretchLastSection(true);
    // Placeholder data
    auto *item1 = new QTreeWidgetItem({"i", "INT", "7"});
    auto *item2 = new QTreeWidgetItem({"name$", "STRING", "\"Alice\""});
    auto *item3 = new QTreeWidgetItem({"total#", "FLOAT", "3.14159"});
    variables_->addTopLevelItem(item1);
    variables_->addTopLevelItem(item2);
    variables_->addTopLevelItem(item3);
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
