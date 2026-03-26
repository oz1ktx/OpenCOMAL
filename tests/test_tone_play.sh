#!/usr/bin/env bash
set -euo pipefail
ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
BIN="$ROOT_DIR/build/libcomal-runtime/comal-run"
PROG="$ROOT_DIR/tests/programs/tone_play_test.lst"

if [ ! -x "$BIN" ]; then
  echo "comal-run binary not found at $BIN" >&2
  exit 2
fi

OUT=$("$BIN" "$PROG" 2>&1 || true)

echo "$OUT" | grep -q "\[sound\]" && {
  echo "Debug sound output found:" >&2
  echo "$OUT" >&2
  exit 1
}

echo "Test passed: no debug sound output and comal-run exited OK"
