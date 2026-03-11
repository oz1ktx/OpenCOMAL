#!/bin/bash

# Test script to verify LSP server works with basic Kate-like messages

LSP_SERVER="./build/comal-lsp/comal-lsp"
TEST_FILE="./legacy/samples/tests/proc1.lst"

echo "Testing OpenCOMAL LSP server with Kate-like messages..."

# Start LSP server in background
$LSP_SERVER &
SERVER_PID=$!

# Give server time to start
sleep 1

# Send initialize request (what Kate would send)
INIT_MSG='{"jsonrpc":"2.0","id":1,"method":"initialize","params":{"processId":null,"rootUri":"file:///home/peter/Workspace/OpenCOMAL","capabilities":{}}}'

echo "Sending initialize request..."
echo "Content-Length: ${#INIT_MSG}" | cat - <(echo -e "\r") <(echo "$INIT_MSG") | nc -q 1 localhost 0 2>/dev/null || echo "Server not responding on stdin/stdout"

# Kill server
kill $SERVER_PID 2>/dev/null
wait $SERVER_PID 2>/dev/null

echo "Test completed."
