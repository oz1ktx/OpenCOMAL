#!/bin/sh
# web_integration_test.sh - basic integration test for serve_comal.sh + wrapper
set -eu
ROOT=$(cd "$(dirname "$0")/../.." && pwd)
SVC="$ROOT/scripts/serve_comal.sh"
PROG="$ROOT/samples/web_dbg.lst"
PORT=18200
LOG=/tmp/opencomal_web_test.log
PIDFILE=/tmp/opencomal_web_test.pid

cleanup() {
  [ -f "$PIDFILE" ] && kill "$(cat $PIDFILE)" 2>/dev/null || true
  pkill -f 'ncat --listen --keep-open --exec' 2>/dev/null || true
  rm -f "$PIDFILE"
}
trap cleanup EXIT INT TERM

# start server
"$SVC" -p "$PORT" "$PROG" >/tmp/serve_test.log 2>&1 &
echo $! > "$PIDFILE"
# give ncat a short moment
sleep 0.3

# query server
OUT=$(curl -sS --max-time 5 http://localhost:$PORT/ || true)
# basic assertions
printf '%s\n' "$OUT" > $LOG
if ! printf '%s' "$OUT" | grep -q "HTTP/1.0 200 OK"; then
  echo "FAIL: missing HTTP status" >&2
  cat $LOG >&2
  exit 2
fi
if ! printf '%s' "$OUT" | grep -q "Hello from COMAL socket server"; then
  echo "FAIL: missing body text" >&2
  cat $LOG >&2
  exit 3
fi

echo "OK"
