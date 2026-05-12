# OpenCOMAL project

OpenCOMAL is a nostalgia project for people who grew up with microcomputers, but it is also a fun way for kids (an everyone else) to learn about programming. You can learn structured programming, debugging, etc.

This project is a fork of OpenCOMAL from Darren Bane https://github.com/poldy/OpenCOMAL which was forked from Christian Pietsch https://github.com/pietsch/OpenCOMAL


## Status

This is a modern C++20 reconstruction of OpenCOMAL, originally built for microcomputers. It features:

- **Qt6 IDE** with syntax highlighting, multi-tab editor, and integrated run/debug workflow
- **Full COMAL execution** with modern AST-based runtime, supporting numberless programs
- **Graphical output** via 13 DRAW commands (lines, circles, rectangles, text, color, fill, etc.)
- **Audio support** (TONE + PLAY with ABC notation subset)
- **Debug facilities** including breakpoints, variable inspection, call-stack tracing, and SPAWN-based concurrency
- **LSP integration** enabling real-time diagnostics and IDE features
- **Language Server Protocol** for VS Code, Kate, Vim, and other LSP-compatible editors

### Known Limitations

- **CURSOR command** — Text positioning at screen coordinates not implemented (PRINT and graphics commands available as alternatives)
- **Variable modification in debugger** — Read-only inspection of variables during breakpoints (planned enhancement)
- **Windows support** — Currently Linux/Unix only; Windows port requires Qt I/O abstraction work
- **Conditional breakpoints** — Basic breakpoint support only; conditional variants planned
- **Find/Replace** — Editor has syntax highlighting and navigation but not Find/Replace (future enhancement)


## Building

In order to build OpenCOMAL on Linux, do the following

Before building, you need to install the following

GCC 15, CMake 3.16+, cpack, Qt6, QScintilla for Qt6, libncurses-dev, libreadline-dev, qt6-base-dev, qt6-svg-dev, libqscintilla2-qt6-dev, qt6-qtmultimedia-dev, fluidsynth-dev

If you use Fedora, the packages are named -devel instead of -dev


```shell
# Clone this repo to your local workspace
git clone https://github.com/oz1ktx/OpenCOMAL.git
# make a build directory
cd OpenCOMAL
mkdir build
# build the code
cd build
cmake ..
make -j
# if you want to install OpenCOMAL or distribute it, make a package
cd ..
cmake -S . -B build -DCPACK_GENERATOR="DEB;RPM"
cmake --build build --target package
```
