/// @file graphics_commands.cpp
/// Command registry and line parser implementation.

#include "comal_graphics_commands.h"

#include <sstream>
#include <algorithm>
#include <cctype>

namespace comal::graphics {

// ── CommandRegistry ─────────────────────────────────────────────────────

CommandRegistry::CommandRegistry() {
    specs_ = {
        // Shapes
        {"line",       4, 4, CommandKind::Shape,
         "Draw a line segment.", "x1 y1 x2 y2"},
        {"rect",       4, 4, CommandKind::Shape,
         "Draw a rectangle.", "x y width height"},
        {"circle",     3, 3, CommandKind::Shape,
         "Draw a circle.", "cx cy radius"},
        {"ellipse",    4, 4, CommandKind::Shape,
         "Draw an ellipse.", "x y width height"},
        {"pixel",      5, 6, CommandKind::Shape,
         "Set a single pixel color.", "x y r g b [a]"},

        // Styles
        {"stroke",     3, 4, CommandKind::Style,
         "Set the stroke (outline) color.", "r g b [a]"},
        {"fill",       3, 4, CommandKind::Style,
         "Set the fill color.", "r g b [a]"},
        {"noFill",     0, 0, CommandKind::Style,
         "Disable fill.", ""},
        {"noStroke",   0, 0, CommandKind::Style,
         "Disable stroke.", ""},
        {"lineWidth",  1, 1, CommandKind::Style,
         "Set the stroke line width.", "width"},

        // Canvas
        {"background", 3, 4, CommandKind::Canvas,
         "Set the canvas background color.", "r g b [a]"},
        {"clear",      0, 0, CommandKind::Canvas,
         "Clear the canvas.", ""},

        // Transforms
        {"translate",  2, 2, CommandKind::Transform,
         "Translate a group.", "dx dy"},
        {"rotate",     1, 1, CommandKind::Transform,
         "Rotate a group (degrees).", "angle"},
        {"scale",      1, 2, CommandKind::Transform,
         "Scale a group.", "sx [sy]"},

        // Text
        {"text",       2, 2, CommandKind::Shape,
         "Draw text at a position (uses current stroke color and fontSize).",
         "x y \"text\"", 1},
        {"fontSize",   1, 1, CommandKind::Style,
         "Set the font size for subsequent text commands.", "size"},
    };

    for (size_t i = 0; i < specs_.size(); ++i) {
        std::string key = specs_[i].name;
        std::transform(key.begin(), key.end(), key.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        index_[key] = i;
    }
}

const CommandSpec* CommandRegistry::find(const std::string& name) const {
    std::string key = name;
    std::transform(key.begin(), key.end(), key.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    auto it = index_.find(key);
    if (it == index_.end()) return nullptr;
    return &specs_[it->second];
}

// ── Tokenizer ───────────────────────────────────────────────────────────

struct Token {
    std::string value;
    bool isQuoted{false};
};

/// Split a line into tokens.  Quoted strings ("...") are produced as a single
/// token with isQuoted=true and their content (escape-processed) as value.
/// On unterminated quote, appends a sentinel token with value=":UNTERMINATED".
static std::vector<Token> tokenize(const std::string& line) {
    std::vector<Token> tokens;
    size_t i = 0;
    const size_t n = line.size();

    while (i < n) {
        // Skip whitespace
        if (std::isspace(static_cast<unsigned char>(line[i]))) { ++i; continue; }

        if (line[i] == '"') {
            ++i; // consume opening quote
            std::string val;
            bool closed = false;
            while (i < n) {
                if (line[i] == '"') {
                    ++i; // consume closing quote
                    closed = true;
                    break;
                }
                if (line[i] == '\\' && i + 1 < n) {
                    ++i;
                    if      (line[i] == '"')  val += '"';
                    else if (line[i] == '\\') val += '\\';
                    else { val += '\\'; val += line[i]; }
                } else {
                    val += line[i];
                }
                ++i;
            }
            if (!closed) {
                tokens.push_back(Token{":UNTERMINATED", false});
                return tokens;
            }
            tokens.push_back(Token{std::move(val), true});
        } else {
            // Unquoted token — read until whitespace
            std::string val;
            while (i < n && !std::isspace(static_cast<unsigned char>(line[i])))
                val += line[i++];
            tokens.push_back(Token{std::move(val), false});
        }
    }
    return tokens;
}

/// Split a qualified name "Group1.Group2.command" into group path + command.
static void splitQualifiedName(const std::string& qualified,
                               std::vector<std::string>& groupPath,
                               std::string& command) {
    groupPath.clear();
    size_t start = 0;
    size_t dot;
    while ((dot = qualified.find('.', start)) != std::string::npos) {
        groupPath.push_back(qualified.substr(start, dot - start));
        start = dot + 1;
    }
    command = qualified.substr(start);
}

static bool isIdentifier(const std::string& s) {
    if (s.empty()) return false;
    if (!std::isalpha(static_cast<unsigned char>(s[0])) && s[0] != '_')
        return false;
    for (size_t i = 1; i < s.size(); ++i) {
        char c = s[i];
        if (!std::isalnum(static_cast<unsigned char>(c)) && c != '_')
            return false;
    }
    return true;
}

// ── parseLine ───────────────────────────────────────────────────────────

bool parseLine(const std::string& line, int lineNo,
               const CommandRegistry& registry,
               ParsedCommand& out, ParseError& error) {
    out = {};
    out.lineNo = lineNo;

    // Strip leading/trailing whitespace
    auto trimmed = line;
    while (!trimmed.empty() && std::isspace(static_cast<unsigned char>(trimmed.front())))
        trimmed.erase(trimmed.begin());
    while (!trimmed.empty() && std::isspace(static_cast<unsigned char>(trimmed.back())))
        trimmed.pop_back();

    // Skip blank lines and comments
    if (trimmed.empty() || trimmed[0] == '#')
        return true;  // no error, but out.command is empty — caller checks

    auto tokens = tokenize(trimmed);
    if (tokens.empty())
        return true;

    // Check for unterminated-quote sentinel
    for (const auto& tok : tokens) {
        if (tok.value == ":UNTERMINATED" && !tok.isQuoted) {
            error = {lineNo, "Unterminated quoted string"};
            return false;
        }
    }

    // First token: qualified command name (quoted or unquoted)
    splitQualifiedName(tokens[0].value, out.groupPath, out.command);

    // Validate group names
    for (const auto& g : out.groupPath) {
        if (!isIdentifier(g)) {
            error = {lineNo, "Invalid group name: '" + g + "'"};
            return false;
        }
    }

    // Validate command name
    if (!isIdentifier(out.command)) {
        error = {lineNo, "Invalid command name: '" + out.command + "'"};
        return false;
    }

    // Look up command (case-insensitive)
    const CommandSpec* spec = registry.find(out.command);
    if (!spec) {
        error = {lineNo, "Unknown command: '" + out.command + "'"};
        return false;
    }
    // Canonicalize: use the registered name for execution dispatch
    out.command = spec->name;

    // Parse remaining tokens: unquoted → numeric arg, quoted → string arg
    for (size_t i = 1; i < tokens.size(); ++i) {
        const auto& tok = tokens[i];
        if (tok.isQuoted) {
            out.stringArgs.push_back(tok.value);
        } else {
            // Try to parse as a number
            try {
                size_t pos;
                double val = std::stod(tok.value, &pos);
                if (pos != tok.value.size()) {
                    error = {lineNo, "Expected number, got: '" + tok.value + "'"};
                    return false;
                }
                out.args.push_back(val);
            } catch (...) {
                error = {lineNo, "Expected number, got: '" + tok.value + "'"};
                return false;
            }
        }
    }

    // Validate numeric arity
    int nargs = static_cast<int>(out.args.size());
    if (nargs < spec->minArgs || nargs > spec->maxArgs) {
        std::string msg = "'" + out.command + "' expects ";
        if (spec->minArgs == spec->maxArgs)
            msg += std::to_string(spec->minArgs);
        else
            msg += std::to_string(spec->minArgs) + "-" + std::to_string(spec->maxArgs);
        msg += " numeric arg(s), got " + std::to_string(nargs);
        error = {lineNo, msg};
        return false;
    }

    // Validate string arity
    int nsargs = static_cast<int>(out.stringArgs.size());
    if (nsargs != spec->numStringArgs) {
        if (spec->numStringArgs == 0 && nsargs > 0) {
            error = {lineNo, "'" + out.command + "' does not accept string arguments"};
        } else {
            error = {lineNo, "'" + out.command + "' expects " +
                     std::to_string(spec->numStringArgs) + " string arg(s), got " +
                     std::to_string(nsargs)};
        }
        return false;
    }

    return true;
}

// ── parseProgram ────────────────────────────────────────────────────────

ParseResult parseProgram(const std::string& source,
                         const CommandRegistry& registry) {
    ParseResult result;
    std::istringstream iss(source);
    std::string line;
    int lineNo = 0;

    while (std::getline(iss, line)) {
        ++lineNo;
        ParsedCommand cmd;
        ParseError err;
        if (parseLine(line, lineNo, registry, cmd, err)) {
            if (!cmd.command.empty())
                result.commands.push_back(std::move(cmd));
        } else {
            result.errors.push_back(std::move(err));
        }
    }

    return result;
}

} // namespace comal::graphics
