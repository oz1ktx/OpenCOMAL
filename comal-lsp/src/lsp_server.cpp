#include "comal_lsp_server.h"
#include "comal_lsp_protocol.h"
#include "comal_graphics_commands.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>

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
        } else if (request.method == "textDocument/documentSymbol") {
            handleDocumentSymbol(request);
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
                "resolveProvider": false,
                "triggerCharacters": [" "]
            },
            "definitionProvider": true,
            "hoverProvider": true,
            "documentSymbolProvider": true,
            "diagnosticProvider": {
                "interFileDependencies": false,
                "workspaceDiagnostics": false
            }
        },
        "serverInfo": {
            "name": "OpenCOMAL Language Server",
            "version": "0.2.0"
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

// Helper: extract the word under the cursor from a document.
static std::string extractWordAtCursor(const std::string& content, int line, int character) {
    std::istringstream iss(content);
    std::string currentLine;
    int currentLineNum = 0;

    while (std::getline(iss, currentLine)) {
        if (!currentLine.empty() && currentLine.back() == '\r')
            currentLine.pop_back();

        if (currentLineNum == line) {
            if (character > static_cast<int>(currentLine.length()))
                return {};

            std::string before = currentLine.substr(0, character);
            std::string after  = currentLine.substr(character);

            size_t ws = before.find_last_of(" \t()[]{},;=+-*/");
            size_t we = after.find_first_of(" \t()[]{},;=+-*/");

            std::string word = before.substr(ws == std::string::npos ? 0 : ws + 1);
            word += (we == std::string::npos) ? after : after.substr(0, we);
            return word;
        }
        currentLineNum++;
    }
    return {};
}

// Helper: check whether cursor is inside a DRAW statement and return the DRAW sub-token.
static std::string extractDrawSubcommand(const std::string& content, int line, int character) {
    std::istringstream iss(content);
    std::string currentLine;
    int currentLineNum = 0;

    while (std::getline(iss, currentLine)) {
        if (!currentLine.empty() && currentLine.back() == '\r')
            currentLine.pop_back();

        if (currentLineNum == line) {
            std::string trimmed = currentLine;
            size_t p = 0;
            while (p < trimmed.size() && (std::isdigit(static_cast<unsigned char>(trimmed[p])) || trimmed[p] == ' '))
                ++p;
            trimmed = trimmed.substr(p);

            std::string upper = trimmed;
            std::transform(upper.begin(), upper.end(), upper.begin(),
                           [](unsigned char c) { return std::toupper(c); });
            if (upper.substr(0, 5) != "DRAW " && upper.substr(0, 5) != "DRAW\t")
                return {};

            return extractWordAtCursor(content, line, character);
        }
        currentLineNum++;
    }
    return {};
}

// Canonical COMAL keyword docs used by both hover and completion.
static const std::vector<std::pair<std::string, std::string>>& keywordDocEntries() {
    static const std::vector<std::pair<std::string, std::string>> entries = {
        {"PRINT",    "Print values to the output device."},
        {"INPUT",    "Read a value from the user."},
        {"IF",       "Conditional execution. Use with THEN, ELSE, ENDIF."},
        {"THEN",     "Introduces the true-branch of IF."},
        {"ELSE",     "Introduces the false-branch of IF."},
        {"ELIF",     "Else-if branch (IF ... ELIF ... ENDIF)."},
        {"END",      "Terminates a program, or closes a block (END IF, END FOR, END PROC, ...)."},
        {"ENDIF",    "Closes a multi-line IF block."},
        {"FOR",      "Counted loop: FOR var := start TO stop [STEP inc]."},
        {"TO",       "Upper bound in a FOR loop."},
        {"DOWNTO",   "Descending FOR direction: FOR i := hi DOWNTO lo."},
        {"STEP",     "Increment value in a FOR loop."},
        {"NEXT",     "End of a FOR loop body (or ENDFOR)."},
        {"ENDFOR",   "End of a FOR loop body."},
        {"WHILE",    "Loop while a condition is true."},
        {"ENDWHILE", "End of a WHILE loop body."},
        {"REPEAT",   "Loop body that repeats UNTIL a condition is true."},
        {"UNTIL",    "Condition that terminates a REPEAT loop."},
        {"DO",       "Start of a DO block (used with LOOP/UNTIL forms)."},
        {"IN",       "Membership/iteration helper keyword in selected statements."},
        {"PROC",     "Define a procedure: PROC name[(params)] ... ENDPROC."},
        {"ENDPROC",  "End of a PROC definition."},
        {"FUNC",     "Define a function: FUNC name[(params)] ... ENDFUNC."},
        {"ENDFUNC",  "End of a FUNC definition."},
        {"RETURN",   "Return a value from a FUNC."},
        {"LOCAL",    "Declare local variables in a PROC or FUNC."},
        {"CLOSED",   "Mark a PROC/FUNC as closed-scope (no access to outer variables)."},
        {"IMPORT",   "Import names into a CLOSED procedure."},
        {"GLOBAL",   "Alias for IMPORT in CLOSED procedure declarations."},
        {"EXPORT",   "Export names from a CLOSED procedure."},
        {"LET",      "Assignment (optional keyword, e.g. LET x := 5)."},
        {"DIM",      "Dimension (allocate) an array."},
        {"READ",     "Read the next value from a DATA list."},
        {"READ ONLY", "Open resource/file in read-only mode."},
        {"WRITE",    "Write values to a file stream or device."},
        {"DATA",     "Define inline data for READ statements."},
        {"RESTORE",  "Reset the DATA pointer."},
        {"STOP",     "Halt program execution."},
        {"TRAP",     "Set up an error/escape handler: TRAP ESC/ERR."},
        {"ESC",      "Escape condition keyword used with TRAP."},
        {"ESCAPE",   "Equivalent to pressing the escape key."},
        {"HANDLER",  "Error/escape handler block."},
        {"ENDTRAP",  "End of a TRAP block."},
        {"RETRY",    "Retry after handling an error/escape in a TRAP handler."},
        {"CASE",     "Multi-way branch: CASE expr OF ... ENDCASE."},
        {"WHEN",     "Branch inside a CASE block."},
        {"OTHERWISE","Default branch inside a CASE block."},
        {"ENDCASE",  "End of a CASE block."},
        {"EXEC",     "Execute a procedure call."},
        {"OPEN",     "Open a file handle for INPUT/OUTPUT/READ/WRITE."},
        {"CLOSE",    "Close an open file handle."},
        {"FILE",     "File-channel designator keyword (often used with #)."},
        {"APPEND",   "Open/write mode that appends to an existing file."},
        {"SELECT INPUT",  "Select default input channel/device."},
        {"SELECT OUTPUT", "Select default output channel/device."},
        {"ZONE",     "Set the print zone width."},
        {"PAGE",     "Clear the screen."},
        {"CURSOR",   "Position the cursor: CURSOR row, col."},
        {"OF",       "Part of CASE ... OF."},
        {"SELECT",   "Select output device."},
        {"DRAW",     "Execute a graphics command: DRAW subcommand args."},
        {"TONE",     "Play a simple sine tone: TONE frequency duration (ms)."},
        {"PLAY",     "Play a melody or instrument sequence (MML/MIDI-like string)."},
        {"SLEEP",    "Pause execution for a number of milliseconds."},
        {"USING",    "Formatted output: PRINT USING format$ ; values."},
        {"EXIT",     "Exit a loop early."},
        {"LOOP",     "Infinite loop (LOOP ... ENDLOOP / EXIT WHEN)."},
        {"ENDLOOP",  "End of a LOOP block."},
        {"NULL",     "No-operation statement."},
        {"DELETE",   "Delete program lines."},
        {"RANDOM",   "Randomize the random number generator."},
        {"RND",      "Random number function."},
        {"PI",       "Mathematical constant pi."},
        {"TRUE",     "Boolean true constant."},
        {"FALSE",    "Boolean false constant."},
        {"EOD",      "End-of-DATA indicator."},
        {"EOF",      "End-of-file indicator/function."},
        {"EOR",      "End-of-record indicator."},
        {"ERR",      "Current runtime error code."},
        {"ERRLINE",  "Line number of the current runtime error."},
        {"ERRTEXT$", "Text message for the current runtime error."},
        {"SPC",      "Output a number of spaces."},
        {"SPC$",     "String-valued spacing function."},
        {"TAB",      "Move to a specific column."},
        {"KEY$",     "Last key input as a string."},
        {"INKEY$",   "Non-blocking single-character input."},
        {"LOWER$",   "Convert a string to lowercase."},
        {"UPPER$",   "Convert a string to uppercase."},
        {"CHR$",     "Character corresponding to an ASCII code."},
        {"STR$",     "String representation of a number."},
        {"VAL",      "Numeric value of a string."},
        {"INT",      "Convert to integer (truncate toward zero)."},
        {"ABS",      "Absolute value."},
        {"SGN",      "Sign of a numeric expression (-1, 0, 1)."},
        {"ROUND",    "Round to nearest integer/value."},
        {"FRAC",     "Fractional part of a number."},
        {"SIN",      "Sine function."},
        {"COS",      "Cosine function."},
        {"TAN",      "Tangent function."},
        {"ATN",      "Arc tangent function."},
        {"ASN",      "Arc sine function."},
        {"ACS",      "Arc cosine function."},
        {"EXP",      "Exponential function e^x."},
        {"LOG",      "Natural logarithm."},
        {"LN",       "Natural logarithm (alias)."},
        {"RAD",      "Convert degrees to radians mode/value."},
        {"DEG",      "Convert radians to degrees mode/value."},
        {"SQR",      "Square root."},
        {"DIV",      "Integer division operator."},
        {"MOD",      "Remainder operator."},
        {"ORD",      "Character code of a single-character string."},
        {"UNIT",     "Current/default unit number."},
        {"UNIT$",    "Current/default unit name/path."},
        {"LEN",      "Length of a string, or number of elements in an array."},
        {"LEFT$",    "Left substring: LEFT$(str, n)."},
        {"RIGHT$",   "Right substring: RIGHT$(str, n)."},
        {"MID$",     "Middle substring: MID$(str, start, length)."},
        {"SPLIT$",   "Split a string into parts: SPLIT$(str, delim, index)."},
        {"DIR",      "Directory command or listing keyword."},
        {"DIR$",     "Directory listing/info function returning string."},
        {"CHDIR",    "Change current directory."},
        {"MKDIR",    "Create a directory."},
        {"RMDIR",    "Remove a directory."},
        {"NAME",     "Rename a file."},
        {"REF",      "Pass-by-reference parameter qualifier."},
        {"DYNAMIC",  "Dynamic variable/array storage attribute."},
        {"STATIC",   "Static variable/array storage attribute."},
        {"EXTERNAL", "Declare symbol defined in another module."},
        {"AND",      "Logical conjunction operator."},
        {"AND THEN", "Short-circuit logical conjunction."},
        {"OR",       "Logical disjunction operator."},
        {"OR THEN",  "Short-circuit logical disjunction."},
        {"NOT",      "Logical negation operator."},
        {"SYS",      "Execute a system command."},
        {"SYS$",     "System information: SYS$(info)."},
        {"OS",       "Operating-system command statement."},
        {"PASS",     "Alias for OS command statement."},
    };
    return entries;
}

static const std::unordered_map<std::string, std::string>& keywordDocs() {
    static const std::unordered_map<std::string, std::string> docs = [] {
        std::unordered_map<std::string, std::string> result;
        for (const auto& entry : keywordDocEntries())
            result.emplace(entry.first, entry.second);
        return result;
    }();
    return docs;
}

static const std::vector<std::string>& completionKeywords() {
    static const std::vector<std::string> keywords = [] {
        std::vector<std::string> result;
        result.reserve(keywordDocEntries().size());
        for (const auto& entry : keywordDocEntries())
            result.push_back(entry.first);
        return result;
    }();
    return keywords;
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
    
    auto docIt = documents_.find(uri);
    if (docIt == documents_.end()) {
        response.result = "null";
        sendResponse(response);
        return;
    }
    
    std::string symbolName = extractWordAtCursor(docIt->second, line, character);

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
    
    auto docIt = documents_.find(uri);
    if (docIt == documents_.end()) {
        response.result = "null";
        sendResponse(response);
        return;
    }
    
    const std::string& content = docIt->second;
    std::string symbolName = extractWordAtCursor(content, line, character);
    if (symbolName.empty()) {
        response.result = "null";
        sendResponse(response);
        return;
    }

    auto makeHover = [&](const std::string& markdown) {
        std::ostringstream oss;
        oss << R"({"contents":{"kind":"markdown","value":")" << markdown
            << R"("},"range":{"start":{"line":)" << line
            << R"(,"character":)" << (character - static_cast<int>(symbolName.length()))
            << R"(},"end":{"line":)" << line
            << R"(,"character":)" << character << R"(}}})";
        response.result = oss.str();
    };

    // 1) Check if it's a DRAW sub-command (cursor on a word inside a DRAW line)
    std::string drawSub = extractDrawSubcommand(content, line, character);
    if (!drawSub.empty()) {
        // Look up in graphics registry (case-insensitive)
        const auto* spec = graphics_registry_.find(drawSub);
        if (spec) {
            std::string md = "**DRAW " + spec->name + "**";
            if (!spec->argDescription.empty())
                md += " " + spec->argDescription;
            md += "\\n\\n" + spec->description;
            if (spec->minArgs == spec->maxArgs)
                md += "\\n\\nArguments: " + std::to_string(spec->minArgs);
            else
                md += "\\n\\nArguments: " + std::to_string(spec->minArgs) + "-" + std::to_string(spec->maxArgs);
            makeHover(md);
            sendResponse(response);
            return;
        }
    }

    // 2) User-defined PROC/FUNC symbol
    SymbolInfo* symbol = findSymbolDefinition(uri, symbolName);
    if (symbol) {
        makeHover(symbol->signature);
        sendResponse(response);
        return;
    }
    
    // 3) COMAL keyword
    std::string upper = symbolName;
    std::transform(upper.begin(), upper.end(), upper.begin(),
                   [](unsigned char c) { return std::toupper(c); });
    auto& docs = keywordDocs();
    auto it = docs.find(upper);
    if (it != docs.end()) {
        makeHover("**" + upper + "**\\n\\n" + it->second);
        sendResponse(response);
        return;
    }
    
    response.result = "null";
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
    
    std::istringstream iss(text);
    std::string line;
    int lineNumber = 0;
    
    // Stack-based block matching
    struct Block { std::string keyword; int line; };
    std::vector<Block> blockStack;
    
    while (std::getline(iss, line)) {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();
        
        // Check for unmatched quotes
        int quoteCount = 0;
        bool inString = false;
        for (size_t i = 0; i < line.size(); ++i) {
            if (line[i] == '"') {
                quoteCount++;
                inString = !inString;
            }
        }
        if (quoteCount % 2 != 0) {
            diagnostics.push_back({
                {lineNumber, 0, lineNumber, static_cast<int>(line.length())},
                "Unmatched quote in string literal",
                std::nullopt, "comal", 1
            });
        }

        // Extract the statement keyword from the line
        // Strip leading line number and whitespace
        std::string trimmed = line;
        size_t p = 0;
        while (p < trimmed.size() && (std::isdigit(static_cast<unsigned char>(trimmed[p])) || trimmed[p] == ' '))
            ++p;
        trimmed = trimmed.substr(p);
        // Strip trailing whitespace
        while (!trimmed.empty() && std::isspace(static_cast<unsigned char>(trimmed.back())))
            trimmed.pop_back();

        if (trimmed.empty()) { lineNumber++; continue; }

        // Uppercase for matching
        std::string upper = trimmed;
        std::transform(upper.begin(), upper.end(), upper.begin(),
                       [](unsigned char c) { return std::toupper(c); });

        // Extract first word
        size_t sp = upper.find_first_of(" \t");
        std::string firstWord = (sp == std::string::npos) ? upper : upper.substr(0, sp);

        // Block openers
        if (firstWord == "FOR")       blockStack.push_back({"FOR", lineNumber});
        else if (firstWord == "WHILE")  blockStack.push_back({"WHILE", lineNumber});
        else if (firstWord == "REPEAT") blockStack.push_back({"REPEAT", lineNumber});
        else if (firstWord == "LOOP")   blockStack.push_back({"LOOP", lineNumber});
        else if (firstWord == "CASE")   blockStack.push_back({"CASE", lineNumber});
        else if (firstWord == "TRAP")   blockStack.push_back({"TRAP", lineNumber});
        else if (firstWord == "IF" && upper.find("THEN") == std::string::npos)
            blockStack.push_back({"IF", lineNumber});  // multi-line IF only
        else if (firstWord == "PROC")   blockStack.push_back({"PROC", lineNumber});
        else if (firstWord == "FUNC")   blockStack.push_back({"FUNC", lineNumber});
        // Block closers
        else if (firstWord == "NEXT" || firstWord == "ENDFOR") {
            if (!blockStack.empty() && blockStack.back().keyword == "FOR")
                blockStack.pop_back();
            else
                diagnostics.push_back({{lineNumber, 0, lineNumber, static_cast<int>(line.length())},
                    firstWord + " without matching FOR", std::nullopt, "comal", 1});
        }
        else if (firstWord == "ENDWHILE") {
            if (!blockStack.empty() && blockStack.back().keyword == "WHILE")
                blockStack.pop_back();
            else
                diagnostics.push_back({{lineNumber, 0, lineNumber, static_cast<int>(line.length())},
                    "ENDWHILE without matching WHILE", std::nullopt, "comal", 1});
        }
        else if (firstWord == "UNTIL") {
            if (!blockStack.empty() && blockStack.back().keyword == "REPEAT")
                blockStack.pop_back();
            else
                diagnostics.push_back({{lineNumber, 0, lineNumber, static_cast<int>(line.length())},
                    "UNTIL without matching REPEAT", std::nullopt, "comal", 1});
        }
        else if (firstWord == "ENDLOOP") {
            if (!blockStack.empty() && blockStack.back().keyword == "LOOP")
                blockStack.pop_back();
            else
                diagnostics.push_back({{lineNumber, 0, lineNumber, static_cast<int>(line.length())},
                    "ENDLOOP without matching LOOP", std::nullopt, "comal", 1});
        }
        else if (firstWord == "ENDCASE") {
            if (!blockStack.empty() && blockStack.back().keyword == "CASE")
                blockStack.pop_back();
            else
                diagnostics.push_back({{lineNumber, 0, lineNumber, static_cast<int>(line.length())},
                    "ENDCASE without matching CASE", std::nullopt, "comal", 1});
        }
        else if (firstWord == "ENDTRAP") {
            if (!blockStack.empty() && blockStack.back().keyword == "TRAP")
                blockStack.pop_back();
            else
                diagnostics.push_back({{lineNumber, 0, lineNumber, static_cast<int>(line.length())},
                    "ENDTRAP without matching TRAP", std::nullopt, "comal", 1});
        }
        else if (firstWord == "ENDIF") {
            if (!blockStack.empty() && blockStack.back().keyword == "IF")
                blockStack.pop_back();
            else
                diagnostics.push_back({{lineNumber, 0, lineNumber, static_cast<int>(line.length())},
                    "ENDIF without matching IF", std::nullopt, "comal", 1});
        }
        else if (firstWord == "ENDPROC") {
            if (!blockStack.empty() && blockStack.back().keyword == "PROC")
                blockStack.pop_back();
            else
                diagnostics.push_back({{lineNumber, 0, lineNumber, static_cast<int>(line.length())},
                    "ENDPROC without matching PROC", std::nullopt, "comal", 1});
        }
        else if (firstWord == "ENDFUNC") {
            if (!blockStack.empty() && blockStack.back().keyword == "FUNC")
                blockStack.pop_back();
            else
                diagnostics.push_back({{lineNumber, 0, lineNumber, static_cast<int>(line.length())},
                    "ENDFUNC without matching FUNC", std::nullopt, "comal", 1});
        }
        // "END" followed by block keyword (e.g. "END FOR", "END IF", "END PROC")
        else if (firstWord == "END" && sp != std::string::npos) {
            std::string rest = upper.substr(sp + 1);
            // Trim leading spaces
            size_t rs = rest.find_first_not_of(" \t");
            if (rs != std::string::npos) rest = rest.substr(rs);
            // Extract the block keyword from "END PROC name" -> "PROC"
            size_t re = rest.find_first_of(" \t");
            std::string blockKw = (re == std::string::npos) ? rest : rest.substr(0, re);

            if (blockKw == "FOR" || blockKw == "WHILE" || blockKw == "IF" ||
                blockKw == "PROC" || blockKw == "FUNC" || blockKw == "CASE" ||
                blockKw == "TRAP" || blockKw == "LOOP") {
                if (!blockStack.empty() && blockStack.back().keyword == blockKw)
                    blockStack.pop_back();
                else
                    diagnostics.push_back({{lineNumber, 0, lineNumber, static_cast<int>(line.length())},
                        "END " + blockKw + " without matching " + blockKw, std::nullopt, "comal", 1});
            }
        }

        // Validate DRAW commands using the graphics registry
        if (firstWord == "DRAW" && sp != std::string::npos) {
            std::string drawArgs = trimmed.substr(sp + 1);
            // Trim leading whitespace
            size_t ds = drawArgs.find_first_not_of(" \t");
            if (ds != std::string::npos) {
                drawArgs = drawArgs.substr(ds);
                // Remove surrounding quotes if it's a string argument (DRAW "...")
                if (!drawArgs.empty() && drawArgs.front() == '"') {
                    // String-based DRAW — skip validation (handled at runtime)
                } else {
                    // Parse with the graphics command registry
                    comal::graphics::ParsedCommand cmd;
                    comal::graphics::ParseError err;
                    if (!comal::graphics::parseLine(drawArgs, lineNumber + 1, graphics_registry_, cmd, err)) {
                        diagnostics.push_back({
                            {lineNumber, 0, lineNumber, static_cast<int>(line.length())},
                            "DRAW: " + err.message,
                            std::nullopt, "comal", 1
                        });
                    }
                }
            }
        }
        // SLEEP requires an argument
        if (firstWord == "SLEEP") {
            if (sp == std::string::npos) {
                diagnostics.push_back({{lineNumber, 0, lineNumber, static_cast<int>(line.length())},
                    "SLEEP requires a numeric argument (milliseconds)", std::nullopt, "comal", 1});
            } else {
                std::string args = trimmed.substr(sp + 1);
                if (args.find_first_not_of(" \t") == std::string::npos) {
                    diagnostics.push_back({{lineNumber, 0, lineNumber, static_cast<int>(line.length())},
                        "SLEEP requires a numeric argument (milliseconds)", std::nullopt, "comal", 1});
                }
            }
        }
        
        lineNumber++;
    }

    // Report unclosed blocks
    for (const auto& block : blockStack) {
        diagnostics.push_back({
            {block.line, 0, block.line, 0},
            "Unclosed " + block.keyword + " block",
            std::nullopt, "comal", 2  // Warning
        });
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
    
    auto docIt = documents_.find(uri);
    if (docIt == documents_.end()) {
        response.result = "[]";
        sendResponse(response);
        return;
    }
    
    const std::string& content = docIt->second;
    
    // Get the current line and prefix being typed
    std::istringstream iss(content);
    std::string currentLine;
    int currentLineNum = 0;
    std::string prefix;
    bool afterDraw = false;
    
    while (std::getline(iss, currentLine)) {
        if (!currentLine.empty() && currentLine.back() == '\r')
            currentLine.pop_back();
        
        if (currentLineNum == line) {
            if (character <= static_cast<int>(currentLine.length())) {
                std::string beforeCursor = currentLine.substr(0, character);
                
                size_t wordStart = beforeCursor.find_last_of(" \t()[]{},;=+-*/");
                if (wordStart == std::string::npos) {
                    prefix = beforeCursor;
                } else {
                    prefix = beforeCursor.substr(wordStart + 1);
                }

                // Check if we are after "DRAW " (context-aware completion)
                std::string trimmed = beforeCursor;
                // Strip leading line number
                size_t p = 0;
                while (p < trimmed.size() && (std::isdigit(static_cast<unsigned char>(trimmed[p])) || trimmed[p] == ' '))
                    ++p;
                std::string upper = trimmed.substr(p);
                std::transform(upper.begin(), upper.end(), upper.begin(),
                               [](unsigned char c) { return std::toupper(c); });
                // "DRAW circle" -> after removing prefix we check for "DRAW "
                // First, remove the prefix itself to see the statement context
                std::string context = upper.substr(0, upper.size() - prefix.size());
                // Trim trailing spaces from context
                while (!context.empty() && context.back() == ' ')
                    context.pop_back();
                if (context == "DRAW")
                    afterDraw = true;
            }
            break;
        }
        currentLineNum++;
    }
    
    // Build JSON response
    std::ostringstream oss;
    oss << "[";
    bool first = true;
    
    auto addItem = [&](const std::string& label, int kind, const std::string& detail) {
        if (!first) oss << ",";
        first = false;
        oss << R"({"label":")" << label << R"(","kind":)" << kind << R"(,"detail":")" << detail << R"("})";
    };

    // Convert prefix to upper for case-insensitive matching
    std::string upperPrefix = prefix;
    std::transform(upperPrefix.begin(), upperPrefix.end(), upperPrefix.begin(),
                   [](unsigned char c) { return std::toupper(c); });

    if (afterDraw) {
        // Offer DRAW sub-commands from the graphics registry
        std::string lowerPrefix = prefix;
        std::transform(lowerPrefix.begin(), lowerPrefix.end(), lowerPrefix.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        for (const auto& spec : graphics_registry_.all()) {
            std::string lowerName = spec.name;
            std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(),
                           [](unsigned char c) { return std::tolower(c); });
            if (lowerName.find(lowerPrefix) == 0) {
                std::string detail = spec.description;
                if (!spec.argDescription.empty())
                    detail = spec.argDescription + " — " + detail;
                addItem(spec.name, 3 /*Function*/, detail);
            }
        }
    } else {
        // Keywords (kind 14 = Keyword)
        for (const auto& keyword : completionKeywords()) {
            if (keyword.find(upperPrefix) == 0)
                addItem(keyword, 14 /*Keyword*/, "COMAL keyword");
        }
        
        // Symbols from the current document (kind 3 = Function / 2 = Method)
        auto symIt = symbol_tables_.find(uri);
        if (symIt != symbol_tables_.end()) {
            for (const auto& symbol : symIt->second) {
                // Case-insensitive prefix match
                std::string upperName = symbol.name;
                std::transform(upperName.begin(), upperName.end(), upperName.begin(),
                               [](unsigned char c) { return std::toupper(c); });
                if (upperName.find(upperPrefix) == 0) {
                    int kind = (symbol.kind == "function") ? 3 : 2;
                    addItem(symbol.name, kind, symbol.signature);
                }
            }
        }
    }
    
    oss << "]";
    response.result = oss.str();
    sendResponse(response);
}

void LspServer::handleDocumentSymbol(const LspRequest& request) {
    LspResponse response;
    response.id = request.id;

    std::string uri;
    int line, character;
    // Reuse the completion param parser — documentSymbol only needs the URI,
    // but the JSON shape is {"textDocument":{"uri":"..."}}, which our parser
    // can extract (line/character will be 0 if missing, but we don't need them).
    // A lightweight approach: just parse the URI directly.
    size_t uriPos = request.params.find("\"uri\"");
    if (uriPos == std::string::npos) {
        response.result = "[]";
        sendResponse(response);
        return;
    }
    uriPos = request.params.find("\"", uriPos + 6);
    size_t uriEnd = request.params.find("\"", uriPos + 1);
    if (uriPos == std::string::npos || uriEnd == std::string::npos) {
        response.result = "[]";
        sendResponse(response);
        return;
    }
    uri = request.params.substr(uriPos + 1, uriEnd - uriPos - 1);

    auto symIt = symbol_tables_.find(uri);
    if (symIt == symbol_tables_.end() || symIt->second.empty()) {
        response.result = "[]";
        sendResponse(response);
        return;
    }

    // DocumentSymbol[] — LSP SymbolInformation format
    std::ostringstream oss;
    oss << "[";
    bool first = true;
    for (const auto& sym : symIt->second) {
        if (!first) oss << ",";
        first = false;
        // SymbolKind: 12=Function, 6=Method (we use 12 for FUNC, 6 for PROC)
        int symbolKind = (sym.kind == "function") ? 12 : 6;
        oss << R"({"name":")" << sym.name
            << R"(","kind":)" << symbolKind
            << R"(,"range":{"start":{"line":)" << sym.line << R"(,"character":0},"end":{"line":)" << sym.line << R"(,"character":)" << static_cast<int>(sym.name.length() + 5) << R"(}})"
            << R"(,"selectionRange":{"start":{"line":)" << sym.line << R"(,"character":)" << sym.character << R"(},"end":{"line":)" << sym.line << R"(,"character":)" << (sym.character + static_cast<int>(sym.name.length())) << R"(}}})";
    }
    oss << "]";
    response.result = oss.str();
    sendResponse(response);
}

}  // namespace comal::lsp
