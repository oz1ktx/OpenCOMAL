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

# ── Tests that need interactive input, run forever, or require
#    unimplemented features (squash file format) ─────────────────────
SKIP="rnd()1.lst rnd()2.lst signif1.lst gentest.lst lst2sq.lst sq2lst.lst"

# Legacy .sq runner tests and TRACE syntax are currently unsupported by
# the modern parser/runtime.
SKIP="$SKIP run1.lst selin1.lst selout1.lst trace1.lst"

# Audio/timing tests are flaky on headless CI runners (no stable audio backend).
# Keep them enabled for local development unless running in CI.
if [[ "${CI:-}" == "true" || "${GITHUB_ACTIONS:-}" == "true" ]]; then
  SKIP="$SKIP tone_block.lst tone_play_test.lst encounters.lst"
fi

run_dir() {
  local dir="$1"
  local label="$2"

  if [[ ! -d "$dir" ]]; then
    return
  fi

  # Collect files into an array (sorted).
  local files=()
  while IFS= read -r -d '' f; do
    files+=("$f")
  done < <(find "$dir" -maxdepth 1 -name '*.lst' -print0 | sort -z)

  local bn rc
  for f in "${files[@]}"; do
    bn=$(basename "$f")
    case " $SKIP " in *" $bn "*) skip=$((skip+1)); total=$((total+1)); continue;; esac

    total=$((total+1))
    timeout --kill-after=2 5 "$COMAL_RUN" "$f" </dev/null >/dev/null 2>&1
    rc=$?
    if [[ $rc -eq 0 ]]; then
      pass=$((pass+1))
    elif [[ $rc -eq 124 || $rc -eq 137 ]]; then
      fail=$((fail+1))
      echo "$label/$bn (TIMEOUT)" >> "$TMPFAIL"
    else
      fail=$((fail+1))
      echo "$label/$bn (rc=$rc)" >> "$TMPFAIL"
    fi
  done
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
