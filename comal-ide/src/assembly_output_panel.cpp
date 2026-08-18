#include "assembly_output_panel.h"

#include <QTextEdit>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFont>
#include <QFileInfo>
#include <QMenu>
#include <QApplication>
#include <QClipboard>
#include <QFileDialog>
#include <QFile>
#include <QDateTime>

AssemblyOutputPanel::AssemblyOutputPanel(QWidget *parent)
    : QWidget(parent)
{
    auto *mainLayout = new QVBoxLayout(this);
    
    // Create tabbed widget for different output views
    tabs_ = new QTabWidget;
    
    // Listing tab
    listingEdit_ = new QTextEdit;
    listingEdit_->setReadOnly(true);
    listingEdit_->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(listingEdit_, &QTextEdit::customContextMenuRequested,
            this, &AssemblyOutputPanel::showContextMenu);
    tabs_->addTab(listingEdit_, tr("Listing"));
    
    // Diagnostics tab
    diagnosticsEdit_ = new QTextEdit;
    diagnosticsEdit_->setReadOnly(true);
    diagnosticsEdit_->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(diagnosticsEdit_, &QTextEdit::customContextMenuRequested,
            this, &AssemblyOutputPanel::showContextMenu);
    tabs_->addTab(diagnosticsEdit_, tr("Diagnostics"));
    
    // Statistics tab
    statisticsEdit_ = new QTextEdit;
    statisticsEdit_->setReadOnly(true);
    statisticsEdit_->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(statisticsEdit_, &QTextEdit::customContextMenuRequested,
            this, &AssemblyOutputPanel::showContextMenu);
    tabs_->addTab(statisticsEdit_, tr("Statistics"));
    
    mainLayout->addWidget(tabs_);
    
    // Bottom toolbar with actions
    auto *toolLayout = new QHBoxLayout;
    
    auto *clearBtn = new QPushButton(tr("Clear"));
    connect(clearBtn, &QPushButton::clicked, this, &AssemblyOutputPanel::onClearListing);
    toolLayout->addWidget(clearBtn);
    
    auto *saveBtn = new QPushButton(tr("Save Listing"));
    connect(saveBtn, &QPushButton::clicked, this, &AssemblyOutputPanel::onSaveListing);
    toolLayout->addWidget(saveBtn);
    
    toolLayout->addStretch();
    mainLayout->addLayout(toolLayout);
    
    setLayout(mainLayout);
}

void AssemblyOutputPanel::clearListing()
{
    listingEdit_->clear();
    diagnosticsEdit_->clear();
    statisticsEdit_->clear();
}

void AssemblyOutputPanel::displayListing(const QString &content)
{
    listingEdit_->setText(content);
    tabs_->setCurrentIndex(0);  // Switch to listing tab
}

void AssemblyOutputPanel::displayDiagnostics(const QString &diagnostics)
{
    diagnosticsEdit_->setText(diagnostics);
    if (!diagnostics.isEmpty()) {
        tabs_->setCurrentIndex(1);  // Switch to diagnostics tab
    }
}

void AssemblyOutputPanel::displayStatistics(const QString &filename, double elapsedSeconds,
                                            const QString &outputPath, int outputSize)
{
    QString stats;
    stats += tr("Assembly Statistics\n");
    stats += tr("═══════════════════════════════════\n\n");
    stats += tr("Source File:    %1\n").arg(QFileInfo(filename).fileName());
    stats += tr("Output File:    %1\n").arg(QFileInfo(outputPath).fileName());
    stats += tr("Output Size:    %1 bytes\n").arg(outputSize);
    stats += tr("Time:           %.3f seconds\n").arg(elapsedSeconds);
    
    if (elapsedSeconds > 0) {
        double rate = outputSize / (elapsedSeconds * 1024);  // KB/s
        stats += tr("Rate:           %.1f KB/s\n").arg(rate);
    }
    
    stats += tr("Timestamp:      %1\n").arg(QDateTime::currentDateTime().toString());
    
    statisticsEdit_->setText(stats);
}

void AssemblyOutputPanel::displayError(const QString &errorMessage)
{
    QString error;
    error += tr("❌ Assembly Failed\n");
    error += tr("═══════════════════════════════════\n\n");
    error += tr("Error: %1\n").arg(errorMessage);
    error += tr("Time: %1\n").arg(QDateTime::currentDateTime().toString());
    
    diagnosticsEdit_->setText(error);
    tabs_->setCurrentIndex(1);  // Switch to diagnostics tab
}

void AssemblyOutputPanel::applyFont(const QFont &font)
{
    listingEdit_->setFont(font);
    diagnosticsEdit_->setFont(font);
    statisticsEdit_->setFont(font);
}

void AssemblyOutputPanel::onClearListing()
{
    clearListing();
}

void AssemblyOutputPanel::onSaveListing()
{
    QString filename = QFileDialog::getSaveFileName(this,
        tr("Save Assembly Listing"), QString(),
        tr("Text Files (*.txt);;Listing Files (*.lst);;All Files (*)"));
    
    if (!filename.isEmpty()) {
        QFile file(filename);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            file.write(listingEdit_->toPlainText().toUtf8());
            file.close();
        }
    }
}

void AssemblyOutputPanel::showContextMenu(const QPoint &pos)
{
    QMenu menu;
    menu.addAction(tr("Copy"), [this]() {
        auto *current = tabs_->currentWidget();
        if (auto *edit = qobject_cast<QTextEdit*>(current)) {
            QApplication::clipboard()->setText(edit->toPlainText());
        }
    });
    menu.addAction(tr("Clear"), this, &AssemblyOutputPanel::onClearListing);
    menu.addSeparator();
    menu.addAction(tr("Select All"), [this]() {
        auto *current = tabs_->currentWidget();
        if (auto *edit = qobject_cast<QTextEdit*>(current)) {
            edit->selectAll();
        }
    });
    
    menu.exec(mapToGlobal(pos));
}
