#pragma once

#include <Qsci/qscilexercustom.h>

/// QScintilla custom lexer for COMAL syntax highlighting.
///
/// Style numbers:
///   0 — Default text
///   1 — Keywords (FOR, IF, PRINT, …)
///   2 — Built-in functions (SIN, COS, CHR$, LEN, …)
///   3 — String literals ("…")
///   4 — Numbers (integer and float)
///   5 — Comments (// …)
///   6 — Operators (:=, +, -, *, /, ^, <>, <=, >=)
///   7 — Variable suffixes (identifiers ending in $ or #)
class QsciLexerComal : public QsciLexerCustom {
    Q_OBJECT

public:
    enum Style {
        Default   = 0,
        Keyword   = 1,
        Builtin   = 2,
        String    = 3,
        Number    = 4,
        Comment   = 5,
        Operator  = 6,
        VarSuffix = 7,
    };

    explicit QsciLexerComal(QObject *parent = nullptr);

    const char *language() const override;
    QString description(int style) const override;
    QColor defaultColor(int style) const override;
    QFont defaultFont(int style) const override;

    void styleText(int start, int end) override;

private:
    static bool isKeyword(const QString &word);
    static bool isBuiltin(const QString &word);
};
