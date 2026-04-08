# AST Modernization Status and Legacy Retirement Plan

**Last Updated:** 8 April 2026
**Intent:** Keep this document short, accurate, and actionable.

---

## Current Status (What Is True Today)

AST modernization is functionally complete for runtime use, but parser internals
still rely on legacy structures and then convert to modern nodes.

- Modern AST definitions are in `libcomal-parser/include/comal_ast_modern.h`.
- Runtime executes modern AST in `libcomal-runtime/`.
- Parser public modern API exists: `comal_parse_line_modern()`.
- Compatibility layer still exists in `libcomal-parser/src/ast_compat.cpp`.
- Legacy AST headers/structures are still present in
  `libcomal-parser/include/comal_ast.h`.

In short: **modern AST is the execution model; legacy AST is still part of parse
construction and compatibility plumbing.**

---

## Why Some Legacy Behavior Is Still Visible

Modern `Expression` float literals are stored as plain `double` values (no source
text field). However, editor/file source text is still preserved as text unless a
formatter rewrites it. This is expected in the current hybrid stage.

---

## Scope of Future Work

This plan is for **phasing out legacy AST later**. No immediate code changes are
required today.

Goals:

1. Remove legacy AST as a required runtime/parser dependency.
2. Keep behavior stable across parser, runtime, IDE, and tests.
3. Preserve optional legacy reference code only where intentionally needed.

Non-goals:

1. Rewriting the legacy C interpreter in `legacy/`.
2. Feature expansion during migration.
3. Broad stylistic refactors unrelated to AST ownership.

---

## Stepwise Plan to Phase Out Legacy AST

### Phase 0: Baseline and Guardrails

1. Freeze a baseline commit and test report.
2. Record parser + runtime behavior snapshots:
   - parse success counts
   - representative AST dumps (`comal-parse-cli -m`)
   - full test suite status
3. Add a migration checklist issue/milestone in project tracking.

Exit criteria:

- Baseline build/test and parse metrics are captured.

### Phase 1: API Boundary Clarification

1. Identify all public/internal APIs that still expose `struct comal_line` or
   `struct expression`.
2. Define modern-only internal interfaces for parser-to-runtime handoff.
3. Keep temporary adapters at boundaries where needed.

Exit criteria:

- Clear map of legacy-exposed APIs and agreed modern replacements.

### Phase 2: Parser Semantic Action Migration

1. Migrate grammar semantic actions to construct modern nodes directly.
2. Keep conversion layer available behind a temporary compatibility path.
3. Ensure line metadata and statement payload parity with current behavior.

Exit criteria:

- Parser can build modern AST without going through legacy AST for normal path.

### Phase 3: Remove Parser Dependence on Legacy AST Types

1. Remove parser-internal reliance on legacy expression/statement structs.
2. Keep only minimal shims for any remaining tools that still need legacy input.
3. Update parser support utilities that currently assume legacy struct layouts.

Exit criteria:

- Parser build path no longer requires legacy AST headers for primary flow.

### Phase 4: Compatibility Layer Reduction

1. Mark `ast_compat.cpp` entry points as deprecated (documented timeline).
2. Remove conversion functions no longer used by production paths.
3. Retain only explicitly required compatibility functions (if any).

Exit criteria:

- Compatibility layer is minimal and intentional, not default infrastructure.

### Phase 5: Legacy AST Decommissioning

1. Remove unused legacy AST declarations/includes from active parser/runtime code.
2. Move any retained legacy definitions to isolated compatibility location.
3. Update docs to state modern AST as single canonical model.

Exit criteria:

- Active code path uses modern AST only.
- Legacy AST is either removed or isolated as optional compatibility artifact.

### Phase 6: Hardening and Cleanup

1. Run full build + tests + targeted parser corpus checks.
2. Validate IDE/LSP behavior on modern-only parser path.
3. Remove dead code, obsolete comments, and stale docs.

Exit criteria:

- Regression-free validation complete.
- Migration checklist closed.

---

## Suggested Validation Matrix for the Migration

For each phase above, run:

1. Build: CMake full project build.
2. Runtime tests: `tests/run_tests.sh`.
3. Parser checks:
   - parse representative numbered and numberless programs
   - compare AST shape against baseline samples
4. IDE smoke test:
   - load file
   - run program
   - verify error line mapping
5. LSP smoke test:
   - diagnostics/completion/definition still functional.

---

## Risks and Mitigations

1. Risk: behavior drift in parser edge cases.
   Mitigation: keep corpus-based parse snapshots and compare before/after.

2. Risk: hidden coupling to legacy struct layout in helper functions.
   Mitigation: migrate in small slices and keep adapters until verified.

3. Risk: documentation and status drift during long migration.
   Mitigation: update this file and `docs/PROJECT_STATUS.md` at each phase exit.

---

## Recommended Start Conditions (When You Decide to Begin)

Start the legacy AST retirement only when:

1. Current main branch is green (build/tests).
2. There is time for multi-phase validation, not a one-shot rewrite.
3. Work can be done in incremental PRs with clear rollback points.

If these conditions are not met, keep the current hybrid model temporarily.

---

## Related Files

- `libcomal-parser/include/comal_ast_modern.h`
- `libcomal-parser/include/comal_ast.h`
- `libcomal-parser/src/ast_compat.cpp`
- `libcomal-parser/src/parser_api.cpp`
- `docs/PROJECT_STATUS.md`
- `docs/AST_USAGE.md`
