#!/bin/bash
# run_tests.sh — Run all COMAL test programs and report results.
#
# Usage:  tests/run_tests.sh [path-to-comal-run]
#
# If no path is given, tries build/libcomal-runtime/comal-run from the
# repository root.

set -uo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"

COMAL_RUN="${1:-$REPO_ROOT/build/libcomal-runtime/comal-run}"

if [[ ! -x "$COMAL_RUN" ]]; then
  echo "ERROR: comal-run not found at $COMAL_RUN"
  echo "Build the project first, or pass the path as argument."
  exit 2
fi

TMPFAIL=$(mktemp)
trap 'rm -f "$TMPFAIL"' EXIT

pass=0; fail=0; skip=0; total=0

# ── Tests that need interactive input or run forever ─────────────────
SKIP="rnd()1.lst rnd()2.lst signif1.lst gentest.lst"

run_dir() {
  local dir="$1"
  local label="$2"

  if [[ ! -d "$dir" ]]; then
    return
  fi

  local count=0
  while IFS= read -r -d '' f; do
    local bn
    bn=$(basename "$f")
    case " $SKIP " in *" $bn "*) skip=$((skip+1)); total=$((total+1)); continue;; esac

    total=$((total+1))
    count=$((count+1))
    timeout -s KILL 3 "$COMAL_RUN" "$f" >/dev/null 2>&1
    local rc=$?
    if [[ $rc -eq 0 ]]; then
      pass=$((pass+1))
    else
      fail=$((fail+1))
      echo "$label/$bn (rc=$rc)" >> "$TMPFAIL"
    fi
  done < <(find "$dir" -maxdepth 1 -name '*.lst' -print0 | sort -z)
}

echo "=== OpenCOMAL Test Suite ==="
echo "Runner: $COMAL_RUN"
echo

# Run numbered (legacy-format) tests
run_dir "$REPO_ROOT/tests/programs" "programs"

# Run numberless tests
run_dir "$REPO_ROOT/tests/programs-nonum" "programs-nonum"

echo "PASS=$pass FAIL=$fail SKIP=$skip TOTAL=$total"

if [[ -s "$TMPFAIL" ]]; then
  echo "--- FAILS ---"
  cat "$TMPFAIL"
  exit 1
fi

exit 0
