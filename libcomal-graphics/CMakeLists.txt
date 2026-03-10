cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ── Sources ────────────────────────────────────────────────────────────────
set(GRAPHICS_SOURCES
    src/graphics_commands.cpp
    src/scene_model.cpp
)

# ── Library ────────────────────────────────────────────────────────────────
add_library(comal-graphics STATIC ${GRAPHICS_SOURCES})

target_include_directories(comal-graphics
    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# ── Tests ──────────────────────────────────────────────────────────────────
add_executable(test_graphics_commands tests/test_commands.cpp)
target_link_libraries(test_graphics_commands PRIVATE comal-graphics)
add_test(NAME graphics_commands COMMAND test_graphics_commands)

add_executable(test_scene_model tests/test_scene_model.cpp)
target_link_libraries(test_scene_model PRIVATE comal-graphics)
add_test(NAME scene_model COMMAND test_scene_model)
