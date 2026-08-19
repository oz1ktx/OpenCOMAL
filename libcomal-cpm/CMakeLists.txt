cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core)

add_library(comal-cpm STATIC
    src/comal_cpm_backend.cpp
    src/z80_com_loader.cpp
)

add_dependencies(comal-cpm sjasmplus)

target_include_directories(comal-cpm
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(comal-cpm PRIVATE
    OPENCOMAL_SJASMPLUS_PATH="$<TARGET_FILE:sjasmplus>"
)

target_link_libraries(comal-cpm
    PUBLIC Qt6::Core
    PUBLIC Z80
)
