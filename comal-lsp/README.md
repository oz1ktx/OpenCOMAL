# OpenCOMAL Language Server Protocol (LSP)

Language Server Protocol (LSP) implementation for OpenCOMAL, enabling IDE integration with VS Code, Kate, Vim, and other LSP-compatible editors.

## Features

- **Syntax Highlighting** — Semantic tokens via token providers (Kate will need a COMAL highlighting file or manual mode assignment; see notes below)
- **Diagnostics** — Real-time parse errors and type checking
- **Code Completion** — Context-aware suggestions for keywords and identifiers
- **Go-to-Definition** — Navigate to PROC and FUNC declarations
- **Hover Information** — Type hints and documentation
- **Symbol Navigation** — Outline and rename support

> **Kate syntax mode**
> Kate ships without a COMAL definition, so `.lst` files often pick up
> COBOL/Fortran highlighting or remain plain text.  To get proper colours you
> can either:
>
> 1. **Create a minimal syntax file** (place in
>    `~/.local/share/org.kde.syntax-highlighting/syntax/`):
>
>    ```xml
>    <language name="COMAL" version="1.0" section="1">
>      <author>OpenCOMAL Team</author>
>      <highlighting>
>        <listString>PRINT|INPUT|IF|THEN|ELSE|END|FOR|TO|STEP|NEXT|PROC|FUNC|RETURN</listString>
>        <comment start="#" />
>        <string start='\"' end='\"' />
>        <numbers />
>      </highlighting>
>    </language>
>    ```
>
>    Restart Kate and choose **Tools → Mode → COMAL**.
>
> 2. **Manually assign an existing mode** (e.g. COBOL) via
>    **Settings → Configure Kate → Filetypes**, then add `*.lst` to the
>    filter.
>
> The server itself does not depend on highlighting; Kate simply needs to
> activate the `comal` LSP server for `.lst` files (see `fileMatch` in the
> LSP configuration).


## Status (May 2026)

**Production-Ready** ✅

All core LSP features are implemented and integrated with the Qt IDE and editor ecosystem:

**Implemented Features:**
- ✓ **Diagnostics** — Real-time parse errors and syntax checking with parser-backed statement classification
- ✓ **Hover** — Type hints and documentation including grouped DRAW forms (e.g., `HUD.line`)
- ✓ **Completion** — Context-aware keyword and identifier suggestions
- ✓ **Go-to-Definition** — Navigate to PROC and FUNC declarations
- ✓ **Document Tracking** — Real-time updates for saved and unsaved (`untitled://`) files
- ✓ **Symbol Navigation** — Rename support and definition lookup

**Integration:**
- Embedded in Qt IDE (`comal-ide`) with full diagnostics in editor
- Standalone server mode for VS Code, Kate, Vim, and other LSP clients
- Robust protocol framing (`Content-Length` transport)
- Custom JSON parser (no external dependencies)

**Recent Enhancements:**
- Parser-backed diagnostics for improved accuracy
- Support for unsaved editor buffers via `untitled://` URIs
- Grouped DRAW command hover support

For integration details, see `docs/COMAL_LSP_USAGE.md`.
- ✓ Definition lookup from modern AST
- ✓ Hover information system
- ✓ Symbol table building for PROC/FUNC definitions

**Phase 4: VS Code Integration**
- ⏳ comal-lsp VS Code extension
- ⏳ Client-side settings and configuration

## Building

```bash
cd build
cmake ..
make -j$(nproc)
```

The LSP server executable will be at `build/comal-lsp/comal-lsp`.

## Running

Typically run by an LSP client (VS Code extension, Neovim plugin, etc.). For testing:

```bash
./comal-lsp
```

The server will listen on stdin for LSP messages formatted with Content-Length headers.

## Architecture

- **comal_lsp_server.h/cpp** — Main LSP server implementation
- **comal_lsp_protocol.h/cpp** — LSP protocol message parsing and serialization
- **comal_lsp.cpp** — CLI entry point

The server integrates with:
- `libcomal-parser` — For parsing and modern AST
- `libcomal-runtime` — For execution context and diagnostics

## Dependencies

- **C++20** compiler (GCC 15+)
- **nlohmann/json** (optional, for production JSON parsing)
- **libcomal-parser** and **libcomal-runtime** (internal)

## See Also

- [LSP Specification](https://microsoft.github.io/language-server-protocol/)
- [PROJECT_STATUS.md](../docs/PROJECT_STATUS.md) — Overall development roadmap
- [AST_USAGE.md](../docs/AST_USAGE.md) — Modern AST usage patterns
