#include "code_editor_panel.h"

#include <QVBoxLayout>
#include <QTabWidget>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QSet>
#include <QRegularExpression>
#include <QSettings>

#include <Qsci/qsciscintilla.h>
#include "qsci_lexer_comal.h"
#include <QToolTip>

static bool isWordChar(QChar c)
{
    return c.isLetterOrNumber() || c == '_';
}

static QString wordAtCursor(const QString &lineText, int column)
{
    if (lineText.isEmpty())
        return {};

    int col = column;
    if (col < 0)
        col = 0;
    if (col > lineText.size())
        col = lineText.size();

    int start = col;
    while (start > 0 && isWordChar(lineText[start - 1]))
        --start;

    int end = col;
    while (end < lineText.size() && isWordChar(lineText[end]))
        ++end;

    if (start == end)
        return {};

    QString word = lineText.mid(start, end - start);
    if (end < lineText.size() && (lineText[end] == '$' || lineText[end] == '#'))
        word += lineText[end];

    return word;
}

CodeEditorPanel::CodeEditorPanel(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    tabs_ = new QTabWidget(this);
    tabs_->setTabsClosable(true);
    tabs_->setMovable(true);
    layout->addWidget(tabs_);

    connect(tabs_, &QTabWidget::tabCloseRequested,
            this,  &CodeEditorPanel::onTabCloseRequested);
    connect(tabs_, &QTabWidget::currentChanged,
            this,  &CodeEditorPanel::onCurrentTabChanged);

    // Open one default tab
    newTab("Untitled");
}

QsciScintilla *CodeEditorPanel::currentEditor() const
{
    return qobject_cast<QsciScintilla *>(tabs_->currentWidget());
}

void CodeEditorPanel::newTab(const QString &title)
{
    auto *editor = createEditor();
    int idx = tabs_->addTab(editor, title);
    tabs_->setCurrentIndex(idx);
}

QsciScintilla *CodeEditorPanel::createEditor()
{
    auto *editor = new QsciScintilla(this);

    // Margins: line numbers + breakpoint markers
    editor->setMarginType(0, QsciScintilla::NumberMargin);
    editor->setMarginWidth(0, "9999");
    editor->setMarginType(1, QsciScintilla::SymbolMargin);
    editor->setMarginWidth(1, 16);
    editor->setMarginSensitivity(1, true);   // click gutter → toggle breakpoint
    editor->markerDefine(QsciScintilla::Circle, 0);

    // Breakpoint marker — red circle
    editor->markerDefine(QsciScintilla::Circle, BREAKPOINT_MARKER_ID);
    editor->setMarkerForegroundColor(QColor(220, 0, 0), BREAKPOINT_MARKER_ID);

    // Error line marker — red background
    editor->markerDefine(QsciScintilla::Background, ERROR_MARKER_ID);
    editor->setMarkerBackgroundColor(QColor(255, 200, 200), ERROR_MARKER_ID);

    // Execution pause marker — yellow background
    editor->markerDefine(QsciScintilla::Background, EXEC_MARKER_ID);
    editor->setMarkerBackgroundColor(QColor(255, 255, 150), EXEC_MARKER_ID);

    // Click on gutter → toggle breakpoint marker
    connect(editor, &QsciScintilla::marginClicked, this, [this, editor](int margin, int line, Qt::KeyboardModifiers) {
        if (margin == 1) {
            toggleBreakpointAtLine(editor, line + 1);
        }
    });

    // Basic editor settings
    editor->setAutoIndent(true);
    // Connect signals for LSP integration
    connect(editor, &QsciScintilla::textChanged, this, [this, editor]{
        if (!lspClient_) return;
        QString text = editor->text();
        QString filePath = currentFilePath();
        lspClient_->sendDidChange(filePath, text);
    });
    connect(editor, &QsciScintilla::cursorPositionChanged, this, [this, editor](int line, int col){
        emit cursorPositionChanged(line, col);
        emit keywordUnderCursorChanged(wordAtCursor(editor->text(line), col));
        if (!lspClient_) return;
        QString filePath = currentFilePath();
        lspClient_->requestHover(filePath, line, col);
        lspClient_->requestCompletion(filePath, line, col);
    });
    editor->setIndentationWidth(2);
    editor->setTabWidth(2);
    editor->setIndentationsUseTabs(false);
    editor->setBraceMatching(QsciScintilla::StrictBraceMatch);
    editor->setCaretLineVisible(true);

    // Syntax highlighting
    auto *lexer = new QsciLexerComal(editor);
    editor->setLexer(lexer);

    // Apply persisted editor font to freshly created tabs.
    QSettings settings("OpenCOMAL", "IDE");
    QString editorFontFamily = settings.value("EditorFont/Family", "Monospace").toString();
    int editorFontSize = settings.value("EditorFont/Size", 11).toInt();
    QFont persistedFont(editorFontFamily, editorFontSize);
    editor->setFont(persistedFont);
    for (int style = QsciLexerComal::Default; style <= QsciLexerComal::GraphicsCmd; ++style) {
        QFont styleFont = persistedFont;
        if (style == QsciLexerComal::Keyword)
            styleFont.setBold(true);
        lexer->setFont(styleFont, style);
    }

    connectEditorSignals(editor);
    return editor;
}

void CodeEditorPanel::setLspClient(ComalLspClient *client) {
    lspClient_ = client;
    // Send didOpen for current tab
    if (auto *editor = currentEditor()) {
        QString text = editor->text();
        QString filePath = currentFilePath();
        lspClient_->sendDidOpen(filePath, text);
    }

    // Connect LSP client signals
    connect(lspClient_, &ComalLspClient::hoverReceived, this, [this](const QString &filePath, const QJsonObject &hover) {
        // Show hover tooltip if editor matches filePath
        if (filePath == currentFilePath() && currentEditor()) {
            QString contents = hover.value("contents").toString();
            if (!contents.isEmpty()) {
                // QsciScintilla does not provide pointFromPosition; show tooltip at viewport center
                QWidget *viewport = currentEditor()->viewport();
                QPoint center = viewport->rect().center();
                QToolTip::showText(viewport->mapToGlobal(center), contents, currentEditor());
            }
        }
    });
    connect(lspClient_, &ComalLspClient::diagnosticsReceived, this, [this](const QString &filePath, const QJsonObject &diagnostics) {
        // TODO: Display diagnostics in editor (underline errors, show markers)
        // For now, print to console
        qDebug() << "Diagnostics for" << filePath << diagnostics;
    });
    // Completion and definition can be handled similarly
    connect(lspClient_, &ComalLspClient::completionReceived, this, [this](const QString &filePath, const QJsonObject &completion) {
        // TODO: Show completion popup
        qDebug() << "Completion for" << filePath << completion;
    });
    connect(lspClient_, &ComalLspClient::definitionReceived, this, [this](const QString &filePath, const QJsonObject &definition) {
        // TODO: Jump to definition
        qDebug() << "Definition for" << filePath << definition;
    });
}

void CodeEditorPanel::connectEditorSignals(QsciScintilla *editor)
{
    // Cursor tracking
    connect(editor, &QsciScintilla::cursorPositionChanged,
            this, [this, editor](int line, int index) {
        if (editor == currentEditor())
            emit cursorPositionChanged(line + 1, index + 1);
    });

    // Modified indicator in tab title
    connect(editor, &QsciScintilla::modificationChanged,
            this, [this, editor](bool /*modified*/) {
        int idx = tabs_->indexOf(editor);
        if (idx >= 0)
            updateTabTitle(idx);
    });
}

void CodeEditorPanel::updateTabTitle(int index)
{
    auto *editor = qobject_cast<QsciScintilla *>(tabs_->widget(index));
    if (!editor) return;

    QString title = tabs_->tabToolTip(index);
    if (title.isEmpty())
        title = "Untitled";
    else
        title = QFileInfo(title).fileName();

    if (editor->isModified())
        title += " *";

    tabs_->setTabText(index, title);
}

void CodeEditorPanel::openFile(const QString &filePath)
{
    // Check if already open in a tab
    for (int i = 0; i < tabs_->count(); ++i) {
        if (tabs_->tabToolTip(i) == filePath) {
            tabs_->setCurrentIndex(i);
            return;
        }
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream stream(&file);
    QString content = stream.readAll();

    // Strip COMAL line numbers (leading digits + optional space)
    // e.g. "0010 PRINT ..." -> "PRINT ..."
    const bool hadTerminalNewline = content.endsWith('\n');
    QStringList strippedLines;
    const auto lines = content.split('\n', Qt::KeepEmptyParts);
    const int limit = hadTerminalNewline ? lines.size() - 1 : lines.size();
    strippedLines.reserve(limit);

    for (int i = 0; i < limit; ++i) {
        QString line = lines[i];
        if (line.endsWith('\r'))
            line.chop(1);

        QString trimmed = line.trimmed();
        // Match optional leading digits followed by space (or end of line)
        int pos = 0;
        while (pos < trimmed.size() && trimmed[pos].isDigit())
            pos++;
        if (pos > 0 && pos < trimmed.size() && trimmed[pos] == ' ')
            strippedLines.append(trimmed.mid(pos + 1));
        else if (pos > 0 && pos == trimmed.size())
            strippedLines.append(QString()); // blank numbered line (e.g. "  80 ")
        else
            strippedLines.append(line);
    }

    QString stripped = strippedLines.join('\n');
    if (hadTerminalNewline)
        stripped += '\n';

    auto *editor = createEditor();
    editor->setText(stripped);
    editor->setModified(false);
    QFileInfo info(filePath);
    int idx = tabs_->addTab(editor, info.fileName());
    tabs_->setTabToolTip(idx, filePath);
    tabs_->setCurrentIndex(idx);

    // Apply any existing breakpoints for this file in the editor gutter.
    applyBreakpointsToEditor(editor, filePath);
}

QString CodeEditorPanel::currentFilePath() const
{
    int idx = tabs_->currentIndex();
    if (idx >= 0)
        return tabs_->tabToolTip(idx);
    return {};
}

// ── File save ───────────────────────────────────────────────────────

bool CodeEditorPanel::saveFile()
{
    QString path = currentFilePath();
    if (path.isEmpty())
        return saveFileAs();

    auto *editor = currentEditor();
    if (!editor) return false;

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    file.write(editor->text().toUtf8());
    editor->setModified(false);
    updateTabTitle(tabs_->currentIndex());
    return true;
}

bool CodeEditorPanel::saveFileAs()
{
    auto *editor = currentEditor();
    if (!editor) return false;

    QString path = QFileDialog::getSaveFileName(
        this, tr("Save As"), QString(),
        tr("COMAL Files (*.lst *.cml);;All Files (*)"));
    if (path.isEmpty()) return false;

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    file.write(editor->text().toUtf8());
    editor->setModified(false);

    int idx = tabs_->currentIndex();

    // Transfer breakpoints from old path to new path (if any)
    QString oldPath = tabs_->tabToolTip(idx);
    if (!oldPath.isEmpty() && oldPath != path) {
        auto it = breakpoints_.find(oldPath);
        if (it != breakpoints_.end()) {
            breakpoints_.insert(path, std::move(*it));
            breakpoints_.erase(it);
        }
    }

    tabs_->setTabToolTip(idx, path);
    updateTabTitle(idx);
    applyBreakpointsToEditor(currentEditor(), path);
    return true;
}

// ── Tab management ──────────────────────────────────────────────────

bool CodeEditorPanel::maybeSaveTab(int index)
{
    auto *editor = qobject_cast<QsciScintilla *>(tabs_->widget(index));
    if (!editor || !editor->isModified())
        return true;

    QString name = tabs_->tabText(index).remove(" *");
    auto btn = QMessageBox::question(
        this, tr("Unsaved Changes"),
        tr("'%1' has unsaved changes.\nSave before closing?").arg(name),
        QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
        QMessageBox::Save);

    if (btn == QMessageBox::Cancel)
        return false;
    if (btn == QMessageBox::Discard)
        return true;

    // Save
    tabs_->setCurrentIndex(index);
    return saveFile();
}

void CodeEditorPanel::onTabCloseRequested(int index)
{
    if (!maybeSaveTab(index))
        return;

    QWidget *w = tabs_->widget(index);
    tabs_->removeTab(index);
    delete w;

    // Ensure at least one tab
    if (tabs_->count() == 0)
        newTab("Untitled");
}

void CodeEditorPanel::closeCurrentTab()
{
    onTabCloseRequested(tabs_->currentIndex());
}

void CodeEditorPanel::onCurrentTabChanged(int /*index*/)
{
    auto *editor = currentEditor();
    if (editor) {
        int line, col;
        editor->getCursorPosition(&line, &col);
        emit cursorPositionChanged(line + 1, col + 1);
    }

    // Notify listeners that the current file changed (for updating debug UI)
    emit currentFileChanged(currentFilePath());
}

// ── Error highlighting ──────────────────────────────────────────────

void CodeEditorPanel::highlightErrorLine(int line)
{
    clearErrorHighlight();
    auto *editor = currentEditor();
    if (!editor || line <= 0) return;
    editor->markerAdd(line - 1, ERROR_MARKER_ID);
    editor->setCursorPosition(line - 1, 0);
    editor->ensureLineVisible(line - 1);
}

void CodeEditorPanel::clearErrorHighlight()
{
    auto *editor = currentEditor();
    if (!editor) return;
    editor->markerDeleteAll(ERROR_MARKER_ID);
}

void CodeEditorPanel::highlightExecutionLine(int line)
{
    clearExecutionHighlight();
    auto *editor = currentEditor();
    if (!editor || line <= 0) return;
    editor->markerAdd(line - 1, EXEC_MARKER_ID);
    editor->setCursorPosition(line - 1, 0);
    editor->ensureLineVisible(line - 1);
}

void CodeEditorPanel::clearExecutionHighlight()
{
    auto *editor = currentEditor();
    if (!editor) return;
    editor->markerDeleteAll(EXEC_MARKER_ID);
}

// ── Format Source ───────────────────────────────────────────────────
//
// COMAL source formatter:
//  1. Uppercase known keywords (print → PRINT, for → FOR, etc.)
//  2. Fix assignment operator (= → := outside comparisons)
//  3. Auto-indent block structure

// Keywords that should be uppercased (checked case-insensitively).
static const QSet<QString> &comalKeywords()
{
    static const QSet<QString> kw {
        "AND", "APPEND", "CALLVEC", "CASE", "CLOSE", "CLOSED",
        "CURSOR", "DATA", "DEL", "DELETE", "DIM", "DIV", "DO",
        "DRAW", "PLAY", "TONE", "SLEEP", "DOWNTO", "ELIF", "ELSE", "END", "ENDCASE", "ENDFOR", "NEXT",
        "ENDFUNC", "ENDIF", "ENDLOOP", "ENDPROC", "ENDTRAP",
        "ENDWHILE", "EXEC", "EXIT", "FALSE", "FILE", "FOR",
        "FUNC", "HANDLER", "IF", "IMPORT", "IN", "INPUT", "LOOP",
        "MOD", "NOT", "NULL", "OF", "OPEN", "OR", "OTHERWISE",
        "OUTPUT", "PAGE", "PRINT", "PROC", "RANDOM", "READ",
        "REF", "REPEAT", "RESTORE", "RETURN", "RUN", "SELECT",
        "SPC", "STEP", "STOP", "TAB", "THEN", "TO", "TRAP",
        "TRUE", "UNTIL", "USE", "USING", "WHEN", "WHILE",
        "WRITE", "ZONE",
    };
    return kw;
}

/// Uppercase COMAL keywords in a line, leaving strings and identifiers
/// (those ending in $ or #) untouched.
static QString uppercaseKeywords(const QString &line)
{
    QString result;
    result.reserve(line.size());
    int i = 0;
    int len = line.size();

    while (i < len) {
        QChar ch = line[i];

        // Skip string literals
        if (ch == '"') {
            result += ch;
            i++;
            while (i < len && line[i] != '"') {
                if (line[i] == '\\' && i + 1 < len) {
                    result += line[i++];
                }
                result += line[i++];
            }
            if (i < len) result += line[i++]; // closing quote
            continue;
        }

        // Skip // comment — pass rest of line through unchanged
        if (ch == '/' && i + 1 < len && line[i + 1] == '/') {
            result += line.mid(i);
            break;
        }

        // Identifier / keyword
        if (ch.isLetter() || ch == '_') {
            int start = i;
            while (i < len && (line[i].isLetterOrNumber() || line[i] == '_'))
                i++;
            // Check for $ or # suffix (variable name — don't uppercase)
            if (i < len && (line[i] == '$' || line[i] == '#')) {
                result += line.mid(start, i - start + 1);
                i++;
                continue;
            }
            QString word = line.mid(start, i - start);
            if (comalKeywords().contains(word.toUpper()))
                result += word.toUpper();
            else
                result += word;
            continue;
        }

        result += ch;
        i++;
    }

    return result;
}

/// Fix assignment operator: bare `=` → `:=` for assignments.
/// Applies to: `ident =`, `ident(...)... =`, `FOR ident =`
/// Does NOT touch: `==`, already `:=`, `=` inside strings, `=` after
/// comparison keywords (IF, WHILE, WHEN, UNTIL, PRINT, etc.)
static QString fixAssignment(const QString &line)
{
    QString upper = line.trimmed().toUpper();

    // Only fix if line starts with an identifier or FOR
    // (i.e. it's an assignment or FOR loop header)
    bool isAssignment = false;
    if (!upper.isEmpty() && (upper[0].isLetter() || upper[0] == '_'))
        isAssignment = true;
    if (!isAssignment)
        return line;

    // Extract the first keyword
    int k = 0;
    while (k < upper.size() && (upper[k].isLetterOrNumber() || upper[k] == '_'))
        k++;
    QString firstWord = upper.left(k);

    // Skip lines that start with keywords where `=` is a comparison
    static const QSet<QString> nofix {
        "IF", "ELIF", "WHILE", "UNTIL", "WHEN", "PRINT", "WRITE",
        "CASE", "RETURN", "EXIT", "INPUT", "DATA", "READ",
    };
    if (nofix.contains(firstWord) && firstWord != "FOR")
        return line;

    // Find the first bare `=` that isn't already `:=` and isn't inside a string
    QString result;
    result.reserve(line.size() + 1);
    bool fixed = false;
    bool inString = false;

    for (int i = 0; i < line.size(); i++) {
        QChar ch = line[i];

        if (ch == '"') {
            inString = !inString;
            result += ch;
            continue;
        }
        if (inString) {
            result += ch;
            continue;
        }

        // Skip // comment
        if (ch == '/' && i + 1 < line.size() && line[i + 1] == '/') {
            result += line.mid(i);
            return result;
        }

        if (!fixed && ch == '=' && (i == 0 || line[i - 1] != ':') &&
            (i == 0 || line[i - 1] != '<') && (i == 0 || line[i - 1] != '>') &&
            (i == 0 || line[i - 1] != '!') &&
            (i + 1 >= line.size() || line[i + 1] != '=')) {
            result += ":=";
            fixed = true;
            continue;
        }

        result += ch;
    }
    return result;
}

void CodeEditorPanel::formatSource()
{
    auto *editor = currentEditor();
    if (!editor) return;

    const int step = 2;
    int indent = 0;

    QString text = editor->text();
    QStringList lines = text.split('\n');
    QStringList result;

    for (const auto &rawLine : lines) {
        QString trimmed = rawLine.trimmed();
        if (trimmed.isEmpty()) {
            result << "";
            continue;
        }

        // 1. Uppercase keywords
        trimmed = uppercaseKeywords(trimmed);

        // 2. Fix assignment operator
        trimmed = fixAssignment(trimmed);

        // 3. Compute indentation
        QString upper = trimmed.toUpper();
        QString firstWord;
        int k = 0;
        while (k < upper.size() && upper[k].isLetter())
            firstWord += upper[k++];

        int delta_before = 0;
        int delta_after = 0;

        // Closers: dedent this line
        if (firstWord == "ENDFOR" || firstWord == "NEXT" || firstWord == "ENDWHILE" ||
            firstWord == "UNTIL"  || firstWord == "ENDLOOP"  ||
            firstWord == "ENDIF"  || firstWord == "ENDCASE"  ||
            firstWord == "ENDPROC"|| firstWord == "ENDFUNC"  ||
            firstWord == "ENDTRAP") {
            delta_before = -step;
        }
        // Mid-block: dedent this line, indent next
        else if (firstWord == "WHEN" || firstWord == "OTHERWISE" ||
                 firstWord == "ELSE" || firstWord == "ELIF"      ||
                 firstWord == "HANDLER") {
            delta_before = -step;
            delta_after  = step;
        }
        // Openers: check for block form vs short form
        else if (firstWord == "FOR" || firstWord == "WHILE") {
            // Block form: no DO, or line ends with DO.
            // Single-line form: body after DO (e.g. FOR i:=1 TO 10 DO PRINT i)
            int doPos = upper.lastIndexOf(" DO");
            if (doPos < 0) {
                // No DO keyword → block form (closed by ENDFOR/ENDWHILE)
                delta_after = step;
            } else if (doPos + 3 >= upper.size()) {
                // DO at end of line → block form
                delta_after = step;
            }
            // else: text after DO → single-line form, no indent
        }
        else if (firstWord == "IF") {
            // Block form only when line ends with THEN
            if (upper.endsWith(" THEN"))
                delta_after = step;
        }
        else if (firstWord == "REPEAT" || firstWord == "LOOP") {
            delta_after = step;
        }
        else if (firstWord == "CASE") {
            if (upper.contains(" OF"))
                delta_after = step;
        }
        else if (firstWord == "PROC" || firstWord == "FUNC" ||
                 firstWord == "TRAP") {
            delta_after = step;
        }

        indent += delta_before;
        if (indent < 0) indent = 0;

        result << QString(indent, ' ') + trimmed;

        indent += delta_after;
        if (indent < 0) indent = 0;
    }

    QString formatted = result.join('\n');

    int line, col;
    editor->getCursorPosition(&line, &col);
    editor->selectAll();
    editor->replaceSelectedText(formatted);
    editor->setCursorPosition(line, col);
}

// ── Breakpoints ────────────────────────────────────────────────────────

static QString breakpointFileKey(const QString &filePath)
{
    if (!filePath.isEmpty())
        return filePath;
    return QStringLiteral("<unsaved>");
}

void CodeEditorPanel::toggleBreakpointAtCurrentLine()
{
    auto *editor = currentEditor();
    if (!editor)
        return;

    int line, col;
    editor->getCursorPosition(&line, &col);
    toggleBreakpointAtLine(editor, line + 1);
}

void CodeEditorPanel::toggleBreakpointAtLine(QsciScintilla *editor, int line)
{
    if (!editor || line <= 0)
        return;

    int idx = tabs_->indexOf(editor);
    if (idx < 0)
        return;

    QString path = breakpointFileKey(tabs_->tabToolTip(idx));
    auto &set = breakpoints_[path];

    if (set.contains(line)) {
        set.remove(line);
        editor->markerDelete(line - 1, BREAKPOINT_MARKER_ID);
    } else {
        set.insert(line);
        editor->markerAdd(line - 1, BREAKPOINT_MARKER_ID);
    }

    QVector<int> lines = breakpointsForFile(path);
    emit breakpointsChanged(path, lines);
}

void CodeEditorPanel::applyBreakpointsToEditor(QsciScintilla *editor, const QString &filePath)
{
    if (!editor)
        return;

    QString key = breakpointFileKey(filePath);
    editor->markerDeleteAll(BREAKPOINT_MARKER_ID);

    auto it = breakpoints_.find(key);
    if (it == breakpoints_.end())
        return;

    for (int line : *it)
        editor->markerAdd(line - 1, BREAKPOINT_MARKER_ID);
}

QVector<int> CodeEditorPanel::breakpointsForFile(const QString &filePath) const
{
    QString key = breakpointFileKey(filePath);
    QVector<int> lines;
    auto it = breakpoints_.constFind(key);
    if (it == breakpoints_.constEnd())
        return lines;

    for (int l : *it)
        lines.append(l);
    std::sort(lines.begin(), lines.end());
    return lines;
}

QVector<int> CodeEditorPanel::breakpointsForCurrentFile() const
{
    return breakpointsForFile(currentFilePath());
}

void CodeEditorPanel::applyFontToAllEditors(const QFont &font)
{
    for (int i = 0; i < tabs_->count(); ++i) {
        if (auto *editor = qobject_cast<QsciScintilla*>(tabs_->widget(i))) {
            editor->setFont(font);

            // Apply per-style fonts on the COMAL lexer; otherwise startup can keep old style sizes.
            if (auto *lexer = qobject_cast<QsciLexerComal*>(editor->lexer())) {
                for (int style = QsciLexerComal::Default; style <= QsciLexerComal::GraphicsCmd; ++style) {
                    QFont styleFont = font;
                    if (style == QsciLexerComal::Keyword)
                        styleFont.setBold(true);
                    lexer->setFont(styleFont, style);
                }
            } else if (auto *lexer = editor->lexer()) {
                lexer->setFont(font);
            }
        }
    }
}
