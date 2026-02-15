#!/bin/sh
# serve_wrapper.sh <opencomalrun> <program.lst>
# prefer explicit args, else fall back to exported env vars
BINARY="${1:-$OPENCOMALRUN}"
PROG_PATH="${2:-$PROG}"
# Prefix a minimal HTTP/1.0 response header so this wrapper can be
# used as a simple CGI-like helper. The COMAL program may still emit
# additional headers or body content; ensure the program's output
# follows the HTTP header we send here.
printf 'HTTP/1.0 200 OK\r\nContent-Type: text/plain\r\n\r\n' >&1
# By default do not prefix an HTTP header here; the COMAL program
# (e.g. samples/web_skeleton.lst) should emit the proper response
# after reading the request. Exec the runtime so it inherits the
# socket as stdin/stdout.
exec "$BINARY" --plain "$PROG_PATH"
