cmake_minimum_required(VERSION 3.16)
project(OpenCOMAL LANGUAGES CXX)

enable_testing()

add_subdirectory(libcomal-parser)

add_subdirectory(libcomal-runtime)

add_subdirectory(libcomal-graphics)

add_subdirectory(comal-lsp)
add_subdirectory(comal-ide)

# ── Integration test: run all COMAL test programs ────────────────────
add_test(
  NAME comal_programs
  COMMAND bash ${CMAKE_SOURCE_DIR}/tests/run_tests.sh
          $<TARGET_FILE:comal-run>
)
set_tests_properties(comal_programs PROPERTIES TIMEOUT 300)

# Install built executables so CPack can produce DEB/RPM packages
install(TARGETS comal-run
  RUNTIME DESTINATION bin
)
install(TARGETS comal-lsp
  RUNTIME DESTINATION bin
)
install(TARGETS comal-ide
  RUNTIME DESTINATION bin
)
install(TARGETS comal-parse-cli comal-ast-demo
  RUNTIME DESTINATION bin
)

# Desktop integration: install .desktop and icon so packages create start-menu entries
install(FILES ${CMAKE_SOURCE_DIR}/packaging/desktop/comal-ide.desktop
  DESTINATION share/applications
)
install(FILES ${CMAKE_SOURCE_DIR}/packaging/icons/comal-ide.svg
  DESTINATION share/icons/hicolor/scalable/apps
)

# CPack packaging configuration: DEB and RPM
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_NAME "OpenCOMAL")
set(CPACK_PACKAGE_VENDOR "OpenCOMAL Project")
set(CPACK_PACKAGE_CONTACT "maintainer@example.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "COMAL interpreter and tools")
if(NOT DEFINED CPACK_PACKAGE_VERSION)
  set(CPACK_PACKAGE_VERSION "0.0.1")
endif()
set(CPACK_GENERATOR "DEB;RPM")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "maintainer@example.com")
# Runtime package dependencies (adjust as appropriate for target distros)
# Debian/DEB: match entries in docs/PROJECT_STATUS.md (may be runtime package names)
set(CPACK_DEBIAN_PACKAGE_DEPENDS "qt6-base, qt6-svg, libqscintilla2-qt6, libncurses6, readline")
# RPM: use common Fedora package names
set(CPACK_RPM_PACKAGE_REQUIRES "qt6-qtbase, qt6-qtsvg, qscintilla-qt6, ncurses, readline")
set(CPACK_RPM_PACKAGE_LICENSE "GPL-3.0-or-later")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/legacy/doc/LICENSE")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
include(CPack)
