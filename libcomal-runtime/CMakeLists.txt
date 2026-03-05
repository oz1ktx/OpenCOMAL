cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ── Sources ────────────────────────────────────────────────────────────────
set(RUNTIME_SOURCES
    src/value.cpp
    src/scope.cpp
    src/evaluator.cpp
    src/executor.cpp
    src/program.cpp
    src/builtins.cpp
    src/file_io.cpp
    src/runtime_error.cpp
)

# ── Library ────────────────────────────────────────────────────────────────
add_library(comal-runtime STATIC ${RUNTIME_SOURCES})

target_include_directories(comal-runtime
    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# The generated parser header (parser.tab.h) lives in the build directory
target_include_directories(comal-runtime
    PRIVATE ${CMAKE_BINARY_DIR}/libcomal-parser
)

target_link_libraries(comal-runtime
    PUBLIC comal-parser          # modern AST types + parser API
)

# ── CLI runner ─────────────────────────────────────────────────────────────
add_executable(comal-run tools/comal_run.cpp)
target_link_libraries(comal-run PRIVATE comal-runtime)
