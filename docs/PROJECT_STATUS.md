# OpenCOMAL Modernization — Project Status

**Last Updated:** 10 March 2026

---

## Quick Status Overview

| Component | Status | Lines |
|-----------|--------|-------|
| Parser Library (libcomal-parser) | ✅ Complete | ~4500 |
| Runtime Library (libcomal-runtime) | ✅ Complete | ~4500 |
| Graphics Library (libcomal-graphics) | ✅ Complete | ~690 |
| LSP Server (comal-lsp) | ✅ Complete | ~1000 |
| Qt6 GUI IDE (comal-ide) | 🔧 In Progress | ~2200 |
| Test Suite | ✅ 127/133 pass | 133 programs |

**Current Phase:** Phase 5 — Qt6 GUI IDE. All prior phases complete.

**Test results:** 127 pass, 6 skip (interactive/infinite-loop/squash-format),
0 failures.

---

## Architecture

```
┌──────────────┐  ┌──────────────────┐  ┌──────────────────┐
│ comal-ide    │  │ comal-lsp        │  │ comal-run (CLI)  │
│ Qt6 GUI      │  │ LSP server       │  │ batch runner     │
└──────┬───────┘  └────────┬─────────┘  └────────┬─────────┘
       │                   │                     │
       ▼                   ▼                     ▼
┌──────────────────────────────────────────────────────────┐
│              libcomal-runtime  (C++20)                   │
│  Interpreter · Executor · Evaluator · Builtins · FileIO  │
└──────────────────────────┬───────────────────────────────┘
                           │
       ┌───────────────────┼───────────────────┐
       ▼                   ▼                   ▼
┌──────────────┐  ┌──────────────────┐  ┌──────────────┐
│ libcomal-    │  │ libcomal-        │  │ legacy/      │
│ parser       │  │ graphics         │  │ (C reference)│
│ Bison/Flex   │  │ Scene model      │  │              │
└──────────────┘  └──────────────────┘  └──────────────┘
```

---

## Completed Components

### Parser Library (`libcomal-parser/`) — ~4500 lines

Bison/Flex grammar producing a modern C++20 AST via a conversion layer.

- **Modern AST** (`comal_ast_modern.h`, ~950 lines): `Expression` with
  `std::variant`, `ComalLine`, `StatementType` enum, record types for all
  statement forms (ForRec, IfWhileRec, ProcFuncRec, PrintRec, etc.)
- **Conversion layer** (`ast_compat.cpp`, ~600 lines): bidirectional
  legacy↔modern AST conversion. Maps 70+ legacy cmd values to `StatementType`.
- **Public API**: `comal_parse_line_modern()` → `ComalLine*`
- **CLI tools**: `comal-parse-cli` (with `-m` for modern AST output),
  `comal-ast-demo`
- **Numberless program support**: programs without COMAL line numbers are
  accepted; sequential file line numbers assigned automatically.

### Runtime Library (`libcomal-runtime/`) — ~4500 lines

Complete batch execution engine for COMAL programs.

- **Value** type: `std::variant<int64_t, double, std::string>` + ArrayData
- **ScopeStack** with CLOSED support for lexical scoping
- **Executor**: 40+ statement types dispatched via `StatementType` switch
- **Evaluator**: recursive expression walker (binary/unary ops, subscripting,
  substring extraction, builtin/FUNC calls)
- **Builtins**: ABS, SIN, COS, TAN, INT, LEN, CHR$, STR$, VAL, SPLIT$, etc.
- **File I/O**: OPEN/CLOSE, sequential READ/WRITE, PRINT FILE
- **PRINT USING**: format-string output (e.g. `####.##`)
- **Interrupt handling**: `InterruptController` with `std::atomic<bool>`,
  checked at loop boundaries. CLI hooks SIGINT; GUI calls `interrupt().request()`.
- **DRAW dispatch**: evaluates args → calls graphics library → notifies GUI
  via callback

### Graphics Library (`libcomal-graphics/`) — ~690 lines

Self-contained scene model and command parser for 2D drawing.

- **13 commands**: line, rect, circle, ellipse, stroke, fill, noFill,
  noStroke, lineWidth, background, clear, translate, rotate, scale
- **Scene model**: tree of Group nodes with shapes, transforms, style state
- **Command registry**: name→spec mapping with arity validation
- **Group nesting**: dot-notation paths (`Spaceship.Engine.rect …`),
  auto-created on first use
- **Unit tests**: command parsing and scene execution

### LSP Server (`comal-lsp/`) — ~1000 lines

Language Server Protocol v3.17 implementation.

- Parse error diagnostics
- Code completion (keywords, builtins, symbols)
- Go-to-definition (PROC/FUNC)
- Hover information
- Symbol table building from parsed AST

### Test Infrastructure (`tests/`)

- **119 numbered** test programs in `tests/programs/`
- **14 numberless** test programs in `tests/programs-nonum/`
- Unified test runner: `tests/run_tests.sh` (CTest-integrated)
- **Results**: 127 pass, 6 skip, 0 failures

---

## In Progress: Qt6 GUI IDE (`comal-ide/`) — ~2200 lines

**Toolkit:** Qt6 6.10 + QScintilla 2.14 (not KDE Frameworks).

### Working Features

| Feature | Notes |
|---------|-------|
| Multi-tab editor | QScintilla, tab close with dirty-file prompt |
| Syntax highlighting | Custom `QsciLexerComal`: keywords (bold blue), builtins (teal), strings (red), numbers (green), comments (green), operators (purple), variable suffixes (brown) |
| File operations | New, Open, Save, Save As, Close |
| Edit operations | Undo, Redo, Cut, Copy, Paste |
| Run / Stop | QThread worker with interrupt support |
| Format Source | Keyword uppercasing, `=`→`:=` fixing, block indentation |
| Line number stripping | Strips COMAL line numbers on open |
| Error highlighting | Red background marker on error line |
| PRINT / INPUT I/O | Output panel with prompt line, context menu |
| File browser | QTreeView of .lst/.prl/.prc files |
| Graphics panel | QGraphicsView rendering of DRAW commands (line, rect, circle, ellipse, styles, groups, transforms). Save as PNG/SVG. |
| Status bar | Line/col, run state, current file |

### Architecture

- **`RunWorker`** — QThread subclass owning an `Interpreter` + `QtIO`
- **`QtIO`** — signal/slot I/O bridge with `QWaitCondition` for blocking INPUT
- **`GraphicsPanel`** — renders `Scene` graph to `QGraphicsScene` items
- **Persistent scene** — survives between program runs
- **Scene-changed callback** → Qt signal (queued connection) → GUI re-render

### Not Yet Implemented

- Breakpoint gutter / debug panel
- Help panel (COMAL keyword reference)
- Find/Replace
- Settings/preferences dialog
- LSP integration (live diagnostics, completion, hover in editor)

### Window Layout

| Panel | Position | Widget |
|-------|----------|--------|
| Code editor (tabbed) | Central | QScintilla |
| Direct command / Output | Bottom | QTextEdit + QLineEdit |
| File browser | Left | QTreeView |
| Graphics canvas | Right | QGraphicsView |
| Debug | Bottom-right | Placeholder |
| Help | Right | Placeholder |

### Menus

| Menu | Items |
|------|-------|
| File | New, Open, Save, Save As, Close, Exit |
| Edit | Undo, Redo, Cut, Copy, Paste, Format Source |
| Program | Run, Stop |
| View | Toggle each panel, Reset Layout |

---

## Future Improvements

### Animation Support
DRAW `animate` command for group-level property animation
(`animate property to value over durationMs [easing] [loop|yoyo]`).
Uses Qt's `QPropertyAnimation` framework (no QML needed). Requires QObject
property wrappers per group and a continuous render loop or incremental
transform updates. See `docs/future_graphics_addon.md` §2.3.

### Stream Processing
Generalize INPUT to accept stream sources (`INPUT STREAM`) for reading
from stdin/pipes, enabling COMAL programs in Unix pipelines
(`cat data.txt | comal-run filter.lst`).

### Multithreading
`INPUT QUEUE` for inter-thread message passing — COMAL PROCs running in
separate threads communicating via typed message channels.

### Packaging
CPack configuration for `.rpm` and `.deb` packages. Package `comal-run`,
`comal-ide`, shared libraries, sample programs.

**Building packages (DEB and RPM)**

From the repository root, create a build dir and run CPack via CMake:

```bash
cmake -S . -B build -DCPACK_GENERATOR="DEB;RPM"
cmake --build build --target package
```

Generated packages will appear in the `build/` directory (e.g. `OpenCOMAL-0.0.1.deb`, `OpenCOMAL-0.0.1.rpm`).
Adjust `CPACK_PACKAGE_VERSION` and maintainer fields in `CMakeLists.txt` as needed.

---

## Key Design Decisions

| Decision | Rationale |
|----------|-----------|
| Pool allocation preserved | Performance; matches legacy parser's memory model |
| `std::variant` for Value/Expression | Type safety over C unions |
| `enum class StatementType` | Exhaustive switch checking |
| Raw pointers + RAII wrapper | Matches Qt ownership style |
| Line numbers discarded on import | COMAL has no GOTO; numbers were BASIC-era artifact |
| Plain `double` for float constants | Eliminated `struct dubbel`; `std::to_chars` for formatting |
| Qt Widgets (not QML) | Simpler, sufficient for COMAL IDE needs |
| QScintilla custom lexer | Avoids recompiling Scintilla; ~200 lines for full highlighting |

---

## Build

```bash
# Build everything
cd build && cmake .. && make -j$(nproc)

# Run a COMAL program
./build/libcomal-runtime/comal-run tests/programs/hello.lst

# Run all tests
bash tests/run_tests.sh ./build/libcomal-runtime/comal-run

# Run via CTest
cd build && ctest --output-on-failure
```

**Dependencies:** C++20, GCC 15, CMake 3.16+, Qt6, QScintilla for Qt6,
libncurses-dev, libreadline-dev.

| Fedora / RPM | Debian / DEB |
|--------------|--------------|
| qt6-qtbase-devel | qt6-base-dev |
| qt6-qtsvg-devel | qt6-svg-dev |
| qscintilla-qt6-devel | libqscintilla2-qt6-dev |

---

## Bugs Found & Fixed (Historical)

### Parser (Phase 3)
1. **`id_root` use-after-free** — `comal_parser_reset()` freed pool but didn't null `id_root` BST pointer. Fixed: `id_reset()`.
2. **Uninitialized memory** — `mem_alloc()` used `malloc()`. Fixed: `calloc()`.
3. **SYS/SYS$ data layout** — conversion accessed wrong union field. Fixed: separate handling.

### Runtime (Phase 4)
4. **Short-form IF/FOR/WHILE** — `stat` pointer set to nullptr, never linked. Fixed: recursive conversion.
5. **ELIF/UNTIL variant mismatch** — used `asIfWhile()` instead of `std::get_if<Expression*>()`. Fixed.
6. **PROC/FUNC body fall-through** — no skip in `execLine`. Fixed: jump to ENDPROC/ENDFUNC via `linePtr`.
7. **PROC call return** — saved cursor inside try block, lost on `ReturnSignal`. Fixed: moved outside try.
8. **FOR step-direction** — negative step with TO looped forever. Fixed: direction-aware `pastEnd()`.
9. **String FUNC vs array** — `evalSid()` created variable before checking procTable. Fixed: check procTable first.
10. **`id_search` missing `strlwr`** — caused uppercase names and double-`$` suffixes. Fixed.
11. **`resolveLval` ignored `OpType::Sid`** — string array element assignment failed. Fixed.
12. **SYS/SYS$ case sensitivity** — after `strlwr` fix, comparisons expected uppercase. Fixed.

### IDE (Phase 5)
13. **DRAW keyword not uppercased** — missing from `comalKeywords()` set. Fixed.
