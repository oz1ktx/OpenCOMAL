# AST Modernization Plan

**Status:** Phase 1 Complete ✅ | Phase 2 Complete ✅ | Phase 3 Complete ✅ | Phase 4 (Runtime) 🔄 In Progress ~50%

**Last Updated:** 5 March 2026

---

## Quick Reference

- **Implementation:** [libcomal-parser/include/comal_ast_modern.h](../libcomal-parser/include/comal_ast_modern.h)
- **Compatibility:** [libcomal-parser/src/ast_compat.cpp](../libcomal-parser/src/ast_compat.cpp)
- **Public API:** [libcomal-parser/include/comal_parser_api.h](../libcomal-parser/include/comal_parser_api.h)
- **Usage Guide:** [AST_USAGE.md](./AST_USAGE.md)
- **Demo:** [libcomal-parser/tools/ast_demo.cpp](../libcomal-parser/tools/ast_demo.cpp)
- **Parse CLI:** [libcomal-parser/tools/parse_cli.cpp](../libcomal-parser/tools/parse_cli.cpp) (`-m` for modern output)

---

## Original State (Legacy)
- C structs with raw pointers
- Pool-based memory allocation (PARSE_POOL, RUN_POOL)
- Manual memory management
- Unions for variant data
- Plain enums

## Goal (Achieved for Expressions)
Modern C++20 AST with:
- ✅ Classes with constructors/destructors
- ✅ Raw pointers with pool ownership (matches Qt style)
- ✅ Type-safe variants (std::variant)
- ✅ Enum classes (OpType)
- ✅ Helper factory functions
- ✅ Visitor pattern support

---

## Key Design Decision: Pool Allocation Strategy

**Challenge:** Pool allocator does bulk deallocation - individual objects don't need destructors called. We need ownership semantics that match Qt's parent-child model for future GUI integration.

**CHOSEN SOLUTION - Option B: Raw Pointers + RAII Wrappers** ✅

**Decision Rationale:**
- Matches Qt's ownership model perfectly (parent owns children)
- Simpler than custom deleters
- Zero runtime overhead
- Na✅ Option B: Raw Pointers + RAII Wrappers (IMPLEMENTED)
Keep raw pointers internally, wrap entire parse tree in RAII wrapper:
```cpp
class ParseTree {
    mem_pool* pool_;       /* owned */
    ASTNode* root_;        /* owned via pool */
public:
    ~ParseTree() { pool_free(pool_); }  // Bulk cleanup
};
```

**Pros:**
- ✅ Simpler internal code
- ✅ Matches allocation model
- ✅ Zero overhead
- ✅ Compatible with Qt's ownership model

**Implementation Notes:**
- Raw pointers annotated with `/* owned */` or `/* borrowed */` comments
- `pool_new<T>()` helper does placement construction
- ParseTree provides RAII for top-level ownership

### Option C: Hybrid (Not Selected)
- Would use smart pointers for owned, raw for borrowed
- Rejected as unnecessarily complex

---

## Implemented Class Hierarchy (Phase 1 Complete) (can be optimized away with empty base optimization)
- Slight complexity

### Option B: Raw Pointers + RAII Wrappers
Keep raw pointers internally, wrap entire parse tree in RAII wrapper:
```cpp
class ParseTree {
    comal_line* root_;  // raw pointer
    mem_pool* pool_;
public:
    ~ParseTree() { mem_pool_free(pool_); }
};
```

**Pros:**
- Simpler internal code
- Matches allocation model
- Zero overhead

**Cons:**
- Less granular ownership
- Easy to accidentally leak if used wrong

### Option C: Hybrid Approach (Suggested)
- Use `pool_ptr<T>` for **owned** children (expression trees, statement lists)
- Use **raw pointers** for **references** (symbol table lookups, back-links)
- Mark pointers `/* owned */` or `/* borrowed */` in comments
✅ Core AST Base (Implemented)
```cpp
namespace comal {

class ASTNode {
protected:
    ASTNode() = default;
public:
    virtual ~ASTNode() = default;
    ASTNode(const ASTNode&) = delete;
    ASTNode& operator=(const ASTNode&) = delete;
    ASTNode(ASTNode&&) = delete;
    ASTNode& operator=(ASTNode&&) = delete;
};

class ParseTree {
    mem_pool* pool_;       /* owned */
    ASTNode* root_;        /* owned via pool */
public:
    explicit ParseTree(mem_pool* pool, ASTNode* root = nullptr);
    ~ParseTree() { if (pool_) pool_free(pool_); }
    // Move semantics supported, copy deleted
};

}
```

### ✅ Expression System (Implemented)
```cpp
enum class OpType : uint8_t {
    Unused, Const, Unary, Binary, IntNum, Float,
    Substr, String, Id, Sid, Sys, Syss,
    ExpIsNum, ExpIsString, Array, Sarray
};

class Expression : public ASTNode {
    OpType op_type_;
    int op_;
    std::variant<
        std::monostate,       // empty
        int64_t,              // num
        double,               // fnum (plain double, no source text)
        string*,              // str (custom homebrew type kept)
        Expression*,          // exp (unary)
        TwoExp,               // twoexp (binary) - {Expression* exp1; Expression* exp2;}
        ExpId,                // expid - {id_rec* id; ExpList* exproot;}
        ExpSid,               // expsid - {id_rec* id; ExpList* exproot; TwoExp* twoexp;}
        ExpSubstr,            // expsubstr - {Expression* exp; TwoExp twoexp;}
        ExpList*              // exproot (array)
    > data_;
    
public:
    Expression(OpType type, int op);
    Expression(OpType type, int op, Data&& data);
    
    // Type-safe accessors with std::get
    int64_t asNum() const;
    double asFloat() const;
    string* asString() const;
    Expression* asExp() const;
    const TwoExp& asTwoExp() const;
    ExpList* asExpList() const;
};
```

**Factory Functions Provided:**
- `make_int_expr(pool, value)`
- `make_float_expr(pool, value)` — plain double, no text param
- `make_string_expr(pool, str)`
- `make_binary_expr(pool, op, left, right)`
- `make_unary_expr(pool, op, operand)`
- `make_id_expr(pool, id, args)`

### ⏳ Statement (ComalLine) - NEXT TO IMPLEMENT
```cpp
// Planned for Phase 2
enum class StatementType {
    Print, Input, For, While, If, //...
};

class ComalLine : public ASTNode {
    LineData* line_data_;        /* owned */
    ComalLine* line_ptr_;        /* borrowed (for GOTO targets) */
    StatementType cmd_;
    
    std::variant<
        string*,              /* owned - for string statements */
        int,                  // for integer statements
        id_rec*,              /* borrowed - symbol table */
        ForRec,               // for FOR statements
        IfWhileRec,           // for IF/WHILE statements  
        PrintRec,             // for PRINT statements
        // ... all the statement-specific records
    > contents_;
    
public:
    ComalLine(long lineno, StatementType cmd);
    
    StatementType command() const;
    long lineNumber() const;
    
    // Typed accessors for specific statement types
    const ForRec* asFor() const;
    const PrintRec* asPrint() const;
---

## Implementation Status

### ✅ Phase 1: Expression Foundation (COMPLETE)

**Files Created:**
- `libcomal-parser/include/comal_ast_modern.h` - 400+ lines of modern AST
- `libcomal-parser/src/ast_compat.cpp` - Legacy↔Modern conversion
- `libcomal-parser/tools/ast_demo.cpp` - Working demonstration
- `docs/AST_USAGE.md` - Comprehensive usage guide

**What Works:**
1. ✅ Base `ASTNode` class with proper C++ semantics
2. ✅ `ParseTree` RAII wrapper for pool ownership
3. ✅ `Expression` class with type-safe `std::variant`
4. ✅ All list types: `ExpList`, `DimList`, `ParmList`, `ImportList`, `PrintList`, `WhenList`, `AssignList`
5. ✅ Helper structs: `TwoExp`, `ExpId`, `ExpSid`, `ExpSubstr`, `Double`, `TwoNum`
6. ✅ Factory functions for common expression patterns
7. ✅ List utilities (cons, reverse, length, visitor)
8. ✅ Bidirectional legacy conversion layer
9. ✅ Full compilation and demo verified
10. ✅ `pool_new<T>()` placement construction helper

**Demo Output Verified:**
```
=== Modern COMAL AST Demo ===
Built expression tree: (10 + 20) * 3
Expression list (reversed): 3, 2, 1
Expression list (after reverse): 1, 2, 3
Type-safe variant access working ✓
```

### ✅ Phase 2: Statement/ComalLine (COMPLETE)

**Implemented:**
1. All statement record classes converted to modern C++:
   - `ForRec` - FOR loop (lval, from, mode, to, step, stat)
   - `IfWhileRec` - IF/WHILE/ELIF/UNTIL (exp, stat)
   - `PrintRec` / `PrintModifier` - PRINT with FILE/USING (std::variant)
   - `InputRec` / `InputModifier` - INPUT with FILE/AT (std::variant)
   - `OpenRec` - OPEN (filenum, filename, type, reclen, read_only)
   - `ReadRec` - READ (modifier, lvalroot)
   - `WriteRec` - WRITE (twoexp, exproot)
   - `ProcFuncRec` - PROC/FUNC (id, closed, external, parms, level, links)
   - `ImportRec` - IMPORT (id, importroot)
   - `ExtRec` - EXTERNAL (dynamic, filename, seg)
   - `TrapRec` - TRAP (esc flag)
   - `ListCmd` - LIST (str, twonum range, id filter)

2. `ComalLine` class implemented:
   - `enum class StatementType` with all ~50 COMAL commands
   - `std::variant` Contents with 21 alternatives
   - Type-safe accessors: `asFor()`, `asPrint()`, `asProcFunc()`, etc.
   - Line metadata via `ComalLineData` (lineno, indent, remarks)
   - Program list navigation: `next()`, `setNext()`, `linePtr()`

3. Factory functions added:
   - `make_line_data()`, `make_line()` (2 overloads)
   - `make_for_line()`, `make_if_line()`, `make_while_line()`
   - `make_print_line()`, `make_proc_line()`, `make_func_line()`
   - `visit_lines()` program traversal

4. Demo verified ✅:
   - FOR, IF, WHILE, PRINT, TRAP, end-markers
   - Linked program traversal
   - Variant type safety (bad_variant_access on mismatch)
   - get_if<> safe access pattern

### 📋 Phase 3: Parser Integration (COMPLETE)

Parser integration completed — `comal-parse-cli -m` produces modern AST
from legacy parser output. 109/113 sample programs parse successfully.

### 🔄 Phase 4: Runtime Library (IN PROGRESS ~50%)

**Implemented:**
- `libcomal-runtime/` — 17 files, ~3521 lines total
- Core execution dispatch (40+ statement types)
- Expression evaluator with variant-based Value type
- Scope stack with CLOSED support
- PROC/FUNC calls with parameter binding (value and REF)
- FOR loops with step-direction-aware termination
- IF/ELIF/ELSE, WHILE, REPEAT/UNTIL, CASE/WHEN
- Batch runner CLI (`comal-run`)
- 13/25 tests passing in partial suite run

**Known issues:** trig builtins timeout, array DIM, file I/O stubs

See `docs/PROJECT_STATUS.md` Phase 4 section for detailed bug list and architecture.

---

## Design Decisions (Resolved)

### ✅ Memory Management
- **Decision:** Raw pointers + pool ownership (Option B)
- **Rationale:** Matches Qt, simple, zero overhead
- **Implementation:** `ParseTree` RAII wrapper, `/* owned */` comments

### ✅ Type Safety
- **Decision:** `std::variant` instead of C unions
- **Rationale:** Type-safe, explicit alternatives, enable std::visit
- **Cost:** Minimal (discriminator already present in old design)

### ✅ List Structures
- **Decision:** Intrusive linked lists (not `std::vector`)
- **Rationale:** Pool-efficient, cache-friendly, low overhead
- **Implementation:** Each list type is its own class with next pointer

### ✅ String Type
- **Decision:** Keep custom `struct string` (not `std::string`)
- **Rationale:** Pool-allocated, length-prefixed, fits existing design
- **Note:** May convert at API boundaries in future

### ✅ Enum Types
- **Decision:** Use `enum class` (strongly typed)
- **Examples:** `OpType`, `StatementType`, `ValueType`

### ✅ Line Numbers
- **Decision:** Discard legacy COMAL line numbers on import
- **Rationale:** COMAL has no GOTO; line numbers were a BASIC-era REPL artifact.
  Modern file-based workflow makes them unnecessary.
- **Implementation:** `ComalLineData::lineno` holds the physical source-file
  line (1-based, sequential), assigned by the parser — not from program text.
  Error messages use `filename:line:` format like C compilers.
- **Impact:** `RENUM`, `AUTO`, line-range `LIST` become obsolete; the lexer
  strips leading `NNN` tokens from legacy programs during import.

### ✅ Float Constants
- **Decision:** Store plain `double` in `Expression` variant (no source text)
- **Rationale:** `std::to_chars` gives shortest round-trip formatting;
  legacy `struct dubbel { double val; char* text; }` was unnecessary overhead.
- **Implementation:** `make_float_expr(pool, value)`, `asFloat()` returns `double`

---

## Current Integration Status

**Compilation:** ✅ Clean build, no warnings
**Legacy Parser:** ✅ Still functional, unchanged
**Modern Types:** ✅ Expressions + Statements complete, tested with demo
**Conversion Layer:** ✅ Bidirectional legacy↔modern working (expressions)
**Parser Integration:** ⏳ Not yet integrated (parser still produces legacy AST)

**Next Integration Step:** Update parser to produce modern AST directly (Option A).
Modern types are complete; line numbers will be assigned as source-file lines.

---

## How to Continue (Next Session)

1. **Phase 4 is in progress (~50%).** The runtime library (`libcomal-runtime/`)
   executes parsed modern AST. Core execution works: FOR, IF/ELIF/ELSE, WHILE,
   REPEAT/UNTIL, CASE/WHEN, PROC/FUNC (with parameters, REF, CLOSED scoping),
   PRINT, INPUT, assignment, and most expressions.

2. **Build and test:**
   ```bash
   cd /home/pnand/Workspace/Scratch/OpenCOMAL/build
   make -j$(nproc)
   # Run a single test
   ./libcomal-runtime/comal-run ../legacy/samples/tests/for1.lst
   # Run all tests with timeout
   for f in ../legacy/samples/tests/*.lst; do
     timeout 2 ./libcomal-runtime/comal-run "$f" >/dev/null 2>&1 && echo "PASS $(basename $f)" || echo "FAIL $(basename $f)"
   done
   ```

3. **Priority fixes (in order):**
   - **Trig builtins** (ACS, ASN, ATN, COS cause timeouts) — check `builtins.cpp`
     dispatch and `evaluator.cpp` function-code routing
   - **Array DIM** (dim1.lst, dim2.lst fail) — verify multi-dim and string array DIM
   - **File I/O** (close1, del1, dirs fail) — OPEN/CLOSE/DELETE stubs in `file_io.cpp`
   - **Full test suite run** — only 25/113 have been tested so far

4. **Key files to review:**
   - `libcomal-runtime/src/executor.cpp` (1185 lines) — statement dispatch
   - `libcomal-runtime/src/evaluator.cpp` (402 lines) — expression evaluation
   - `libcomal-runtime/src/builtins.cpp` (222 lines) — builtin functions
   - `libcomal-runtime/include/comal_executor.h` — public execution API
   - `docs/PROJECT_STATUS.md` — comprehensive status with bugs found/fixed

5. **Reference documents:**
   - `docs/PROJECT_STATUS.md` — detailed Phase 4 status, bugs, test results
   - `docs/AST_USAGE.md` for modern AST patterns
   - `libcomal-parser/include/comal_ast_modern.h` for AST definitions

---

## Files Reference

**Core Implementation:**
- `libcomal-parser/include/comal_ast_modern.h` - Modern C++ AST definitions (~950 lines)
- `libcomal-parser/src/ast_compat.cpp` - Legacy↔Modern conversion (~600+ lines)
- `libcomal-parser/include/comal_parser_api.h` - Public API (C and C++)
- `libcomal-parser/src/parser_api.cpp` - API implementation
- `libcomal-parser/include/comal_ast.h` - Legacy C structures (reference)

**Documentation:**
- `docs/AST_MODERNIZATION.md` - This file (plan & status)
- `docs/AST_USAGE.md` - Usage examples & patterns
- `docs/PIPELINE.md` - Overall project roadmap

**Testing:**
- `libcomal-parser/tools/ast_demo.cpp` - Modern AST demonstration
- `libcomal-parser/tools/parse_cli.cpp` - Legacy parser CLI
- `samples/` - Test COMAL programs

**Build:**
- `libcomal-parser/CMakeLists.txt` - Build configuration
- Build: `cd build && make`
- Run demo: `./libcomal-parser/comal-ast-demo`t, DimList, etc.)
4. Update parser semantic actions for expressions
5. **Verify build and test**

### Phase 2: Statements
1. Convert statement-specific records (ForRecord, PrintRecord, etc.)
2. Convert `ComalLine` class
3. Update parser semantic actions for statements
4. **Verify build and test**

### Phase 3: Support Types
1. Convert symbol table types (IdRec, SymItem, etc.)
2. Convert environment types
3. Update remainder of codebase
4. **Final verification**

## Migration Notes

- Keep backward compatibility during transition: expose C-style accessors
- Parser can gradually adopt new constructors
- Old pool allocation still works alongside new code
- Can mix raw/smart pointers during transition

## Questions to Resolve

1. **pool_ptr vs raw?** Prefer Option C (hybrid)?
2. **std::variant vs unions?** Variant is type-safe but slightly larger
3. **Intrusive lists vs std::vector?** Lists keep pool efficiency
4. **enum class names?** OpType, StatementType, ValueType, SymbolType?

## Next Steps

1. Get agreement on design approach
2. Implement Phase 1 (Expression + lists)
3. Update parser incrementally
4. Verify with existing tests
