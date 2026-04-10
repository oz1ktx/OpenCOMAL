# OpenCOMAL project

OpenCOMAL is a nostalgia project for people who grew up with microcomputers, but it is also a fun way for kids (an everyone else) to learn about programming. You can learn structured programming, debugging, etc.

This project is a fork of OpenCOMAL from Darren Bane https://github.com/poldy/OpenCOMAL which was forked from Christian Pietsch https://github.com/pietsch/OpenCOMAL


## Status

This version of COMAL is built for Linux using the Qt6 GUI components. You get an IDE with all the usual features: An editor with syntax highlighting, a debug panel to watch variables and the stack, and breakpoints. You also get a graphical panel where the COMAL program can draw using simple commands.


### Missing features

The CURSOR command (placing text on a coordinate on the text screen) is not implemented.
Debugging does not support modifying variables.
The GUI could be prettier.
Menus are not all functional yet.


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
