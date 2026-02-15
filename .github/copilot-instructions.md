# OpenCOMAL — Copilot Instructions

Purpose: give AI coding agents the essential, actionable knowledge
to be productive in this repository (build, structure, conventions).

**Quick Commands:**
- **Build:** `make` (top-level) or `cd src && make` to build the binaries.
- **Install:** `make install` (top-level runs `cd bin && make install`).
- **Clean:** `make clean` (top-level delegates to `src` makefile).
- **Generate parser/lexer manually:** `bison -vd src/pdcpars.y` and `flex src/pdclex.l` (the `src/Makefile` does this automatically).

**Big Picture / Architecture:**
- `src/` — C implementation of the COMAL interpreter. Key entry points: `pdcmain.c`, `pdccloop.c`, `pdcrun.c`.
- `bin/` — produced binaries: `opencomal` (interactive interpreter) and `opencomalrun` (batch runner). See `bin/Makefile` for install steps.
- `tools/` — small build helpers (`bumpbuild`, `genversion`, `gentar`) used from the `src/Makefile`.
- `doc/` and `README.md` — historical docs and platform notes.
- `tests/` — many `.lst` files (sample programs / expected behaviors). There is no automated test harness; tests are example inputs/outputs.

**Build specifics (important):**
- Compiler flags in `src/Makefile`: `-std=c11 -DOS_LINUX -Os` plus `-flto` are used. Avoid changing global flags without testing linkage.
- External libs: `-lncurses` and `-lreadline` (look at `OSLIB` and `LIBS` in `src/Makefile`). Install system packages `libncurses-dev` and `libreadline-dev` before building on Debian/Ubuntu.
- Generated sources: `pdcpars.tab.c` (from `pdcpars.y`) and `lex.yy.c` (from `pdclex.l`) — these are included in `SOURCES`/dependency include. Do not remove the rules that regenerate them.
- Build number/version: `src/BUILD` holds the build number (e.g., `597`). `src/Makefile` calls `../tools/bumpbuild BUILD` and `../tools/genversion` from the `build` target.

**Project-specific conventions & patterns:**
- C symbol and file prefix: most sources and headers begin with `pdc*` (for example `pdcenv.c`, `pdcstr.c`, `pdcsym.c`). Follow the naming when adding new modules.
- Parser/lexer workflow: changes to grammar (`pdcpars.y`) or lexer (`pdclex.l`) should be followed by `make` which runs `bison`/`flex` and updates generated files.
- Dependency files `.d` are generated and `include`d at the end of `src/Makefile`. Commit only source and generated outputs intentionally; prefer committing generated parser/lexer output when needed for reproducible builds on systems without `bison`/`flex`.
- When adding a new source file, update `SOURCES`, and the corresponding `OBJ1`/`OBJ2` lists in `src/Makefile` to include it in the correct binary.

**Where to look for common changes:**
- Parser/lexer: `src/pdcpars.y`, `src/pdclex.l`.
- Runtime entry and dispatch: `src/pdcmain.c`, `src/pdcexec.c`, `src/pdcrun.c`, `src/pdccloop.c`.
- Environment and state: `src/pdcenv.c`, `src/pdcval.c`, `src/pdcsym.c`.
- Memory helpers and utilities: `src/pdcmem.c`, `src/pdcstr.c`, `src/pdcmisc.c`.
- Build helpers: `tools/bumpbuild`, `tools/genversion`, `tools/gentar`.

**Testing & validation tips:**
- The `tests/` folder contains many `.lst` examples. Use `bin/opencomal` interactively to test behavior, or `bin/opencomalrun` to run scripts non-interactively.
- There is no CI runner or test script; for quick verification build `src` and try a few `tests/*.lst` programs manually.

**Editing note for contributors/agents:**
- Prefer minimal, localized changes. Keep C style and file naming consistent with `pdc*` conventions.
- Avoid editing generated files unless necessary; if you regenerate parser/lexer, ensure generated outputs are in sync with committed sources.
- When touching build rules, ensure `bison`/`flex` and `makedepend` compatibility; test on a clean checkout.

If any section is unclear or you'd like examples added (for example: a short recipe to run one of the `tests/*.lst` files), tell me which part and I'll iterate.
