#include "comal_lsp_protocol.h"
#include <sstream>
#include <stdexcept>

namespace comal::lsp {

// Minimal JSON parsing for LSP protocol
// In production, would use nlohmann/json or similar

LspRequest parseRequest(const std::string& json) {
    LspRequest req;

    // Very basic parsing - extract key fields
    // This is a placeholder; proper JSON parsing should use a library

    // Extract jsonrpc
    size_t pos = json.find("\"jsonrpc\"");
    if (pos != std::string::npos) {
        pos = json.find("\"", pos + 10);
        size_t end = json.find("\"", pos + 1);
        req.jsonrpc = json.substr(pos + 1, end - pos - 1);
    }

    // Extract id (optional)
    pos = json.find("\"id\"");
    if (pos != std::string::npos) {
        pos = json.find(":", pos);
        size_t end = json.find_first_of(",}", pos);
        std::string idStr = json.substr(pos + 1, end - pos - 1);
        // Try to parse as integer
        try {
            req.id = std::stoi(idStr);
        } catch (...) {
            // Not an integer ID
        }
    }

    // Extract method
    pos = json.find("\"method\"");
    if (pos != std::string::npos) {
        pos = json.find("\"", pos + 9);
        size_t end = json.find("\"", pos + 1);
        req.method = json.substr(pos + 1, end - pos - 1);
    }

    // Extract params (raw)
    pos = json.find("\"params\"");
    if (pos != std::string::npos) {
        pos = json.find(":", pos);
        pos = json.find_first_not_of(" \t", pos + 1);
        if (json[pos] == '{' || json[pos] == '[') {
            // Find matching bracket
            int depth = 0;
            size_t end = pos;
            for (; end < json.length(); ++end) {
                if (json[end] == '{' || json[end] == '[') depth++;
                if (json[end] == '}' || json[end] == ']') {
                    depth--;
                    if (depth == 0) {
                        end++;
                        break;
                    }
                }
            }
            req.params = json.substr(pos, end - pos);
        }
    }

    return req;
}

std::string serializeResponse(const LspResponse& response) {
    std::ostringstream oss;
    oss << "{\"jsonrpc\":\"2.0\"";

    if (response.id) {
        oss << ",\"id\":" << response.id.value();
    }

    if (response.error) {
        oss << ",\"error\":{\"code\":-32603,\"message\":\"" << response.error.value() << "\"}";
    } else {
        oss << ",\"result\":" << response.result;
    }

    oss << "}";
    return oss.str();
}

std::string serializeNotification(const LspNotification& notification) {
    std::ostringstream oss;
    oss << "{\"jsonrpc\":\"2.0\",\"method\":\"" << notification.method << "\",\"params\":" << notification.params << "}";
    return oss.str();
}

}  // namespace comal::lsp
