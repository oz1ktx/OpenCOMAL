#pragma once

#include <string>
#include <map>
#include <vector>
#include <optional>

namespace comal::lsp {

// ── Basic types ────────────────────────────────────────────────────────
struct Position {
    int line = 0;
    int character = 0;
};

struct Range {
    Position start;
    Position end;
};

struct Location {
    std::string uri;
    Range range;
};

// ── Diagnostic ────────────────────────────────────────────────────────
struct Diagnostic {
    Range range;
    std::string message;
    std::optional<int> code;
    std::string source = "comal";
    int severity = 1;  // 1=Error, 2=Warning, 3=Information, 4=Hint
};

// ── Completion ────────────────────────────────────────────────────────
struct CompletionItem {
    std::string label;
    std::string detail;
    std::string documentation;
    int kind = 1;  // 1=Text, 2=Method, 3=Function, 4=Constructor, etc.
};

// ── LSP Protocol Messages ──────────────────────────────────────────────
struct LspRequest {
    std::string jsonrpc = "2.0";
    std::optional<int> id;
    std::string method;
    std::string params;  // Raw JSON params
};

struct LspResponse {
    std::string jsonrpc = "2.0";
    std::optional<int> id;
    std::string result;  // Raw JSON result
    std::optional<std::string> error;
};

struct LspNotification {
    std::string jsonrpc = "2.0";
    std::string method;
    std::string params;  // Raw JSON params
};

// ── Parser functions ──────────────────────────────────────────────────
LspRequest parseRequest(const std::string& json);
std::string serializeResponse(const LspResponse& response);
std::string serializeNotification(const LspNotification& notification);

}  // namespace comal::lsp
