cmake_minimum_required(VERSION 3.16)
project(comal_parser CXX)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

set(PARSER_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(LEGACY_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../legacy/src)

bison_target(comal_parser ${PARSER_SRC_DIR}/parser.y
    ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.cc
    DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.h
    COMPILE_FLAGS "--defines --verbose")

flex_target(comal_lexer ${PARSER_SRC_DIR}/lexer.l
    ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.cc)

add_flex_bison_dependency(comal_lexer comal_parser)

add_library(comal-parser
    ${BISON_comal_parser_OUTPUTS}
    ${FLEX_comal_lexer_OUTPUTS}
    ${PARSER_SRC_DIR}/lexer_support.cpp
    ${PARSER_SRC_DIR}/parser_support.cpp
    ${PARSER_SRC_DIR}/parser_api.cpp
    ${PARSER_SRC_DIR}/parser_deps.cpp
    ${PARSER_SRC_DIR}/ast_compat.cpp
)

add_executable(comal-parse-cli
    ${CMAKE_CURRENT_SOURCE_DIR}/tools/parse_cli.cpp
)

add_executable(comal-ast-demo
    ${CMAKE_CURRENT_SOURCE_DIR}/tools/ast_demo.cpp
)

target_link_libraries(comal-parse-cli PRIVATE comal-parser)
target_include_directories(comal-parse-cli PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(comal-ast-demo PRIVATE comal-parser)
target_include_directories(comal-ast-demo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(comal-parser
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${PARSER_SRC_DIR} ${CMAKE_CURRENT_BINARY_DIR}
)

target_compile_definitions(comal-parser PRIVATE FLEX)
