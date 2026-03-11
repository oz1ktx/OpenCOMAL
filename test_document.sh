#!/bin/bash

echo "Testing LSP server with document operations..."

# Initialize
INIT='{"jsonrpc":"2.0","id":1,"method":"initialize","params":{"processId":null,"rootUri":"file:///home/peter/Workspace/OpenCOMAL","capabilities":{}}}'
printf "Content-Length: %d\r\n\r\n%s" ${#INIT} "$INIT" | ./build/comal-lsp/comal-lsp

echo -e "\n--- Initialize response above ---\n"

# Document open
DOC_CONTENT="10 PROC hallo\n20 PRINT \"Hello\"\n30 ENDPROC"
DOC_MSG="{\"jsonrpc\":\"2.0\",\"method\":\"textDocument/didOpen\",\"params\":{\"textDocument\":{\"uri\":\"file:///tmp/test.lst\",\"languageId\":\"comal\",\"version\":1,\"text\":\"$DOC_CONTENT\"}}}"
printf "Content-Length: %d\r\n\r\n%s" ${#DOC_MSG} "$DOC_MSG" | ./build/comal-lsp/comal-lsp

echo -e "\n--- Document open response above ---\n"

echo "Test completed."
