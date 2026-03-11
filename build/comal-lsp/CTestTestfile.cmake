# CMake generated Testfile for 
# Source directory: /home/peter/Workspace/OpenCOMAL/comal-lsp
# Build directory: /home/peter/Workspace/OpenCOMAL/build/comal-lsp
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(lsp_protocol "/home/peter/Workspace/OpenCOMAL/build/comal-lsp/test_lsp_protocol")
set_tests_properties(lsp_protocol PROPERTIES  _BACKTRACE_TRIPLES "/home/peter/Workspace/OpenCOMAL/comal-lsp/CMakeLists.txt;50;add_test;/home/peter/Workspace/OpenCOMAL/comal-lsp/CMakeLists.txt;0;")
add_test(lsp_server "/home/peter/Workspace/OpenCOMAL/build/comal-lsp/test_lsp_server")
set_tests_properties(lsp_server PROPERTIES  _BACKTRACE_TRIPLES "/home/peter/Workspace/OpenCOMAL/comal-lsp/CMakeLists.txt;59;add_test;/home/peter/Workspace/OpenCOMAL/comal-lsp/CMakeLists.txt;0;")
add_test(lsp_integration "/home/peter/Workspace/OpenCOMAL/build/comal-lsp/test_integration")
set_tests_properties(lsp_integration PROPERTIES  _BACKTRACE_TRIPLES "/home/peter/Workspace/OpenCOMAL/comal-lsp/CMakeLists.txt;68;add_test;/home/peter/Workspace/OpenCOMAL/comal-lsp/CMakeLists.txt;0;")
