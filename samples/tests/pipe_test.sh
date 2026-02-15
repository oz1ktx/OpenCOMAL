#!/bin/sh
set -euo pipefail

# Run from repo: samples/tests/pipe_test.sh
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
BIN="$ROOT/bin/opencomalrun"
PROG="$ROOT/samples/filter_pipe.lst"

if [ ! -x "$BIN" ]; then
  echo "ERROR: binary not found at $BIN"
  exit 2
fi

OUT=$(printf 'hello plain\n\n' | "$BIN" --plain "$PROG")
EXPECTED="hello plain"

if [ "$OUT" = "$EXPECTED" ]; then
  echo "OK"
  exit 0
else
  echo "FAIL"
  echo "expected: <$EXPECTED>"
  echo "got: <$OUT>"
  exit 3
fi
