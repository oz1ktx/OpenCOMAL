#pragma once

/// @file comal_graphics_commands.h
/// Command registry and line parser for the graphics language.
///
/// Parses text lines of the form:
///   [Group1.Group2....] commandName arg1 arg2 ...
///
/// All arguments are numeric (double).  The group path is optional;
/// without it, commands target the root canvas.

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <stdexcept>

namespace comal::graphics {

// ── Parsed line ─────────────────────────────────────────────────────────

struct ParsedCommand {
    std::vector<std::string> groupPath;   // e.g. {"Spaceship", "Engine"}
    std::string command;                  // e.g. "circle"
    std::vector<double> args;             // numeric arguments
    std::vector<std::string> stringArgs;  // string arguments (e.g. text content)
    int lineNo{0};                        // source line number (1-based)
};

// ── Command specification ───────────────────────────────────────────────

enum class CommandKind {
    Shape,       // line, rect, circle, ellipse
    Style,       // stroke, fill, noFill, noStroke, lineWidth
    Canvas,      // background, clear
    Transform,   // translate, rotate, scale
};

struct CommandSpec {
    std::string name;
    int minArgs;                   // minimum numeric arguments
    int maxArgs;                   // maximum numeric arguments
    CommandKind kind;
    std::string description;       // One-line description (for hover)
    std::string argDescription;    // Argument synopsis (e.g. "x1 y1 x2 y2")
    int numStringArgs{0};          // number of required string arguments (0 for most commands)
};

// ── Parse errors ────────────────────────────────────────────────────────

struct ParseError {
    int lineNo;
    std::string message;
};

// ── Command registry ────────────────────────────────────────────────────

/// Registry of known graphics commands with their argument counts.
class CommandRegistry {
public:
    CommandRegistry();

    /// Look up a command by name.  Returns nullptr if unknown.
    const CommandSpec* find(const std::string& name) const;

    /// Get all registered commands (for help/completion).
    const std::vector<CommandSpec>& all() const { return specs_; }

private:
    std::vector<CommandSpec> specs_;
    std::unordered_map<std::string, size_t> index_;  // name → specs_ index
};

// ── Line parser ─────────────────────────────────────────────────────────

/// Parse a single text line into a ParsedCommand.
/// Returns true on success, false on error (fills `error`).
bool parseLine(const std::string& line, int lineNo,
               const CommandRegistry& registry,
               ParsedCommand& out, ParseError& error);

/// Parse multiple lines (convenience).  Returns commands and errors.
struct ParseResult {
    std::vector<ParsedCommand> commands;
    std::vector<ParseError> errors;
};

ParseResult parseProgram(const std::string& source,
                         const CommandRegistry& registry);

} // namespace comal::graphics
