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
    callStack_->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(callStack_, &QTreeWidget::itemActivated, this, [this](QTreeWidgetItem *item, int) {
        if (!item) return;
        int line = item->data(0, Qt::UserRole).toInt();
        if (line > 0)
            emit frameActivated(line);
    });
    tabs_->addTab(callStack_, tr("Call Stack"));

    // Breakpoints tab
    breakpoints_ = new QTreeWidget;
    breakpoints_->setHeaderLabels({tr("File"), tr("Line"), tr("Condition")});
    breakpoints_->header()->setStretchLastSection(true);
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

void DebugPanel::updateCallStack(const QVariantList &frames)
{
    callStack_->clear();
    int index = 0;
    for (const QVariant &frame : frames) {
        QVariantMap frameMap = frame.toMap();
        QString name = frameMap["name"].toString();
        int line = frameMap["line"].toInt();
        QString location = QString("line %1").arg(line);
        auto *item = new QTreeWidgetItem({QString("#%1 %2").arg(index).arg(name), location});
        item->setData(0, Qt::UserRole, line);
        // Bold the current frame (top of stack)
        if (index == 0) {
            QFont font = item->font(0);
            font.setBold(true);
            item->setFont(0, font);
            item->setFont(1, font);
        }
        callStack_->addTopLevelItem(item);
        index++;
    }
}

void DebugPanel::updateBreakpoints(const QString &filePath, const QVector<int> &lines)
{
    breakpoints_->clear();
    for (int line : lines) {
        auto *item = new QTreeWidgetItem({filePath, QString::number(line), QString()});
        breakpoints_->addTopLevelItem(item);
    }
}
