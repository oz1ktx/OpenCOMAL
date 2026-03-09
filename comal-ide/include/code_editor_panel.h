#pragma once

#include <QWidget>

class QsciScintilla;
class QTabWidget;

// Multi-tab code editor using QScintilla.
// Central widget of the main window.
class CodeEditorPanel : public QWidget {
    Q_OBJECT

public:
    explicit CodeEditorPanel(QWidget *parent = nullptr);

    QsciScintilla *currentEditor() const;
    void newTab(const QString &title = "Untitled");
    void openFile(const QString &filePath);
    QString currentFilePath() const;

private:
    QTabWidget    *tabs_;
    QsciScintilla *createEditor();
};
