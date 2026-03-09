#include "direct_command_panel.h"

#include <QVBoxLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>

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
    QString cmd = input_->text().trimmed();
    if (cmd.isEmpty()) return;

    appendOutput("> " + cmd);
    appendOutput("[stub: command execution not yet connected]");
    input_->clear();
}
