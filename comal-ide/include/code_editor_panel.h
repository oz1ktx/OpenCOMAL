
#pragma once
#include <QWidget>
#include "comal_lsp_client.h"

class QsciScintilla;
class QTabWidget;

// Multi-tab code editor using QScintilla.
// Central widget of the main window.
class CodeEditorPanel : public QWidget {
    Q_OBJECT

public:
    void setLspClient(ComalLspClient *client);
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
    void highlightExecutionLine(int line);
    void clearExecutionHighlight();
    void formatSource();

    /// Toggle breakpoint at the current cursor line.
    void toggleBreakpointAtCurrentLine();
    QVector<int> breakpointsForCurrentFile() const;

    /// Apply font to all editor tabs
    void applyFontToAllEditors(const QFont &font);

signals:
    void cursorPositionChanged(int line, int col);
    void currentFileChanged(const QString &filePath);
    void keywordUnderCursorChanged(const QString &keyword);

    /// Emitted when breakpoints change for the current file.
    void breakpointsChanged(const QString &filePath, const QVector<int> &lines);

private slots:
    void onTabCloseRequested(int index);
    void onCurrentTabChanged(int index);

private:
    QTabWidget    *tabs_;
    QsciScintilla *createEditor();
    void connectEditorSignals(QsciScintilla *editor);
    bool maybeSaveTab(int index);
    void updateTabTitle(int index);

    // Breakpoints keyed by file path (tabs). The set contains 1-based line numbers.
    QMap<QString, QSet<int>> breakpoints_;

    // Helpers for breakpoint markers
    void toggleBreakpointAtLine(QsciScintilla *editor, int line);
    void applyBreakpointsToEditor(QsciScintilla *editor, const QString &filePath);
    QVector<int> breakpointsForFile(const QString &filePath) const;

    static constexpr int ERROR_MARKER_ID = 1;
    static constexpr int EXEC_MARKER_ID = 2;
    static constexpr int BREAKPOINT_MARKER_ID = 3;

    ComalLspClient *lspClient_ = nullptr; // Added member for LSP client
};
