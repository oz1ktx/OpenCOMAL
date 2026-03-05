#ifndef COMAL_PARSER_API_H
#define COMAL_PARSER_API_H

#include <stddef.h>

#include "comal_ast.h"

// Legacy API — returns a C struct
int comal_parse_line(const char *line, struct comal_line *out_line,
			     char *errbuf, size_t errbuf_len, int *errpos);
void comal_parser_reset(void);

// Modern C++ API
#ifdef __cplusplus
#include "comal_ast_modern.h"

namespace comal {

/// Parse a single COMAL line and return a modern ComalLine*.
/// The returned pointer is heap-allocated; caller owns it.
/// On parse error, returns nullptr and fills errbuf/errpos.
ComalLine* comal_parse_line_modern(const char *line,
                                   char *errbuf, size_t errbuf_len,
                                   int *errpos);

/// Convert a legacy comal_line to a modern ComalLine*.
/// Caller owns the returned pointer.
ComalLine* convert_comal_line(const struct comal_line* old_line);

/// Convert a legacy expression to a modern Expression*.
Expression* convert_expression(const struct expression* old_exp);

/// Convert a modern expression to a legacy expression (pool-allocated).
struct expression* convert_to_legacy_expression(const Expression* new_exp, int pool);

/// Return a human-readable name for a StatementType enum value
const char* statement_type_name(StatementType cmd);

} // namespace comal
#endif

#endif
