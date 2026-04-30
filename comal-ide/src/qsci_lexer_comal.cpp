#include "qsci_lexer_comal.h"

#include <QColor>
#include <QFont>
#include <QSet>
#include <Qsci/qsciscintilla.h>

// ── Keyword and builtin tables ──────────────────────────────────────────

static const QSet<QString> &comalKeywords()
{
    static const QSet<QString> kw {
        "AND", "APPEND", "CASE", "CLOSE", "CLOSED",
        "CURSOR", "DATA", "DEL", "DELETE", "DIM", "DIV", "DO",
        "DRAW", "PLAY", "TONE", "SLEEP", "DOWNTO", "ELIF", "ELSE", "END", "ENDCASE", "ENDFOR", "NEXT",
        "ENDFUNC", "ENDIF", "ENDLOOP", "ENDPROC", "ENDTRAP",
        "ENDWHILE", "EXEC", "EXIT", "FILE", "FOR",
        "FUNC", "HANDLER", "IF", "IMPORT", "IN", "INPUT", "LOOP",
        "MOD", "NOT", "NULL", "OF", "OPEN", "OR", "OTHERWISE",
        "OUTPUT", "PAGE", "PRINT", "PROC", "RANDOM", "READ",
        "REF", "REPEAT", "RESTORE", "RETURN", "RUN", "SELECT", "SPAWN",
        "STEP", "STOP", "THEN", "TO", "TRAP",
        "UNTIL", "USE", "USING", "WHEN", "WHILE",
        "WRITE", "ZONE",
    };
    return kw;
}

static const QSet<QString> &comalBuiltins()
{
    // Numeric and string built-in functions recognised by the parser.
    static const QSet<QString> bf {
        "ABS", "ASN", "ATN", "COS", "DEG", "EOD", "EOF", "ERR",
        "ERRLINE", "EXP", "FALSE", "FRAC", "INT", "LEN", "LN",
        "LOG", "NOT", "ORD", "PI", "RAD", "RND", "ROUND", "SGN",
        "SIN", "SQR", "TAN", "TRUE", "VAL",
        // String builtins (matched without the trailing $)
        "CHR$", "DIR$", "ERRTEXT$", "INKEY$", "KEY$", "LOWER$",
        "SPC$", "SPLIT$", "STR$", "SYS$", "UNIT$", "UPPER$",
    };
    return bf;
}

static const QSet<QString> &comalGraphicsCommands()
{
    // Graphics subcommands for DRAW statements (libcomal-graphics)
    static const QSet<QString> gc {
        // Shape commands (exactly as in libcomal-graphics)
        "line", "rect", "circle", "ellipse", "pixel", "text",
        // Style commands
        "stroke", "fill", "noFill", "noStroke", "lineWidth", "fontSize",
        // Canvas commands
        "background", "clear",
        // Transform commands
        "translate", "rotate", "scale",
    };
    return gc;
}

// ── Constructor ─────────────────────────────────────────────────────────

QsciLexerComal::QsciLexerComal(QObject *parent)
    : QsciLexerCustom(parent)
{
}

const char *QsciLexerComal::language() const
{
    return "COMAL";
}

QString QsciLexerComal::description(int style) const
{
    switch (style) {
    case Default:      return tr("Default");
    case Keyword:      return tr("Keyword");
    case Builtin:      return tr("Built-in function");
    case String:       return tr("String");
    case Number:       return tr("Number");
    case Comment:      return tr("Comment");
    case Operator:     return tr("Operator");
    case VarSuffix:    return tr("String/integer variable");
    case GraphicsCmd:  return tr("Graphics command");
    default:           return {};
    }
}

QColor QsciLexerComal::defaultColor(int style) const
{
    switch (style) {
    case Keyword:      return QColor(0, 0, 180);       // dark blue
    case Builtin:      return QColor(0, 128, 128);      // teal
    case String:       return QColor(163, 21, 21);      // dark red
    case Number:       return QColor(9, 134, 88);       // green
    case Comment:      return QColor(0, 128, 0);        // green
    case Operator:     return QColor(128, 0, 128);      // purple
    case VarSuffix:    return QColor(120, 73, 42);      // brown
    case GraphicsCmd:  return QColor(200, 0, 128);      // dark magenta
    default:           return QColor(0, 0, 0);          // black
    }
}

QFont QsciLexerComal::defaultFont(int style) const
{
    QFont f = QsciLexerCustom::defaultFont(style);
    if (style == Keyword)
        f.setBold(true);
    return f;
}

// ── Helpers ─────────────────────────────────────────────────────────────

bool QsciLexerComal::isKeyword(const QString &word)
{
    return comalKeywords().contains(word.toUpper());
}

bool QsciLexerComal::isBuiltin(const QString &word)
{
    return comalBuiltins().contains(word.toUpper());
}

static bool isGraphicsCommand(const QString &word)
{
    // Case-insensitive check since graphics commands are stored in original case
    const auto& commands = comalGraphicsCommands();
    for (const auto& cmd : commands) {
        if (cmd.compare(word, Qt::CaseInsensitive) == 0) {
            return true;
        }
    }
    return false;
}

// ── styleText — the main lexer entry point ──────────────────────────────

void QsciLexerComal::styleText(int start, int end)
{
    if (!editor())
        return;

    Q_UNUSED(start);
    Q_UNUSED(end);

    // Style the whole document on each pass. This avoids partial-range UTF-8
    // boundary issues that can cause stray underlines/artifacts.
    const QString text = editor()->text();
    if (text.isEmpty())
        return;

    startStyling(0);

    int i = 0;
    int len = text.length();

    auto setStylingForChars = [&](int charStart, int charEnd, int style) {
        const int charCount = charEnd - charStart;
        if (charCount <= 0)
            return;
        const int byteCount = text.mid(charStart, charCount).toUtf8().size();
        if (byteCount > 0)
            setStyling(byteCount, style);
    };

    while (i < len) {
        QChar ch = text[i];

        // ── Comment: // to end of line ──────────────────────────────
        if (ch == '/' && i + 1 < len && text[i + 1] == '/') {
            int commentStart = i;
            while (i < len && text[i] != '\n')
                ++i;
            setStylingForChars(commentStart, i, Comment);
            continue;
        }

        // ── String literal: "…" ─────────────────────────────────────
        if (ch == '"') {
            int strStart = i;
            ++i;   // skip opening quote
            while (i < len && text[i] != '"' && text[i] != '\n')
                ++i;
            if (i < len && text[i] == '"')
                ++i;   // skip closing quote
            setStylingForChars(strStart, i, String);
            continue;
        }

        // ── Number (integer or float) ───────────────────────────────
        if (ch.isDigit() || (ch == '.' && i + 1 < len && text[i + 1].isDigit())) {
            int numStart = i;
            while (i < len && (text[i].isDigit() || text[i] == '.'))
                ++i;
            // Allow trailing E notation: 1.5E-3
            if (i < len && (text[i] == 'E' || text[i] == 'e')) {
                ++i;
                if (i < len && (text[i] == '+' || text[i] == '-'))
                    ++i;
                while (i < len && text[i].isDigit())
                    ++i;
            }
            setStylingForChars(numStart, i, Number);
            continue;
        }

        // ── Identifier / keyword / builtin ──────────────────────────
        if (ch.isLetter() || ch == '_') {
            int wordStart = i;
            while (i < len && (text[i].isLetterOrNumber() || text[i] == '_'))
                ++i;
            // Include trailing $ or # (string/integer variable suffix)
            bool hasSuffix = false;
            if (i < len && (text[i] == '$' || text[i] == '#')) {
                hasSuffix = true;
                ++i;
            }
            QString word = text.mid(wordStart, i - wordStart);

            if (hasSuffix) {
                // Check if it's a builtin like CHR$, STR$, etc.
                if (isBuiltin(word))
                    setStylingForChars(wordStart, i, Builtin);
                else
                    setStylingForChars(wordStart, i, VarSuffix);
            } else if (isKeyword(word)) {
                setStylingForChars(wordStart, i, Keyword);
            } else if (isBuiltin(word)) {
                setStylingForChars(wordStart, i, Builtin);
            } else if (isGraphicsCommand(word)) {
                setStylingForChars(wordStart, i, GraphicsCmd);
            } else {
                setStylingForChars(wordStart, i, Default);
            }
            continue;
        }

        // ── Multi-character operators: :=, :+, :-, <>, <=, >= ──────
        if (i + 1 < len) {
            QString two = text.mid(i, 2);
            if (two == ":=" || two == ":+" || two == ":-" ||
                two == "<>" || two == "<=" || two == ">=") {
                setStyling(2, Operator);
                i += 2;
                continue;
            }
        }

        // ── Single-character operators ──────────────────────────────
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
            ch == '^' || ch == '=' || ch == '<' || ch == '>' ||
            ch == '(' || ch == ')') {
            setStyling(1, Operator);
            ++i;
            continue;
        }

        // ── Everything else (whitespace, commas, etc.) ──────────────
        setStyling(1, Default);
        ++i;
    }
}
