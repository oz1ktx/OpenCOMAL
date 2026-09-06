#include "direct_command_panel.h"

#include <qtermwidget.h>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QApplication>
#include <QClipboard>

#include <unistd.h>

namespace {

void writeTerminalOutput(QTermWidget *terminal, const QString &text)
{
    const int fd = terminal->getPtySlaveFd();
    if (fd < 0) {
        return;
    }

    const QByteArray bytes = text.toUtf8();
    const char *data = bytes.constData();
    qsizetype remaining = bytes.size();
    while (remaining > 0) {
        const ssize_t written = ::write(fd, data, static_cast<size_t>(remaining));
        if (written <= 0) {
            return;
        }
        data += written;
        remaining -= written;
    }
}

} // namespace

DirectCommandPanel::DirectCommandPanel(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(2, 2, 2, 2);

    // Terminal-emulation output area. Teletype mode accepts data from the
    // application without starting a shell process.
    output_ = new QTermWidget(0, this);
    output_->setTerminalFont(QFont("Monospace", 10));
    output_->setScrollBarPosition(QTermWidget::ScrollBarRight);
    output_->setHistorySize(2000);
    output_->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(output_, &QTermWidget::customContextMenuRequested,
            this,    &DirectCommandPanel::showOutputContextMenu);
    output_->startTerminalTeletype();
    layout->addWidget(output_, /*stretch=*/1);

    // Command input line
    auto *inputLayout = new QHBoxLayout;
    promptLabel_ = new QLabel(tr(">"), this);
    promptLabel_->setFont(QFont("Monospace", 10));
    input_ = new QLineEdit(this);
    input_->setFont(QFont("Monospace", 10));
    input_->setPlaceholderText(tr("Enter COMAL command..."));
    inputLayout->addWidget(promptLabel_);
    inputLayout->addWidget(input_);
    layout->addLayout(inputLayout);

    connect(input_, &QLineEdit::returnPressed,
            this,   &DirectCommandPanel::onCommandEntered);

    // Welcome message
    appendOutput("OpenCOMAL Direct Command\nReady.\n");
}

void DirectCommandPanel::appendOutput(const QString &text)
{
    writeTerminalOutput(output_, text);
    output_->scrollToEnd();
}

void DirectCommandPanel::clearOutputPanel()
{
    clearOutput();
}

void DirectCommandPanel::focusInput()
{
    input_->setFocus();
}

void DirectCommandPanel::onCommandEntered()
{
    QString cmd = input_->text();
    if (cmd.isEmpty()) return;

    input_->clear();
    emit lineEntered(cmd);
}

void DirectCommandPanel::setInputEnabled(bool enabled)
{
    inputForProgram_ = enabled;
    // Input line is always enabled for direct commands;
    // this flag just tracks whether a running program wants input.
    if (enabled)
        input_->setFocus();
}

bool DirectCommandPanel::isInputForProgram() const
{
    return inputForProgram_;
}

void DirectCommandPanel::showInputMarker(const QString &prompt)
{
    if (!prompt.isEmpty())
        promptLabel_->setText(prompt);
    else
        promptLabel_->setText(tr(">"));
}

void DirectCommandPanel::echoInput(const QString &text)
{
    writeTerminalOutput(output_, text + "\r\n");
    output_->scrollToEnd();

    promptLabel_->setText(tr(">"));
}

void DirectCommandPanel::showOutputContextMenu(const QPoint &pos)
{
    QMenu menu(this);

    QAction *copyAct = menu.addAction(tr("&Copy"));
    copyAct->setShortcut(QKeySequence::Copy);
    copyAct->setEnabled(!output_->selectedText().isEmpty());
    connect(copyAct, &QAction::triggered, output_, &QTermWidget::copyClipboard);

    menu.addSeparator();

    QAction *clearAct = menu.addAction(tr("C&lear"));
    clearAct->setEnabled(true);
    connect(clearAct, &QAction::triggered, this, &DirectCommandPanel::clearOutput);

    menu.addSeparator();

    QAction *saveAct = menu.addAction(tr("&Save Output..."));
    saveAct->setEnabled(true);
    connect(saveAct, &QAction::triggered, this, &DirectCommandPanel::saveOutput);

    menu.exec(output_->mapToGlobal(pos));
}

void DirectCommandPanel::clearOutput()
{
    output_->clear();
    promptLabel_->setText(tr(">"));
}

void DirectCommandPanel::saveOutput()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Save Output"),
                                                QString(), tr("Text Files (*.txt);;All Files (*)"));
    if (path.isEmpty()) return;

    QFile file(path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        file.write(output_->selectedText(true).toUtf8());
    }
}

void DirectCommandPanel::applyFont(const QFont &font)
{
    output_->setTerminalFont(font);
    input_->setFont(font);
}
