# OpenCOMAL Project Status

**Last Updated:** 26 April 2026
**Purpose:** Short, ordered snapshot of current project state and near-term work.

---

## At a Glance

| Area | Status | Notes |
|------|--------|-------|
| Parser (`libcomal-parser`) | Stable | Modern AST available via modern API; legacy compatibility layer still present |
| Runtime (`libcomal-runtime`) | Stable | Modern AST execution path in active use; SPAWN v1 implemented |
| Graphics (`libcomal-graphics`) | Stable | DRAW command set includes `text` and style controls |
| Sound (`libcomal-sound`) | Partial but usable | `TONE` works; `PLAY` has basic support, full MML remains TODO |
| LSP (`comal-lsp`) | Stable | Diagnostics, completion, definition, hover; parser-backed diagnostics classification is now in place |
| IDE (`comal-ide`) | In progress | Core workflow works; editor now shows live LSP diagnostics in saved and unsaved tabs |
| Test suite | Strong | 127 pass / 6 skip / 0 fail |

---

## Current Phase

**Phase 5: Qt6 IDE refinement**

All earlier modernization phases are complete enough for daily development.
Current work is mostly IDE ergonomics, debugger depth, and integration polish.

---

## What Is Working Well

### 1. Parser and AST pipeline

- Modern AST types are implemented and used in runtime-facing flows.
- Numberless COMAL programs are supported.
- Legacy AST is still present as compatibility plumbing.

### 2. Runtime execution

- Core statement execution is stable (loops, conditionals, PROC/FUNC, assignment, I/O).
- Expression evaluation and value model are stable.
- Interrupt and stop behavior is integrated for CLI and IDE usage.
- **Phase 1 queue message passing is implemented:**
  - `OPEN QUEUE <n>, "name", READ|WRITE`
  - `PRINT QUEUE <n>: ...`, `INPUT QUEUE <n>: ...`, `CLOSE QUEUE <n>`
  - `FILE` spellings for these queue channel operations are supported as compatibility aliases.
- **SPAWN v1 (restrictive) is implemented:**
  - `SPAWN procName` and `SPAWN procName(args...)` run a PROC asynchronously.
  - SPAWN target must be a `CLOSED` `PROC`.
  - Spawned workers are fire-and-forget in this iteration (no process id and no explicit join point).
  - Worker lifecycle is tied to the main interpreter; workers are cancelled when main execution ends.
  - Worker creation/registration now handles resource exhaustion safely and raises runtime errors instead of terminating the process.
  - In spawned context, call graph is restricted to `CLOSED` `PROC/FUNC` only.
  - `DIM`/`LOCAL` inside `CLOSED` `PROC/FUNC` is rejected in this restrictive mode.
  - Spawned `PRINT`/`INPUT` now route via the parent interpreter I/O path (IDE output panel compatibility).
- **File I/O semantics correctly implement COMAL 80 spec:**
  - `PRINT FILE` / `INPUT FILE` use plain text format (human-readable, line-oriented).
  - `WRITE FILE` / `READ FILE` use binary format with type tags (compatible with legacy OpenCOMAL).
  - `RANDOM` files always use binary fixed-record format.
  - Record positioning (e.g., `READ FILE 1,pos:`) now correctly seeks before reading.
  - Runtime supports both file I/O and queue-based message passing.

### 3. IDE core workflow

- Multi-tab editing, file open/save, formatting, run/stop are working.
- Direct command panel and program execution are wired.
- Graphics panel renders DRAW output.
- Persistent interpreter flow allows calling retained PROC definitions from direct commands after a program run.
- LSP-backed diagnostics are shown directly in the editor with markers and line annotations.
- Saved and unsaved tabs both participate in LSP (`untitled://` URIs are used for unsaved buffers).
- LSP client/server framing and handshake are now robust (`Content-Length` transport + initialize/initialized flow).
- IDE shutdown now waits for LSP process exit, avoiding process-lifecycle warnings.
- LSP diagnostics now use parser-backed statement classification with heuristic fallback for partial/invalid lines.
- LSP diagnostics internals are split into a dedicated module (`comal_lsp_diagnostics`) for clearer maintenance and easier future AST migration.
- Source formatter now treats `IF ...` without `THEN` as a block opener for indentation consistency.
- Qt I/O prompt buffering is now synchronized for concurrent SPAWN output, fixing a verified IDE crash under high thread counts (`double free or corruption (fasttop)`).

### 4. Tooling and testing

- Unified test runner in `tests/run_tests.sh`.
- Current aggregate result: **127 pass, 6 skip, 0 fail**.

### 5. Help and discoverability

- Keyword and built-in help text is now sourced from `docs/comal-keyword-docs.tsv`.
- Packaged installs include this file at `/usr/share/doc/opencomal/comal-keyword-docs.tsv`.
- LSP hover and IDE Help panel use the same shared documentation source.
- `SPAWN` help is included in the shared keyword docs and available to both LSP hover and IDE Help.
- `DRAW` hovers now support grouped command forms (e.g. `HUD.line`, `Ship.Engine.rect`).
- `PLAY` documentation now reflects the currently implemented ABC subset.
- ABC parser beat-unit fix: `Q:1/4=123` now correctly applies the beat unit fraction;
  prior to this, all `Q:<unit>=BPM` files (e.g. Pink Panther at `Q:1/4=123`) played 4× too fast.

---

## Current Gaps (Intentional or Pending)

### IDE / Debug depth

- Step-over/step-out and richer debug controls need completion.
- Breakpoint features are basic (no conditional breakpoints yet).
- Scope/variable presentation can be improved.
- LSP diagnostics/hover/completion are integrated; remaining work is polish (code actions, richer inline UX, and diagnostics controls).

### Sound roadmap

- `TONE` is functional.
- `PLAY` ABC subset now handles `Q:<unit>=BPM` beat timing correctly.
- Known remaining ABC gaps: tuplet compression, tied-note duration extension, chord notation.
- Full MML interpretation and polyphony are still pending.

### Architecture transition

- Legacy AST compatibility still exists in parser internals.
- Full legacy AST retirement is planned but not started now.

---

## Test Status

| Metric | Value |
|--------|-------|
| Total test programs | 133 |
| Pass | 127 |
| Skip | 6 |
| Fail | 0 |

**Skip reasons (expected):** interactive, infinite-loop, or squash-format related cases.

---

## Build and Validation Commands

```bash
# Configure and build
cmake -S . -B build
cmake --build build -j$(nproc)

# Run runtime tests
bash tests/run_tests.sh ./build/libcomal-runtime/comal-run

# CTest view
cd build && ctest --output-on-failure
```

---

## Near-Term Priorities (Ordered)

1. IDE debug experience polish (step controls, breakpoint UX, variable/call-stack clarity).
2. IDE editor integration polish (code actions, richer diagnostics UX, completion tuning).
3. Sound feature expansion (`PLAY` compatibility beyond current minimal support).
4. Preparation work for future legacy AST retirement (no execution yet).

---

## Deferred Initiative: Legacy AST Retirement

A phased, deferred plan is maintained in:

- `docs/AST_MODERNIZATION.md`

This is intentionally scheduled for later and is not part of immediate delivery work.

---

## Deferred Investigation: Runtime Performance Backend (Bytecode)

Evaluate a project-specific bytecode VM as a future execution backend for OpenCOMAL.

- Preferred direction: project-specific bytecode (rather than reusing another language bytecode such as Lua) to preserve COMAL semantics, debugger line mapping, and IDE/LSP integration.

### Scope for initial spike

- Define a minimal v1 opcode set for statements and expressions.
- Compile modern AST to bytecode after parse/structure scan.
- Keep AST interpreter as reference/fallback for behavior parity.
- Add source-line mapping for breakpoints/step/debug views.

### Success criteria

- Measurable speedup on representative COMAL programs.
- No semantic regressions in existing runtime test suite.
- Clean integration path for SPAWN, TRAP/HANDLER, DATA/READ, and file/queue I/O.

---

## Deferred Investigation: SPAWN Handles and WAIT Synchronization

Improve educational concurrency ergonomics by adding a small, explicit join/cancel model while preserving current SPAWN behavior.

### Accepted syntax direction

- Existing spawn remains valid: `SPAWN procName(args...)`
- Add optional handle form: `SPAWN <handle>: procName(args...)`
- Add synchronization: `WAIT` (all workers), `WAIT <handle>` (single worker)
- Extend STOP for worker cancellation: `STOP SPAWN <handle>`

### Semantic rules (v1)

- Handles are interpreter-managed logical worker IDs (not OS thread IDs).
- Reusing an active handle is a runtime error.
- `WAIT <handle>` returns immediately if the worker is already finished.
- `STOP SPAWN <handle>` is cooperative cancellation via worker interrupt request (no force-kill).
- Existing `STOP` semantics for main program execution remain unchanged.

### Implementation checklist

- Parser and grammar: add `WAIT`, `WAIT <exp>`, `SPAWN <exp> : <proc-call>`, and `STOP SPAWN <exp>` forms.
- AST and statement typing: add payload support for WAIT target and STOP-SPAWN target.
- Runtime worker table: track worker lifecycle by handle (running, finished, canceled, failed).
- Runtime synchronization: implement wait-all and wait-single with condition variable signaling.
- Runtime cancellation: route `STOP SPAWN` through existing cooperative interrupt path.
- Error handling: define and test diagnostics for invalid handle, duplicate handle, and non-worker target.
- IDE/debug integration: preserve line mapping and ensure break/stop controls behave consistently.
- Documentation/examples: update SPAWN docs and convert `examples/mandelbrot_pixel_spawn.lst` to `WAIT`-based completion.
- Tests: add parser coverage, runtime behavior tests, cancellation tests, and regression checks for existing SPAWN v1 programs.

---

## Deferred Initiative: Windows port

Investigate supporting Windows by providing optional Qt-backed implementations that hide OS-specific details (console/terminal I/O, audio via QtMultimedia or FluidSynth, threading/timers, and file/process APIs). Implement Qt backends behind the existing `IOInterface` and gate them with CMake options so headless/CLI builds remain unaffected. Initial target: MSVC + vcpkg (native); MSYS2/MinGW as an alternate for early testing.

---

## Related Documents

- `docs/AST_MODERNIZATION.md`
- `docs/AST_USAGE.md`
- `docs/COMAL_LSP_USAGE.md`
- `docs/GRAPHICS_COMMANDS.md`
- `docs/PLAY_COMMAND.md`
- `docs/comal-keyword-docs.tsv`
## Platform Ports (Deferred)

