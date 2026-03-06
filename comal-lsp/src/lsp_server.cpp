#include "comal_lsp_server.h"
#include "comal_lsp_protocol.h"

#include <iostream>
#include <sstream>
#include <algorithm>

namespace comal::lsp {

LspServer::LspServer() : running_(false) {}

LspServer::~LspServer() = default;

void LspServer::run() {
    running_ = true;
    std::string line;

    while (running_ && std::getline(std::cin, line)) {
        if (line.empty()) continue;

        // Simple Content-Length header parsing
        if (line.find("Content-Length:") == 0) {
            // Skip header lines
            continue;
        }

        // Empty line signals end of headers
        if (line == "\r" || line == "") {
            // Read the actual message
            std::getline(std::cin, line);
            if (!line.empty()) {
                handleMessage(line);
            }
        }
    }
}

void LspServer::stop() {
    running_ = false;
}

void LspServer::handleMessage(const std::string& rawMessage) {
    try {
        LspRequest request = parseRequest(rawMessage);

        if (request.method == "initialize") {
            handleInitialize(request);
        } else if (request.method == "shutdown") {
            handleShutdown(request);
        } else if (request.method == "exit") {
            handleExit(request);
        } else if (request.method == "textDocument/didOpen") {
            handleDidOpen(request);
        } else if (request.method == "textDocument/didChange") {
            handleDidChange(request);
        } else if (request.method == "textDocument/didClose") {
            handleDidClose(request);
        } else if (request.method == "textDocument/completion") {
            handleCompletion(request);
        } else if (request.method == "textDocument/definition") {
            handleDefinition(request);
        } else if (request.method == "textDocument/hover") {
            handleHover(request);
        } else {
            // Unknown method
            if (request.id) {
                LspResponse response;
                response.id = request.id;
                response.error = "Unknown method: " + request.method;
                sendResponse(response);
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error handling message: " << e.what() << std::endl;
    }
}

void LspServer::handleInitialize(const LspRequest& request) {
    LspResponse response;
    response.id = request.id;

    // Minimal capabilities response
    response.result = R"({
        "capabilities": {
            "textDocumentSync": 1,
            "completionProvider": {
                "resolveProvider": false
            },
            "definitionProvider": true,
            "hoverProvider": true,
            "diagnosticProvider": {
                "interFileDependencies": false,
                "workspaceDiagnostics": false
            }
        },
        "serverInfo": {
            "name": "OpenCOMAL Language Server",
            "version": "0.1.0"
        }
    })";

    sendResponse(response);
}

void LspServer::handleShutdown(const LspRequest& request) {
    LspResponse response;
    response.id = request.id;
    response.result = "null";
    sendResponse(response);
}

void LspServer::handleExit(const LspRequest& request) {
    stop();
}

void LspServer::handleDidOpen(const LspRequest& request) {
    // Parse textDocument/didOpen params
    // Expected format: {"textDocument": {"uri": "...", "languageId": "...", "version": ..., "text": "..."}}
    
    std::string uri, text;
    if (parseDocumentParams(request.params, uri, text)) {
        documents_[uri] = text;
        buildSymbolTable(uri, text);
        publishDiagnostics(uri, parseDocument(text));
    }
}

void LspServer::handleDidChange(const LspRequest& request) {
    // Parse textDocument/didChange params
    // Expected format: {"textDocument": {"uri": "...", "version": ...}, "contentChanges": [{"text": "..."}]}
    
    std::string uri, text;
    if (parseDocumentChangeParams(request.params, uri, text)) {
        documents_[uri] = text;
        buildSymbolTable(uri, text);
        publishDiagnostics(uri, parseDocument(text));
    }
}

void LspServer::handleDidClose(const LspRequest& request) {
    // Parse textDocument/didClose params
    // Expected format: {"textDocument": {"uri": "..."}}
    
    std::string uri;
    if (parseDocumentCloseParams(request.params, uri)) {
        documents_.erase(uri);
        // Clear diagnostics for closed document
        publishDiagnostics(uri, {});
    }
}

void LspServer::handleDefinition(const LspRequest& request) {
    LspResponse response;
    response.id = request.id;
    
    std::string uri;
    int line, character;
    if (!parseDefinitionParams(request.params, uri, line, character)) {
        response.result = "null";
        sendResponse(response);
        return;
    }
    
    // Get the document content
    auto docIt = documents_.find(uri);
    if (docIt == documents_.end()) {
        response.result = "null";
        sendResponse(response);
        return;
    }
    
    const std::string& content = docIt->second;
    
    // Find the word at the cursor position
    std::istringstream iss(content);
    std::string currentLine;
    int currentLineNum = 0;
    std::string symbolName;
    
    while (std::getline(iss, currentLine)) {
        if (!currentLine.empty() && currentLine.back() == '\r') {
            currentLine.pop_back();
        }
        
        if (currentLineNum == line) {
            // Extract the word at the cursor position
            if (character <= static_cast<int>(currentLine.length())) {
                std::string beforeCursor = currentLine.substr(0, character);
                std::string afterCursor = currentLine.substr(character);
                
                // Find word boundaries
                size_t wordStart = beforeCursor.find_last_of(" \t()[]{},;=+-*/");
                size_t wordEnd = afterCursor.find_first_of(" \t()[]{},;=+-*/");
                
                if (wordStart == std::string::npos) {
                    wordStart = 0;
                } else {
                    wordStart += 1;
                }
                
                std::string word = beforeCursor.substr(wordStart);
                if (wordEnd != std::string::npos) {
                    word += afterCursor.substr(0, wordEnd);
                } else {
                    word += afterCursor;
                }
                
                symbolName = word;
            }
            break;
        }
        currentLineNum++;
    }
    
    // Find the symbol definition
    SymbolInfo* definition = findSymbolDefinition(uri, symbolName);
    if (definition) {
        std::ostringstream oss;
        oss << R"({"uri":")" << uri << R"(","range":{"start":{"line":)" << definition->line 
            << R"(,"character":)" << definition->character << R"(},"end":{"line":)" << definition->line 
            << R"(,"character":)" << (definition->character + static_cast<int>(definition->name.length())) << R"(}}})";
        response.result = oss.str();
    } else {
        response.result = "null";
    }
    
    sendResponse(response);
}

void LspServer::handleHover(const LspRequest& request) {
    LspResponse response;
    response.id = request.id;
    
    std::string uri;
    int line, character;
    if (!parseCompletionParams(request.params, uri, line, character)) {
        response.result = "null";
        sendResponse(response);
        return;
    }
    
    // Get the document content
    auto docIt = documents_.find(uri);
    if (docIt == documents_.end()) {
        response.result = "null";
        sendResponse(response);
        return;
    }
    
    const std::string& content = docIt->second;
    
    // Find the word at the cursor position (reuse logic from definition)
    std::istringstream iss(content);
    std::string currentLine;
    int currentLineNum = 0;
    std::string symbolName;
    
    while (std::getline(iss, currentLine)) {
        if (!currentLine.empty() && currentLine.back() == '\r') {
            currentLine.pop_back();
        }
        
        if (currentLineNum == line) {
            if (character <= static_cast<int>(currentLine.length())) {
                std::string beforeCursor = currentLine.substr(0, character);
                std::string afterCursor = currentLine.substr(character);
                
                size_t wordStart = beforeCursor.find_last_of(" \t()[]{},;=+-*/");
                size_t wordEnd = afterCursor.find_first_of(" \t()[]{},;=+-*/");
                
                if (wordStart == std::string::npos) {
                    wordStart = 0;
                } else {
                    wordStart += 1;
                }
                
                std::string word = beforeCursor.substr(wordStart);
                if (wordEnd != std::string::npos) {
                    word += afterCursor.substr(0, wordEnd);
                } else {
                    word += afterCursor;
                }
                
                symbolName = word;
            }
            break;
        }
        currentLineNum++;
    }
    
    // Find symbol information
    SymbolInfo* symbol = findSymbolDefinition(uri, symbolName);
    if (symbol) {
        std::ostringstream oss;
        oss << R"({"contents":{"kind":"markdown","value":")" << symbol->signature << R"("},"range":{"start":{"line":)" << line 
            << R"(,"character":)" << (character - static_cast<int>(symbolName.length())) << R"(},"end":{"line":)" << line 
            << R"(,"character":)" << character << R"(}}})";
        response.result = oss.str();
    } else {
        // Check if it's a keyword
        std::vector<std::string> keywords = {
            "PRINT", "INPUT", "IF", "THEN", "ELSE", "END", "FOR", "TO", "STEP", "NEXT",
            "WHILE", "REPEAT", "UNTIL", "PROC", "FUNC", "RETURN", "LOCAL", "CLOSED"
        };
        
        bool isKeyword = false;
        for (const auto& keyword : keywords) {
            if (keyword == symbolName) {
                isKeyword = true;
                break;
            }
        }
        
        if (isKeyword) {
            std::ostringstream oss;
            oss << R"({"contents":{"kind":"markdown","value":"**)" << symbolName << R"(**\n\nCOMAL keyword")";
            oss << R"("},"range":{"start":{"line":)" << line 
                << R"(,"character":)" << (character - static_cast<int>(symbolName.length())) << R"(},"end":{"line":)" << line 
                << R"(,"character":)" << character << R"(}}})";
            response.result = oss.str();
        } else {
            response.result = "null";
        }
    }
    
    sendResponse(response);
}

void LspServer::sendResponse(const LspResponse& response) {
    std::string json = serializeResponse(response);
    std::cout << "Content-Length: " << json.length() << "\r\n\r\n";
    std::cout << json << std::flush;
}

void LspServer::sendNotification(const std::string& method, const std::string& params) {
    LspNotification notif;
    notif.method = method;
    notif.params = params;
    std::string json = serializeNotification(notif);
    std::cout << "Content-Length: " << json.length() << "\r\n\r\n";
    std::cout << json << std::flush;
}

void LspServer::publishDiagnostics(const std::string& uri, const std::vector<Diagnostic>& diagnostics) {
    LspNotification notif;
    notif.method = "textDocument/publishDiagnostics";
    
    std::ostringstream oss;
    oss << R"({"uri":")" << uri << R"(","diagnostics":[)";
    
    for (size_t i = 0; i < diagnostics.size(); ++i) {
        if (i > 0) oss << ",";
        oss << R"({"range":{"start":{"line":)" << diagnostics[i].range.start.line 
            << R"(,"character":)" << diagnostics[i].range.start.character << R"(},"end":{"line":)" 
            << diagnostics[i].range.end.line << R"(,"character":)" << diagnostics[i].range.end.character 
            << R"(}},"message":")" << diagnostics[i].message << R"(","severity":)" << diagnostics[i].severity 
            << R"(,"source":")" << diagnostics[i].source << R"("})";
    }
    
    oss << "]}";
    notif.params = oss.str();
    
    sendNotification(notif.method, notif.params);
}

std::string LspServer::unescapeJsonString(const std::string& str) {
    std::string result;
    result.reserve(str.length());
    
    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] == '\\' && i + 1 < str.length()) {
            switch (str[i + 1]) {
                case 'n': result += '\n'; i++; break;
                case 't': result += '\t'; i++; break;
                case 'r': result += '\r'; i++; break;
                case '"': result += '"'; i++; break;
                case '\\': result += '\\'; i++; break;
                default: result += str[i]; break; // Keep the backslash if unknown escape
            }
        } else {
            result += str[i];
        }
    }
    
    return result;
}

bool LspServer::parseDocumentParams(const std::string& params, std::string& uri, std::string& text) {
    // Simple JSON parsing for textDocument/didOpen
    // Format: {"textDocument": {"uri": "...", "languageId": "...", "version": ..., "text": "..."}}
    
    size_t uriPos = params.find("\"uri\"");
    if (uriPos == std::string::npos) return false;
    
    uriPos = params.find("\"", uriPos + 6);
    if (uriPos == std::string::npos) return false;
    
    size_t uriEnd = params.find("\"", uriPos + 1);
    if (uriEnd == std::string::npos) return false;
    
    uri = params.substr(uriPos + 1, uriEnd - uriPos - 1);
    
    // Find text field
    size_t textPos = params.find("\"text\"");
    if (textPos == std::string::npos) return false;
    
    textPos = params.find("\"", textPos + 7);
    if (textPos == std::string::npos) return false;
    
    // Find the actual end of the JSON string, handling escaped quotes
    size_t textEnd = textPos + 1;
    while (textEnd < params.length()) {
        if (params[textEnd] == '"' && params[textEnd - 1] != '\\') {
            // Found unescaped quote
            break;
        }
        textEnd++;
    }
    if (textEnd >= params.length()) return false;
    
    std::string rawText = params.substr(textPos + 1, textEnd - textPos - 1);
    text = unescapeJsonString(rawText);
    return true;
}

bool LspServer::parseDocumentChangeParams(const std::string& params, std::string& uri, std::string& text) {
    // Simple JSON parsing for textDocument/didChange
    // Format: {"textDocument": {"uri": "...", "version": ...}, "contentChanges": [{"text": "..."}]}
    
    size_t uriPos = params.find("\"uri\"");
    if (uriPos == std::string::npos) return false;
    
    uriPos = params.find("\"", uriPos + 6);
    if (uriPos == std::string::npos) return false;
    
    size_t uriEnd = params.find("\"", uriPos + 1);
    if (uriEnd == std::string::npos) return false;
    
    uri = params.substr(uriPos + 1, uriEnd - uriPos - 1);
    
    // Find contentChanges array
    size_t changesPos = params.find("\"contentChanges\"");
    if (changesPos == std::string::npos) return false;
    
    // For simplicity, assume single change with full text
    size_t textPos = params.find("\"text\"", changesPos);
    if (textPos == std::string::npos) return false;
    
    textPos = params.find("\"", textPos + 7);
    if (textPos == std::string::npos) return false;
    
    // Find the actual end of the JSON string, handling escaped quotes
    size_t textEnd = textPos + 1;
    while (textEnd < params.length()) {
        if (params[textEnd] == '"' && params[textEnd - 1] != '\\') {
            // Found unescaped quote
            break;
        }
        textEnd++;
    }
    if (textEnd >= params.length()) return false;
    
    std::string rawText = params.substr(textPos + 1, textEnd - textPos - 1);
    text = unescapeJsonString(rawText);
    return true;
}

bool LspServer::parseDocumentCloseParams(const std::string& params, std::string& uri) {
    // Simple JSON parsing for textDocument/didClose
    // Format: {"textDocument": {"uri": "..."}}
    
    size_t uriPos = params.find("\"uri\"");
    if (uriPos == std::string::npos) return false;
    
    uriPos = params.find("\"", uriPos + 6);
    if (uriPos == std::string::npos) return false;
    
    size_t uriEnd = params.find("\"", uriPos + 1);
    if (uriEnd == std::string::npos) return false;
    
    uri = params.substr(uriPos + 1, uriEnd - uriPos - 1);
    return true;
}

std::vector<Diagnostic> LspServer::parseDocument(const std::string& text) {
    std::vector<Diagnostic> diagnostics;
    
    // Basic syntax checking - look for common COMAL syntax errors
    std::istringstream iss(text);
    std::string line;
    int lineNumber = 0;
    
    while (std::getline(iss, line)) {
        // Remove carriage return if present
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        
        // Check for unmatched quotes
        int quoteCount = 0;
        for (char c : line) {
            if (c == '"') quoteCount++;
        }
        if (quoteCount % 2 != 0) {
            diagnostics.push_back({
                {lineNumber, 0, lineNumber, static_cast<int>(line.length())},
                "Unmatched quote in string literal",
                std::nullopt,
                "comal",
                1  // Error
            });
        }
        
        // Check for missing END statements (very basic)
        if (line.find("FOR ") != std::string::npos || 
            line.find("WHILE ") != std::string::npos ||
            line.find("IF ") != std::string::npos) {
            // This is a very basic check - in a real implementation we'd need proper AST analysis
            // For now, just flag potential issues
        }
        
        lineNumber++;
    }
    
    return diagnostics;
}

void LspServer::buildSymbolTable(const std::string& uri, const std::string& content) {
    std::vector<SymbolInfo>& symbols = symbol_tables_[uri];
    symbols.clear();
    
    std::istringstream iss(content);
    std::string line;
    int lineNumber = 0;
    
    while (std::getline(iss, line)) {
        // Remove carriage return if present
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        
        // Trim leading whitespace
        size_t start = line.find_first_not_of(" \t");
        if (start == std::string::npos) {
            lineNumber++;
            continue; // Empty line
        }
        line = line.substr(start);
        
        // Check for PROC or FUNC definitions
        if (line.substr(0, 5) == "PROC " || line.substr(0, 5) == "FUNC ") {
            std::string kind = (line.substr(0, 4) == "PROC") ? "procedure" : "function";
            std::string remaining = line.substr(5); // Skip "PROC " or "FUNC "
            
            // Find the function/procedure name
            size_t nameEnd = remaining.find_first_of(" (");
            if (nameEnd != std::string::npos) {
                std::string name = remaining.substr(0, nameEnd);
                
                // Build signature
                std::string signature = kind + " " + name;
                if (remaining.find('(') != std::string::npos) {
                    size_t paramStart = remaining.find('(');
                    size_t paramEnd = remaining.find(')', paramStart);
                    if (paramEnd != std::string::npos) {
                        signature += remaining.substr(paramStart, paramEnd - paramStart + 1);
                    }
                }
                
                symbols.push_back({
                    name,
                    lineNumber,
                    static_cast<int>(start + 5), // Position after "PROC " or "FUNC "
                    kind,
                    signature
                });
            }
        }
        
        lineNumber++;
    }
}

std::vector<SymbolInfo> LspServer::findSymbolsAtPosition(const std::string& uri, int line, int character) {
    std::vector<SymbolInfo> result;
    auto it = symbol_tables_.find(uri);
    if (it == symbol_tables_.end()) return result;
    
    // For now, return all symbols (could be filtered by position later)
    return it->second;
}

SymbolInfo* LspServer::findSymbolDefinition(const std::string& uri, const std::string& name) {
    auto it = symbol_tables_.find(uri);
    if (it == symbol_tables_.end()) return nullptr;
    
    for (auto& symbol : it->second) {
        if (symbol.name == name) {
            return &symbol;
        }
    }
    return nullptr;
}

bool LspServer::parseCompletionParams(const std::string& params, std::string& uri, int& line, int& character) {
    // Simple JSON parsing for textDocument/completion
    // Format: {"textDocument": {"uri": "..."}, "position": {"line": ..., "character": ...}}
    
    size_t uriPos = params.find("\"uri\"");
    if (uriPos == std::string::npos) return false;
    
    uriPos = params.find("\"", uriPos + 6);
    if (uriPos == std::string::npos) return false;
    
    size_t uriEnd = params.find("\"", uriPos + 1);
    if (uriEnd == std::string::npos) return false;
    
    uri = params.substr(uriPos + 1, uriEnd - uriPos - 1);
    
    // Find line
    size_t linePos = params.find("\"line\"");
    if (linePos == std::string::npos) return false;
    
    size_t colonPos = params.find(":", linePos);
    if (colonPos == std::string::npos) return false;
    
    size_t commaPos = params.find(",", colonPos);
    if (commaPos == std::string::npos) commaPos = params.find("}", colonPos);
    if (commaPos == std::string::npos) return false;
    
    std::string lineStr = params.substr(colonPos + 1, commaPos - colonPos - 1);
    line = std::stoi(lineStr);
    
    // Find character
    size_t charPos = params.find("\"character\"", commaPos);
    if (charPos == std::string::npos) return false;
    
    colonPos = params.find(":", charPos);
    if (colonPos == std::string::npos) return false;
    
    commaPos = params.find(",", colonPos);
    if (commaPos == std::string::npos) commaPos = params.find("}", colonPos);
    if (commaPos == std::string::npos) return false;
    
    std::string charStr = params.substr(colonPos + 1, commaPos - colonPos - 1);
    character = std::stoi(charStr);
    
    return true;
}
bool LspServer::parseDefinitionParams(const std::string& params, std::string& uri, int& line, int& character) {
    // Same format as completion
    return parseCompletionParams(params, uri, line, character);
}
void LspServer::handleCompletion(const LspRequest& request) {
    LspResponse response;
    response.id = request.id;
    
    std::string uri;
    int line, character;
    if (!parseCompletionParams(request.params, uri, line, character)) {
        response.result = "[]";
        sendResponse(response);
        return;
    }
    
    // Get the document content
    auto docIt = documents_.find(uri);
    if (docIt == documents_.end()) {
        response.result = "[]";
        sendResponse(response);
        return;
    }
    
    const std::string& content = docIt->second;
    
    // Find the word being typed
    std::istringstream iss(content);
    std::string currentLine;
    int currentLineNum = 0;
    std::string prefix;
    
    while (std::getline(iss, currentLine)) {
        if (!currentLine.empty() && currentLine.back() == '\r') {
            currentLine.pop_back();
        }
        
        if (currentLineNum == line) {
            // Extract the word up to the cursor position
            if (character <= static_cast<int>(currentLine.length())) {
                std::string beforeCursor = currentLine.substr(0, character);
                
                // Find the start of the current word
                size_t wordStart = beforeCursor.find_last_of(" \t()[]{},;=+-*/");
                if (wordStart == std::string::npos) {
                    prefix = beforeCursor;
                } else {
                    prefix = beforeCursor.substr(wordStart + 1);
                }
            }
            break;
        }
        currentLineNum++;
    }
    
    // Generate completion items
    std::vector<std::string> completions;
    
    // Add keywords
    std::vector<std::string> keywords = {
        "PRINT", "INPUT", "IF", "THEN", "ELSE", "END", "FOR", "TO", "STEP", "NEXT",
        "WHILE", "REPEAT", "UNTIL", "PROC", "FUNC", "RETURN", "LOCAL", "CLOSED",
        "IMPORT", "EXPORT", "LET", "DIM", "READ", "DATA", "RESTORE", "STOP",
        "TRAP", "ESCAPE", "EXECUTE", "RUN", "NEW", "OLD", "SAVE", "LIST",
        "DELETE", "RENUMBER", "AUTO", "PAGE", "CURSOR", "ZONE", "USING"
    };
    
    for (const auto& keyword : keywords) {
        if (keyword.find(prefix) == 0) {
            completions.push_back(keyword);
        }
    }
    
    // Add symbols from the current document
    auto symIt = symbol_tables_.find(uri);
    if (symIt != symbol_tables_.end()) {
        for (const auto& symbol : symIt->second) {
            if (symbol.name.find(prefix) == 0) {
                completions.push_back(symbol.name);
            }
        }
    }
    
    // Build JSON response
    std::ostringstream oss;
    oss << "[";
    for (size_t i = 0; i < completions.size(); ++i) {
        if (i > 0) oss << ",";
        oss << R"({"label":")" << completions[i] << R"(","kind":)" << 14 << R"(,"detail":"COMAL"})";
    }
    oss << "]";
    
    response.result = oss.str();
    sendResponse(response);
}

}  // namespace comal::lsp
