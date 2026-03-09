#pragma once

#include <QWidget>

class QTextEdit;
class QLineEdit;

// Combined output log + command input (REPL).
// Upper area: read-only output (PRINT, errors).
// Lower area: single-line input for direct COMAL commands.
class DirectCommandPanel : public QWidget {
    Q_OBJECT

public:
    explicit DirectCommandPanel(QWidget *parent = nullptr);

    void appendOutput(const QString &text);

private slots:
    void onCommandEntered();

private:
    QTextEdit *output_;
    QLineEdit *input_;
};
