# libcomal-parser

C++20 parser library providing modern AST construction from COMAL source text.

## Current Status (May 2026)

**Modernization Complete:**
- Modern AST fully defined in `include/comal_ast_modern.h` (~950 lines)
- Public API: `comal_parse_line_modern()` for immediate execution
- Compatibility layer: `src/ast_compat.cpp` seamlessly converts legacy→modern AST during parsing
- Numberless COMAL program support fully implemented (line numbers optional)
- Backend: Original Flex/Bison grammar sources with C support routines

**Architecture:**
- Parser uses legacy AST internally (proven, stable)
- Automatic conversion to modern AST for runtime execution
- Separation maintained for compatibility and gradual modernization

**Design Details:**
See `docs/AST_MODERNIZATION.md` for the complete transition plan and current phase status.
