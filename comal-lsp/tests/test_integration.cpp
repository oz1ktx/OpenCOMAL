#include "comal_lsp_server.h"
#include "comal_lsp_protocol.h"
#include "comal_graphics_commands.h"
#include "test_framework.h"
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>

using namespace comal::lsp;
using namespace comal::lsp::test;

// Integration test for document tracking
TEST_FUNC(test_document_tracking_integration) {
    // This test verifies that document tracking works end-to-end
    // We'll test the parsing functions directly since full LSP message handling
    // requires more complex setup with stdin/stdout redirection
    
    LspServer server;
    
    // Test didOpen parsing
    std::string didOpenParams = R"({"textDocument":{"uri":"file:///test.lst","languageId":"comal","version":1,"text":"PRINT Hello\n"}})";
    std::string uri, text;
    bool parsed = server.parseDocumentParams(didOpenParams, uri, text);
    ASSERT_TRUE(parsed, "Should parse didOpen params");
    ASSERT_EQUAL(uri, "file:///test.lst", "URI should match");
    ASSERT_EQUAL(text, "PRINT Hello\n", "Text should match");
    
    // Test didChange parsing
    std::string didChangeParams = R"({"textDocument":{"uri":"file:///test.lst","version":2},"contentChanges":[{"text":"PRINT Updated\n"}]})";
    parsed = server.parseDocumentChangeParams(didChangeParams, uri, text);
    ASSERT_TRUE(parsed, "Should parse didChange params");
    ASSERT_EQUAL(uri, "file:///test.lst", "URI should match");
    ASSERT_EQUAL(text, "PRINT Updated\n", "Updated text should match");
    
    // Test didClose parsing
    std::string didCloseParams = R"({"textDocument":{"uri":"file:///test.lst"}})";
    parsed = server.parseDocumentCloseParams(didCloseParams, uri);
    ASSERT_TRUE(parsed, "Should parse didClose params");
    ASSERT_EQUAL(uri, "file:///test.lst", "URI should match");
}

TEST_FUNC(test_diagnostic_generation) {
    LspServer server;
    
    // Test clean code (no diagnostics)
    std::string cleanCode = "PRINT \"Hello World\"\nEND\n";
    auto diagnostics = server.parseDocument(cleanCode);
    ASSERT_TRUE(diagnostics.empty(), "Clean code should have no diagnostics");
    
    // Test code with syntax error
    std::string errorCode = "PRINT \"Hello World\n";  // Missing closing quote
    diagnostics = server.parseDocument(errorCode);
    ASSERT_TRUE(diagnostics.size() > 0, "Code with syntax error should have diagnostics");
    
    // Check that the diagnostic has the right properties
    const auto& diag = diagnostics[0];
    ASSERT_CONTAINS(diag.message, "quote", "Error message should mention quotes");
    ASSERT_TRUE(diag.severity == 1, "Should be an error (severity 1)");
    ASSERT_EQUAL(diag.source, "comal", "Source should be 'comal'");
}

TEST_FUNC(test_symbol_table_building) {
    LspServer server;
    
    std::string testCode = R"(
PROC calculate_sum(a, b)
  RETURN a + b
END PROC calculate_sum

FUNC main()
  LOCAL result
  result := calculate_sum(5, 3)
  PRINT "Result: "; result
END FUNC main
)";
    
    server.buildSymbolTable("file:///test.lst", testCode);
    auto symbols = server.findSymbolsAtPosition("file:///test.lst", 0, 0);
    
    ASSERT_EQUAL(std::to_string(symbols.size()), "2", "Should find 2 symbols");
    ASSERT_EQUAL(symbols[0].name, "calculate_sum", "First symbol should be calculate_sum");
    ASSERT_EQUAL(symbols[0].kind, "procedure", "calculate_sum should be a procedure");
    ASSERT_EQUAL(symbols[1].name, "main", "Second symbol should be main");
    ASSERT_EQUAL(symbols[1].kind, "function", "main should be a function");
}

TEST_FUNC(test_definition_lookup) {
    LspServer server;
    
    std::string testCode = R"(
PROC test_proc()
  PRINT "Hello"
END PROC test_proc

PRINT "Calling: "
test_proc()
)";
    
    server.buildSymbolTable("file:///test.lst", testCode);
    
    // Test finding definition
    SymbolInfo* def = server.findSymbolDefinition("file:///test.lst", "test_proc");
    ASSERT_TRUE(def != nullptr, "Should find test_proc definition");
    ASSERT_EQUAL(def->name, "test_proc", "Definition name should match");
    ASSERT_EQUAL(std::to_string(def->line), "1", "Definition should be on line 1");
    
    // Test non-existent symbol
    def = server.findSymbolDefinition("file:///test.lst", "nonexistent");
    ASSERT_TRUE(def == nullptr, "Should not find nonexistent symbol");
}

TEST_FUNC(test_diagnostics_block_matching) {
    LspServer server;

    // Unclosed FOR
    std::string code1 = "FOR i := 1 TO 10\n  PRINT i\n";
    auto diags = server.parseDocument(code1);
    bool foundUnclosedFor = false;
    for (const auto& d : diags)
        if (d.message.find("Unclosed FOR") != std::string::npos)
            foundUnclosedFor = true;
    ASSERT_TRUE(foundUnclosedFor, "Should detect unclosed FOR block");

    // Properly closed FOR  
    std::string code2 = "FOR i := 1 TO 10\n  PRINT i\nNEXT i\n";
    diags = server.parseDocument(code2);
    bool anyBlockError = false;
    for (const auto& d : diags)
        if (d.message.find("Unclosed") != std::string::npos || d.message.find("without matching") != std::string::npos)
            anyBlockError = true;
    ASSERT_FALSE(anyBlockError, "Properly closed FOR should have no block errors");

    // NEXT without FOR
    std::string code3 = "PRINT \"hello\"\nNEXT i\n";
    diags = server.parseDocument(code3);
    bool foundOrphanNext = false;
    for (const auto& d : diags)
        if (d.message.find("NEXT without matching FOR") != std::string::npos)
            foundOrphanNext = true;
    ASSERT_TRUE(foundOrphanNext, "Should detect NEXT without matching FOR");

    // One-line block forms should not be treated as unclosed blocks
    std::string code4 =
        "IF 1 THEN PRINT \"ok\"\n"
        "FOR i := 1 TO 2 DO PRINT i\n"
        "WHILE 0 DO PRINT \"x\"\n";
    diags = server.parseDocument(code4);
    bool foundFalseUnclosed = false;
    for (const auto& d : diags)
        if (d.message.find("Unclosed") != std::string::npos || d.message.find("without matching") != std::string::npos)
            foundFalseUnclosed = true;
    ASSERT_FALSE(foundFalseUnclosed, "One-line IF/FOR/WHILE should not produce block matching errors");
}

TEST_FUNC(test_diagnostics_draw_validation) {
    LspServer server;

    // Valid DRAW command
    std::string code1 = "DRAW circle 100 200 50\n";
    auto diags = server.parseDocument(code1);
    bool anyDrawError = false;
    for (const auto& d : diags)
        if (d.message.find("DRAW:") != std::string::npos)
            anyDrawError = true;
    ASSERT_FALSE(anyDrawError, "Valid DRAW circle should have no errors");

    // Invalid DRAW command: wrong arg count
    std::string code2 = "DRAW circle 100\n";
    diags = server.parseDocument(code2);
    bool foundArgError = false;
    for (const auto& d : diags)
        if (d.message.find("DRAW:") != std::string::npos)
            foundArgError = true;
    ASSERT_TRUE(foundArgError, "DRAW circle with wrong arg count should produce error");

    // Unknown DRAW subcommand
    std::string code3 = "DRAW banana 1 2 3\n";
    diags = server.parseDocument(code3);
    bool foundUnknown = false;
    for (const auto& d : diags)
        if (d.message.find("Unknown command") != std::string::npos)
            foundUnknown = true;
    ASSERT_TRUE(foundUnknown, "DRAW unknown subcommand should produce error");

    // DRAW with variable args should be accepted by static diagnostics
    std::string code4 = "x:=100\ny:=200\nr:=30\nDRAW circle x y r\n";
    diags = server.parseDocument(code4);
    bool anyVarDrawError = false;
    for (const auto& d : diags)
        if (d.message.find("DRAW:") != std::string::npos)
            anyVarDrawError = true;
    ASSERT_FALSE(anyVarDrawError, "DRAW circle with variable args should have no DRAW errors");
}

TEST_FUNC(test_graphics_registry_in_server) {
    // Verify the LSP server's embedded graphics registry has the expected commands
    comal::graphics::CommandRegistry reg;
    const auto& all = reg.all();
    ASSERT_TRUE(all.size() >= 14, "Should have at least 14 graphics commands");

    // Check that descriptions are populated
    const auto* circle = reg.find("circle");
    ASSERT_TRUE(circle != nullptr, "Should find circle command");
    ASSERT_TRUE(!circle->description.empty(), "circle should have a description");
    ASSERT_EQUAL(circle->argDescription, "cx cy radius", "circle arg description");
}

int main() {
    TestRunner &runner = TestRunner::instance();
    
    // Register integration tests
    runner.addTest("Document Tracking: Integration test", test_document_tracking_integration);
    runner.addTest("Diagnostics: Generation and validation", test_diagnostic_generation);
    runner.addTest("Symbol Table: Building", test_symbol_table_building);
    runner.addTest("Definition: Lookup", test_definition_lookup);
    runner.addTest("Diagnostics: Block matching", test_diagnostics_block_matching);
    runner.addTest("Diagnostics: DRAW validation", test_diagnostics_draw_validation);
    runner.addTest("Graphics: Registry in server", test_graphics_registry_in_server);
    
    return runner.runTests();
}