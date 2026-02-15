#!/bin/sh
# serve_comal.sh - simple TCP launcher for opencomalrun
# Usage: serve_comal.sh [-p PORT] /path/to/program.lst
# If `ncat` is available it will be used; otherwise `socat` is used.

PORT=8080
while getopts "p:" opt; do
  case "$opt" in
    p) PORT="$OPTARG" ;;
    *) echo "Usage: $0 [-p PORT] program.lst"; exit 2 ;;
  esac
done
shift $((OPTIND-1))

PROG="$1"
if [ -z "$PROG" ]; then
  echo "Usage: $0 [-p PORT] program.lst" >&2
  exit 2
fi

# Find opencomalrun (prefer repo bin)
if [ -x "$(pwd)/../bin/opencomalrun" ]; then
  OPENCOMALRUN="$(pwd)/../bin/opencomalrun"
elif [ -x "../bin/opencomalrun" ]; then
  OPENCOMALRUN="../bin/opencomalrun"
else
  OPENCOMALRUN="$(command -v opencomalrun 2>/dev/null || true)"
fi

if [ -z "$OPENCOMALRUN" ] || [ ! -x "$OPENCOMALRUN" ]; then
  echo "opencomalrun binary not found. Build it or put it in PATH." >&2
  exit 3
fi

echo "Serving $PROG on port $PORT using $OPENCOMALRUN"

if command -v ncat >/dev/null 2>&1; then
  echo "Using ncat for incoming connections (wrapper)"
  WRAPPER="$(pwd)/scripts/serve_wrapper.sh"
  export OPENCOMALRUN PROG
  exec ncat --listen --keep-open --exec "$WRAPPER" -p "$PORT"
elif command -v socat >/dev/null 2>&1; then
  echo "Using socat for incoming connections (wrapper)"
  WRAPPER="$(pwd)/scripts/serve_wrapper.sh"
  export OPENCOMALRUN PROG
  exec socat TCP-LISTEN:$PORT,reuseaddr,fork EXEC:"$WRAPPER"
else
  echo "Please install ncat (nmap-ncat) or socat" >&2
  exit 4
fi
