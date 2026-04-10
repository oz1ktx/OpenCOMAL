#pragma once

#include <QWidget>

class QTextEdit;
class QLineEdit;
class QLabel;

// Combined output log + command input (REPL).
// Upper area: read-only output (PRINT, errors).
// Lower area: single-line input for direct COMAL commands.
class DirectCommandPanel : public QWidget {
    Q_OBJECT

public:
    explicit DirectCommandPanel(QWidget *parent = nullptr);

    void appendOutput(const QString &text);
    void clearOutputPanel();
    void focusInput();
    void setInputEnabled(bool enabled);
    bool isInputForProgram() const;

    /// Show the input block marker in the output and set prompt in input line.
    void showInputMarker(const QString &prompt);

    /// Echo user input into the output area (replacing the block marker).
    void echoInput(const QString &text);

    /// Apply font to output panel
    void applyFont(const QFont &font);

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
    QLabel    *promptLabel_;
    bool inputForProgram_{false};
    int  markerPos_{-1};    // character position of the block marker
};
