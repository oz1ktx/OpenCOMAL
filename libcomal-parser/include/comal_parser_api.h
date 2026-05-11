#ifndef COMAL_PARSER_API_H
#define COMAL_PARSER_API_H

#include <stddef.h>

// Forward declarations — callers do not need the full legacy struct layout.
// (Implementation in parser_api.cpp includes comal_ast.h directly.)
struct comal_line;
struct expression;

// ── Legacy API ───────────────────────────────────────────────────────────────
// Parses a single COMAL line into a legacy struct comal_line.
// Prefer comal_parse_line_modern() for all C++ callers.
// Retained for legacy tooling (parse_cli legacy mode) and backward compatibility.
int comal_parse_line(const char *line, struct comal_line *out_line,
                     char *errbuf, size_t errbuf_len, int *errpos);

void comal_parser_reset(void);

// ── Modern C++ API ───────────────────────────────────────────────────────────
#ifdef __cplusplus
#include "comal_ast_modern.h"

namespace comal {

/// Parse a single COMAL line and return a modern ComalLine*.
/// The returned pointer is heap-allocated; caller owns it.
/// On parse error, returns nullptr and fills errbuf/errpos.
ComalLine* comal_parse_line_modern(const char *line,
                                   char *errbuf, size_t errbuf_len,
                                   int *errpos);

/// Return a human-readable name for a StatementType enum value.
const char* statement_type_name(StatementType cmd);

} // namespace comal
#endif

#endif
