#include "help_panel.h"

#include <QVBoxLayout>
#include <QTextBrowser>
#include <QHash>

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

static const QHash<QString, QString> &keywordDocs()
{
    static const QHash<QString, QString> docs {
        {"PRINT", "Print values to the output device."},
        {"INPUT", "Read a value from the user."},
        {"IF", "Conditional execution. Use with THEN, ELSE, ENDIF."},
        {"THEN", "Introduces the true branch of IF."},
        {"ELSE", "Introduces the false branch of IF."},
        {"ELIF", "Else-if branch in multi-line IF blocks."},
        {"FOR", "Counted loop: FOR var := start TO stop [STEP inc]."},
        {"TO", "Upper bound in a FOR loop."},
        {"DOWNTO", "Descending FOR direction: FOR i := hi DOWNTO lo."},
        {"STEP", "Increment value in a FOR loop."},
        {"ENDFOR", "End of a FOR loop body."},
        {"NEXT", "Compatibility synonym for ENDFOR."},
        {"WHILE", "Loop while a condition is true."},
        {"ENDWHILE", "End of a WHILE loop body."},
        {"REPEAT", "Loop body that repeats UNTIL a condition is true."},
        {"UNTIL", "Condition that terminates a REPEAT loop."},
        {"CASE", "Multi-way branch: CASE expr OF ... ENDCASE."},
        {"WHEN", "Branch inside a CASE block."},
        {"OTHERWISE", "Default branch inside a CASE block."},
        {"ENDCASE", "End of a CASE block."},
        {"PROC", "Define a procedure: PROC name[(params)] ... ENDPROC."},
        {"ENDPROC", "End of a PROC definition."},
        {"FUNC", "Define a function: FUNC name[(params)] ... ENDFUNC."},
        {"ENDFUNC", "End of a FUNC definition."},
        {"RETURN", "Return a value from a FUNC."},
        {"EXEC", "Execute a procedure call."},
        {"LOCAL", "Declare local variables in a PROC or FUNC."},
        {"IMPORT", "Import names into a CLOSED procedure."},
        {"DIM", "Dimension (allocate) an array."},
        {"DATA", "Define inline data for READ statements."},
        {"READ", "Read the next value from a DATA list."},
        {"WRITE", "Write values to a file stream or device."},
        {"RESTORE", "Reset the DATA pointer."},
        {"OPEN", "Open a file handle for INPUT/OUTPUT/READ/WRITE."},
        {"CLOSE", "Close an open file handle."},
        {"SELECT", "Select input/output device context."},
        {"OUTPUT", "Used with SELECT OUTPUT."},
        {"STOP", "Halt program execution."},
        {"END", "Terminate a program or close a block (END IF, END FOR, ...)."},
        {"TRAP", "Set up an error/escape handler."},
        {"HANDLER", "Error/escape handler block."},
        {"ENDTRAP", "End of a TRAP block."},
        {"DRAW", "Execute a graphics command: DRAW subcommand args."},
        {"TONE", "Play a simple sine tone: TONE frequency duration (ms)."},
        {"PLAY", "Play a melody or instrument sequence."},
        {"SLEEP", "Pause execution for a number of milliseconds."},
        {"PAGE", "Clear the output screen."},
        {"CURSOR", "Position the cursor: CURSOR row, col."},
        {"RANDOM", "Randomize the random number generator."},
        {"USING", "Formatted output: PRINT USING format$; values."},
        {"ZONE", "Set print zone width."},
        {"TAB", "Move to a specific column."},
        {"LEN", "Length of a string, or number of elements in an array."},
    };
    return docs;
}

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
    const QString upper = keyword.trimmed().toUpper();
    if (upper.isEmpty()) {
        browser_->setHtml(defaultHelp);
        return;
    }

    const auto &docs = keywordDocs();
    const QString doc = docs.value(upper, "No dedicated documentation text yet for this keyword.");

    browser_->setHtml(
        "<h3>" + upper + "</h3>"
        "<p>" + doc + "</p>"
        "<p><i>Tip: keep cursor on a keyword in the editor to update this panel.</i></p>"
    );
}
