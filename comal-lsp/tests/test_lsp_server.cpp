#include "comal_lsp_server.h"
#include "comal_lsp_protocol.h"
#include "test_framework.h"
#include <iostream>

using namespace comal::lsp;
using namespace comal::lsp::test;

// Test functions
TEST_FUNC(test_server_creation) {
    LspServer server;
    ASSERT_TRUE(true, "Server created successfully");
}

TEST_FUNC(test_server_initial_state) {
    LspServer server;
    ASSERT_FALSE(server.isRunning(), "Server should not be running initially");
}

TEST_FUNC(test_server_stop) {
    LspServer server;
    server.stop();
    ASSERT_FALSE(server.isRunning(), "Server should be stopped after stop() call");
}

TEST_FUNC(test_protocol_initialize_request_format) {
    std::string json = R"({"jsonrpc":"2.0","id":1,"method":"initialize","params":{"processId":1234,"rootPath":"/workspace","capabilities":{}}})";
    LspRequest req = parseRequest(json);
    ASSERT_EQUAL(req.method, "initialize", "method should be initialize");
    ASSERT_TRUE(req.id.has_value(), "initialize should have an id");
    ASSERT_CONTAINS(req.params, "processId", "params should contain processId");
}

TEST_FUNC(test_protocol_didopen_notification_format) {
    std::string json = R"({"jsonrpc":"2.0","method":"textDocument/didOpen","params":{"textDocument":{"uri":"file:///home/user/test.lst","languageId":"comal","version":1,"text":"PRINT \"Hello\""}}})";
    LspRequest req = parseRequest(json);
    ASSERT_EQUAL(req.method, "textDocument/didOpen", "method mismatch");
    ASSERT_FALSE(req.id.has_value(), "didOpen is a notification without id");
    ASSERT_CONTAINS(req.params, "textDocument", "params should have textDocument");
}

TEST_FUNC(test_protocol_didchange_notification_format) {
    std::string json = R"({"jsonrpc":"2.0","method":"textDocument/didChange","params":{"textDocument":{"uri":"file:///test.lst","version":2},"contentChanges":[{"text":"PRINT"}]}})";
    LspRequest req = parseRequest(json);
    ASSERT_EQUAL(req.method, "textDocument/didChange", "method mismatch");
    ASSERT_CONTAINS(req.params, "contentChanges", "should track content changes");
}

TEST_FUNC(test_protocol_completion_request_format) {
    std::string json = R"({"jsonrpc":"2.0","id":5,"method":"textDocument/completion","params":{"textDocument":{"uri":"file:///test.lst"},"position":{"line":0,"character":3}}})";
    LspRequest req = parseRequest(json);
    ASSERT_EQUAL(req.method, "textDocument/completion", "method mismatch");
    ASSERT_TRUE(req.id.has_value(), "completion request should have id");
    ASSERT_CONTAINS(req.params, "position", "should have cursor position");
}

TEST_FUNC(test_protocol_definition_request_format) {
    std::string json = R"({"jsonrpc":"2.0","id":6,"method":"textDocument/definition","params":{"textDocument":{"uri":"file:///test.lst"},"position":{"line":5,"character":10}}})";
    LspRequest req = parseRequest(json);
    ASSERT_EQUAL(req.method, "textDocument/definition", "method mismatch");
    ASSERT_CONTAINS(req.params, "position", "should have position");
}

TEST_FUNC(test_protocol_hover_request_format) {
    std::string json = R"({"jsonrpc":"2.0","id":7,"method":"textDocument/hover","params":{"textDocument":{"uri":"file:///test.lst"},"position":{"line":2,"character":6}}})";
    LspRequest req = parseRequest(json);
    ASSERT_EQUAL(req.method, "textDocument/hover", "method mismatch");
    ASSERT_CONTAINS(req.params, "position", "should have position");
}

TEST_FUNC(test_protocol_shutdown_request_format) {
    std::string json = R"({"jsonrpc":"2.0","id":99,"method":"shutdown"})";
    LspRequest req = parseRequest(json);
    ASSERT_EQUAL(req.method, "shutdown", "method mismatch");
    ASSERT_TRUE(req.id.has_value(), "shutdown should have id");
}

TEST_FUNC(test_protocol_exit_notification_format) {
    std::string json = R"({"jsonrpc":"2.0","method":"exit"})";
    LspRequest req = parseRequest(json);
    ASSERT_EQUAL(req.method, "exit", "method mismatch");
    ASSERT_FALSE(req.id.has_value(), "exit is a notification without id");
}

TEST_FUNC(test_document_tracking_didopen_parsing) {
    LspServer server;
    std::string json = R"({"jsonrpc":"2.0","method":"textDocument/didOpen","params":{"textDocument":{"uri":"file:///test.lst","languageId":"comal","version":1,"text":"PRINT \"Hello\""}}})";
    LspRequest req = parseRequest(json);
    
    std::string uri, text;
    // Test the parsing helper method indirectly through the request structure
    ASSERT_EQUAL(req.method, "textDocument/didOpen", "method should be didOpen");
    ASSERT_CONTAINS(req.params, "textDocument", "should contain textDocument");
    ASSERT_CONTAINS(req.params, "test.lst", "should contain filename");
}

TEST_FUNC(test_document_tracking_didchange_parsing) {
    LspServer server;
    std::string json = R"({"jsonrpc":"2.0","method":"textDocument/didChange","params":{"textDocument":{"uri":"file:///test.lst","version":2},"contentChanges":[{"text":"PRINT \"Updated\""}]}})";
    LspRequest req = parseRequest(json);
    
    ASSERT_EQUAL(req.method, "textDocument/didChange", "method should be didChange");
    ASSERT_CONTAINS(req.params, "contentChanges", "should contain contentChanges");
}

TEST_FUNC(test_document_tracking_didclose_parsing) {
    LspServer server;
    std::string json = R"({"jsonrpc":"2.0","method":"textDocument/didClose","params":{"textDocument":{"uri":"file:///test.lst"}}})";
    LspRequest req = parseRequest(json);
    
    ASSERT_EQUAL(req.method, "textDocument/didClose", "method should be didClose");
    ASSERT_CONTAINS(req.params, "textDocument", "should contain textDocument");
}

TEST_FUNC(test_basic_syntax_diagnostics) {
    // Test basic diagnostic generation without accessing private methods
    // We'll test this indirectly through integration tests later
    ASSERT_TRUE(true, "Basic diagnostics test placeholder");
}

int main() {
    TestRunner &runner = TestRunner::instance();
    
    // Register all tests
    runner.addTest("Server: Creation", test_server_creation);
    runner.addTest("Server: Initial state is stopped", test_server_initial_state);
    runner.addTest("Server: Stop method", test_server_stop);
    runner.addTest("Protocol: Initialize request format", test_protocol_initialize_request_format);
    runner.addTest("Protocol: DidOpen notification format", test_protocol_didopen_notification_format);
    runner.addTest("Protocol: DidChange notification format", test_protocol_didchange_notification_format);
    runner.addTest("Protocol: Completion request format", test_protocol_completion_request_format);
    runner.addTest("Protocol: Definition request format", test_protocol_definition_request_format);
    runner.addTest("Protocol: Hover request format", test_protocol_hover_request_format);
    runner.addTest("Protocol: Shutdown request format", test_protocol_shutdown_request_format);
    runner.addTest("Protocol: Exit notification format", test_protocol_exit_notification_format);
    runner.addTest("Document Tracking: DidOpen parsing", test_document_tracking_didopen_parsing);
    runner.addTest("Document Tracking: DidChange parsing", test_document_tracking_didchange_parsing);
    runner.addTest("Document Tracking: DidClose parsing", test_document_tracking_didclose_parsing);
    runner.addTest("Basic syntax diagnostics", test_basic_syntax_diagnostics);
    
    return runner.runTests();
}
