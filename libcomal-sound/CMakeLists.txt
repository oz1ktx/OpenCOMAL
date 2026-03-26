cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ── Sources ────────────────────────────────────────────────────────────────
set(SOUND_SOURCES
    src/sound_commands.cpp
    src/sound_engine.cpp
)

# ── Library ────────────────────────────────────────────────────────────────
add_library(comal-sound STATIC ${SOUND_SOURCES})

target_include_directories(comal-sound
    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(Qt6 COMPONENTS Core QUIET)
find_package(Qt6 COMPONENTS Multimedia QUIET)

if (Qt6Core_FOUND)
    target_link_libraries(comal-sound PUBLIC Qt6::Core)
endif()

if (Qt6Multimedia_FOUND)
    target_compile_definitions(comal-sound PUBLIC USE_QTMULTIMEDIA)
    target_link_libraries(comal-sound PUBLIC Qt6::Multimedia)
else()
    message(STATUS "Qt6 Multimedia not found; building sound stub only.")
endif()

# ── Tests ──────────────────────────────────────────────────────────────────
add_executable(test_sound_commands tests/test_commands.cpp)
target_link_libraries(test_sound_commands PRIVATE comal-sound)
add_test(NAME sound_commands COMMAND test_sound_commands)

add_executable(test_sound_engine tests/test_engine.cpp)
target_link_libraries(test_sound_engine PRIVATE comal-sound)
add_test(NAME sound_engine COMMAND test_sound_engine)
