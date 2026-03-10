cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

# ── Qt6 modules ──────────────────────────────────────────────────────
#   Qt6::Widgets        — QMainWindow, QDockWidget, QMenuBar, QToolBar,
#                         QStatusBar, QTabWidget, QTreeView, QTextEdit,
#                         QLineEdit, QSplitter, QFileSystemModel, …
#   Qt6::PrintSupport   — required by QScintilla (even if we don't print)
#
# QScintilla has no CMake config; we link by library name.
# ─────────────────────────────────────────────────────────────────────

find_package(Qt6 REQUIRED COMPONENTS Widgets PrintSupport Svg)

# ── QScintilla (headers + library) ──────────────────────────────────
find_path(QSCINTILLA_INCLUDE_DIR
    NAMES Qsci/qsciscintilla.h
    HINTS ${Qt6Widgets_INCLUDE_DIRS}
    PATH_SUFFIXES qt6
)
find_library(QSCINTILLA_LIBRARY
    NAMES qscintilla2_qt6
)

if(NOT QSCINTILLA_INCLUDE_DIR OR NOT QSCINTILLA_LIBRARY)
    message(FATAL_ERROR
        "QScintilla for Qt6 not found.\n"
        "  Fedora/RHEL:  dnf install qscintilla-qt6-devel\n"
        "  Debian/Ubuntu: apt install libqscintilla2-qt6-dev")
endif()

message(STATUS "QScintilla include: ${QSCINTILLA_INCLUDE_DIR}")
message(STATUS "QScintilla library: ${QSCINTILLA_LIBRARY}")

# ── Sources ─────────────────────────────────────────────────────────
add_executable(comal-ide
    src/main.cpp
    src/main_window.cpp
    src/code_editor_panel.cpp
    src/direct_command_panel.cpp
    src/graphics_panel.cpp
    src/debug_panel.cpp
    src/file_browser_panel.cpp
    src/help_panel.cpp
    src/qt_io.cpp
    src/run_worker.cpp
    include/main_window.h
    include/code_editor_panel.h
    include/direct_command_panel.h
    include/graphics_panel.h
    include/debug_panel.h
    include/file_browser_panel.h
    include/help_panel.h
    include/qt_io.h
    include/run_worker.h
)

target_include_directories(comal-ide PRIVATE
    include
    ${QSCINTILLA_INCLUDE_DIR}
)

target_link_libraries(comal-ide PRIVATE
    Qt6::Widgets
    Qt6::PrintSupport
    Qt6::Svg
    ${QSCINTILLA_LIBRARY}
    comal-runtime
    comal-graphics
)
