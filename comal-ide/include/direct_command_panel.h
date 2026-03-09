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
    void setInputEnabled(bool enabled);

signals:
    void lineEntered(const QString &line);

private slots:
    void onCommandEntered();
    void showOutputContextMenu(const QPoint &pos);
    void clearOutput();
    void saveOutput();

private:
    QTextEdit *output_;
    QLineEdit *input_;
};
