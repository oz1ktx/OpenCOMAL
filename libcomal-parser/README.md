# libcomal-parser (initial extraction)

This directory contains the extracted lexer/parser sources from legacy OpenCOMAL.

Status:
- Uses the original Flex/Bison sources with the existing C support routines.
- Still depends on legacy headers/types in legacy/src.

Next steps:
- Carve out shared AST and type definitions into libcomal-parser/include.
- Remove dependencies on runtime/editor-specific headers.
- Provide a stable parse API for full-document parsing.
