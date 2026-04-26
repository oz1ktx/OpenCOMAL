cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ── Check for required dependencies ────────────────────────────────────────
find_package(nlohmann_json 3.2.0 QUIET)
if (NOT nlohmann_json_FOUND)
    message(STATUS "nlohmann_json not found, will use bundled or skip LSP server build")
    # For now, we proceed without nlohmann_json and use a minimal JSON parser
    # In production, add cmake fetch or package requirement
endif()

# ── Sources ────────────────────────────────────────────────────────────────
set(LSP_SOURCES
    src/lsp_server.cpp
    src/lsp_diagnostics.cpp
    src/lsp_protocol.cpp
)

# ── Library ────────────────────────────────────────────────────────────────
add_library(comal_lsp STATIC ${LSP_SOURCES})

target_include_directories(comal_lsp
    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(comal_lsp
    PUBLIC comal-parser comal-runtime comal-graphics
)

# Optional: nlohmann/json if available
if (nlohmann_json_FOUND)
    target_link_libraries(comal_lsp PUBLIC nlohmann_json::nlohmann_json)
    target_compile_definitions(comal_lsp PUBLIC HAVE_NLOHMANN_JSON)
endif()

# ── LSP Server CLI ─────────────────────────────────────────────────────────
add_executable(comal-lsp tools/comal_lsp.cpp)
target_link_libraries(comal-lsp PRIVATE comal_lsp)

# ── Testing ────────────────────────────────────────────────────────────────
# Protocol tests
add_executable(test_lsp_protocol tests/test_lsp_protocol.cpp src/lsp_protocol.cpp)
target_include_directories(test_lsp_protocol
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests
)
target_link_libraries(test_lsp_protocol PRIVATE comal_lsp)
add_test(NAME lsp_protocol COMMAND test_lsp_protocol)

# Server tests
add_executable(test_lsp_server tests/test_lsp_server.cpp src/lsp_protocol.cpp)
target_include_directories(test_lsp_server
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests
)
target_link_libraries(test_lsp_server PRIVATE comal_lsp)
add_test(NAME lsp_server COMMAND test_lsp_server)

# Integration tests
add_executable(test_integration tests/test_integration.cpp src/lsp_protocol.cpp)
target_include_directories(test_integration
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests
)
target_link_libraries(test_integration PRIVATE comal_lsp)
add_test(NAME lsp_integration COMMAND test_integration)