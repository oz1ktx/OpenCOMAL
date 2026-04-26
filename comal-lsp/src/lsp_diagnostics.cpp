#include "comal_lsp_diagnostics.h"

#include "comal_parser_api.h"

#include <algorithm>
#include <cctype>
#include <memory>
#include <sstream>
#include <variant>

namespace comal::lsp {

namespace {

struct StatementParseResult {
    bool parsed{false};
    comal::StatementType command{comal::StatementType::Empty};
    bool inlineBody{false};
};

// Helper: make DRAW args suitable for static validation.
// The graphics parser expects numeric literals, but COMAL DRAW accepts
// expressions/variables. Replace non-numeric unquoted arg tokens after the
// command token with numeric placeholders so we can still validate command
// names and arity without false positives.
std::string normalizeDrawArgsForDiagnostics(const std::string& drawArgs) {
    struct Tok {
        std::string value;
        bool quoted{false};
    };

    auto tokenizeWithQuotes = [](const std::string& s) {
        std::vector<Tok> toks;
        size_t i = 0;
        while (i < s.size()) {
            if (std::isspace(static_cast<unsigned char>(s[i]))) {
                ++i;
                continue;
            }
            if (s[i] == '"') {
                ++i;
                std::string val;
                while (i < s.size()) {
                    if (s[i] == '"') {
                        ++i;
                        break;
                    }
                    if (s[i] == '\\' && i + 1 < s.size()) {
                        ++i;
                        val += s[i++];
                        continue;
                    }
                    val += s[i++];
                }
                toks.push_back({std::move(val), true});
            } else {
                std::string val;
                while (i < s.size() && !std::isspace(static_cast<unsigned char>(s[i]))) {
                    val += s[i++];
                }
                toks.push_back({std::move(val), false});
            }
        }
        return toks;
    };

    auto isNumericLiteral = [](const std::string& s) {
        if (s.empty()) {
            return false;
        }
        try {
            size_t pos = 0;
            (void)std::stod(s, &pos);
            return pos == s.size();
        } catch (...) {
            return false;
        }
    };

    auto escapeForQuotes = [](const std::string& s) {
        std::string out;
        out.reserve(s.size());
        for (char c : s) {
            if (c == '\\' || c == '"') {
                out.push_back('\\');
            }
            out.push_back(c);
        }
        return out;
    };

    auto toks = tokenizeWithQuotes(drawArgs);
    if (toks.empty()) {
        return drawArgs;
    }

    for (size_t i = 1; i < toks.size(); ++i) {
        if (toks[i].quoted) {
            continue;
        }
        if (!isNumericLiteral(toks[i].value)) {
            toks[i].value = "0";
        }
    }

    std::string normalized;
    for (size_t i = 0; i < toks.size(); ++i) {
        if (i > 0) {
            normalized += ' ';
        }
        if (toks[i].quoted) {
            normalized += '"' + escapeForQuotes(toks[i].value) + '"';
        } else {
            normalized += toks[i].value;
        }
    }
    return normalized;
}

StatementParseResult parseLineWithParserForDiagnostics(const std::string& sourceLine) {
    StatementParseResult info;

    char errbuf[256] = {0};
    int errpos = 0;

    std::unique_ptr<comal::ComalLine> parsed(
        comal::comal_parse_line_modern(sourceLine.c_str(), errbuf, sizeof(errbuf), &errpos));
    if (!parsed) {
        ::comal_parser_reset();
        return info;
    }

    info.parsed = true;
    info.command = parsed->command();

    switch (info.command) {
        case comal::StatementType::For:
            info.inlineBody = parsed->asFor().stat != nullptr;
            break;
        case comal::StatementType::If:
        case comal::StatementType::While:
        case comal::StatementType::Elif:
            info.inlineBody = parsed->asIfWhile().stat != nullptr;
            break;
        case comal::StatementType::Repeat:
            if (std::holds_alternative<comal::IfWhileRec>(parsed->contents())) {
                info.inlineBody = std::get<comal::IfWhileRec>(parsed->contents()).stat != nullptr;
            }
            break;
        default:
            break;
    }

    ::comal_parser_reset();
    return info;
}

struct Block {
    std::string keyword;
    int line;
};

struct NormalizedLine {
    std::string raw;
    std::string trimmed;
    std::string upper;
    std::string firstWord;
    size_t splitPos{std::string::npos};
};

void pushDiagnostic(std::vector<Diagnostic>& diagnostics,
                    int lineNumber,
                    int endCharacter,
                    const std::string& message,
                    int severity = 1) {
    diagnostics.push_back({
        {lineNumber, 0, lineNumber, endCharacter},
        message,
        std::nullopt, "comal", severity
    });
}

void popOrReportBlockMismatch(std::vector<Block>& blockStack,
                              std::vector<Diagnostic>& diagnostics,
                              int lineNumber,
                              int lineLength,
                              const std::string& expected,
                              const std::string& closerText) {
    if (!blockStack.empty() && blockStack.back().keyword == expected) {
        blockStack.pop_back();
    } else {
        pushDiagnostic(
            diagnostics,
            lineNumber,
            lineLength,
            closerText + " without matching " + expected,
            1);
    }
}

NormalizedLine normalizeLineForDiagnostics(const std::string& rawLine) {
    NormalizedLine normalized;
    normalized.raw = rawLine;

    if (!normalized.raw.empty() && normalized.raw.back() == '\r') {
        normalized.raw.pop_back();
    }

    normalized.trimmed = normalized.raw;
    size_t p = 0;
    while (p < normalized.trimmed.size() &&
           (std::isdigit(static_cast<unsigned char>(normalized.trimmed[p])) || normalized.trimmed[p] == ' ')) {
        ++p;
    }
    normalized.trimmed = normalized.trimmed.substr(p);
    while (!normalized.trimmed.empty() && std::isspace(static_cast<unsigned char>(normalized.trimmed.back()))) {
        normalized.trimmed.pop_back();
    }

    normalized.upper = normalized.trimmed;
    std::transform(normalized.upper.begin(), normalized.upper.end(), normalized.upper.begin(),
                   [](unsigned char c) { return std::toupper(c); });

    normalized.splitPos = normalized.upper.find_first_of(" \t");
    normalized.firstWord = (normalized.splitPos == std::string::npos)
                              ? normalized.upper
                              : normalized.upper.substr(0, normalized.splitPos);
    return normalized;
}

void runQuoteDiagnostics(const NormalizedLine& normalized,
                         int lineNumber,
                         std::vector<Diagnostic>& diagnostics) {
    int quoteCount = 0;
    for (char c : normalized.raw) {
        if (c == '"') {
            quoteCount++;
        }
    }
    if (quoteCount % 2 != 0) {
        pushDiagnostic(diagnostics,
                       lineNumber,
                       static_cast<int>(normalized.raw.length()),
                       "Unmatched quote in string literal",
                       1);
    }
}

void runParserBlockPass(const NormalizedLine& normalized,
                        const StatementParseResult& parsedLine,
                        int lineNumber,
                        std::vector<Block>& blockStack,
                        std::vector<Diagnostic>& diagnostics) {
    if (!parsedLine.parsed) {
        return;
    }

    switch (parsedLine.command) {
        case comal::StatementType::For:
            if (!parsedLine.inlineBody) blockStack.push_back({"FOR", lineNumber});
            break;
        case comal::StatementType::While:
            if (!parsedLine.inlineBody) blockStack.push_back({"WHILE", lineNumber});
            break;
        case comal::StatementType::Repeat:
            if (!parsedLine.inlineBody) blockStack.push_back({"REPEAT", lineNumber});
            break;
        case comal::StatementType::Loop:
            blockStack.push_back({"LOOP", lineNumber});
            break;
        case comal::StatementType::Case:
            blockStack.push_back({"CASE", lineNumber});
            break;
        case comal::StatementType::Trap:
            blockStack.push_back({"TRAP", lineNumber});
            break;
        case comal::StatementType::If:
            if (!parsedLine.inlineBody) blockStack.push_back({"IF", lineNumber});
            break;
        case comal::StatementType::Proc:
            blockStack.push_back({"PROC", lineNumber});
            break;
        case comal::StatementType::Func:
            blockStack.push_back({"FUNC", lineNumber});
            break;
        case comal::StatementType::EndFor:
            popOrReportBlockMismatch(blockStack,
                                     diagnostics,
                                     lineNumber,
                                     static_cast<int>(normalized.raw.length()),
                                     "FOR",
                                     normalized.firstWord == "NEXT" ? "NEXT" : "ENDFOR");
            break;
        case comal::StatementType::EndWhile:
            popOrReportBlockMismatch(blockStack,
                                     diagnostics,
                                     lineNumber,
                                     static_cast<int>(normalized.raw.length()),
                                     "WHILE",
                                     "ENDWHILE");
            break;
        case comal::StatementType::Until:
            popOrReportBlockMismatch(blockStack,
                                     diagnostics,
                                     lineNumber,
                                     static_cast<int>(normalized.raw.length()),
                                     "REPEAT",
                                     "UNTIL");
            break;
        case comal::StatementType::EndLoop:
            popOrReportBlockMismatch(blockStack,
                                     diagnostics,
                                     lineNumber,
                                     static_cast<int>(normalized.raw.length()),
                                     "LOOP",
                                     "ENDLOOP");
            break;
        case comal::StatementType::EndCase:
            popOrReportBlockMismatch(blockStack,
                                     diagnostics,
                                     lineNumber,
                                     static_cast<int>(normalized.raw.length()),
                                     "CASE",
                                     "ENDCASE");
            break;
        case comal::StatementType::EndTrap:
            popOrReportBlockMismatch(blockStack,
                                     diagnostics,
                                     lineNumber,
                                     static_cast<int>(normalized.raw.length()),
                                     "TRAP",
                                     "ENDTRAP");
            break;
        case comal::StatementType::EndIf:
            popOrReportBlockMismatch(blockStack,
                                     diagnostics,
                                     lineNumber,
                                     static_cast<int>(normalized.raw.length()),
                                     "IF",
                                     "ENDIF");
            break;
        case comal::StatementType::EndProc:
            popOrReportBlockMismatch(blockStack,
                                     diagnostics,
                                     lineNumber,
                                     static_cast<int>(normalized.raw.length()),
                                     "PROC",
                                     "ENDPROC");
            break;
        case comal::StatementType::EndFunc:
            popOrReportBlockMismatch(blockStack,
                                     diagnostics,
                                     lineNumber,
                                     static_cast<int>(normalized.raw.length()),
                                     "FUNC",
                                     "ENDFUNC");
            break;
        default:
            break;
    }
}

bool isLikelyBlockIf(const NormalizedLine& normalized) {
    const size_t thenPos = normalized.upper.find("THEN");
    bool isBlockIf = (thenPos == std::string::npos);
    if (!isBlockIf) {
        std::string tail = normalized.upper.substr(thenPos + 4);
        const size_t firstNonWs = tail.find_first_not_of(" \t");
        if (firstNonWs == std::string::npos) {
            isBlockIf = true;
        } else {
            tail = tail.substr(firstNonWs);
            if (tail.rfind("REM", 0) == 0 || tail[0] == '\'') {
                isBlockIf = true;
            }
        }
    }
    return isBlockIf;
}

void runFallbackBlockPass(const NormalizedLine& normalized,
                          int lineNumber,
                          std::vector<Block>& blockStack,
                          std::vector<Diagnostic>& diagnostics) {
    if (normalized.firstWord == "FOR") blockStack.push_back({"FOR", lineNumber});
    else if (normalized.firstWord == "WHILE") blockStack.push_back({"WHILE", lineNumber});
    else if (normalized.firstWord == "REPEAT") blockStack.push_back({"REPEAT", lineNumber});
    else if (normalized.firstWord == "LOOP") blockStack.push_back({"LOOP", lineNumber});
    else if (normalized.firstWord == "CASE") blockStack.push_back({"CASE", lineNumber});
    else if (normalized.firstWord == "TRAP") blockStack.push_back({"TRAP", lineNumber});
    else if (normalized.firstWord == "IF") {
        if (isLikelyBlockIf(normalized)) {
            blockStack.push_back({"IF", lineNumber});
        }
    } else if (normalized.firstWord == "PROC") {
        blockStack.push_back({"PROC", lineNumber});
    } else if (normalized.firstWord == "FUNC") {
        blockStack.push_back({"FUNC", lineNumber});
    } else if (normalized.firstWord == "NEXT" || normalized.firstWord == "ENDFOR") {
        popOrReportBlockMismatch(blockStack,
                                 diagnostics,
                                 lineNumber,
                                 static_cast<int>(normalized.raw.length()),
                                 "FOR",
                                 normalized.firstWord);
    } else if (normalized.firstWord == "ENDWHILE") {
        popOrReportBlockMismatch(blockStack,
                                 diagnostics,
                                 lineNumber,
                                 static_cast<int>(normalized.raw.length()),
                                 "WHILE",
                                 "ENDWHILE");
    } else if (normalized.firstWord == "UNTIL") {
        popOrReportBlockMismatch(blockStack,
                                 diagnostics,
                                 lineNumber,
                                 static_cast<int>(normalized.raw.length()),
                                 "REPEAT",
                                 "UNTIL");
    } else if (normalized.firstWord == "ENDLOOP") {
        popOrReportBlockMismatch(blockStack,
                                 diagnostics,
                                 lineNumber,
                                 static_cast<int>(normalized.raw.length()),
                                 "LOOP",
                                 "ENDLOOP");
    } else if (normalized.firstWord == "ENDCASE") {
        popOrReportBlockMismatch(blockStack,
                                 diagnostics,
                                 lineNumber,
                                 static_cast<int>(normalized.raw.length()),
                                 "CASE",
                                 "ENDCASE");
    } else if (normalized.firstWord == "ENDTRAP") {
        popOrReportBlockMismatch(blockStack,
                                 diagnostics,
                                 lineNumber,
                                 static_cast<int>(normalized.raw.length()),
                                 "TRAP",
                                 "ENDTRAP");
    } else if (normalized.firstWord == "ENDIF") {
        popOrReportBlockMismatch(blockStack,
                                 diagnostics,
                                 lineNumber,
                                 static_cast<int>(normalized.raw.length()),
                                 "IF",
                                 "ENDIF");
    } else if (normalized.firstWord == "ENDPROC") {
        popOrReportBlockMismatch(blockStack,
                                 diagnostics,
                                 lineNumber,
                                 static_cast<int>(normalized.raw.length()),
                                 "PROC",
                                 "ENDPROC");
    } else if (normalized.firstWord == "ENDFUNC") {
        popOrReportBlockMismatch(blockStack,
                                 diagnostics,
                                 lineNumber,
                                 static_cast<int>(normalized.raw.length()),
                                 "FUNC",
                                 "ENDFUNC");
    } else if (normalized.firstWord == "END" && normalized.splitPos != std::string::npos) {
        std::string rest = normalized.upper.substr(normalized.splitPos + 1);
        size_t rs = rest.find_first_not_of(" \t");
        if (rs != std::string::npos) rest = rest.substr(rs);
        size_t re = rest.find_first_of(" \t");
        std::string blockKw = (re == std::string::npos) ? rest : rest.substr(0, re);

        if (blockKw == "FOR" || blockKw == "WHILE" || blockKw == "IF" ||
            blockKw == "PROC" || blockKw == "FUNC" || blockKw == "CASE" ||
            blockKw == "TRAP" || blockKw == "LOOP") {
            popOrReportBlockMismatch(blockStack,
                                     diagnostics,
                                     lineNumber,
                                     static_cast<int>(normalized.raw.length()),
                                     blockKw,
                                     "END " + blockKw);
        }
    }
}

void runDrawDiagnostics(const NormalizedLine& normalized,
                        int lineNumber,
                        const comal::graphics::CommandRegistry& graphicsRegistry,
                        std::vector<Diagnostic>& diagnostics) {
    if (normalized.firstWord != "DRAW" || normalized.splitPos == std::string::npos) {
        return;
    }

    std::string drawArgs = normalized.trimmed.substr(normalized.splitPos + 1);
    size_t ds = drawArgs.find_first_not_of(" \t");
    if (ds == std::string::npos) {
        return;
    }

    drawArgs = drawArgs.substr(ds);
    if (!drawArgs.empty() && drawArgs.front() == '"') {
        return;
    }

    std::replace(drawArgs.begin(), drawArgs.end(), ',', ' ');
    drawArgs = normalizeDrawArgsForDiagnostics(drawArgs);
    comal::graphics::ParsedCommand cmd;
    comal::graphics::ParseError err;
    if (!comal::graphics::parseLine(drawArgs, lineNumber + 1, graphicsRegistry, cmd, err)) {
        pushDiagnostic(diagnostics,
                       lineNumber,
                       static_cast<int>(normalized.raw.length()),
                       "DRAW: " + err.message,
                       1);
    }
}

void runSleepDiagnostics(const NormalizedLine& normalized,
                         int lineNumber,
                         std::vector<Diagnostic>& diagnostics) {
    if (normalized.firstWord != "SLEEP") {
        return;
    }

    if (normalized.splitPos == std::string::npos) {
        pushDiagnostic(diagnostics,
                       lineNumber,
                       static_cast<int>(normalized.raw.length()),
                       "SLEEP requires a numeric argument (milliseconds)",
                       1);
        return;
    }

    std::string args = normalized.trimmed.substr(normalized.splitPos + 1);
    if (args.find_first_not_of(" \t") == std::string::npos) {
        pushDiagnostic(diagnostics,
                       lineNumber,
                       static_cast<int>(normalized.raw.length()),
                       "SLEEP requires a numeric argument (milliseconds)",
                       1);
    }
}

void emitUnclosedBlockDiagnostics(const std::vector<Block>& blockStack,
                                  std::vector<Diagnostic>& diagnostics) {
    for (const auto& block : blockStack) {
        diagnostics.push_back({
            {block.line, 0, block.line, 0},
            "Unclosed " + block.keyword + " block",
            std::nullopt, "comal", 2
        });
    }
}

}  // namespace

std::vector<Diagnostic> computeDiagnostics(const std::string& text,
                                           const comal::graphics::CommandRegistry& graphicsRegistry) {
    std::vector<Diagnostic> diagnostics;

    std::istringstream iss(text);
    std::string rawLine;
    int lineNumber = 0;
    std::vector<Block> blockStack;

    while (std::getline(iss, rawLine)) {
        NormalizedLine normalized = normalizeLineForDiagnostics(rawLine);
        runQuoteDiagnostics(normalized, lineNumber, diagnostics);

        if (normalized.trimmed.empty()) {
            lineNumber++;
            continue;
        }

        const StatementParseResult parsedLine = parseLineWithParserForDiagnostics(normalized.trimmed);
        if (parsedLine.parsed) {
            runParserBlockPass(normalized, parsedLine, lineNumber, blockStack, diagnostics);
        } else {
            runFallbackBlockPass(normalized, lineNumber, blockStack, diagnostics);
        }

        runDrawDiagnostics(normalized, lineNumber, graphicsRegistry, diagnostics);
        runSleepDiagnostics(normalized, lineNumber, diagnostics);

        lineNumber++;
    }

    emitUnclosedBlockDiagnostics(blockStack, diagnostics);

    return diagnostics;
}

}  // namespace comal::lsp
