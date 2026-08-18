# comal-ide

Qt6 graphical IDE for writing, running, and debugging COMAL programs.

## Features

- **Multi-tab editor** with syntax highlighting (custom `QsciLexerComal` via QScintilla)
- **Run / Stop** — execute programs and interrupt them with a single button
- **Format Source** — auto-indent and keyword capitalisation
- **Live LSP diagnostics** — parse errors shown inline in the editor as you type (via embedded `comal-lsp`)
- **Graphics panel** — renders `DRAW` output from running programs
- **Direct command panel** — REPL-style command entry while a program's definitions are retained
- **File browser panel** — navigate and open `.lst` files
- **Debug panel** — breakpoints, step, variable inspection; Z80 register/memory/disassembly view for assembly programs
- **Assembly output panel** — assembles Z80 `.asm` source via `sjasmplus` and runs the resulting `.COM` file
- **Sound** — `TONE` and `PLAY` statements produce audio via `libcomal-sound`
- **Settings dialog** — font, theme, LSP path, and interpreter options

## Architecture

| Component | Purpose |
|-----------|---------|
| `main_window.cpp` | Top-level window, menu bar, panel wiring |
| `code_editor_panel.cpp` | QScintilla-based editor with LSP annotation |
| `qsci_lexer_comal.cpp` | Custom QScintilla lexer for COMAL syntax |
| `run_worker.cpp` | Background thread that drives `libcomal-runtime` |
| `graphics_panel.cpp` | `QGraphicsScene` renderer for `libcomal-graphics` output |
| `direct_command_panel.cpp` | Interactive command entry and output |
| `debug_panel.cpp` | Breakpoint and variable inspector |
| `assembly_output_panel.cpp` | Z80 assembly workflow panel |
| `comal_lsp_client.h/cpp` | Embedded LSP client talking to `comal-lsp` |

## Dependencies

- Qt 6 (Base, SVG, Multimedia)
- QScintilla2 for Qt6 (`libqscintilla2-qt6-dev`)
- `libcomal-parser`, `libcomal-runtime`, `libcomal-graphics`, `libcomal-sound` (internal)

## Building

```bash
cd build && cmake .. && make comal-ide -j$(nproc)
```

## See Also

- [`comal-lsp`](../comal-lsp/README.md) — LSP server embedded in the IDE
- [`libcomal-runtime`](../libcomal-runtime/README.md) — execution engine
- [`docs/PROJECT_STATUS.md`](../docs/PROJECT_STATUS.md) — overall project status
