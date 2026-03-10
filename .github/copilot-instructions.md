# OpenCOMAL — Copilot Instructions

Purpose: give AI coding agents the essential, actionable knowledge
to be productive in this repository (build, structure, conventions).

**Quick Commands:**
- **Build (modern, CMake):** `cd build && cmake .. && make -j$(nproc)`
- **Run program:** `./build/libcomal-runtime/comal-run path/to/file.lst`
- **Build legacy:** `cd legacy && make` (C11, requires libncurses-dev, libreadline-dev)
- **Clean:** `cd build && make clean`
- **Generate parser/lexer manually:** `bison -vd` and `flex` (CMake does this automatically).

**Big Picture / Architecture:**
This project has a **modern C++20** frontend and runtime, plus a **legacy C** codebase for reference.

- `libcomal-parser/` — C++20 parser library. Bison/Flex grammar → legacy AST → modern AST conversion.
  - `include/comal_ast_modern.h` — Modern AST definitions (~950 lines): Expression (variant-based), ComalLine, StatementType enum, ForRec, IfWhileRec, ProcFuncRec, etc.
  - `include/comal_ast.h` — Legacy C AST structures (id_rec, string, VAL_TYPE)
  - `include/comal_parser_api.h` — Public parser API (C and C++)
  - `src/ast_compat.cpp` — Legacy↔Modern AST conversion (~600+ lines)
  - `src/parser_api.cpp` — Parser API implementation
  - `tools/parse_cli.cpp` — Parser CLI (`-m` for modern AST output)
  - `tools/ast_demo.cpp` — AST demo/test tool
- `libcomal-runtime/` — C++20 runtime library (~4200 lines).
  - `include/` — Headers: `comal_interpreter.h`, `comal_executor.h`, `comal_evaluator.h`, `comal_value.h`, `comal_scope.h`, `comal_builtins.h`, `comal_file_io.h`, `comal_error.h`, `comal_interrupt.h`
  - `src/` — Implementations: `executor.cpp` (1627 lines, main dispatch), `evaluator.cpp` (478), `program.cpp` (378), `value.cpp` (273), `builtins.cpp` (287), `file_io.cpp` (193), `scope.cpp` (138), `runtime_error.cpp` (13)
  - `tools/comal_run.cpp` — Batch execution CLI with SIGINT interrupt handling
- `tests/` — Test infrastructure.
  - `run_tests.sh` — Unified test runner (numbered + numberless tests, CTest-integrated)
  - `programs/` — 119 numbered `.lst` test programs (+ 5 `.prl`, 1 `.prc`)
  - `programs-nonum/` — 13 numberless `.lst` test programs (line-number-free syntax)
- `legacy/` — Original C implementation (reference only).
  - `src/` — C sources with `pdc*` prefix (pdcexec.c, pdcrun.c, etc.)
  - `bin/` — Legacy binaries (opencomal, opencomalrun)
- `docs/` — Project documentation.
  - `PROJECT_STATUS.md` — **Comprehensive status** (read this first!)
  - `AST_MODERNIZATION.md` — Phase plan and design decisions
  - `AST_USAGE.md` — Modern AST usage patterns and examples
- `comal-ide/` — Qt6 GUI IDE (in progress: multi-tab editor, syntax highlighting, run/stop, graphics, Format Source, file ops)
  - `include/` — Headers: `main_window.h`, `code_editor_panel.h`, `qsci_lexer_comal.h`, `direct_command_panel.h`, `graphics_panel.h`, `qt_io.h`, `run_worker.h`, panel headers
  - `src/` — Implementations: `main_window.cpp` (401), `code_editor_panel.cpp` (532), `qsci_lexer_comal.cpp` (216), `direct_command_panel.cpp` (177), `graphics_panel.cpp` (157), `run_worker.cpp` (81), `qt_io.cpp` (50), panel stubs
- `comal-lsp/` — LSP server (complete: diagnostics, completion, definition, hover)

**Build specifics (modern):**
- CMake build, C++20, GCC 15
- Dependencies: `libncurses-dev`, `libreadline-dev` (for legacy parser that is linked)
- Generated sources: `parser.tab.cc` (from Bison) and `lex.yy.cc` (from Flex) in `build/libcomal-parser/`
- Three build targets: `comal-parser` (library), `comal-parse-cli`, `comal-ast-demo`, `comal-run`, `comal-ide`

**Project-specific conventions & patterns:**
- Legacy C files use `pdc*` prefix (e.g., `pdcenv.c`, `pdcstr.c`)
- Modern C++ files use `comal_*` prefix (e.g., `comal_executor.cpp`, `comal_value.h`)
- Runtime uses `std::variant`-based `Value` type: `{int64_t, double, std::string}`
- Exception-based control flow: `ReturnSignal` for PROC/FUNC return, `StopSignal` for END/STOP
- `ScopeStack` with CLOSED support for variable scoping
- Token constants in `parser.tab.h` (toSYM=364, downtoSYM=280, etc.)
- Builtin function codes in `comal_functions.h` (_ABS=4000 through _SPLIT=4039)

**Where to look for common changes:**
- GUI syntax highlighting: `comal-ide/src/qsci_lexer_comal.cpp`
- GUI panels and wiring: `comal-ide/src/main_window.cpp`
- GUI editor and formatting: `comal-ide/src/code_editor_panel.cpp`
- GUI runtime worker: `comal-ide/src/run_worker.cpp`
- Statement execution: `libcomal-runtime/src/executor.cpp`
- Expression evaluation: `libcomal-runtime/src/evaluator.cpp`
- Builtin functions: `libcomal-runtime/src/builtins.cpp`
- AST definitions: `libcomal-parser/include/comal_ast_modern.h`
- Parser grammar: `libcomal-parser/src/pdcpars.y`, `libcomal-parser/src/pdclex.l`
- Legacy execution (reference): `legacy/src/pdcexec.c`, `legacy/src/pdcrun.c`

**Testing & validation tips:**
- Test programs (numbered): `tests/programs/*.lst` (~119 files)
- Test programs (numberless): `tests/programs-nonum/*.lst` (13 files)
- Run single test: `./build/libcomal-runtime/comal-run tests/programs/for1.lst`
- Run all tests: `bash tests/run_tests.sh` (127 PASS / 0 FAIL / 6 SKIP / 133 TOTAL)
- Run via CTest: `cd build && ctest --output-on-failure`
- Test runner: `tests/run_tests.sh` — accepts optional path to `comal-run` binary, skips interactive/infinite-loop tests
- Pre-existing skips: rnd()1, rnd()2, signif1 (infinite loops), gentest (interactive), lst2sq, sq2lst (squash format)
- Numberless tests verify line-number-free parsing: FOR, IF, WHILE, REPEAT, PROC, FUNC, CASE, TRAP, nested, mixed, simple, DATA, EXIT

**Current project phase:**
- Phases 1-4 complete (Expression AST, Statement AST, Parser Integration, Runtime Library)
- Phase 5 in progress: Qt6 GUI IDE (comal-ide/) — ~2200 lines
  - Working: multi-tab editor, syntax highlighting (custom QsciLexerComal), run/stop, Format Source, graphics panel (DRAW rendering), file browser, I/O panel
  - Not yet: debug panel, help panel, Find/Replace, settings, LSP integration
- Graphics library complete (libcomal-graphics/) — 13 DRAW commands, scene model, group nesting
- LSP Server complete (diagnostics, completion, definition, hover)
- Numberless program support: parser accepts programs without COMAL line numbers
- 127/133 tests passing (6 skipped: interactive/infinite-loop/squash-format)
- See `docs/PROJECT_STATUS.md` for detailed status

**Editing notes for contributors/agents:**
- Prefer minimal, localized changes
- Keep modern C++ naming consistent with `comal_*` prefix
- Test changes by building and running a relevant `.lst` file
- Read `docs/PROJECT_STATUS.md` Phase 4 section for known bugs and priorities
- When adding runtime features, update executor.cpp dispatch switch and add tests
