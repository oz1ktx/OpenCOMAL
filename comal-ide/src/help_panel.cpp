#include "help_panel.h"

#include <QVBoxLayout>
#include <QTextBrowser>

static const char *defaultHelp = R"HTML(
<h2>OpenCOMAL Quick Reference</h2>
<table border="1" cellpadding="4" cellspacing="0">
<tr><th>Category</th><th>Keywords</th></tr>
<tr><td>Control Flow</td><td>IF/THEN/ELIF/ELSE/ENDIF, FOR/TO/STEP/DO/ENDFOR (or NEXT),
    WHILE/DO/ENDWHILE, REPEAT/UNTIL, CASE/WHEN/OTHERWISE/ENDCASE,
    LOOP/EXIT/ENDLOOP</td></tr>
<tr><td>Procedures</td><td>PROC/ENDPROC, FUNC/RETURN/ENDFUNC,
    EXEC, CLOSED</td></tr>
<tr><td>I/O</td><td>PRINT, INPUT, OPEN, CLOSE, READ, WRITE,
    SELECT OUTPUT, SELECT INPUT</td></tr>
<tr><td>Variables</td><td>DIM, OF, :=, LOCAL, IMPORT, READ ONLY</td></tr>
<tr><td>Data</td><td>DATA, READ, RESTORE</td></tr>
<tr><td>String</td><td>LEN, MID$, LEFT$, RIGHT$, CHR$, ORD, VAL, STR$,
    UPPER$, LOWER$</td></tr>
<tr><td>Math</td><td>ABS, INT, SQR, SIN, COS, TAN, ATN, LOG, EXP, RND,
    SGN, MOD, DIV, RANDOMIZE</td></tr>
<tr><td>Graphics</td><td>DRAW (future: line, rect, circle, …)</td></tr>
<tr><td>Other</td><td>STOP, END, RUN, LIST, DELETE, AUTO, RENUM,
    TRAP/ENDTRAP/HANDLER, SYS, SYS$, PAGE,
    ZONE, TAB, USING, CURSOR</td></tr>
</table>
<p><i>Click a keyword in the editor for detailed help (via LSP hover).</i></p>
)HTML";

HelpPanel::HelpPanel(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    browser_ = new QTextBrowser(this);
    browser_->setOpenExternalLinks(false);
    browser_->setHtml(defaultHelp);
    layout->addWidget(browser_);
}

void HelpPanel::showKeywordHelp(const QString &keyword)
{
    browser_->setHtml(
        "<h3>" + keyword.toUpper() + "</h3>"
        "<p><i>Detailed help not yet connected.</i></p>"
    );
}
