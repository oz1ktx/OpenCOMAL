#!/bin/bash

# Simple test to verify LSP server can handle basic messages

LSP_SERVER="./build/comal-lsp/comal-lsp"
TEST_FILE="./legacy/samples/tests/proc1.lst"

echo "Testing OpenCOMAL LSP server..."

# Create a temporary file with LSP messages
cat > /tmp/lsp_input.txt << 'EOM'
Content-Length: 157

{"jsonrpc":"2.0","id":1,"method":"initialize","params":{"processId":null,"rootUri":"file:///home/peter/Workspace/OpenCOMAL","capabilities":{}}}

Content-Length: 139

{"jsonrpc":"2.0","method":"initialized","params":{}}

Content-Length: 44

{"jsonrpc":"2.0","method":"shutdown","params":null}

Content-Length: 33

{"jsonrpc":"2.0","id":2,"method":"exit"}
EOM

# Run the LSP server with the input and capture output
echo "Running LSP server with test messages..."
cat /tmp/lsp_input.txt | timeout 10s $LSP_SERVER 2>&1

echo "Test completed."
