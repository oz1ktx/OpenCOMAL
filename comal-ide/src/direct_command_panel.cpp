#include "direct_command_panel.h"

#include <QVBoxLayout>
#include <QTextEdit>
#include <QTextCursor>
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
    // Use insertPlainText to avoid QTextEdit::append() adding a new paragraph
    QTextCursor cursor = output_->textCursor();
    cursor.movePosition(QTextCursor::End);
    cursor.insertText(text, QTextCharFormat());  // explicit default format
    output_->setTextCursor(cursor);
    output_->ensureCursorVisible();
}

void DirectCommandPanel::onCommandEntered()
{
    QString cmd = input_->text();
    if (cmd.isEmpty()) return;

    // Don't echo "> cmd" when program is waiting for input —
    // echoInput() handles that case
    if (!inputForProgram_)
        appendOutput("> " + cmd + "\n");

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
    // Show the prompt in the input line label
    if (!prompt.isEmpty())
        promptLabel_->setText(prompt);
    else
        promptLabel_->setText(tr(">"));

    // Insert a solid block marker (█) in the output at the current position
    QTextCursor cursor = output_->textCursor();
    cursor.movePosition(QTextCursor::End);
    markerPos_ = cursor.position();

    QTextCharFormat markerFmt;
    markerFmt.setForeground(QColor(0, 120, 215));  // blue marker
    cursor.insertText(QString::fromUtf8("\u2588"), markerFmt);

    output_->setTextCursor(cursor);
    output_->ensureCursorVisible();
}

void DirectCommandPanel::echoInput(const QString &text)
{
    // Replace the block marker with the actual input text
    if (markerPos_ >= 0) {
        QTextCursor cursor = output_->textCursor();
        cursor.setPosition(markerPos_);
        cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, 1);
        cursor.removeSelectedText();

        QTextCharFormat inputFmt;
        inputFmt.setForeground(QColor(0, 120, 215));  // blue for user input
        cursor.insertText(text + "\n", inputFmt);

        // Reset to default format so subsequent output isn't blue
        cursor.setCharFormat(QTextCharFormat());
        output_->setTextCursor(cursor);

        markerPos_ = -1;
    }

    // Reset prompt label
    promptLabel_->setText(tr(">"));

    output_->ensureCursorVisible();
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
