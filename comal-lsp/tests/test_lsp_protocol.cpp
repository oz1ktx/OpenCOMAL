#include "comal_lsp_protocol.h"
#include "test_framework.h"
#include <iostream>

using namespace comal::lsp;
using namespace comal::lsp::test;

// Test functions
TEST_FUNC(test_parse_simple_initialize) {
    std::string json = R"({"jsonrpc":"2.0","id":1,"method":"initialize","params":{}})";
    LspRequest req = parseRequest(json);
    ASSERT_EQUAL(req.jsonrpc, "2.0", "jsonrpc mismatch");
    ASSERT_TRUE(req.id.has_value(), "id should be present");
    ASSERT_EQUAL(std::to_string(req.id.value()), "1", "id mismatch");
    ASSERT_EQUAL(req.method, "initialize", "method mismatch");
}

TEST_FUNC(test_parse_request_with_object_params) {
    std::string json = R"({"jsonrpc":"2.0","id":2,"method":"textDocument/didOpen","params":{"textDocument":{"uri":"file:///test.lst"}}})";
    LspRequest req = parseRequest(json);
    ASSERT_EQUAL(req.method, "textDocument/didOpen", "method mismatch");
    ASSERT_CONTAINS(req.params, "uri", "params should contain uri");
    ASSERT_CONTAINS(req.params, "test.lst", "params should contain filename");
}

TEST_FUNC(test_parse_request_without_id) {
    std::string json = R"({"jsonrpc":"2.0","method":"shutdown"})";
    LspRequest req = parseRequest(json);
    ASSERT_EQUAL(req.method, "shutdown", "method mismatch");
    ASSERT_FALSE(req.id.has_value(), "id should not be present for notifications");
}

TEST_FUNC(test_serialize_response_with_result) {
    LspResponse resp;
    resp.jsonrpc = "2.0";
    resp.id = 1;
    resp.result = R"({"capabilities":{"textDocumentSync":1}})";
    
    std::string json = serializeResponse(resp);
    ASSERT_CONTAINS(json, "\"jsonrpc\":\"2.0\"", "should contain jsonrpc");
    ASSERT_CONTAINS(json, "\"id\":1", "should contain id");
    ASSERT_CONTAINS(json, "textDocumentSync", "should contain result");
}

TEST_FUNC(test_serialize_response_with_error) {
    LspResponse resp;
    resp.jsonrpc = "2.0";
    resp.id = 99;
    resp.error = "Unknown method";
    
    std::string json = serializeResponse(resp);
    ASSERT_CONTAINS(json, "\"error\"", "should contain error field");
    ASSERT_CONTAINS(json, "Unknown method", "should contain error message");
}

TEST_FUNC(test_serialize_notification) {
    LspNotification notif;
    notif.method = "textDocument/publishDiagnostics";
    notif.params = R"({"uri":"file:///test.lst","diagnostics":[]})";
    
    std::string json = serializeNotification(notif);
    ASSERT_CONTAINS(json, "\"method\":\"textDocument/publishDiagnostics\"", "should contain method");
    ASSERT_CONTAINS(json, "publishDiagnostics", "should contain method name");
    ASSERT_CONTAINS(json, "diagnostics", "should contain params");
}

TEST_FUNC(test_parse_request_with_array_params) {
    std::string json = R"({"jsonrpc":"2.0","id":3,"method":"test","params":[1,2,3]})";
    LspRequest req = parseRequest(json);
    ASSERT_EQUAL(req.method, "test", "method mismatch");
    ASSERT_CONTAINS(req.params, "[1,2,3]", "params should contain array");
}

TEST_FUNC(test_parse_nested_json_structures) {
    std::string json = R"({"jsonrpc":"2.0","id":4,"method":"test","params":{"nested":{"deep":"value"}}})";
    LspRequest req = parseRequest(json);
    ASSERT_CONTAINS(req.params, "nested", "should preserve nested structure");
    ASSERT_CONTAINS(req.params, "deep", "should preserve deeply nested values");
}

int main() {
    TestRunner &runner = TestRunner::instance();
    
    // Register all tests
    runner.addTest("Protocol: Parse simple initialize request", test_parse_simple_initialize);
    runner.addTest("Protocol: Parse request with object params", test_parse_request_with_object_params);
    runner.addTest("Protocol: Parse request without id (notification)", test_parse_request_without_id);
    runner.addTest("Protocol: Serialize response with result", test_serialize_response_with_result);
    runner.addTest("Protocol: Serialize response with error", test_serialize_response_with_error);
    runner.addTest("Protocol: Serialize notification", test_serialize_notification);
    runner.addTest("Protocol: Parse request with array params", test_parse_request_with_array_params);
    runner.addTest("Protocol: Parse nested JSON structures", test_parse_nested_json_structures);
    
    return runner.runTests();
}
