cmake_minimum_required(VERSION 3.16)
project(OpenCOMAL LANGUAGES CXX)

enable_testing()

add_subdirectory(libcomal-parser)

add_subdirectory(libcomal-runtime)

add_subdirectory(comal-lsp)
# add_subdirectory(comal-ide)

# ── Integration test: run all COMAL test programs ────────────────────
add_test(
  NAME comal_programs
  COMMAND bash ${CMAKE_SOURCE_DIR}/tests/run_tests.sh
          $<TARGET_FILE:comal-run>
)
set_tests_properties(comal_programs PROPERTIES TIMEOUT 300)
