# libcomal-runtime

C++20 runtime library that executes parsed COMAL programs from the modern AST.

This module intentionally excludes the Z80 / CP-M-compatible assembly path, which lives in [`libcomal-cpm`](../libcomal-cpm/README.md).

## Responsibilities

- **Statement execution** — full dispatch of all COMAL statement types (loops, conditionals, PROC/FUNC calls, I/O, file operations, SPAWN)
- **Expression evaluation** — arithmetic, string, relational, and logical expressions using a `std::variant`-based `Value` type (`int64_t`, `double`, `std::string`)
- **Scope management** — `ScopeStack` with `CLOSED` proc/func isolation and nested block scoping
- **Built-in functions** — `ABS`, `SQR`, `STR$`, `VAL`, `CHR$`, `ORD`, `SPLIT`, and the full COMAL 80 standard library (~40 functions)
- **File I/O** — text-format (`PRINT FILE` / `INPUT FILE`) and binary-format (`WRITE FILE` / `READ FILE`) channels, random-access records
- **Queue messaging** — `OPEN QUEUE`, `PRINT QUEUE`, `INPUT QUEUE` for inter-process communication
- **SPAWN** — asynchronous fire-and-forget execution of `CLOSED PROC` definitions
- **Interrupt handling** — SIGINT (Ctrl-C) and IDE stop-button integration via `InterruptFlag`
- **`EVAL()`** — runtime evaluation of numeric expressions from strings in the current scope

## Key Files

| File | Purpose |
|------|---------|
| `src/executor.cpp` | Main statement dispatch (~1600 lines) |
| `src/evaluator.cpp` | Expression evaluation |
| `src/value.cpp` | `Value` type and coercions |
| `src/builtins.cpp` | Built-in function implementations |
| `src/file_io.cpp` | File and queue channel I/O |
| `src/scope.cpp` | `ScopeStack` variable scoping |
| `src/program.cpp` | Program loader and line index |
| `include/comal_interpreter.h` | Top-level interpreter interface |
| `tools/comal_run.cpp` | Batch execution CLI (`comal-run`) |

## Building

```bash
cd build && cmake .. && make comal-run -j$(nproc)
```

## Running a Program

```bash
./build/libcomal-runtime/comal-run path/to/program.lst
```

## See Also

- [`libcomal-parser`](../libcomal-parser/README.md) — provides the AST consumed by this library
- [`libcomal-cpm`](../libcomal-cpm/README.md) — separate Z80 / CP-M-compatible assembly and `.COM` execution path
- [`docs/PROJECT_STATUS.md`](../docs/PROJECT_STATUS.md) — overall project status
