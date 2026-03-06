cmake_minimum_required(VERSION 3.16)
project(OpenCOMAL LANGUAGES CXX)

enable_testing()

add_subdirectory(libcomal-parser)

add_subdirectory(libcomal-runtime)

add_subdirectory(comal-lsp)
# add_subdirectory(comal-ide)
