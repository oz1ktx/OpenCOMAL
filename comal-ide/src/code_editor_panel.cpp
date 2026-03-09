#include "code_editor_panel.h"

#include <QVBoxLayout>
#include <QTabWidget>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexercpp.h>    // placeholder until COMAL lexer exists

CodeEditorPanel::CodeEditorPanel(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    tabs_ = new QTabWidget(this);
    tabs_->setTabsClosable(true);
    tabs_->setMovable(true);
    layout->addWidget(tabs_);

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
    tabs_->addTab(editor, title);
    tabs_->setCurrentWidget(editor);
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

    // Basic editor settings
    editor->setAutoIndent(true);
    editor->setIndentationWidth(2);
    editor->setTabWidth(2);
    editor->setIndentationsUseTabs(false);
    editor->setBraceMatching(QsciScintilla::StrictBraceMatch);
    editor->setCaretLineVisible(true);

    // Placeholder sample text (COMAL)
    editor->setText(
        "// OpenCOMAL — sample program\n"
        "DIM name$ OF 40\n"
        "INPUT \"What is your name? \": name$\n"
        "PRINT \"Hello, \", name$\n"
        "FOR i:=1 TO 10 DO\n"
        "  PRINT i, \" squared is \", i*i\n"
        "ENDFOR i\n"
    );

    return editor;
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
    // e.g. "0010 PRINT ..." → "PRINT ..."
    QString stripped;
    const auto lines = content.split('\n');
    for (const auto &line : lines) {
        auto trimmed = line.trimmed();
        // Match optional leading digits followed by space
        int pos = 0;
        while (pos < trimmed.size() && trimmed[pos].isDigit())
            pos++;
        if (pos > 0 && pos < trimmed.size() && trimmed[pos] == ' ')
            stripped += trimmed.mid(pos + 1) + '\n';
        else
            stripped += line + '\n';
    }

    auto *editor = createEditor();
    editor->setText(stripped);
    QFileInfo info(filePath);
    int idx = tabs_->addTab(editor, info.fileName());
    tabs_->setTabToolTip(idx, filePath);
    tabs_->setCurrentIndex(idx);
}

QString CodeEditorPanel::currentFilePath() const
{
    int idx = tabs_->currentIndex();
    if (idx >= 0)
        return tabs_->tabToolTip(idx);
    return {};
}
