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

    bool saveFile();
    bool saveFileAs();
    void closeCurrentTab();
    void highlightErrorLine(int line);
    void clearErrorHighlight();
    void formatSource();

signals:
    void cursorPositionChanged(int line, int col);

private slots:
    void onTabCloseRequested(int index);
    void onCurrentTabChanged(int index);

private:
    QTabWidget    *tabs_;
    QsciScintilla *createEditor();
    void connectEditorSignals(QsciScintilla *editor);
    bool maybeSaveTab(int index);
    void updateTabTitle(int index);

    static constexpr int ERROR_MARKER_ID = 1;
};
