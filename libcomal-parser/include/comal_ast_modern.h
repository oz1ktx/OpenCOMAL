#ifndef COMAL_AST_MODERN_H
#define COMAL_AST_MODERN_H

#include <variant>
#include <cstdint>
#include <string_view>
#include "comal_memory.h"

// Forward declarations of legacy types we still reference
struct string;
struct id_rec;
struct seg_des;

namespace comal {

// ============================================================================
// Base Types
// ============================================================================

/// Base class for all AST nodes
/// Memory is pool-allocated; destruction is handled by pool cleanup
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

/// RAII wrapper for parse trees - owns the pool
class ParseTree {
    mem_pool* pool_;       /* owned */
    ASTNode* root_;        /* owned via pool */
    
public:
    explicit ParseTree(mem_pool* pool, ASTNode* root = nullptr)
        : pool_(pool), root_(root) {}
    
    ~ParseTree() {
        if (pool_) {
            pool_free(pool_);
        }
    }
    
    ParseTree(const ParseTree&) = delete;
    ParseTree& operator=(const ParseTree&) = delete;
    
    ParseTree(ParseTree&& other) noexcept
        : pool_(other.pool_), root_(other.root_) {
        other.pool_ = nullptr;
        other.root_ = nullptr;
    }
    
    ParseTree& operator=(ParseTree&& other) noexcept {
        if (this != &other) {
            if (pool_) pool_free(pool_);
            pool_ = other.pool_;
            root_ = other.root_;
            other.pool_ = nullptr;
            other.root_ = nullptr;
        }
        return *this;
    }
    
    ASTNode* root() const { return root_; }
    void setRoot(ASTNode* r) { root_ = r; }
    mem_pool* pool() const { return pool_; }
};

/// Pair of numeric values
struct TwoNum {
    int64_t num1;
    int64_t num2;
    
    TwoNum() : num1(0), num2(0) {}
    TwoNum(int64_t n1, int64_t n2) : num1(n1), num2(n2) {}
};

// ============================================================================
// Forward Declarations (needed for circular dependencies)
// ============================================================================

class Expression;
class ExpList;
class PrintList;
class ComalLine;

// ============================================================================
// Expression System
// ============================================================================

enum class OpType : uint8_t {
    Unused,
    Const,
    Unary,
    Binary,
    IntNum,
    Float,
    Substr,
    String,
    Id,
    Sid,
    Sys,
    Syss,
    ExpIsNum,
    ExpIsString,
    Array,
    Sarray
};

// Define these BEFORE Expression since they're used in its variant

/// Pair of expressions
struct TwoExp {
    Expression* exp1;  /* owned */
    Expression* exp2;  /* owned */
    
    TwoExp() : exp1(nullptr), exp2(nullptr) {}
    TwoExp(Expression* e1, Expression* e2) : exp1(e1), exp2(e2) {}
};

/// Expression ID reference (variable or function call)
struct ExpId {
    id_rec* id;          /* borrowed - symbol table owns */
    ExpList* exproot;    /* owned - argument list */
    
    ExpId() : id(nullptr), exproot(nullptr) {}
    ExpId(id_rec* i, ExpList* e) : id(i), exproot(e) {}
};

/// String ID reference (string variable with substring)
struct ExpSid {
    id_rec* id;          /* borrowed */
    ExpList* exproot;    /* owned */
    TwoExp* twoexp;      /* owned */
    
    ExpSid() : id(nullptr), exproot(nullptr), twoexp(nullptr) {}
    ExpSid(id_rec* i, ExpList* e, TwoExp* t) : id(i), exproot(e), twoexp(t) {}
};

/// Substring expression
struct ExpSubstr {
    Expression* exp;     /* owned */
    TwoExp twoexp;       /* owned */
    
    ExpSubstr() : exp(nullptr), twoexp() {}
    ExpSubstr(Expression* e, const TwoExp& t) : exp(e), twoexp(t) {}
};

/// Expression node representing COMAL expressions
class Expression : public ASTNode {
public:
    using Data = std::variant<
        std::monostate,        // empty/unused
        int64_t,               // num (IntNum)
        double,                // fnum (Float) - value only, no source text
        string*,               // str (String) - borrowed from pool
        Expression*,           // exp (Unary) - owned
        TwoExp,                // twoexp (Binary) - owned
        ExpId,                 // expid (Id) - owned
        ExpSid,                // expsid (Sid) - owned  
        ExpSubstr,             // expsubstr (Substr) - owned
        ExpList*               // exproot (Array/Sarray) - owned
    >;
    
private:
    OpType op_type_;
    int op_;
    Data data_;
    
public:
    Expression(OpType type, int op) 
        : op_type_(type), op_(op), data_() {}
    
    Expression(OpType type, int op, Data&& data)
        : op_type_(type), op_(op), data_(std::move(data)) {}
    
    OpType opType() const { return op_type_; }
    int op() const { return op_; }
    
    const Data& data() const { return data_; }
    Data& data() { return data_; }
    
    // Convenience accessors
    int64_t asNum() const { return std::get<int64_t>(data_); }
    double asFloat() const { return std::get<double>(data_); }
    string* asString() const { return std::get<string*>(data_); }
    Expression* asExp() const { return std::get<Expression*>(data_); }
    const TwoExp& asTwoExp() const { return std::get<TwoExp>(data_); }
    ExpList* asExpList() const { return std::get<ExpList*>(data_); }
};

// ============================================================================
// List Types (Intrusive linked lists for pool efficiency)
// ============================================================================

/// Expression list node
class ExpList : public ASTNode {
    ExpList* next_;      /* owned */
    Expression* exp_;    /* owned */
    
public:
    ExpList(Expression* exp, ExpList* next = nullptr)
        : next_(next), exp_(exp) {}
    
    Expression* exp() const { return exp_; }
    ExpList* next() const { return next_; }
    
    void setNext(ExpList* n) { next_ = n; }
    void setExp(Expression* e) { exp_ = e; }
};

/// Dimension specification for array dimensions
class DimEnsion : public ASTNode {
    DimEnsion* next_;         /* owned */
    Expression* bottom_;      /* owned */
    Expression* top_;         /* owned */
    
public:
    DimEnsion(Expression* bottom, Expression* top, DimEnsion* next = nullptr)
        : next_(next), bottom_(bottom), top_(top) {}
    
    Expression* bottom() const { return bottom_; }
    Expression* top() const { return top_; }
    DimEnsion* next() const { return next_; }
    
    void setNext(DimEnsion* n) { next_ = n; }
};

/// Dimension list entry (for DIM statements)
class DimList : public ASTNode {
    DimList* next_;              /* owned */
    id_rec* id_;                 /* borrowed */
    DimEnsion* dimensionroot_;   /* owned */
    Expression* strlen_;         /* owned */
    
public:
    DimList(id_rec* id, DimEnsion* dims = nullptr, Expression* slen = nullptr, DimList* next = nullptr)
        : next_(next), id_(id), dimensionroot_(dims), strlen_(slen) {}
    
    id_rec* id() const { return id_; }
    DimEnsion* dimensions() const { return dimensionroot_; }
    Expression* strlen() const { return strlen_; }
    DimList* next() const { return next_; }
    
    void setNext(DimList* n) { next_ = n; }
};

/// Parameter list entry
class ParmList : public ASTNode {
    ParmList* next_;     /* owned */
    id_rec* id_;         /* borrowed */
    int ref_type_;       // 0=value, refSYM=REF, nameSYM=NAME, procSYM=PROC, funcSYM=FUNC
    bool array_;         // array parameter
    
public:
    ParmList(id_rec* id, int ref_type = 0, bool array = false, ParmList* next = nullptr)
        : next_(next), id_(id), ref_type_(ref_type), array_(array) {}
    
    id_rec* id() const { return id_; }
    bool isRef() const;   // defined out-of-line — true for refSYM
    bool isName() const;  // true for nameSYM
    bool isProc() const;  // true for procSYM
    bool isFunc() const;  // true for funcSYM
    int refType() const { return ref_type_; }
    bool isArray() const { return array_; }
    ParmList* next() const { return next_; }
    
    void setNext(ParmList* n) { next_ = n; }
};

/// Import list entry
class ImportList : public ASTNode {
    ImportList* next_;   /* owned */
    id_rec* id_;         /* borrowed */
    bool array_;
    
public:
    ImportList(id_rec* id, bool array = false, ImportList* next = nullptr)
        : next_(next), id_(id), array_(array) {}
    
    id_rec* id() const { return id_; }
    bool isArray() const { return array_; }
    ImportList* next() const { return next_; }
    
    void setNext(ImportList* n) { next_ = n; }
};

/// Print list entry
class PrintList : public ASTNode {
    PrintList* next_;    /* owned */
    int pr_sep_;         // separator type
    Expression* exp_;    /* owned */
    
public:
    PrintList(Expression* exp, int sep = 0, PrintList* next = nullptr)
        : next_(next), pr_sep_(sep), exp_(exp) {}
    
    Expression* exp() const { return exp_; }
    int separator() const { return pr_sep_; }
    PrintList* next() const { return next_; }
    
    void setNext(PrintList* n) { next_ = n; }
};

/// When list entry (for CASE statements)
class WhenList : public ASTNode {
    WhenList* next_;     /* owned */
    int op_;
    Expression* exp_;    /* owned */
    
public:
    WhenList(int op, Expression* exp, WhenList* next = nullptr)
        : next_(next), op_(op), exp_(exp) {}
    
    int op() const { return op_; }
    Expression* exp() const { return exp_; }
    WhenList* next() const { return next_; }
    
    void setNext(WhenList* n) { next_ = n; }
};

/// Assignment list entry (for multiple assignments)
class AssignList : public ASTNode {
    AssignList* next_;   /* owned */
    int op_;
    Expression* lval_;   /* owned */
    Expression* exp_;    /* owned */
    
public:
    AssignList(int op, Expression* lval, Expression* exp, AssignList* next = nullptr)
        : next_(next), op_(op), lval_(lval), exp_(exp) {}
    
    int op() const { return op_; }
    Expression* lval() const { return lval_; }
    Expression* exp() const { return exp_; }
    AssignList* next() const { return next_; }
    
    void setNext(AssignList* n) { next_ = n; }
};

// ============================================================================
// Forward Declarations (needed for statement records)
// ============================================================================

class ComalLine;

// ============================================================================
// Statement-Specific Record Classes (Phase 2)
// ============================================================================

/// FOR loop record:  FOR lval := from TO/DOWNTO to STEP step
class ForRec {
public:
    Expression* lval;    /* owned - loop variable */
    Expression* from;    /* owned - start expression */
    int mode;            // direction: toSYM or downtoSYM
    Expression* to;      /* owned - end expression */
    Expression* step;    /* owned - step expression (may be nullptr) */
    ComalLine* stat;     /* borrowed - single-line body (FOR..DO) */

    ForRec()
        : lval(nullptr), from(nullptr), mode(0),
          to(nullptr), step(nullptr), stat(nullptr) {}

    ForRec(Expression* lv, Expression* f, int m,
           Expression* t, Expression* s = nullptr, ComalLine* st = nullptr)
        : lval(lv), from(f), mode(m), to(t), step(s), stat(st) {}
};

/// IF / WHILE / ELIF / UNTIL record
class IfWhileRec {
public:
    Expression* exp;     /* owned - condition expression */
    ComalLine* stat;     /* borrowed - single-line body (short form) */

    IfWhileRec() : exp(nullptr), stat(nullptr) {}
    IfWhileRec(Expression* e, ComalLine* s = nullptr)
        : exp(e), stat(s) {}
};

/// Print modifier (FILE/USING clause)
class PrintModifier {
public:
    int type;            // modifier type token
    // variant: either a USING format-string or FILE twoexp (file#, position)
    std::variant<
        std::monostate,
        Expression*,     /* owned - USING format string */
        TwoExp           /* owned - FILE (filenum, position) */
    > data;

    PrintModifier() : type(0), data() {}
    PrintModifier(int t, Expression* str) : type(t), data(str) {}
    PrintModifier(int t, const TwoExp& te) : type(t), data(te) {}
};

/// PRINT statement record
class PrintRec {
public:
    PrintModifier* modifier;   /* owned - FILE/USING clause (may be nullptr) */
    PrintList* printroot;      /* owned - list of print items */
    int pr_sep;                // trailing separator

    PrintRec() : modifier(nullptr), printroot(nullptr), pr_sep(0) {}
    PrintRec(PrintModifier* mod, PrintList* root, int sep = 0)
        : modifier(mod), printroot(root), pr_sep(sep) {}
};

/// Input modifier (FILE/AT clause)
class InputModifier {
public:
    int type;            // modifier type token
    std::variant<
        std::monostate,
        TwoExp,          /* owned - FILE (filenum, position) */
        string*          /* borrowed - AT prompt string */
    > data;

    InputModifier() : type(0), data() {}
    InputModifier(int t, const TwoExp& te) : type(t), data(te) {}
    InputModifier(int t, string* s) : type(t), data(s) {}
};

/// INPUT statement record
class InputRec {
public:
    InputModifier* modifier;   /* owned - FILE/AT clause (may be nullptr) */
    ExpList* lvalroot;         /* owned - list of l-values to read into */

    InputRec() : modifier(nullptr), lvalroot(nullptr) {}
    InputRec(InputModifier* mod, ExpList* lvals)
        : modifier(mod), lvalroot(lvals) {}
};

/// OPEN statement record
class OpenRec {
public:
    Expression* filenum;       /* owned - file number expression */
    Expression* filename;      /* owned - filename expression */
    int type;                  // open mode (READ/WRITE/APPEND/RANDOM)
    Expression* reclen;        /* owned - record length (may be nullptr) */
    int read_only;             // read-only flag

    OpenRec()
        : filenum(nullptr), filename(nullptr), type(0),
          reclen(nullptr), read_only(0) {}

    OpenRec(Expression* fnum, Expression* fname, int t,
            Expression* rlen = nullptr, int ro = 0)
        : filenum(fnum), filename(fname), type(t),
          reclen(rlen), read_only(ro) {}
};

/// READ statement record
class ReadRec {
public:
    TwoExp* modifier;          /* owned - FILE modifier (may be nullptr) */
    ExpList* lvalroot;         /* owned - list of l-values */

    ReadRec() : modifier(nullptr), lvalroot(nullptr) {}
    ReadRec(TwoExp* mod, ExpList* lvals)
        : modifier(mod), lvalroot(lvals) {}
};

/// WRITE statement record
class WriteRec {
public:
    TwoExp twoexp;             /* owned - FILE (filenum, position) */
    ExpList* exproot;          /* owned - list of expressions to write */

    WriteRec() : twoexp(), exproot(nullptr) {}
    WriteRec(const TwoExp& te, ExpList* exps)
        : twoexp(te), exproot(exps) {}
};

/// External module reference
class ExtRec {
public:
    int dynamic;               // dynamic loading flag
    Expression* filename;      /* owned - module filename */
    seg_des* seg;              /* borrowed - segment descriptor */

    ExtRec() : dynamic(0), filename(nullptr), seg(nullptr) {}
    ExtRec(int dyn, Expression* fname, seg_des* s = nullptr)
        : dynamic(dyn), filename(fname), seg(s) {}
};

/// PROC/FUNC definition record
class ProcFuncRec {
public:
    id_rec* id;                /* borrowed - procedure/function name */
    int closed;                // CLOSED flag
    ExtRec* external;          /* owned - EXTERNAL spec (may be nullptr) */
    ParmList* parmroot;        /* owned - parameter list */
    int level;                 // nesting level
    ComalLine* proclink;       /* borrowed - linked procedure */
    ComalLine* localproc;      /* borrowed - local proc chain */
    ComalLine* fatherproc;     /* borrowed - enclosing proc */
    seg_des* seg;              /* borrowed - segment descriptor */

    ProcFuncRec()
        : id(nullptr), closed(0), external(nullptr), parmroot(nullptr),
          level(0), proclink(nullptr), localproc(nullptr),
          fatherproc(nullptr), seg(nullptr) {}

    ProcFuncRec(id_rec* i, int cl = 0, ExtRec* ext = nullptr,
                ParmList* parms = nullptr)
        : id(i), closed(cl), external(ext), parmroot(parms),
          level(0), proclink(nullptr), localproc(nullptr),
          fatherproc(nullptr), seg(nullptr) {}
};

/// IMPORT statement record
class ImportRec {
public:
    id_rec* id;                /* borrowed - module name */
    ImportList* importroot;    /* owned - list of imported identifiers */

    ImportRec() : id(nullptr), importroot(nullptr) {}
    ImportRec(id_rec* i, ImportList* imports)
        : id(i), importroot(imports) {}
};

/// TRAP statement record
class TrapRec {
public:
    int esc;                   // ESC trap flag

    TrapRec() : esc(0) {}
    explicit TrapRec(int e) : esc(e) {}
};

/// LIST command record (line range + optional filter)
class ListCmd {
public:
    string* str;               /* borrowed - filename for LIST to file */
    TwoNum twonum;             // line range (from, to)
    id_rec* id;                /* borrowed - identifier filter */

    ListCmd() : str(nullptr), twonum(), id(nullptr) {}
    ListCmd(string* s, const TwoNum& tn, id_rec* i = nullptr)
        : str(s), twonum(tn), id(i) {}
};

// ============================================================================
// Statement Type Enumeration
// ============================================================================

/// All COMAL statement/command types
/// Values match legacy token SYM constants for easy migration
enum class StatementType : int {
    Empty       = 0,    // empty line / no command

    // --- Simple statements (no body) ---
    Assign,             // variable := expression
    Print,              // PRINT ...
    Input,              // INPUT ...
    Open,               // OPEN ...
    Close,              // CLOSE ...
    Read,               // READ ...
    Write,              // WRITE ...
    Dim,                // DIM ...
    Data,               // DATA ...
    Restore,            // RESTORE
    Exec,               // EXEC ...
    Return,             // RETURN [expr]
    Stop,               // STOP
    End,                // END
    Exit,               // EXIT [WHEN expr]
    Null,               // NULL (no-op)
    Run,                // RUN [filename]
    Del,                // DEL var
    Page,               // PAGE
    Cursor,             // CURSOR row, col
    Select_Output,      // SELECT OUTPUT ...
    Select_Input,       // SELECT INPUT ...
    Dir,                // DIR [path]
    Unit,               // UNIT [path]
    Chdir,              // CHDIR path
    Mkdir,              // MKDIR path
    Rmdir,              // RMDIR path
    Os,                 // OS command
    Draw,               // DRAW expr, ... (graphics placeholder)
    Tone,               // TONE freq_ms duration_ms
    Play,               // PLAY param-list / MML string
    Retry,              // RETRY (in HANDLER)
    Trace,              // TRACE on/off
    Label,              // label:
    Local,              // LOCAL vars...

    // --- Complex statements (have body) ---
    For,                // FOR ... [DO stat | ENDFOR]
    If,                 // IF ... THEN [stat | ENDIF]
    Elif,               // ELIF ...
    Else,               // ELSE
    While,              // WHILE ... [DO stat | ENDWHILE]
    Repeat,             // REPEAT
    Until,              // UNTIL expr
    Loop,               // LOOP
    Case,               // CASE expr OF
    When,               // WHEN ...
    Otherwise,          // OTHERWISE
    Trap,               // TRAP [ESC]
    Handler,            // HANDLER
    Proc,               // PROC name(...)
    Func,               // FUNC name(...)
    Import,             // IMPORT name, ...

    // --- End markers ---
    EndFor,
    EndIf,
    EndWhile,
    EndLoop,
    EndCase,
    EndProc,
    EndFunc,
    EndTrap,

    // --- Interactive commands ---
    List,               // LIST [range]
    Save,               // SAVE filename
    Load,               // LOAD filename
    Enter,              // ENTER filename
    New,                // NEW
    Scan,               // SCAN
    Auto,               // AUTO
    Cont,               // CONT
    Edit,               // EDIT
    Renumber,           // RENUM
    Env,                // ENV
    Quit,               // QUIT
};

// ============================================================================
// ComalLine - The central AST node for program lines
// ============================================================================

/// Line metadata (line number, indentation, remarks)
class ComalLineData : public ASTNode {
public:
    ComalLine* next;           /* owned - next line in program */
    long lineno;               // line number (0 = direct mode)
    int indent;                // indentation level
    string* rem;               /* owned - remark/comment text */

    ComalLineData()
        : next(nullptr), lineno(0), indent(0), rem(nullptr) {}

    ComalLineData(long lno, int ind = 0, string* r = nullptr)
        : next(nullptr), lineno(lno), indent(ind), rem(r) {}
};

/// The central AST node: one COMAL program line / statement.
///
/// The `contents` variant holds statement-specific data. Which alternative
/// is active is determined by `cmd` (the StatementType).
class ComalLine : public ASTNode {
public:
    /// Statement-specific payload
    using Contents = std::variant<
        std::monostate,        // empty / no data (Null, End, Else, Repeat, ...)
        string*,               /* borrowed - for Save/Load/Enter/Os/Label/... */
        int,                   // integer value (Close filenum, Exit when-op, ...)
        id_rec*,               /* borrowed - Del, Local */
        TwoNum,                // Renumber/Auto (from, step)
        TwoExp,                // Cursor (row, col), Select (file#, ...)
        ListCmd,               // LIST command
        Expression*,           /* owned - Case expr, Return expr, Run expr, ... */
        ExpList*,              /* owned - Data list */
        DimList*,              /* owned - DIM list */
        ForRec,                // FOR statement
        IfWhileRec,            // IF / WHILE / ELIF / UNTIL
        ImportRec,             // IMPORT statement
        InputRec,              // INPUT statement
        OpenRec,               // OPEN statement
        PrintRec,              // PRINT statement
        ProcFuncRec,           // PROC / FUNC definition
        TrapRec,               // TRAP statement
        ReadRec,               // READ statement
        WhenList*,             /* owned - WHEN list */
        WriteRec,              // WRITE statement
        AssignList*            /* owned - assignment(s) */
    >;

private:
    ComalLineData* ld_;        /* owned - line metadata */
    ComalLine* lineptr_;       /* borrowed - target (GOTO, loop end, etc.) */
    StatementType cmd_;        // statement type
    Contents contents_;        // statement-specific data

public:
    ComalLine()
        : ld_(nullptr), lineptr_(nullptr),
          cmd_(StatementType::Empty), contents_() {}

    ComalLine(ComalLineData* data, StatementType cmd)
        : ld_(data), lineptr_(nullptr),
          cmd_(cmd), contents_() {}

    ComalLine(ComalLineData* data, StatementType cmd, Contents&& c)
        : ld_(data), lineptr_(nullptr),
          cmd_(cmd), contents_(std::move(c)) {}

    // --- Accessors ---
    StatementType command() const { return cmd_; }
    void setCommand(StatementType c) { cmd_ = c; }

    ComalLineData* lineData() const { return ld_; }
    void setLineData(ComalLineData* d) { ld_ = d; }

    ComalLine* linePtr() const { return lineptr_; }
    void setLinePtr(ComalLine* p) { lineptr_ = p; }

    long lineNumber() const { return ld_ ? ld_->lineno : 0; }

    const Contents& contents() const { return contents_; }
    Contents& contents() { return contents_; }
    void setContents(Contents&& c) { contents_ = std::move(c); }

    // --- Typed accessors (throw std::bad_variant_access on mismatch) ---
    const ForRec& asFor() const { return std::get<ForRec>(contents_); }
    ForRec& asFor() { return std::get<ForRec>(contents_); }

    const IfWhileRec& asIfWhile() const { return std::get<IfWhileRec>(contents_); }
    IfWhileRec& asIfWhile() { return std::get<IfWhileRec>(contents_); }

    const PrintRec& asPrint() const { return std::get<PrintRec>(contents_); }
    PrintRec& asPrint() { return std::get<PrintRec>(contents_); }

    const InputRec& asInput() const { return std::get<InputRec>(contents_); }
    InputRec& asInput() { return std::get<InputRec>(contents_); }

    const OpenRec& asOpen() const { return std::get<OpenRec>(contents_); }
    OpenRec& asOpen() { return std::get<OpenRec>(contents_); }

    const ReadRec& asRead() const { return std::get<ReadRec>(contents_); }
    ReadRec& asRead() { return std::get<ReadRec>(contents_); }

    const WriteRec& asWrite() const { return std::get<WriteRec>(contents_); }
    WriteRec& asWrite() { return std::get<WriteRec>(contents_); }

    const ProcFuncRec& asProcFunc() const { return std::get<ProcFuncRec>(contents_); }
    ProcFuncRec& asProcFunc() { return std::get<ProcFuncRec>(contents_); }

    const ImportRec& asImport() const { return std::get<ImportRec>(contents_); }
    ImportRec& asImport() { return std::get<ImportRec>(contents_); }

    const TrapRec& asTrap() const { return std::get<TrapRec>(contents_); }
    TrapRec& asTrap() { return std::get<TrapRec>(contents_); }

    const ListCmd& asList() const { return std::get<ListCmd>(contents_); }
    ListCmd& asList() { return std::get<ListCmd>(contents_); }

    Expression* asExpr() const { return std::get<Expression*>(contents_); }
    ExpList* asExpList() const { return std::get<ExpList*>(contents_); }
    DimList* asDimList() const { return std::get<DimList*>(contents_); }
    WhenList* asWhenList() const { return std::get<WhenList*>(contents_); }
    AssignList* asAssignList() const { return std::get<AssignList*>(contents_); }
    string* asString() const { return std::get<string*>(contents_); }
    int asInt() const { return std::get<int>(contents_); }
    id_rec* asId() const { return std::get<id_rec*>(contents_); }
    const TwoNum& asTwoNum() const { return std::get<TwoNum>(contents_); }
    const TwoExp& asTwoExp() const { return std::get<TwoExp>(contents_); }

    // --- Navigation: next line in program ---
    ComalLine* next() const { return ld_ ? ld_->next : nullptr; }
    void setNext(ComalLine* n) { if (ld_) ld_->next = n; }
};

// ============================================================================
// Compatibility Layer - map C structs to C++ classes
// ============================================================================

// Helper functions to allocate modern types from pool
template<typename T, typename... Args>
T* pool_new(int pool, Args&&... args) {
    void* mem = mem_alloc(pool, sizeof(T));
    return new (mem) T(std::forward<Args>(args)...);
}

// ============================================================================
// Convenience Factories for Common AST Patterns
// ============================================================================

/// Create an integer constant expression
inline Expression* make_int_expr(int pool, int64_t value) {
    return pool_new<Expression>(pool, OpType::IntNum, 0, Expression::Data{value});
}

/// Create a float constant expression
inline Expression* make_float_expr(int pool, double value) {
    return pool_new<Expression>(pool, OpType::Float, 0, Expression::Data{value});
}

/// Create a string constant expression
inline Expression* make_string_expr(int pool, string* str) {
    return pool_new<Expression>(pool, OpType::String, 0, Expression::Data{str});
}

/// Create a binary expression
inline Expression* make_binary_expr(int pool, int op, Expression* left, Expression* right) {
    return pool_new<Expression>(pool, OpType::Binary, op, Expression::Data{TwoExp{left, right}});
}

/// Create a unary expression
inline Expression* make_unary_expr(int pool, int op, Expression* operand) {
    return pool_new<Expression>(pool, OpType::Unary, op, Expression::Data{operand});
}

/// Create an ID expression (variable reference or function call)
inline Expression* make_id_expr(int pool, id_rec* id, ExpList* args = nullptr) {
    return pool_new<Expression>(pool, OpType::Id, 0, Expression::Data{ExpId{id, args}});
}

// ============================================================================
// Statement Factory Functions
// ============================================================================

/// Allocate line metadata
inline ComalLineData* make_line_data(int pool, long lineno, int indent = 0,
                                      string* rem = nullptr) {
    return pool_new<ComalLineData>(pool, lineno, indent, rem);
}

/// Create an empty statement line
inline ComalLine* make_line(int pool, long lineno, StatementType cmd) {
    auto* ld = make_line_data(pool, lineno);
    return pool_new<ComalLine>(pool, ld, cmd);
}

/// Create a statement line with contents
inline ComalLine* make_line(int pool, long lineno, StatementType cmd,
                            ComalLine::Contents&& contents) {
    auto* ld = make_line_data(pool, lineno);
    return pool_new<ComalLine>(pool, ld, cmd, std::move(contents));
}

/// Create a FOR statement
inline ComalLine* make_for_line(int pool, long lineno,
                                Expression* lval, Expression* from,
                                int mode, Expression* to,
                                Expression* step = nullptr) {
    return make_line(pool, lineno, StatementType::For,
                     ComalLine::Contents{ForRec{lval, from, mode, to, step}});
}

/// Create an IF or WHILE statement
inline ComalLine* make_if_line(int pool, long lineno, Expression* cond,
                               ComalLine* stat = nullptr) {
    return make_line(pool, lineno, StatementType::If,
                     ComalLine::Contents{IfWhileRec{cond, stat}});
}

inline ComalLine* make_while_line(int pool, long lineno, Expression* cond,
                                  ComalLine* stat = nullptr) {
    return make_line(pool, lineno, StatementType::While,
                     ComalLine::Contents{IfWhileRec{cond, stat}});
}

/// Create a PRINT statement
inline ComalLine* make_print_line(int pool, long lineno,
                                  PrintList* items, int trailing_sep = 0,
                                  PrintModifier* mod = nullptr) {
    return make_line(pool, lineno, StatementType::Print,
                     ComalLine::Contents{PrintRec{mod, items, trailing_sep}});
}

/// Create a PROC definition
inline ComalLine* make_proc_line(int pool, long lineno,
                                 id_rec* id, ParmList* parms = nullptr,
                                 int closed = 0) {
    return make_line(pool, lineno, StatementType::Proc,
                     ComalLine::Contents{ProcFuncRec{id, closed, nullptr, parms}});
}

/// Create a FUNC definition
inline ComalLine* make_func_line(int pool, long lineno,
                                 id_rec* id, ParmList* parms = nullptr,
                                 int closed = 0) {
    return make_line(pool, lineno, StatementType::Func,
                     ComalLine::Contents{ProcFuncRec{id, closed, nullptr, parms}});
}

/// Visit all lines in a program (linked list traversal)
template<typename Visitor>
void visit_lines(ComalLine* line, Visitor&& visitor) {
    for (ComalLine* cur = line; cur != nullptr; cur = cur->next()) {
        visitor(cur);
    }
}

/// Prepend an expression to a list (returns new head)
inline ExpList* cons_exp(int pool, Expression* exp, ExpList* tail) {
    return pool_new<ExpList>(pool, exp, tail);
}

/// Reverse an expression list (modifies pointers, returns new head)
ExpList* reverse_exp_list(ExpList* list);

/// Count elements in list
template<typename T>
size_t list_length(const T* list) {
    size_t count = 0;
    for (const T* node = list; node != nullptr; node = node->next()) {
        ++count;
    }
    return count;
}

/// Visit all expressions in a tree (pre-order traversal)
template<typename Visitor>
void visit_expression(Expression* expr, Visitor&& visitor) {
    if (!expr) return;
    
    visitor(expr);
    
    switch (expr->opType()) {
        case OpType::Binary: {
            if (auto* data = std::get_if<TwoExp>(&expr->data())) {
                visit_expression(data->exp1, visitor);
                visit_expression(data->exp2, visitor);
            }
            break;
        }
        case OpType::Unary: {
            if (auto* subexpr = std::get_if<Expression*>(&expr->data())) {
                visit_expression(*subexpr, visitor);
            }
            break;
        }
        case OpType::Array:
        case OpType::Sarray: {
            if (auto* list = std::get_if<ExpList*>(&expr->data())) {
                for (ExpList* node = *list; node; node = node->next()) {
                    visit_expression(node->exp(), visitor);
                }
            }
            break;
        }
        // Add more cases as needed
        default:
            break;
    }
}

} // namespace comal

#endif // COMAL_AST_MODERN_H
