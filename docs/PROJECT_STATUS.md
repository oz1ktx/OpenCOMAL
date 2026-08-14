# OpenCOMAL Project Status

**Last Updated:** 14 Aug 2026
**Purpose:** Short, ordered snapshot of current project state and near-term work.

---

## At a Glance

| Area | Status | Notes |
|------|--------|-------|
| Parser (`libcomal-parser`) | Stable | Modern AST available via modern API; legacy compatibility layer still present |
| Runtime (`libcomal-runtime`) | Stable | Modern AST execution path in active use; SPAWN v1 implemented; profiling-driven lookup/eval optimizations applied |
| Graphics (`libcomal-graphics`) | Stable | DRAW command set includes `text` and style controls |
| Sound (`libcomal-sound`) | Partial but usable | `TONE` works; `PLAY` has basic support, full MML remains TODO |
| LSP (`comal-lsp`) | Stable | Diagnostics, completion, definition, hover; parser-backed diagnostics classification is now in place |
| IDE (`comal-ide`) | In progress | Core workflow works; editor now shows live LSP diagnostics in saved and unsaved tabs |
| Z80 / CP-M-style assembly path | Partial but usable | `.COM` loading/execution works, BDOS console/file subset works, `sjasmplus` adapter assembles `.asm` to `.COM`, IDE assembly output panel is wired |
| Test suite | Strong | 140 pass / 15 skip / 0 fail |

---

## Current Phase

**Phase 5: Qt6 IDE refinement**

All earlier modernization phases are complete enough for daily development.
Current work is mostly IDE ergonomics, debugger depth, and integration polish.
The bytecode backend investigation is intentionally deferred while runtime hotspots are addressed with targeted optimizations.

In parallel, the first Z80/CP-M-style teaching path is now active in the IDE/backend layer, but it is still below the maturity level of the COMAL workflow.

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
  - Runtime now supports `EVAL(expr$)` for numeric expressions parsed from strings in the current interpreter scope.
  - **Profiling-driven optimization pass completed (May 2026):**
    - `perf` and `valgrind` profiling runs were performed on `examples/mandelbrot_pixel.lst` and `examples/mandelbrot_pixel_spawn.lst`.
    - Primary hotspots were confirmed in symbol lookup and expression evaluation (`Scope::find`, `evaluate`, `evalId`).
    - Runtime now uses transparent string-key lookup and view-based name handling in hot paths to reduce temporary allocations and repeated lookup overhead.
    - First-pass profiling after changes shows a meaningful reduction in evaluator self-time on spawn-heavy workload.

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
- Current aggregate result: **140 pass, 15 skip, 0 fail**.
- Dedicated assembly/Z80 backend tests now cover:
  - `.COM` image loading
  - BDOS console input/output
  - BDOS file I/O through FCB + DMA
  - sequential read EOF behavior
  - assembly source -> `.COM` -> execution using the vendored `sjasmplus` adapter
- Post-output-routing regression fix is in place: Z80 backend BDOS tests now validate `BackendRunResult.z80RuntimeOutput` (instead of `errorMessage`) so CI assertions match current runtime output routing.

### 5. Z80 assembly / CP-M-compatible path

- redcode/Z80 is integrated as the current CPU execution core.
- redcode/Zeta is vendored as the dependency required by redcode/Z80.
- `sjasmplus` is integrated as the first assembler backend behind an adapter boundary.
- IDE assembly UI flow is implemented end-to-end:
  - assembly start/success/failure lifecycle signaling
  - assembly output panel tabs for listing, diagnostics, and statistics
  - assembler console output capture and display in diagnostics
  - Z80 runtime console output routed into the same direct command output path used by COMAL `PRINT`
- The current execution flow for source assembly is:
  - assemble `.asm` / `.z80` / `.s` into `.COM`
  - load the `.COM` image at `0100h`
  - run it through the same Z80 backend path used for raw `.COM` files
- Current BDOS subset implemented in the runtime shim:
  - `0`, `1`, `2`, `6`, `9`, `12`, `15`, `16`, `20`, `25`, `26`
- Unsupported BDOS functions return deterministic diagnostics.
- The assembler backend is intentionally abstracted so the project can switch away from `sjasmplus` later if needed.

### 6. Help and discoverability

- Keyword and built-in help text is now sourced from `docs/comal-keyword-docs.tsv`.
- Packaged installs include this file at `/usr/share/doc/opencomal/comal-keyword-docs.tsv`.
- LSP hover and IDE Help panel use the same shared documentation source.
- `SPAWN` help is included in the shared keyword docs and available to both LSP hover and IDE Help.
- `EVAL` help is included in the shared keyword docs and available to both LSP hover and IDE Help.
- `EVAL` is syntax-highlighted as a built-in function in the IDE editor (teal, same category as `SIN`, `VAL`, etc.).
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
- Z80 debug views (registers, memory, disassembly, source-level stepping) are not yet surfaced in the IDE.
- Assembly diagnostics are not yet surfaced as first-class editor diagnostics; current errors are still backend-run oriented.

### Sound roadmap

- `TONE` is functional.
- `PLAY` ABC subset now handles `Q:<unit>=BPM` beat timing correctly.
- Known remaining ABC gaps: tuplet compression, tied-note duration extension, chord notation.
- Full MML interpretation and polyphony are still pending.

### Architecture transition

- Legacy AST compatibility still exists in parser internals.
- Full legacy AST retirement is planned but not started now.

### Assembly path constraints

- `sjasmplus` is a practical current choice, but it carries ZX Spectrum and retro-platform specific directives/features that must remain constrained behind the adapter.
- The OpenCOMAL assembly subset/dialect is not yet formally enforced.

---

## Test Status

| Metric | Value |
|--------|-------|
| Total test programs | 155 |
| Pass | 140 |
| Skip | 15 |
| Fail | 0 |

**Skip reasons (expected):** interactive, infinite-loop, squash-format, or audio/timing cases.

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

# Optional profiling build
cmake -S . -B build-prof -DCMAKE_BUILD_TYPE=RelWithDebInfo
cmake --build build-prof -j$(nproc)

# Example perf run
perf record -e cpu-clock -F 999 -g --call-graph dwarf -- \
  ./build-prof/libcomal-runtime/comal-run examples/mandelbrot_pixel_spawn.lst
perf report --stdio --dsos comal-run
```

---

## Near-Term Priorities (Ordered)

1. Continue runtime hotspot reduction (symbol lookup caching and expression path optimizations).
2. IDE debug experience polish (step controls, breakpoint UX, variable/call-stack clarity).
3. IDE editor integration polish (code actions, richer diagnostics UX, completion tuning).
4. Z80 assembly path tightening: constrain assembler-facing syntax/profile, improve diagnostics flow, and add debugger-facing state exposure.
5. Sound feature expansion (`PLAY` compatibility beyond current minimal support).
6. Preparation work for future legacy AST retirement (no execution yet).

---

## Deferred Initiative: Legacy AST Retirement

A phased, deferred plan is maintained in:

- `docs/AST_MODERNIZATION.md`

This is intentionally scheduled for later and is not part of immediate delivery work.

---

## Deferred Investigation: Runtime Performance Backend (Bytecode)

Evaluate a project-specific bytecode VM as a future execution backend for OpenCOMAL.

Status: **Deferred by decision (May 2026)** until profiling-led interpreter optimizations flatten current hotspots.

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
- `docs/future_assembly_addon.md`

## Related Ongoing Z80/Assembly Work

- `third_party/Z80`
- `third_party/Zeta`
- `third_party/sjasmplus`
- `tests/assembly/hello_loop.asm`
## Platform Ports (Deferred)

# Future Development

## Educational Multi-Language IDE Direction (COMAL + Z80 with CP/M-Compatible Conventions)

We plan to evolve the IDE into a language-flexible teaching environment that supports both:

### COMAL workflows (current)
Z80 assembly programming with console-first execution and CP/M-compatible conventions (future)

### Why this direction

Reuse the existing Qt IDE shell, editor, run control, panel layout, and LSP integration patterns.
Avoid maintaining separate cloned applications with duplicated UI and tooling code.
Enable comparative teaching workflows across high-level and low-level programming models in one environment.
Proposed architecture direction

Introduce a backend abstraction layer so the IDE can host multiple execution engines.
Keep COMAL as the first backend implementation.
Add a Z80 backend for assemble, load, run, step, break, and inspect state, while preserving CP/M-style load and syscall conventions for forward compatibility.
Expected teaching capabilities (future)

Edit and assemble simple Z80 programs.
Run with standardized console I/O behavior through a lightweight execution environment.
Preserve CP/M-compatible load address and system-call conventions without requiring full CP/M emulation in the first iteration.
Inspect registers, flags, stack, memory windows, and disassembly.
Use breakpoints and stepping controls similar to existing IDE run/debug workflow.
Status

Accepted as a future development direction.
Initial work should prioritize shared abstractions and minimal disruption to existing COMAL behavior.
Detailed planning will be maintained in a separate draft document.
