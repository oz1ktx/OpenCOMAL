/// @file test_commands.cpp
/// Tests for CommandRegistry and the line/program parsers.

#include "comal_graphics_commands.h"
#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>

using namespace comal::graphics;

static int tests_passed = 0;
static int tests_failed = 0;

#define TEST(name)                                                \
    do {                                                          \
        std::cout << "  " #name "... ";                           \
        std::cout.flush();                                        \
    } while (0)

#define PASS()                                                    \
    do {                                                          \
        std::cout << "OK\n";                                      \
        ++tests_passed;                                           \
    } while (0)

#define FAIL(msg)                                                 \
    do {                                                          \
        std::cout << "FAIL: " << (msg) << "\n";                   \
        ++tests_failed;                                           \
    } while (0)

#define ASSERT(cond, msg)                                         \
    do {                                                          \
        if (!(cond)) { FAIL(msg); return; }                       \
    } while (0)

// ── Registry tests ──────────────────────────────────────────────────────

static void test_registry_known_commands() {
    TEST(registry_known_commands);
    CommandRegistry reg;

    const char* names[] = {
        "line", "rect", "circle", "ellipse",
        "stroke", "fill", "noFill", "noStroke", "lineWidth",
        "background", "clear",
        "translate", "rotate", "scale"
    };

    for (auto* name : names) {
        auto* spec = reg.find(name);
        ASSERT(spec != nullptr, std::string("missing command: ") + name);
    }
    PASS();
}

static void test_registry_unknown_command() {
    TEST(registry_unknown_command);
    CommandRegistry reg;
    ASSERT(reg.find("explode") == nullptr, "should not find unknown command");
    PASS();
}

static void test_registry_all_count() {
    TEST(registry_all_count);
    CommandRegistry reg;
    ASSERT(reg.all().size() == 14, "expected 14 registered commands");
    PASS();
}

static void test_registry_arity() {
    TEST(registry_arity);
    CommandRegistry reg;

    auto* line = reg.find("line");
    ASSERT(line && line->minArgs == 4 && line->maxArgs == 4, "line should take 4 args");

    auto* circle = reg.find("circle");
    ASSERT(circle && circle->minArgs == 3 && circle->maxArgs == 3, "circle should take 3 args");

    auto* clear = reg.find("clear");
    ASSERT(clear && clear->minArgs == 0 && clear->maxArgs == 0, "clear takes 0 args");

    auto* scale = reg.find("scale");
    ASSERT(scale && scale->minArgs == 1 && scale->maxArgs == 2, "scale takes 1-2 args");

    auto* stroke = reg.find("stroke");
    ASSERT(stroke && stroke->minArgs == 3 && stroke->maxArgs == 4, "stroke takes 3-4 args");

    PASS();
}

// ── parseLine tests ─────────────────────────────────────────────────────

static void test_parse_simple_command() {
    TEST(parse_simple_command);
    CommandRegistry reg;
    ParsedCommand cmd;
    ParseError err;

    bool ok = parseLine("circle 100 200 50", 1, reg, cmd, err);
    ASSERT(ok, err.message);
    ASSERT(cmd.command == "circle", "command should be circle");
    ASSERT(cmd.groupPath.empty(), "no group path expected");
    ASSERT(cmd.args.size() == 3, "expected 3 args");
    ASSERT(cmd.args[0] == 100.0, "arg0");
    ASSERT(cmd.args[1] == 200.0, "arg1");
    ASSERT(cmd.args[2] == 50.0,  "arg2");
    PASS();
}

static void test_parse_grouped_command() {
    TEST(parse_grouped_command);
    CommandRegistry reg;
    ParsedCommand cmd;
    ParseError err;

    bool ok = parseLine("Spaceship.Engine.circle 10 20 5", 1, reg, cmd, err);
    ASSERT(ok, err.message);
    ASSERT(cmd.groupPath.size() == 2, "expected 2-level group path");
    ASSERT(cmd.groupPath[0] == "Spaceship", "group[0]");
    ASSERT(cmd.groupPath[1] == "Engine",    "group[1]");
    ASSERT(cmd.command == "circle", "command should be circle");
    ASSERT(cmd.args.size() == 3, "expected 3 args");
    PASS();
}

static void test_parse_no_args() {
    TEST(parse_no_args);
    CommandRegistry reg;
    ParsedCommand cmd;
    ParseError err;

    bool ok = parseLine("clear", 1, reg, cmd, err);
    ASSERT(ok, err.message);
    ASSERT(cmd.command == "clear", "command");
    ASSERT(cmd.args.empty(), "no args expected");
    PASS();
}

static void test_parse_extra_whitespace() {
    TEST(parse_extra_whitespace);
    CommandRegistry reg;
    ParsedCommand cmd;
    ParseError err;

    bool ok = parseLine("   line  10  20  30  40   ", 1, reg, cmd, err);
    ASSERT(ok, err.message);
    ASSERT(cmd.command == "line", "command");
    ASSERT(cmd.args.size() == 4, "expected 4 args");
    PASS();
}

static void test_parse_negative_args() {
    TEST(parse_negative_args);
    CommandRegistry reg;
    ParsedCommand cmd;
    ParseError err;

    bool ok = parseLine("translate -10 -20", 1, reg, cmd, err);
    ASSERT(ok, err.message);
    ASSERT(cmd.args.size() == 2, "expected 2 args");
    ASSERT(cmd.args[0] == -10.0, "negative x");
    ASSERT(cmd.args[1] == -20.0, "negative y");
    PASS();
}

static void test_parse_float_args() {
    TEST(parse_float_args);
    CommandRegistry reg;
    ParsedCommand cmd;
    ParseError err;

    bool ok = parseLine("scale 1.5 2.75", 1, reg, cmd, err);
    ASSERT(ok, err.message);
    ASSERT(std::abs(cmd.args[0] - 1.5) < 1e-9, "arg0");
    ASSERT(std::abs(cmd.args[1] - 2.75) < 1e-9, "arg1");
    PASS();
}

// ── Error cases ─────────────────────────────────────────────────────────

static void test_parse_unknown_command() {
    TEST(parse_unknown_command);
    CommandRegistry reg;
    ParsedCommand cmd;
    ParseError err;

    bool ok = parseLine("explode 1 2 3", 1, reg, cmd, err);
    ASSERT(!ok, "should fail for unknown command");
    ASSERT(err.lineNo == 1, "error line should be 1");
    PASS();
}

static void test_parse_too_few_args() {
    TEST(parse_too_few_args);
    CommandRegistry reg;
    ParsedCommand cmd;
    ParseError err;

    bool ok = parseLine("circle 100 200", 1, reg, cmd, err);
    ASSERT(!ok, "should fail with too few args");
    PASS();
}

static void test_parse_too_many_args() {
    TEST(parse_too_many_args);
    CommandRegistry reg;
    ParsedCommand cmd;
    ParseError err;

    bool ok = parseLine("circle 100 200 50 999", 1, reg, cmd, err);
    ASSERT(!ok, "should fail with too many args");
    PASS();
}

static void test_parse_non_numeric_arg() {
    TEST(parse_non_numeric_arg);
    CommandRegistry reg;
    ParsedCommand cmd;
    ParseError err;

    bool ok = parseLine("circle abc 200 50", 1, reg, cmd, err);
    ASSERT(!ok, "should fail with non-numeric arg");
    PASS();
}

static void test_parse_blank_line() {
    TEST(parse_blank_line);
    CommandRegistry reg;
    ParsedCommand cmd;
    ParseError err;

    bool ok = parseLine("", 1, reg, cmd, err);
    // Blank lines may either return false or be silently skipped;
    // either way, no crash.
    (void)ok;
    PASS();
}

static void test_parse_comment_line() {
    TEST(parse_comment_line);
    CommandRegistry reg;
    ParsedCommand cmd;
    ParseError err;

    bool ok = parseLine("# this is a comment", 1, reg, cmd, err);
    // Comment lines should be skipped (not an error).
    (void)ok;
    PASS();
}

static void test_parse_invalid_group_name() {
    TEST(parse_invalid_group_name);
    CommandRegistry reg;
    ParsedCommand cmd;
    ParseError err;

    bool ok = parseLine("123bad.circle 10 20 5", 1, reg, cmd, err);
    ASSERT(!ok, "should reject group starting with digit");
    PASS();
}

// ── parseProgram tests ──────────────────────────────────────────────────

static void test_parse_program_multi() {
    TEST(parse_program_multi);
    CommandRegistry reg;

    std::string source =
        "background 30 30 60\n"
        "circle 100 200 50\n"
        "Spaceship.rect 10 20 30 40\n";

    auto result = parseProgram(source, reg);
    ASSERT(result.errors.empty(), "no errors expected");
    ASSERT(result.commands.size() == 3, "expected 3 commands");

    ASSERT(result.commands[0].command == "background", "cmd0");
    ASSERT(result.commands[1].command == "circle",     "cmd1");
    ASSERT(result.commands[2].command == "rect",       "cmd2");
    ASSERT(result.commands[2].groupPath.size() == 1,   "cmd2 group");
    ASSERT(result.commands[2].groupPath[0] == "Spaceship", "cmd2 group name");
    PASS();
}

static void test_parse_program_mixed_errors() {
    TEST(parse_program_mixed_errors);
    CommandRegistry reg;

    std::string source =
        "circle 100 200 50\n"
        "bogus 1 2\n"
        "rect 10 20 30 40\n";

    auto result = parseProgram(source, reg);
    ASSERT(result.commands.size() == 2, "expected 2 valid commands");
    ASSERT(result.errors.size() == 1,   "expected 1 error");
    ASSERT(result.errors[0].lineNo == 2, "error on line 2");
    PASS();
}

static void test_parse_program_blank_and_comments() {
    TEST(parse_program_blank_and_comments);
    CommandRegistry reg;

    std::string source =
        "# header comment\n"
        "\n"
        "circle 100 200 50\n"
        "\n"
        "# another comment\n"
        "rect 10 20 30 40\n";

    auto result = parseProgram(source, reg);
    ASSERT(result.errors.empty(), "no errors expected");
    ASSERT(result.commands.size() == 2, "expected 2 commands (skipping blanks/comments)");
    PASS();
}

// ── main ────────────────────────────────────────────────────────────────

int main() {
    std::cout << "=== CommandRegistry tests ===\n";
    test_registry_known_commands();
    test_registry_unknown_command();
    test_registry_all_count();
    test_registry_arity();

    std::cout << "\n=== parseLine tests ===\n";
    test_parse_simple_command();
    test_parse_grouped_command();
    test_parse_no_args();
    test_parse_extra_whitespace();
    test_parse_negative_args();
    test_parse_float_args();

    std::cout << "\n=== parseLine error cases ===\n";
    test_parse_unknown_command();
    test_parse_too_few_args();
    test_parse_too_many_args();
    test_parse_non_numeric_arg();
    test_parse_blank_line();
    test_parse_comment_line();
    test_parse_invalid_group_name();

    std::cout << "\n=== parseProgram tests ===\n";
    test_parse_program_multi();
    test_parse_program_mixed_errors();
    test_parse_program_blank_and_comments();

    std::cout << "\n--- Results: " << tests_passed << " passed, "
              << tests_failed << " failed ---\n";

    return tests_failed > 0 ? 1 : 0;
}
