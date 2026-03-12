#pragma once

#include <string>
#include <map>
#include <memory>
#include <functional>
#include <vector>
#include <unordered_map>

#include "comal_parser_api.h"
#include "comal_ast_modern.h"
#include "comal_graphics_commands.h"

namespace comal::lsp {

// Forward declarations
struct LspRequest;
struct LspResponse;
struct Diagnostic;

/// Symbol information for code intelligence
struct SymbolInfo {
    std::string name;
    int line;           // 0-based line number
    int character;      // 0-based character position
    std::string kind;   // "procedure", "function", "variable", etc.
    std::string signature; // For PROC/FUNC signatures
};

/// LSP Server implementation for OpenCOMAL
/// Implements Language Server Protocol version 3.17
class LspServer {
public:
    LspServer();
    ~LspServer();

    /// Start listening for LSP messages on stdin/stdout
    void run();

    /// Stop the server gracefully
    void stop();

    /// Check if server is running
    bool isRunning() const { return running_; }

    // Test-friendly interface (public for testing)
    bool parseDocumentParams(const std::string& params, std::string& uri, std::string& text);
    bool parseDocumentChangeParams(const std::string& params, std::string& uri, std::string& text);
    bool parseDocumentCloseParams(const std::string& params, std::string& uri);
    std::vector<Diagnostic> parseDocument(const std::string& text);
    
    // Completion helpers
    bool parseCompletionParams(const std::string& params, std::string& uri, int& line, int& character);
    bool parseDefinitionParams(const std::string& params, std::string& uri, int& line, int& character);
    
    // Symbol table (public for testing)
    void buildSymbolTable(const std::string& uri, const std::string& content);
    std::vector<SymbolInfo> findSymbolsAtPosition(const std::string& uri, int line, int character);
    SymbolInfo* findSymbolDefinition(const std::string& uri, const std::string& name);

private:
    bool running_ = false;

    // JSON parsing helpers
    std::string unescapeJsonString(const std::string& str);

    // Message handlers
    void handleMessage(const std::string& rawMessage);
    void handleInitialize(const LspRequest& request);
    void handleShutdown(const LspRequest& request);
    void handleExit(const LspRequest& request);

    // Diagnostics
    void handleDidOpen(const LspRequest& request);
    void handleDidChange(const LspRequest& request);
    void handleDidClose(const LspRequest& request);

    // Code intelligence
    void handleCompletion(const LspRequest& request);
    void handleDefinition(const LspRequest& request);
    void handleHover(const LspRequest& request);
    void handleDocumentSymbol(const LspRequest& request);

    // Utility
    void sendResponse(const LspResponse& response);
    void sendNotification(const std::string& method, const std::string& params);
    void publishDiagnostics(const std::string& uri, const std::vector<Diagnostic>& diagnostics);

    // Document parsing helpers (moved to public for testing)
    // bool parseDocumentParams(const std::string& params, std::string& uri, std::string& text);
    // bool parseDocumentChangeParams(const std::string& params, std::string& uri, std::string& text);
    // bool parseDocumentCloseParams(const std::string& params, std::string& uri);
    // std::vector<Diagnostic> parseDocument(const std::string& text);

    // Graphics command registry (single source of truth from libcomal-graphics)
    comal::graphics::CommandRegistry graphics_registry_;

    // Document tracking
    std::map<std::string, std::string> documents_;  // URI -> content
    std::map<std::string, std::vector<SymbolInfo>> symbol_tables_;  // URI -> symbols
};

}  // namespace comal::lsp
