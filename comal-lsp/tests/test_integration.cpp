#include "comal_lsp_server.h"
#include "comal_lsp_protocol.h"
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

int main() {
    TestRunner &runner = TestRunner::instance();
    
    // Register integration tests
    runner.addTest("Document Tracking: Integration test", test_document_tracking_integration);
    runner.addTest("Diagnostics: Generation and validation", test_diagnostic_generation);
    
    return runner.runTests();
}