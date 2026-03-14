#ifndef COMAL_SCOPE_H
#define COMAL_SCOPE_H

/// @file comal_scope.h
/// Symbol table and scope management for the COMAL runtime.
/// Replaces legacy sym_env / sym_item linked-list chains with
/// C++ data structures while preserving COMAL's scoping rules:
///   - CLOSED procedures block upward visibility
///   - REF parameters alias the caller's variable
///   - IMPORT makes outer-scope variables visible locally

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <optional>

#include "comal_value.h"

struct id_rec;   // forward from legacy parser

namespace comal {
class ComalLine;
class Expression;
}

namespace comal::runtime {

// ── Symbol entry ────────────────────────────────────────────────────────

enum class SymbolKind {
    Variable,      // ordinary variable or array
    RefAlias,      // REF parameter — points to another Variable's storage
    ProcRef,       // PROC variable (passed as parameter)
    FuncRef,       // FUNC variable (passed as parameter)
    NameThunk,     // NAME parameter — unevaluated expression + calling scope
};

class Scope;  // forward declaration for use in Symbol

/// One symbol in a scope.
struct Symbol {
    SymbolKind kind{SymbolKind::Variable};

    /// For Variable: the actual storage.
    /// For RefAlias: unused (we store raw pointer to the target Value).
    Value value;

    /// For RefAlias: pointer to the aliased Value (in the caller's scope).
    Value* ref_target{nullptr};

    /// For ProcRef / FuncRef: the line defining the routine.
    ComalLine* routine_line{nullptr};

    /// For NameThunk: the unevaluated expression and calling scope.
    const Expression* name_expr{nullptr};
    Scope* name_scope{nullptr};

    // Convenience
    Value& resolve() { return ref_target ? *ref_target : value; }
    const Value& resolve() const { return ref_target ? *ref_target : value; }
};

// ── Scope ───────────────────────────────────────────────────────────────

/// A single scope frame (one per PROC/FUNC call, plus the global scope).
/// Replaces legacy sym_env.
class Scope {
public:
    Scope* parent{nullptr};        // enclosing scope (nullptr for global)
    bool closed{false};            // CLOSED procedure — blocks sym lookup
    std::string name;              // e.g. "GLOBAL", procedure name
    ComalLine* curproc{nullptr};   // the PROC/FUNC line that opened this scope
    int level{0};                  // nesting depth

    // ── Lookup ──────────────────────────────────────────────────────────

    /// Find a symbol in THIS scope only.
    Symbol* findLocal(const std::string& name);

    /// Find a symbol, walking up through parent scopes.
    /// Stops at a CLOSED boundary (like legacy sym_search).
    Symbol* find(const std::string& name);

    // ── Mutation ────────────────────────────────────────────────────────

    /// Define a new variable (errors if already exists in this scope).
    Symbol& define(const std::string& name, Value&& initial = Value{});

    /// Define a REF alias.
    Symbol& defineRef(const std::string& name, Value* target);

    /// Define a NAME thunk (unevaluated expression + calling scope).
    Symbol& defineName(const std::string& name, const Expression* expr, Scope* caller_scope);

    /// Define a PROC/FUNC reference.
    Symbol& defineProcFunc(const std::string& name, SymbolKind kind,
                           ComalLine* routine);

    /// Import a symbol from an ancestor scope into this scope as an alias.
    void importSymbol(const std::string& symbolName);

    // ── Bulk ────────────────────────────────────────────────────────────

    /// Remove all symbols (used when cleaning up a scope before reuse).
    void clear();

    /// Number of symbols in this scope.
    size_t size() const { return symbols_.size(); }

    /// Get all symbols in this scope (for debugging/variable inspection).
    const std::unordered_map<std::string, Symbol>& allSymbols() const { return symbols_; }

private:
    std::unordered_map<std::string, Symbol> symbols_;
};

// ── Scope stack (managed by the interpreter) ────────────────────────────

/// Owns all scopes and manages push/pop.
class ScopeStack {
public:
    ScopeStack();

    /// The global (bottom-most) scope.
    Scope& global() { return *scopes_.front(); }

    /// The current (top-most) scope.
    Scope& current() {
        if (!raw_stack_.empty()) return *raw_stack_.back();
        return *scopes_.back();
    }
    const Scope& current() const {
        if (!raw_stack_.empty()) return *raw_stack_.back();
        return *scopes_.back();
    }

    /// Push a new scope (for a PROC/FUNC call).
    Scope& push(const std::string& name, bool closed, ComalLine* proc, int level);

    /// Pop the current scope (returning from a PROC/FUNC).
    void pop();

    /// Push a borrowed scope pointer (for NAME thunk evaluation).
    /// The caller retains ownership; must call popRaw() before the scope is destroyed.
    void pushRaw(Scope* s);

    /// Pop a borrowed scope pushed via pushRaw().
    void popRaw();

    /// Depth (1 = global only).
    size_t depth() const { return scopes_.size() + raw_stack_.size(); }

private:
    std::vector<std::unique_ptr<Scope>> scopes_;
    std::vector<Scope*> raw_stack_;    // borrowed scope pointers from pushRaw
};

} // namespace comal::runtime

#endif // COMAL_SCOPE_H
