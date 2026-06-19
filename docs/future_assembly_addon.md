# OpenCOMAL Future Draft: Multi-Language Teaching Environment (Z80/CP/M)

## Purpose

Define a phased path to extend OpenCOMAL from a COMAL-first IDE/runtime into a multi-language teaching platform that also supports Z80 assembly and CP/M-style emulation, while preserving current COMAL stability.

## Goals

- Keep one IDE codebase with multiple language backends.
- Preserve existing COMAL functionality and tests.
- Add beginner-friendly Z80/CP/M teaching workflows.
- Reuse existing UI, execution lifecycle, and diagnostics plumbing where practical.

## Non-Goals (Initial)

- Full CP/M hardware-accurate emulation in the first iteration.
- A fully advanced assembler macro ecosystem in the first release.
- Immediate debugger parity with mature external emulators.

## Reuse Opportunities

- IDE shell and dock/panel layout.
- Editor tabs, markers, breakpoints, and diagnostics display.
- Worker-thread run model and GUI I/O signaling pattern.
- LSP client process integration pattern.
- Existing run/stop/break UX conventions.

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
- Z80/CP/M backend: adapter over assembler and emulator components.

### 2. Language Profile System

Introduce per-document or per-project language profiles:

- Language id
- File extensions
- Lexer/formatter selection
- LSP server command
- Backend selector

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
- Optional CP/M console panel for command interaction
- Maintain consistent run controls across modes

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

### Phase 3: Minimal Emulator Integration

- Add CPU execution loop and memory model.
- Implement run/stop/step and breakpoints.
- Provide registers and disassembly in the debug panel.

### Phase 4: CP/M Teaching Layer

- Add pragmatic CP/M behaviors for simple educational programs.
- Add sample templates and guided exercises.
- Expand diagnostics and help text.
- Consider adding a simplified **GSX** (Graphics System Extension) teaching layer.
  - GSX was the official CP/M graphics API developed by Digital Research (circa 1983-84), based on the ISO GKS (Graphical Kernel Standard).
  - It provided device-independent drawing primitives (lines, rectangles, text, fills) dispatched through a VDI-style (Virtual Device Interface) layer.
  - Digital Research later carried this design forward into GEM's graphics subsystem.
  - The existing `libcomal-graphics` scene model and rendering pipeline (lines, rects, ellipses, text, pixels) maps naturally onto what a GSX-style API would expose, making this a low-cost addition with high historical authenticity.

### Phase 5: Polish and Curriculum Support

- Improve completions, hover help, and quick-fix hints.
- Add tutorials and example projects.
- Collect classroom feedback and refine UX.

## Testing Strategy

### Compatibility Gate

- Existing COMAL test suite remains green at every phase.

### New Assembly/Emulator Tests

- Assembler parser and symbol-resolution unit tests.
- Instruction execution correctness tests.
- Step/breakpoint integration tests.
- End-to-end sample programs for classroom scenarios.

### IDE Integration Tests

- Open/edit/build/run for both language modes.
- Diagnostics behavior in saved and unsaved buffers.
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
- User can step instructions and inspect registers/memory.
- Unified IDE experience remains clear and stable across both languages.

## Open Decisions

- Build vs adopt assembler/emulator components.
- Exact CP/M subset for first educational release.
- Single binary with mode switching vs separate launch profiles.
- Whether to include a GSX teaching layer in Phase 4, and if so, which subset of primitives to expose first.

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

- Hello-world style CP/M console output example.
- Register arithmetic and flag inspection exercise.
- Loop and conditional branch exercise with breakpoint stepping.
- Memory copy routine with before/after memory watch.

### Scope Guardrails

- Start with a documented instruction subset; expand only after tests pass.
- Keep CPU debug views read-only in first release.
- Defer advanced macro features and cycle-accurate timing.
- Require every new assembly feature to include at least one teaching-oriented example.
