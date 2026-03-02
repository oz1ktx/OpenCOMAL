Here is a **clean, self‑contained Markdown document** you can drop directly into your `poldy/OpenCOMAL` workspace (e.g., as `REFORM_PLAN.md`, `DEV_GUIDE.md`, or `.copilot/context.md`).  
It contains **no citations**, no system‑prompt details, no external references — just project‑internal context written for GitHub Copilot and future contributors.

You can simply copy/paste this file into your repo.

***

# COMAL Modernization Context & Refactor Plan

This document provides background and design intent for the ongoing modernization of **OpenCOMAL**, specifically the refactor based on the `poldy/OpenCOMAL` fork.  
Its purpose is to give GitHub Copilot (and human contributors) enough context to assist with development in a clean, consistent, forward‑looking architecture.

***

## 1. Project Goals

The overarching goal is to build a **modern COMAL development environment** while preserving the language’s structured, Pascal‑like spirit and its historical educational value.

Key objectives:

*   Replace the retro **line‑editor + ncurses** front end with a **modern GUI editor**, using a KDE/KTextEditor‑based application.
*   Maintain **COMAL language compatibility** while enabling a clean, maintainable architecture.
*   Support **incremental parsing**, modern diagnostics, and LSP‑based tooling.
*   Enable long‑term extensibility (debugger, breakpoints, semantic tools, program visualization, etc.)

***

## 2. High‑Level Strategy

Going forward, this project will **reuse the lexer/parser** from OpenCOMAL but **rewrite the rest of the interpreter/runtime stack**.

### Why this approach?

*   The parser is the most cleanly isolated, formally defined part of the codebase.
*   The existing interpreter is tightly coupled to historic constraints:
    *   strict “line must parse before it is stored” rule,
    *   program representation centered around numbered lines,
    *   ncurses‑oriented interaction loop.
*   Modern GUIs require:
    *   free multi‑line editing,
    *   cut/paste/undo operations,
    *   temporarily invalid syntax states,
    *   real‑time diagnostics rather than hard rejection.

Retaining the lexer/parser while redesigning the runtime produces the most maintainable and extensible architecture.

***

## 3. Target Architecture

The new system is organized into clean, well‑separated layers:

    +------------------------------------------------------+
    |  KDE GUI Application (KTextEditor integration)        |
    |    - Editing, syntax highlighting                    |
    |    - Run/Stop commands                               |
    |    - Error markers, diagnostics UI                   |
    +------------------------------------------------------+
    |  COMAL LSP Server                                    |
    |    - Incremental parsing using libcomal-parser       |
    |    - Diagnostics, outline, goto-definition           |
    |    - Optional semantic features                      |
    +------------------------------------------------------+
    |  libcomal-runtime (new)                              |
    |    - Interpreter / VM                                |
    |    - Execution environment                           |
    |    - Procedures, variables, arrays                   |
    |    - Error reporting                                 |
    |    - Hooks for debugging                             |
    +------------------------------------------------------+
    |  libcomal-parser (refactored from existing code)     |
    |    - Lexer / parser (from OpenCOMAL)                 |
    |    - AST definitions                                 |
    |    - Parse API for full documents                    |
    +------------------------------------------------------+

### Notes:

*   The **runtime** will be rewritten to operate on ASTs, not numbered lines.
*   “Strict acceptance” from classic COMAL will not be enforced; diagnostics will be surfaced normally but editing is unrestricted.
*   A **compatibility layer** may later provide line‑numbered COMAL import/export if needed for legacy programs.

***

## 4. Editing Model

Because the new environment is GUI‑based:

*   Users may keep *incomplete* or *invalid* code in the editor.
*   The parser will run incrementally (via the LSP server) to provide:
    *   syntax errors,
    *   warnings,
    *   semantic tasks.

The interpreter will run only on **fully valid ASTs**.

There is *no* concept of rejecting user input during editing.

***

## 5. Runtime Design Principles

The new runtime (`libcomal-runtime`) should:

*   Take a validated AST as its input.
*   Maintain a structured execution environment:
    *   global variables,
    *   local variables,
    *   scopes,
    *   procedures,
    *   arrays.
*   Produce structured error objects that can be surfaced in the UI.
*   Optionally include:
    *   stepping API,
    *   breakpoints,
    *   execution traces,
    *   introspection for variables.

Execution *never* depends on line numbers; program flow is entirely structural.

***

## 6. Parser Refactor Notes

The lexer/parser (Flex/Bison or original Lex/Yacc) will be extracted into a standalone library:

*   Clear C or C++ API:
    *   `parse_string`
    *   `parse_file`
    *   return AST or error list
*   AST nodes should be stable, extensible, and easy to traverse.
*   No ncurses, no terminal interaction, no I/O side effects.
*   No dependence on numeric line labels:
    *   The parser should accept (but not require) explicit line numbers.
    *   Line numbers are treated purely as metadata, not control structures.

***

## 7. KDE Application Plan

A standalone KDE app will be built on:

*   **Qt 6**
*   **KDE Frameworks 6**
*   **KTextEditor** component for rich editing

This app will support:

*   Syntax highlighting via KSyntaxHighlighting.
*   LSP‑powered features (completion, go‑to definition, hover).
*   Run/Stop integration via the new runtime library.
*   Output/console dock panels.
*   Future additions: debugger UI, call stacks, variable inspector.

***

## 8. Folder Structure Proposal

Inside the repository, the refactor will move toward this structure:

    /libcomal-parser/
        lexer.l
        parser.y
        ast.h / ast.cpp
        parser_api.h / parser_api.cpp

    /libcomal-runtime/
        runtime.h / runtime.cpp
        evaluator.cpp
        environment.cpp
        values.cpp

    /comal-lsp/
        main.cpp
        lsp_server.cpp
        lsp_protocol.cpp

    /comal-ide/
        (KDE application)
        main.cpp
        MainWindow.cpp
        EditorWidget.cpp

    /docs/
        REFORM_PLAN.md  (this document)

The legacy code remains available under `/legacy/` or the root until removed.

***

## 9. Guiding Principles for Copilot

When generating code or transformations, Copilot should:

1.  Favor **modern, clean abstractions** over patching legacy mechanisms.
2.  Keep parser/AST and runtime/interpreter strictly separated.
3.  Avoid reintroducing line‑editor semantics.
4.  Generate code that assumes:
    *   free text editing,
    *   full‑document parsing,
    *   AST‑based execution.
5.  Support incremental/language‑server workflows.
6.  Use CMake for all new modules.
7.  Prefer C++17+ for new components unless otherwise required.

***

## 10. Future Extensions (Non‑blocking)

Potential later work includes:

*   A full debugger (breakpoints, stepping, locals).
*   Visualizations (flow graphs, AST views).
*   Formatter / pretty‑printer for COMAL.
*   COMAL → C transpiler for performance or educational purposes.
*   Compatibility importer for old numbered COMAL programs.

***

## 11. Summary

This project aims to transform OpenCOMAL into a fully modern development environment while preserving the language’s essence. The legacy line‑editor and ncurses UI are intentionally being retired. The lexer/parser are retained; a new runtime is being built; the user experience will be based on KDE and LSP technologies.

This document provides the context needed for tooling, including GitHub Copilot, to assist effectively with the project.

***
