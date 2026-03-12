# COMAL LSP Usage Guide

## Using the OpenCOMAL LSP Server in Kate and VS Code

### 1. Build the LSP Server

- From your OpenCOMAL workspace:
  ```bash
  cd build && cmake .. && make -j$(nproc)
  ```
- The LSP server binary will be at:
  `build/comal-lsp/comal-lsp`

### 2. Using in Kate

- Open Kate.
- Go to `Settings` → `Configure Kate` → `LSP Client`.
- Click `+` to add a new LSP server:
  - **Name:** COMAL
  - **Executable:** `/path/to/build/comal-lsp/comal-lsp`
  - **Root URI:** (leave blank or set project root)
  - **File extensions:** `*.lst` (or your COMAL file extension)
- Enable LSP features (diagnostics, completion, hover, go to definition).
- Open a COMAL file and verify LSP features are active.

### 3. Using in VS Code

- Install the [Language Server Protocol](https://marketplace.visualstudio.com/items?itemName=Microsoft.vscode-lsp) extension (if not already present).
- Use the [LSP Client](https://marketplace.visualstudio.com/items?itemName=rinvex.language-server-client) extension or configure a custom language server:
  - Go to `settings.json` and add:
    ```json
    "lsp-client.servers": {
      "comal": {
        "command": ["/path/to/build/comal-lsp/comal-lsp"],
        "languages": ["comal"],
        "fileExtensions": [".lst"]
      }
    }
    ```
- Open a COMAL file (`.lst`) and check for diagnostics, completion, hover, and definition support.

### 4. Troubleshooting

- Ensure the LSP server binary is executable.
- Check the LSP server logs for errors.
- If features are missing, verify the LSP client configuration and file extension mapping.

### 5. IDE Integration

- The OpenCOMAL IDE integrates the LSP server automatically for COMAL files.
- No manual setup is needed; diagnostics, completion, hover, and definition are available in the editor.

---
For more details, see the OpenCOMAL documentation or contact the project maintainers.
