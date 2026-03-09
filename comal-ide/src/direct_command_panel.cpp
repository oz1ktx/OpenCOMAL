#include "direct_command_panel.h"

#include <QVBoxLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QApplication>
#include <QClipboard>

DirectCommandPanel::DirectCommandPanel(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(2, 2, 2, 2);

    // Read-only output area
    output_ = new QTextEdit(this);
    output_->setReadOnly(true);
    output_->setFont(QFont("Monospace", 10));
    output_->setPlaceholderText(tr("Program output appears here..."));
    output_->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(output_, &QTextEdit::customContextMenuRequested,
            this,    &DirectCommandPanel::showOutputContextMenu);
    layout->addWidget(output_, /*stretch=*/1);

    // Command input line
    auto *inputLayout = new QHBoxLayout;
    auto *prompt = new QLabel(tr(">"), this);
    prompt->setFont(QFont("Monospace", 10));
    input_ = new QLineEdit(this);
    input_->setFont(QFont("Monospace", 10));
    input_->setPlaceholderText(tr("Enter COMAL command..."));
    inputLayout->addWidget(prompt);
    inputLayout->addWidget(input_);
    layout->addLayout(inputLayout);

    connect(input_, &QLineEdit::returnPressed,
            this,   &DirectCommandPanel::onCommandEntered);

    // Welcome message
    appendOutput("OpenCOMAL Direct Command\nReady.\n");
}

void DirectCommandPanel::appendOutput(const QString &text)
{
    output_->append(text);
}

void DirectCommandPanel::onCommandEntered()
{
    QString cmd = input_->text();
    if (cmd.isEmpty()) return;

    appendOutput("> " + cmd);
    input_->clear();
    emit lineEntered(cmd);
}

void DirectCommandPanel::setInputEnabled(bool enabled)
{
    input_->setEnabled(enabled);
    if (enabled)
        input_->setFocus();
}

void DirectCommandPanel::showOutputContextMenu(const QPoint &pos)
{
    QMenu menu(this);

    QAction *copyAct = menu.addAction(tr("&Copy"));
    copyAct->setShortcut(QKeySequence::Copy);
    copyAct->setEnabled(output_->textCursor().hasSelection());
    connect(copyAct, &QAction::triggered, output_, &QTextEdit::copy);

    QAction *selectAllAct = menu.addAction(tr("Select &All"));
    selectAllAct->setShortcut(QKeySequence::SelectAll);
    selectAllAct->setEnabled(!output_->toPlainText().isEmpty());
    connect(selectAllAct, &QAction::triggered, output_, &QTextEdit::selectAll);

    menu.addSeparator();

    QAction *clearAct = menu.addAction(tr("C&lear"));
    clearAct->setEnabled(!output_->toPlainText().isEmpty());
    connect(clearAct, &QAction::triggered, this, &DirectCommandPanel::clearOutput);

    menu.addSeparator();

    QAction *saveAct = menu.addAction(tr("&Save Output..."));
    saveAct->setEnabled(!output_->toPlainText().isEmpty());
    connect(saveAct, &QAction::triggered, this, &DirectCommandPanel::saveOutput);

    menu.exec(output_->mapToGlobal(pos));
}

void DirectCommandPanel::clearOutput()
{
    output_->clear();
}

void DirectCommandPanel::saveOutput()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Save Output"),
                                                QString(), tr("Text Files (*.txt);;All Files (*)"));
    if (path.isEmpty()) return;

    QFile file(path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        file.write(output_->toPlainText().toUtf8());
    }
}
