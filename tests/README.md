# tests

Test suite for the OpenCOMAL runtime.

## Structure

| Path | Contents |
|------|---------|
| `programs/` | ~119 numbered COMAL test programs (`.lst`) covering core language features |
| `programs-nonum/` | 13 numberless COMAL programs testing line-number-free syntax |
| `assembly/` | Z80 assembly test programs |
| `run_tests.sh` | Unified test runner (also used by CTest) |
| `test_tone_play.sh` | Manual smoke test for `TONE` and `PLAY` sound output |
| `validate_comal_keyword_docs.sh` | Checks that all keywords are documented |

## Running

**All tests (via shell):**
```bash
bash tests/run_tests.sh
```

**All tests (via CTest):**
```bash
cd build && ctest --output-on-failure
```

**Single program:**
```bash
./build/libcomal-runtime/comal-run tests/programs/for1.lst
```

## Test Categories

- **Numbered programs** — classic COMAL with line numbers; cover FOR/NEXT, IF/THEN/ELSE, WHILE, REPEAT, PROC/FUNC, CASE, TRAP, DATA/READ, file I/O, string functions, SPAWN, queues, DRAW, and more
- **Numberless programs** — same constructs without line numbers, validating the numberless parser path
- **Skipped tests** — a small set of interactive, infinite-loop, or squash-format programs that cannot be run non-interactively (documented in `run_tests.sh`)

## Current Status

140 pass / 15 skip / 0 fail

## See Also

- [`libcomal-runtime`](../libcomal-runtime/README.md) — the runtime under test
- [`docs/PROJECT_STATUS.md`](../docs/PROJECT_STATUS.md) — overall project status
