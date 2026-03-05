# SPLIT$

Signature: SPLIT$(source$, separator$, index)

- Returns the Nth token (1-based) from `source$` split by the substring `separator$`.
- If `separator$` is the empty string, behaviour: index==1 returns the whole `source$`, other indexes return an empty string.
- If `index` is out of range the function returns an empty string.
- Numeric first/second parameters are coerced to strings; the third parameter must be numeric (integer or float).

Examples:

- `PRINT SPLIT$("a;b;c",";",1)` -> `a`
- `PRINT SPLIT$("a;b;c",";",3)` -> `c`
- `LET s$ = "x:y" : PRINT SPLIT$(s$, ":", 2)` -> `y`

Notes:
- Indexing is 1-based by design.
- Whitespace around parameters is ignored by the parser.
