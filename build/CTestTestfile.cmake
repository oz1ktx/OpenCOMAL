# CMake generated Testfile for 
# Source directory: /home/peter/Workspace/OpenCOMAL
# Build directory: /home/peter/Workspace/OpenCOMAL/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(comal_programs "bash" "/home/peter/Workspace/OpenCOMAL/tests/run_tests.sh" "/home/peter/Workspace/OpenCOMAL/build/libcomal-runtime/comal-run")
set_tests_properties(comal_programs PROPERTIES  TIMEOUT "300" _BACKTRACE_TRIPLES "/home/peter/Workspace/OpenCOMAL/CMakeLists.txt;16;add_test;/home/peter/Workspace/OpenCOMAL/CMakeLists.txt;0;")
subdirs("libcomal-parser")
subdirs("libcomal-runtime")
subdirs("libcomal-graphics")
subdirs("comal-lsp")
subdirs("comal-ide")
