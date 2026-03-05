/// @file scope.cpp
/// Scope / symbol-table implementation.

#include "comal_scope.h"
#include "comal_error.h"

namespace comal::runtime {

// ── Scope: local lookup ─────────────────────────────────────────────────

Symbol* Scope::findLocal(const std::string& name) {
    auto it = symbols_.find(name);
    return (it != symbols_.end()) ? &it->second : nullptr;
}

// ── Scope: walk-up lookup (respects CLOSED) ─────────────────────────────

Symbol* Scope::find(const std::string& name) {
    // Search this scope first
    if (Symbol* s = findLocal(name))
        return s;

    // If this scope is CLOSED, stop here (don't walk up)
    if (closed)
        return nullptr;

    // Try parent
    if (parent)
        return parent->find(name);

    return nullptr;
}

// ── Scope: define ───────────────────────────────────────────────────────

Symbol& Scope::define(const std::string& name, Value&& initial) {
    auto [it, inserted] = symbols_.emplace(name, Symbol{});
    if (!inserted)
        throw ComalError(ErrorCode::Var, "Variable '" + name + "' already exists");
    it->second.kind = SymbolKind::Variable;
    it->second.value = std::move(initial);
    return it->second;
}

Symbol& Scope::defineRef(const std::string& name, Value* target) {
    auto [it, inserted] = symbols_.emplace(name, Symbol{});
    if (!inserted)
        throw ComalError(ErrorCode::Var,
            "REF variable '" + name + "' already exists");
    it->second.kind = SymbolKind::RefAlias;
    it->second.ref_target = target;
    return it->second;
}

Symbol& Scope::defineProcFunc(const std::string& name, SymbolKind kind,
                               ComalLine* routine) {
    auto [it, inserted] = symbols_.emplace(name, Symbol{});
    if (!inserted)
        throw ComalError(ErrorCode::Var,
            "PROC/FUNC variable '" + name + "' already exists");
    it->second.kind = kind;
    it->second.routine_line = routine;
    return it->second;
}

void Scope::importSymbol(const std::string& symbolName) {
    // Walk up to find the symbol in an ancestor scope
    Symbol* outer = parent ? parent->find(symbolName) : nullptr;
    if (!outer)
        throw ComalError(ErrorCode::Import,
            "Cannot IMPORT '" + symbolName + "' — not found in outer scope");

    // Create a ref alias in this scope pointing to the outer value
    auto [it, inserted] = symbols_.emplace(symbolName, Symbol{});
    if (!inserted)
        throw ComalError(ErrorCode::Import,
            "'" + symbolName + "' already exists in local scope");

    it->second.kind = SymbolKind::RefAlias;
    it->second.ref_target = &outer->resolve();
}

void Scope::clear() {
    symbols_.clear();
}

// ── ScopeStack ──────────────────────────────────────────────────────────

ScopeStack::ScopeStack() {
    // Create the global scope
    auto g = std::make_unique<Scope>();
    g->name = "GLOBAL";
    g->closed = false;
    g->level = 0;
    scopes_.push_back(std::move(g));
}

Scope& ScopeStack::push(const std::string& name, bool closed,
                          ComalLine* proc, int level) {
    auto s = std::make_unique<Scope>();
    s->parent = scopes_.back().get();
    s->name = name;
    s->closed = closed;
    s->curproc = proc;
    s->level = level;
    scopes_.push_back(std::move(s));
    return *scopes_.back();
}

void ScopeStack::pop() {
    if (scopes_.size() <= 1)
        throw ComalError(ErrorCode::Parm, "Cannot pop the global scope");
    scopes_.pop_back();
}

} // namespace comal::runtime
