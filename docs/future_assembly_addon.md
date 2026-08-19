# OpenCOMAL Future Draft: Multi-Language Teaching Environment (Z80 + CP/M-Compatible Conventions)

## Purpose

Define a phased path to extend OpenCOMAL from a COMAL-first IDE/runtime into a multi-language teaching platform that supports Z80 assembly with a lightweight execution environment, while preserving CP/M-compatible conventions (load model and system-call interface) for future expansion and preserving current COMAL stability.

## Goals

- Keep one IDE codebase with multiple language backends.
- Preserve existing COMAL functionality and tests.
- Add beginner-friendly Z80 teaching workflows with CP/M-compatible conventions.
- Reuse existing UI, execution lifecycle, and diagnostics plumbing where practical.

## Non-Goals (Initial)

- Full CP/M hardware-accurate emulation in the first iteration.
- Full CP/M disk/filesystem/process emulation in the first iteration.
- Broad BDOS compatibility beyond console-oriented calls in the first iteration.
- A fully advanced assembler macro ecosystem in the first release.
- Immediate debugger parity with mature external emulators.

## Reuse Opportunities

- IDE shell and dock/panel layout.
- Editor tabs, markers, breakpoints, and diagnostics display.
- Worker-thread run model and GUI I/O signaling pattern.
- LSP client process integration pattern.
- Existing run/stop/break UX conventions.

## Current Status (August 2026)

The project has moved beyond design-only exploration and now contains an initial working Z80 execution and assembly path inside the Qt IDE/runtime layer.

Implemented so far:

- Backend abstraction is in place in `comal-ide` and COMAL execution already runs through it.
- CP/M/Z80 execution support has been extracted into a dedicated `libcomal-cpm` library instead of remaining IDE-local.
- Z80 `.COM` loading is implemented with CP/M-compatible startup conventions:
	- load at `0100h`
	- warm-boot vector at `0000h`
	- BDOS call vector at `0005h`
	- default DMA address at `0080h`
- A redcode/Z80 CPU core is integrated as a vendored submodule (`third_party/Z80`) with its Zeta dependency (`third_party/Zeta`).
- Minimal Z80 execution is live for `.COM` programs in the backend layer.
- Current BDOS support in the runtime shim includes:
	- `0` terminate
	- `1` console input with echo
	- `2` console char output
	- `6` direct console I/O
	- `9` console string output
	- `12` version
	- `15` open via FCB
	- `16` close via FCB
	- `20` sequential read
	- `25` get current drive
	- `26` set DMA address
- Unsupported BDOS calls currently return deterministic diagnostics.
- An assembler path is now present via a swappable adapter interface, with `sjasmplus` integrated as the first backend implementation.
- `.asm` / `.z80` / `.s` files can now be assembled to `.COM` through the adapter and then executed through the same runtime path as raw `.COM` files.
- The IDE assembly workflow is now explicit and user-visible:
	- assembly lifecycle signals are wired (`started`, `succeeded`, `failed`)
	- a dockable assembly output panel is present with listing/diagnostics/statistics tabs
	- assembler (`sjasmplus`) stdout/stderr is captured and shown in assembly diagnostics
	- Z80 runtime console output (for example BDOS function 9 string printing) is routed to the same direct command output panel used by COMAL `PRINT`
- Assembly-specific editor behavior is now present:
	- COMAL keyword help no longer remains active when editing assembly files
	- the Help panel shows an assembly placeholder instead of stale COMAL help
	- the Format Source action applies conservative assembly indentation/case normalization
- Source-level stepping and breakpoint mapping for assembled source are now wired through the IDE run/debug flow.
- Paused Z80 execution now populates debug-panel views for registers, flags, memory, and disassembly.
- CP/M file I/O can now be mapped to a user-selected host folder, providing a simple "drive root" without full disk emulation.
- End-to-end tests now cover:
	- `.COM` loader behavior
	- BDOS console I/O
	- BDOS file I/O through FCB + DMA
	- mapped host-folder drive selection for BDOS file access
	- sequential read EOF behavior
	- assembly source -> `.COM` -> execution
	- CI-aligned output assertions via `z80RuntimeOutput` for BDOS runtime-output checks

Not implemented yet:

- Assembly diagnostics surfaced as first-class editor problems instead of backend error strings only
- Assembly formatting support in LSP/client path
- Assembly instruction help/reference content beyond the current placeholder panel
- A constrained OpenCOMAL-owned assembly dialect/profile layer on top of the assembler backend

## Core Refactor Proposal

### 1. Backend Abstraction Layer

Define a backend interface that the IDE can drive uniformly:

- `loadSource()`
- `buildOrAssemble()`
- `run()`
- `stop()`
- `pause()`
- `stepInto()`
- `stepOver()`
- `setBreakpoints()`
- `queryExecutionState()`
- `queryDiagnostics()`

Implementation mapping:

- COMAL backend: adapter over current interpreter/runtime.
- Z80 backend: adapter over assembler, execution engine, and CP/M-compatible syscall shim (console subset first).

### 2. Language Profile System

Introduce per-document or per-project language profiles:

- Language id
- File extensions
- Lexer/formatter selection
- LSP server command
- Backend selector

Formatting note:

- Treat source formatting as a language service, not as runtime/backend logic.
- COMAL and Z80 assembly may use different formatter implementations behind a shared IDE action.
- Prefer exposing formatting through the LSP/client path (`textDocument/formatting`) so editor integrations and the Qt IDE share one formatting contract.

### 3. Debug Data Model Generalization

Current COMAL debug model:

- Variables
- Call stack

Assembly-oriented debug model:

- Registers: A, F, B, C, D, E, H, L, IX, IY, SP, PC
- Flags
- Memory views
- Disassembly around PC
- Breakpoints by address and optional source mapping

### 4. Incremental UI Evolution

Keep existing panes and add mode-specific tabs where needed.

- Debug panel:
	- COMAL tab set (existing)
	- Z80 tab set (registers/memory/disassembly)
- Optional assembly console panel for command interaction
- Maintain consistent run controls across modes
- Add a menu/settings option to choose the default working directory used when running
  assembly and COMAL programs, so file-backed teaching examples are not forced to rely
  on the source file location or generated build directory.

## Suggested Phases

### Phase 0: Design and Safety

- Define interfaces and language profile schema.
- Add feature flags so the new path remains optional.
- Add architecture notes and acceptance criteria.

### Phase 1: COMAL Adapter Extraction

- Refactor run worker to use backend interfaces.
- Implement COMAL adapter with no behavior change.
- Validate full COMAL regression suite.

### Phase 2: Minimal Assembler Pipeline

- Add basic Z80 assembler support (labels, directives, core instruction subset).
- Produce binary output and listing.
- Integrate editor diagnostics for assembler errors.
- Add a minimal deterministic assembly formatter for labels/opcodes/operands/comments.
- Keep first formatter pass syntax-aware but lightweight; do not block on a full semantic assembler.

Implementation note:

- `sjasmplus` is currently the selected first assembler backend, integrated behind an adapter boundary so it can be replaced later if needed.
- The adapter approach is intentional: assembler choice is not treated as a permanent commitment to `sjasmplus` syntax or platform-specific directives.

### Phase 3: Minimal Execution Engine Integration

- Add CPU execution loop and memory model.
- Implement run/stop/step and breakpoints.
- Provide registers and disassembly in the debug panel.

Implementation note:

- The CPU execution core is currently redcode/Z80, integrated as a vendored dependency behind OpenCOMAL backend code.
- Current runtime support is execution-oriented, not yet debugger-oriented.

### Phase 4: CP/M Compatibility Envelope (Console-First)

- Keep execution lightweight while preserving CP/M-facing conventions.
- Enforce a conventional load model (default `ORG`/load address at `0100h`, configurable).
- Implement a v1 BDOS subset that includes both console I/O and file I/O via a stable syscall shim.
- Support at minimum these BDOS functions in v1: `0` (terminate), `2` (console char out), `9` (console string out), `15` (open via FCB), `20` (sequential read), `26` (set DMA address).
- Add near-term BDOS functions after v1 baseline: `16` (close), `12` (version), `25` (get current drive).
- Return deterministic "not implemented" diagnostics for unsupported system calls.
- Add `.COM` program loader support: load binary at `0100h`, initialize CP/M low-memory vectors, and run with `PC=0100h`.
- Intercept `CALL 0005h` for BDOS dispatch while preserving normal `HALT` semantics.
- Add sample templates and guided exercises.
- Expand diagnostics and help text.
- Defer GSX-style graphics API compatibility to a later optional phase.

Implementation note:

- The runtime shim has already implemented the initial console/file subset and related tests, so this phase is partially in progress rather than purely planned.
- Current FCB support is intentionally minimal and host-file backed, suitable for deterministic teaching/test scenarios rather than full CP/M filesystem emulation.

### Phase 4.1: `.COM` Runtime Entry and Program Lifecycle

- Accept `.COM` file launch from IDE run actions and run-worker pipeline.
- Enforce memory bounds: reject binaries that exceed configured TPA/program memory.
- Pre-populate CP/M-compatible low-memory vectors (`0000h` warm boot, `0005h` BDOS vector, default DMA at `0080h`).
- End program cleanly on warm-boot path (`JP 0000h`/equivalent return path) and surface exit reason in diagnostics.
- Provide deterministic error diagnostics for malformed or unsupported runtime state.

### Phase 5: Polish and Curriculum Support

- Improve completions, hover help, and quick-fix hints.
- Expand assembly formatting rules and configurability once the instruction/directive subset stabilizes.
- Add formatter support to the LSP server capabilities and IDE client request path if not already completed earlier.
- Add an IDE menu action for configuring the default working directory for assembly and
  COMAL execution.
- Add tutorials and example projects.
- Collect classroom feedback and refine UX.

## Testing Strategy

### Compatibility Gate

- Existing COMAL test suite remains green at every phase.

### New Assembly/Execution Tests

- Assembler parser and symbol-resolution unit tests.
- Instruction execution correctness tests.
- Step/breakpoint integration tests.
- Load-address/`ORG` behavior and bounds-validation tests.
- Syscall ABI tests for supported console+file BDOS calls and unsupported-call diagnostics.
- `.COM` loader tests (size limits, load address, low-memory vector initialization, startup `PC`).
- BDOS dispatch tests that verify `CALL 0005h` interception and return-state behavior.
- Formatter tests for stable label/opcode/operand/comment alignment and idempotent reformatting.
- End-to-end sample programs for classroom scenarios.

### IDE Integration Tests

- Open/edit/build/run for both language modes.
- Diagnostics behavior in saved and unsaved buffers.
- Format-document request/response coverage for assembly buffers in both IDE and external LSP clients.
- Panel state and debug updates under concurrent UI interactions.

## Risks and Mitigations

- Risk: abstraction leaks between COMAL and assembly models.
	- Mitigation: strict backend contracts and mode-specific debug adapters.
- Risk: debugger UX complexity increases.
	- Mitigation: shared shell with clear language-specific tabs and labels.
- Risk: scope creep in CP/M fidelity.
	- Mitigation: teaching-focused subset with explicit non-goals.

## Success Criteria

- No regressions in current COMAL workflows.
- User can assemble and run a simple Z80 program in the IDE.
- User can load and run a `.COM` file from the IDE.
- User gets deterministic console I/O behavior through the standardized runtime interface.
- User can open and read a file via the supported BDOS file I/O subset.
- User can format assembly source consistently from the IDE and, when enabled, through LSP formatting.
- User can step instructions and inspect registers/memory.
- Unified IDE experience remains clear and stable across both languages.
- CP/M-compatible load and syscall conventions are preserved for future expansion.

## Open Decisions

- Build vs adopt assembler/emulator components.
- Exact v1 CP/M compatibility profile (entry conventions, register contract, memory map).
- Which BDOS console calls are required in v1 vs deferred.
- Whether assembly formatting should live in the existing OpenCOMAL LSP server, a separate assembly-focused language server, or a shared formatter library used by both.
- Exact assembly formatting policy: case normalization, label column rules, operand spacing, directive alignment, and comment preservation.
- Whether `sjasmplus` remains acceptable once OpenCOMAL defines a constrained teaching subset, or whether the project should switch to a smaller/cleaner assembler such as GNU zasm.
- How strictly the project should filter or reject assembler-specific extensions (for example fake instructions, device-specific directives, Lua scripting, and ZX-oriented pseudo-ops).
- Single binary with mode switching vs separate launch profiles.
- Whether to include a GSX compatibility layer in a later optional phase.

## Choices Made So Far

These choices are already reflected in the repository state:

- Emulator/runtime CPU core: redcode/Z80
	- Reason: active upstream, strong correctness/testing story, CMake-friendly integration.
- Emulator dependency pattern: vendored submodule(s)
	- redcode/Z80 plus redcode/Zeta are added under `third_party/`.
- Assembler integration pattern: adapter over third-party tool
	- Reason: keeps assembler choice replaceable and isolates vendor-specific syntax/behavior.
- First assembler backend: `sjasmplus`
	- Reason: active upstream, BSD license, extensive tests, practical build integration.
	- Caveat: it has significant ZX Spectrum / retro-platform feature baggage, so it must remain behind a constrained OpenCOMAL-facing adapter.
- Future fallback assembler candidate: GNU zasm remains under consideration
	- Reason: conceptually smaller/cleaner, but currently a weaker maintenance choice.
- Runtime execution strategy: assemble to `.COM`, then run the `.COM` through the same backend path
	- Reason: keeps source assembly and binary execution loosely coupled.
- Current CP/M file strategy: host-backed minimal FCB/DMA behavior
	- Reason: enough for deterministic teaching workflows and tests without full disk emulation.
	- Current implementation: default to the program directory, with an IDE setting that can remap the active drive to a selected host folder.

## Startup Suggestions (Implementation Kickoff)

### Suggested First Milestone (2-3 weeks)

- Extract backend interface and wire COMAL through it.
- Keep all current COMAL behavior unchanged.
- Add a hidden or experimental language selector.
- Add scaffolding for a Z80 backend without enabling full execution yet.

Deliverable:

- IDE launches, runs COMAL normally, and compiles with backend abstraction in place.

### Suggested Initial Backlog

1. Create `ILanguageBackend` and `BackendFactory` abstractions.
2. Refactor run worker to call backend interface only.
3. Implement `ComalBackendAdapter` with regression test checks.
4. Add `LanguageProfile` model and extension mapping (`.lst`, `.asm`).
5. Add `Z80BackendStub` that returns controlled "not implemented" diagnostics.
6. Add debug-panel data adapters for COMAL vs CPU modes.
7. Add basic assembler diagnostic path (line/column/severity/message).
8. Add `.COM` loader path (`0100h` load, low-memory vector setup, startup registers).
9. Add BDOS dispatch layer for `CALL 0005h` with v1 console+file function set.
10. Add FCB/DMA helpers and fixture tests for sequential read workflows.
11. Add `textDocument/formatting` support path for assembly source with golden formatter fixtures.

### Suggested Document and Code Organization

- `docs/assembly/`
	- `ASSEMBLY_SCOPE.md`
	- `CPM_SUBSET.md`
	- `DEBUG_MODEL_CPU.md`
- `comal-ide/include/` and `comal-ide/src/`
	- backend interfaces and adapters
	- language profile plumbing
	- mode-aware debug panel support
- `tests/assembly/`
	- assembler unit cases
	- emulator instruction fixtures
	- IDE integration scenarios

### Suggested First Teaching Scenarios

- Hello-world style console output example using CP/M-compatible syscall conventions.
- Register arithmetic and flag inspection exercise.
- Loop and conditional branch exercise with breakpoint stepping.
- Memory copy routine with before/after memory watch.

### Scope Guardrails

- Start with a documented instruction subset; expand only after tests pass.
- Keep formatter rules deterministic and conservative; avoid semantic rewrites in the first release.
- Keep CPU debug views read-only in first release.
- Defer advanced macro features and cycle-accurate timing.
- Keep non-console system calls out of scope until compatibility profile tests are in place.
- Require every new assembly feature to include at least one teaching-oriented example.
