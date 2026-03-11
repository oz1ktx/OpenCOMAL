Packaging helpers for DEB/RPM

This directory contains optional maintainer script templates and notes for building distribution packages using CPack (DEB and RPM).

Usage
- Customize the templates in `debian/` or `rpm/` as needed.
- Build packages from the project build directory with:

  cmake -S . -B build -DCPACK_GENERATOR="DEB;RPM"
  cmake --build build --target package

Files
- debian/postinst.tpl: post-installation script template for DEB packages
- debian/prerm.tpl: pre-removal script template for DEB packages
- rpm/postinstall.tpl: post-installation script template for RPM packages
