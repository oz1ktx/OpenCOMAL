#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include <sstream>

namespace comal::lsp::test {

struct TestResult {
    std::string name;
    bool passed;
    std::string message;
};

class TestRunner {
public:
    static TestRunner& instance() {
        static TestRunner runner;
        return runner;
    }

    void addTest(const std::string& name, std::function<void()> testFunc) {
        try {
            testFunc();
            results_.push_back({name, true, ""});
        } catch (const std::exception& e) {
            results_.push_back({name, false, e.what()});
        } catch (const std::string& e) {
            results_.push_back({name, false, e});
        } catch (...) {
            results_.push_back({name, false, "Unknown exception"});
        }
    }

    int runTests() {
        int passed = 0, failed = 0;

        std::cout << "\n" << std::string(70, '=') << std::endl;
        std::cout << "LSP Server Test Suite" << std::endl;
        std::cout << std::string(70, '=') << std::endl;

        for (const auto& result : results_) {
            if (result.passed) {
                std::cout << "✓ " << result.name << std::endl;
                passed++;
            } else {
                std::cout << "✗ " << result.name << std::endl;
                if (!result.message.empty()) {
                    std::cout << "  → " << result.message << std::endl;
                }
                failed++;
            }
        }

        std::cout << std::string(70, '=') << std::endl;
        std::cout << "Results: " << passed << " passed, " << failed << " failed out of "
                  << (passed + failed) << " tests" << std::endl;
        std::cout << std::string(70, '=') << std::endl;

        return failed == 0 ? 0 : 1;
    }

private:
    std::vector<TestResult> results_;
};

// Test assertion helpers
inline void ASSERT_EQUAL(const std::string& actual, const std::string& expected,
                         const std::string& message = "") {
    if (actual != expected) {
        std::string err = "Expected: [" + expected + "]\n  Got: [" + actual + "]";
        if (!message.empty()) err += "\n  " + message;
        throw err;
    }
}

inline void ASSERT_TRUE(bool condition, const std::string& message = "") {
    if (!condition) {
        throw message.empty() ? std::string("Assertion failed") : message;
    }
}

inline void ASSERT_FALSE(bool condition, const std::string& message = "") {
    if (condition) {
        throw message.empty() ? std::string("Assertion failed") : message;
    }
}

inline void ASSERT_CONTAINS(const std::string& text, const std::string& substring,
                            const std::string& message = "") {
    if (text.find(substring) == std::string::npos) {
        std::string err = "Text does not contain substring: [" + substring + "]\n  Text: [" + text + "]";
        if (!message.empty()) err += "\n  " + message;
        throw err;
    }
}

} // namespace comal::lsp::test

// Simple test registration - tests must call addTest() explicitly in main()
// Example usage:
//   TEST_FUNC(my_test_name) {
//       ASSERT_TRUE(condition);
//   }
//   
//   int main() {
//       addTest("my_test_name", my_test_name);
//       return TestRunner::instance().runTests();
//   }
#define TEST_FUNC(name) void name()
