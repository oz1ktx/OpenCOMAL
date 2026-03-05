# OpenCOMAL Documentation

Welcome to the OpenCOMAL modernization project documentation.

## Quick Navigation

### 📊 Project Overview
- **[PROJECT_STATUS.md](PROJECT_STATUS.md)** - Current status, what's done, what's next
  - Quick status table
  - Commands reference
  - File locations
  - **START HERE** when returning to the project

### 🏗️ Architecture & Design
- **[AST_MODERNIZATION.md](AST_MODERNIZATION.md)** - Detailed AST modernization plan
  - Design decisions and rationale
  - Implementation status (Phase 1 ✅, Phase 2 ⏳)
  - Memory management strategy
  - **READ THIS** before working on AST Phase 2

- **[AST_USAGE.md](AST_USAGE.md)** - How to use the modern AST API
  - Code examples
  - Common patterns
  - Factory functions
  - Ownership rules
  - **REFERENCE THIS** when writing AST code

### 📚 Legacy Documentation
These files are in `legacy/doc/`:
- `REFORM_PLAN.md` - Original modernization vision
- `PIPELINE.md` - Original plan (now superseded by docs above)
- `SPLIT.md` - Notes on code splitting
- `CHANGES` - Legacy changelog
- `TODO` - Legacy todo list
- `OpenComal.txt` - Original COMAL documentation

## Documentation Status

| Document | Purpose | Status |
|----------|---------|--------|
| PROJECT_STATUS.md | Overall project tracking | ✅ Current |
| AST_MODERNIZATION.md | AST design & implementation | ✅ Current |
| AST_USAGE.md | API usage guide | ✅ Current |
| README.md (this) | Documentation index | ✅ Current |

## For New Contributors

1. Read [PROJECT_STATUS.md](PROJECT_STATUS.md) first
2. Review [AST_MODERNIZATION.md](AST_MODERNIZATION.md) to understand the design
3. Check [AST_USAGE.md](AST_USAGE.md) for code examples
4. Look at `libcomal-parser/tools/ast_demo.cpp` for working code

## For Returning to Development

1. Check [PROJECT_STATUS.md](PROJECT_STATUS.md) - "What's Next" section
2. Review [AST_MODERNIZATION.md](AST_MODERNIZATION.md) - "How to Continue" section
3. Build and test: `cd build && make && ./libcomal-parser/comal-ast-demo`

## Documentation Updates

When making significant changes:
- Update PROJECT_STATUS.md with completion markers
- Update AST_MODERNIZATION.md if design changes
- Add examples to AST_USAGE.md if introducing new patterns
- Keep this README in sync with new documents

---

Last updated: 3 March 2026
