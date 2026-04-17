# CMake generated Testfile for 
# Source directory: /home/pnand/Workspace/Scratch/OpenCOMAL
# Build directory: /home/pnand/Workspace/Scratch/OpenCOMAL/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(comal_programs "bash" "/home/pnand/Workspace/Scratch/OpenCOMAL/tests/run_tests.sh" "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-runtime/comal-run")
set_tests_properties(comal_programs PROPERTIES  TIMEOUT "300" _BACKTRACE_TRIPLES "/home/pnand/Workspace/Scratch/OpenCOMAL/CMakeLists.txt;20;add_test;/home/pnand/Workspace/Scratch/OpenCOMAL/CMakeLists.txt;0;")
add_test(keyword_docs_format "bash" "/home/pnand/Workspace/Scratch/OpenCOMAL/tests/validate_comal_keyword_docs.sh" "/home/pnand/Workspace/Scratch/OpenCOMAL/docs/comal-keyword-docs.tsv")
set_tests_properties(keyword_docs_format PROPERTIES  _BACKTRACE_TRIPLES "/home/pnand/Workspace/Scratch/OpenCOMAL/CMakeLists.txt;28;add_test;/home/pnand/Workspace/Scratch/OpenCOMAL/CMakeLists.txt;0;")
subdirs("libcomal-parser")
subdirs("libcomal-runtime")
subdirs("libcomal-graphics")
subdirs("libcomal-sound")
subdirs("comal-lsp")
subdirs("comal-ide")
