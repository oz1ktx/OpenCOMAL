
#pragma once
#include <QWidget>
#include <QHash>
#include <QMap>
#include <QSet>
#include <QStringList>
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
    QString filePathToUri(const QString &filePath) const;  // Convert plain path to file:// URI

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
    QString filePathForEditor(QsciScintilla *editor) const;
    QString lspUriForEditor(QsciScintilla *editor);
    void clearLspDiagnostics(QsciScintilla *editor);
    void applyLspDiagnostics(QsciScintilla *editor, const QString &filePath);
    QString diagnosticMessageForLine(const QString &filePath, int oneBasedLine) const;
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
    static constexpr int LSP_ERROR_MARKER_ID = 4;
    static constexpr int LSP_WARNING_MARKER_ID = 5;
    static constexpr int LSP_INFO_MARKER_ID = 6;

    // LSP diagnostics cached by file and line (1-based line numbers).
    QHash<QString, QMap<int, int>> lspSeverityByFile_;
    QHash<QString, QMap<int, QStringList>> lspMessagesByFile_;
    QHash<QsciScintilla *, QString> untitledUriByEditor_;

    ComalLspClient *lspClient_ = nullptr; // Added member for LSP client
};
