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
- `libcomal-runtime/` — C++20 runtime library (IN PROGRESS, ~3521 lines).
  - `include/` — Headers: `comal_interpreter.h`, `comal_executor.h`, `comal_evaluator.h`, `comal_value.h`, `comal_scope.h`, `comal_builtins.h`, `comal_file_io.h`, `comal_runtime_error.h`
  - `src/` — Implementations: `executor.cpp` (1185 lines, main dispatch), `evaluator.cpp` (402), `program.cpp` (364), `value.cpp` (252), `builtins.cpp` (222), `file_io.cpp` (215), `scope.cpp` (116), `runtime_error.cpp` (13)
  - `tools/comal_run.cpp` — Batch execution CLI
- `legacy/` — Original C implementation (reference only).
  - `src/` — C sources with `pdc*` prefix (pdcexec.c, pdcrun.c, etc.)
  - `samples/tests/` — ~113 `.lst` test programs
  - `bin/` — Legacy binaries (opencomal, opencomalrun)
- `docs/` — Project documentation.
  - `PROJECT_STATUS.md` — **Comprehensive status** (read this first!)
  - `AST_MODERNIZATION.md` — Phase plan and design decisions
  - `AST_USAGE.md` — Modern AST usage patterns and examples
- `comal-ide/` — Future IDE (not started)
- `comal-lsp/` — Future LSP server (not started)

**Build specifics (modern):**
- CMake build, C++20, GCC 15
- Dependencies: `libncurses-dev`, `libreadline-dev` (for legacy parser that is linked)
- Generated sources: `parser.tab.cc` (from Bison) and `lex.yy.cc` (from Flex) in `build/libcomal-parser/`
- Three build targets: `comal-parser` (library), `comal-parse-cli`, `comal-ast-demo`, `comal-run`

**Project-specific conventions & patterns:**
- Legacy C files use `pdc*` prefix (e.g., `pdcenv.c`, `pdcstr.c`)
- Modern C++ files use `comal_*` prefix (e.g., `comal_executor.cpp`, `comal_value.h`)
- Runtime uses `std::variant`-based `Value` type: `{int64_t, double, std::string}`
- Exception-based control flow: `ReturnSignal` for PROC/FUNC return, `StopSignal` for END/STOP
- `ScopeStack` with CLOSED support for variable scoping
- Token constants in `parser.tab.h` (toSYM=364, downtoSYM=280, etc.)
- Builtin function codes in `comal_functions.h` (_ABS=4000 through _SPLIT=4039)

**Where to look for common changes:**
- Statement execution: `libcomal-runtime/src/executor.cpp`
- Expression evaluation: `libcomal-runtime/src/evaluator.cpp`
- Builtin functions: `libcomal-runtime/src/builtins.cpp`
- AST definitions: `libcomal-parser/include/comal_ast_modern.h`
- Parser grammar: `libcomal-parser/src/pdcpars.y`, `libcomal-parser/src/pdclex.l`
- Legacy execution (reference): `legacy/src/pdcexec.c`, `legacy/src/pdcrun.c`

**Testing & validation tips:**
- Test programs: `legacy/samples/tests/*.lst` (~113 files)
- Run single test: `./build/libcomal-runtime/comal-run legacy/samples/tests/for1.lst`
- Run all tests: `cd build && for f in ../legacy/samples/tests/*.lst; do timeout 2 ./libcomal-runtime/comal-run "$f" >/dev/null 2>&1 && echo "PASS $(basename $f)" || echo "FAIL $(basename $f)"; done`
- No automated test harness yet; manual verification against expected output
- Some tests need INPUT (will timeout with no stdin) — use timeout

**Current project phase:**
- Phases 1-3 complete (Expression AST, Statement AST, Parser Integration)
- Phase 4 in progress (~50%): Runtime Library — batch execution of .lst files
- 13/25 tests passing in partial suite run
- See `docs/PROJECT_STATUS.md` for detailed status, bugs found/fixed, and priorities

**Editing notes for contributors/agents:**
- Prefer minimal, localized changes
- Keep modern C++ naming consistent with `comal_*` prefix
- Test changes by building and running a relevant `.lst` file
- Read `docs/PROJECT_STATUS.md` Phase 4 section for known bugs and priorities
- When adding runtime features, update executor.cpp dispatch switch and add tests
