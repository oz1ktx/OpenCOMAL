/// @file evaluator.cpp
/// Expression evaluator — walks the modern Expression AST and produces Values.
/// Replaces legacy calc_exp() / exptab[] dispatch.

#include "comal_evaluator.h"
#include "comal_builtins.h"
#include "comal_interpreter.h"
#include "comal_executor.h"      // execFuncCall
#include "comal_ast.h"           // full definitions: id_rec, string, VAL_TYPE, etc.
#include "comal_ast_modern.h"
#include "comal_functions.h"
#include "parser.tab.h"          // token constants (plusSYM, minusSYM, ...)

#include <cmath>
#include <algorithm>
#include <cctype>

namespace comal::runtime {

// ── Forward declarations ────────────────────────────────────────────────

static Value evalBinary(Interpreter& interp, int op,
                        const comal::Expression* left,
                        const comal::Expression* right);
static Value evalUnary(Interpreter& interp, int op,
                       const comal::Expression* operand);
static Value evalId(Interpreter& interp, const comal::ExpId& eid);
static Value evalSid(Interpreter& interp, const comal::ExpSid& esid);
static Value evalArrayElem(Interpreter& interp, const comal::ExpList* indices,
                           Symbol* sym);
static Value evalSubstr(Interpreter& interp, const comal::ExpSubstr& sub);

// ── Helpers ─────────────────────────────────────────────────────────────

/// Get the name of an id_rec (legacy struct)
static std::string idName(const id_rec* id) {
    return id ? id->name : "<null>";
}

// ── Main entry point ────────────────────────────────────────────────────

Value evaluate(Interpreter& interp, const comal::Expression* expr) {
    if (!expr)
        throw ComalError(ErrorCode::Id, "Null expression");

    switch (expr->opType()) {
    case OpType::IntNum:
        return Value(expr->asNum());

    case OpType::Float:
        return Value(expr->asFloat());

    case OpType::String: {
        // Legacy string* → C++ std::string
        const auto* str = expr->asString();
        if (!str) return Value(std::string{});
        return Value(std::string(str->s, str->len));
    }

    case OpType::Const:
        // Named constants (TRUE, FALSE, PI, etc.)
        return evalBuiltinUnary(interp, expr->op(), Value{});

    case OpType::Unary:
        return evalUnary(interp, expr->op(), expr->asExp());

    case OpType::Binary: {
        const auto& te = expr->asTwoExp();
        return evalBinary(interp, expr->op(), te.exp1, te.exp2);
    }

    case OpType::Id: {
        const auto& eid = std::get<comal::ExpId>(expr->data());
        return evalId(interp, eid);
    }

    case OpType::Sid: {
        const auto& esid = std::get<comal::ExpSid>(expr->data());
        return evalSid(interp, esid);
    }

    case OpType::Array:
    case OpType::Sarray: {
        // Array element or function call with parenthesized args
        // If the expression has an ExpList, it could be an array subscript
        // or a FUNC call — we disambiguate at lookup time.
        const auto& eid = std::get<comal::ExpId>(expr->data());
        return evalId(interp, eid);
    }

    case OpType::Substr: {
        const auto& sub = std::get<comal::ExpSubstr>(expr->data());
        return evalSubstr(interp, sub);
    }

    case OpType::Sys: {
        const auto* subexpr = std::get_if<comal::Expression*>(&expr->data());
        if (!subexpr || !*subexpr) {
            // SYS with ExpList (from e.exproot)
            const auto* elist = std::get_if<comal::ExpList*>(&expr->data());
            if (elist && *elist) {
                Value arg = evaluate(interp, (*elist)->exp());
                return evalSys(interp, arg);
            }
            return evalSys(interp, Value{int64_t{0}});
        }
        Value arg = evaluate(interp, *subexpr);
        return evalSys(interp, arg);
    }

    case OpType::Syss: {
        const auto* subexpr = std::get_if<comal::Expression*>(&expr->data());
        if (!subexpr || !*subexpr) {
            const auto* elist = std::get_if<comal::ExpList*>(&expr->data());
            if (elist && *elist) {
                Value arg = evaluate(interp, (*elist)->exp());
                return evalSyss(interp, arg);
            }
            return evalSyss(interp, Value{int64_t{0}});
        }
        Value arg = evaluate(interp, *subexpr);
        return evalSyss(interp, arg);
    }

    case OpType::ExpIsNum:
    case OpType::ExpIsString: {
        // Type-tagged wrapper — just unwrap and evaluate the inner expression
        const auto* inner = expr->asExp();
        return evaluate(interp, inner);
    }

    default:
        throw ComalError(ErrorCode::Id,
            "Unknown expression optype " + std::to_string(static_cast<int>(expr->opType())));
    }
}

// ── Binary expressions ──────────────────────────────────────────────────

static Value evalBinary(Interpreter& interp, int op,
                        const comal::Expression* left,
                        const comal::Expression* right) {
    // Short-circuit logical operators
    if (op == andthenSYM) {
        Value lv = evaluate(interp, left);
        if (lv.toInt() == 0) return Value(int64_t{0});
        return Value(evaluate(interp, right).toInt() ? int64_t{1} : int64_t{0});
    }
    if (op == orthenSYM) {
        Value lv = evaluate(interp, left);
        if (lv.toInt() != 0) return Value(int64_t{1});
        return Value(evaluate(interp, right).toInt() ? int64_t{1} : int64_t{0});
    }

    // RND(lo, hi) — special form
    if (op == _RND) {
        Value lo = evaluate(interp, left);
        Value hi = evaluate(interp, right);
        return evalRnd(interp, lo, hi);
    }

    Value lv = evaluate(interp, left);
    Value rv = evaluate(interp, right);

    // Logical operators (non-short-circuit)
    if (op == andSYM)
        return Value(int64_t{(lv.toInt() && rv.toInt()) ? 1 : 0});
    if (op == orSYM)
        return Value(int64_t{(lv.toInt() || rv.toInt()) ? 1 : 0});
    if (op == eorSYM)
        return Value(int64_t{(lv.toInt() != 0) != (rv.toInt() != 0) ? 1 : 0});

    // Relational operators
    switch (op) {
    case eqlSYM:  return Value(int64_t{lv == rv ? 1 : 0});
    case neqSYM:  return Value(int64_t{lv != rv ? 1 : 0});
    case lssSYM:  return Value(int64_t{lv <  rv ? 1 : 0});
    case leqSYM:  return Value(int64_t{lv <= rv ? 1 : 0});
    case gtrSYM:  return Value(int64_t{lv >  rv ? 1 : 0});
    case geqSYM:  return Value(int64_t{lv >= rv ? 1 : 0});
    default: break;
    }

    // String concatenation
    if (lv.isString() && rv.isString() && op == plusSYM)
        return lv + rv;

    // Arithmetic operators
    switch (op) {
    case plusSYM:    return lv + rv;
    case minusSYM:  return lv - rv;
    case timesSYM:  return lv * rv;
    case divideSYM: return lv / rv;
    case divSYM:    return lv.intDiv(rv);
    case modSYM:    return lv.intMod(rv);
    case powerSYM:  return lv.power(rv);
    case inSYM: {
        // a IN b — substring test: returns position or 0
        if (!lv.isString() || !rv.isString())
            throw ComalError(ErrorCode::Type, "IN requires string operands");
        auto pos = rv.asString().find(lv.asString());
        return Value(int64_t{pos != std::string::npos ? static_cast<int64_t>(pos + 1) : 0});
    }
    default:
        throw ComalError(ErrorCode::Id,
            "Unknown binary operator " + std::to_string(op));
    }
}

// ── Unary expressions ───────────────────────────────────────────────────

static Value evalUnary(Interpreter& interp, int op,
                       const comal::Expression* operand) {
    // Parenthesized expression or unary plus — just pass through
    if (op == lparenSYM || op == plusSYM)
        return evaluate(interp, operand);

    // Unary minus
    if (op == minusSYM)
        return evaluate(interp, operand).negate();

    // Built-in function — delegate to builtins
    Value arg = evaluate(interp, operand);
    return evalBuiltinUnary(interp, op, arg);
}

// ── Variable lookup (Id) ────────────────────────────────────────────────

static Value evalId(Interpreter& interp, const comal::ExpId& eid) {
    std::string name = idName(eid.id);

    // Check if it's a function call first
    if (eid.exproot) {
        // Could be a FUNC call or an array subscript
        Symbol* sym = interp.scopes.current().find(name);
        if (sym) {
            if (sym->resolve().isArray()) {
                return evalArrayElem(interp, eid.exproot, sym);
            }
            // If it's a FUNC reference, call it
            if (sym->kind == SymbolKind::FuncRef) {
                // TODO: call through func reference
                throw ComalError(ErrorCode::NotImpl,
                    "FUNC variable call not yet implemented");
            }
        }

        // Check the proc table for a user-defined FUNC
        auto it = interp.procTable.find(name);
        if (it != interp.procTable.end()) {
            return execFuncCall(interp, name, eid.exproot);
        }

        throw ComalError(ErrorCode::Id, "Unknown function or array '" + name + "'");
    }

    // Simple variable lookup
    Symbol* sym = interp.scopes.current().find(name);
    if (!sym) {
        // Auto-create numeric variables as 0, string variables as ""
        // (COMAL auto-initializes on first reference)
        Value init;
        if (eid.id && eid.id->type == V_STRING)
            init = Value(std::string{});
        else
            init = Value(int64_t{0});
        sym = &interp.scopes.current().define(name, std::move(init));
    }

    return sym->resolve();
}

// ── String variable lookup (Sid) ────────────────────────────────────────

static Value evalSid(Interpreter& interp, const comal::ExpSid& esid) {
    std::string name = idName(esid.id);

    // If there are arguments, check for FUNC call first
    if (esid.exproot) {
        auto it = interp.procTable.find(name);
        if (it != interp.procTable.end()) {
            return execFuncCall(interp, name, esid.exproot);
        }
    }

    // Look up the variable
    Symbol* sym = interp.scopes.current().find(name);
    if (!sym) {
        // Auto-create string variable
        sym = &interp.scopes.current().define(name, Value(std::string{}));
    }

    Value base;
    if (esid.exproot) {
        // Array element access
        if (sym->resolve().isArray()) {
            base = evalArrayElem(interp, esid.exproot, sym);
        } else {
            throw ComalError(ErrorCode::Array,
                "'" + name + "' is not an array");
        }
    } else {
        base = sym->resolve();
    }

    // Apply substring if present
    if (esid.twoexp) {
        if (!base.isString())
            throw ComalError(ErrorCode::Type,
                "Substring applied to non-string variable");

        const std::string& s = base.asString();
        int64_t from = 1, to = static_cast<int64_t>(s.size());

        if (esid.twoexp->exp1)
            from = evalInt(interp, esid.twoexp->exp1);
        if (esid.twoexp->exp2)
            to = evalInt(interp, esid.twoexp->exp2);

        if (from < 1) from = 1;
        if (to > static_cast<int64_t>(s.size()))
            to = static_cast<int64_t>(s.size());
        if (from > to)
            return Value(std::string{});

        return Value(s.substr(from - 1, to - from + 1));
    }

    return base;
}

// ── Array element access ────────────────────────────────────────────────

static Value evalArrayElem(Interpreter& interp, const comal::ExpList* indices,
                           Symbol* sym) {
    // Evaluate all index expressions
    std::vector<int64_t> idx;
    for (const comal::ExpList* node = indices; node; node = node->next()) {
        idx.push_back(evalInt(interp, node->exp()));
    }

    ArrayData& arr = sym->resolve().asArray();
    int64_t flat = arr.flatIndex(idx);
    return arr.elements[flat];
}

// ── Substring expression ────────────────────────────────────────────────

static Value evalSubstr(Interpreter& interp, const comal::ExpSubstr& sub) {
    Value base = evaluate(interp, sub.exp);
    if (!base.isString())
        throw ComalError(ErrorCode::Type, "Substring of non-string expression");

    const std::string& s = base.asString();
    int64_t from = 1, to = static_cast<int64_t>(s.size());

    if (sub.twoexp.exp1)
        from = evalInt(interp, sub.twoexp.exp1);
    if (sub.twoexp.exp2)
        to = evalInt(interp, sub.twoexp.exp2);

    if (from < 1) from = 1;
    if (to > static_cast<int64_t>(s.size()))
        to = static_cast<int64_t>(s.size());
    if (from > to)
        return Value(std::string{});

    return Value(s.substr(from - 1, to - from + 1));
}

// ── Typed evaluation wrappers ───────────────────────────────────────────

int64_t evalInt(Interpreter& interp, const comal::Expression* expr) {
    return evaluate(interp, expr).toInt();
}

double evalFloat(Interpreter& interp, const comal::Expression* expr) {
    return evaluate(interp, expr).toDouble();
}

std::string evalString(Interpreter& interp, const comal::Expression* expr) {
    Value v = evaluate(interp, expr);
    if (!v.isString())
        throw ComalError(ErrorCode::Type, "Expected string expression");
    return v.asString();
}

std::vector<Value> evalList(Interpreter& interp, const comal::ExpList* list) {
    std::vector<Value> result;
    for (auto* node = list; node; node = node->next())
        result.push_back(evaluate(interp, node->exp()));
    return result;
}

std::vector<int64_t> evalIntList(Interpreter& interp, const comal::ExpList* list) {
    std::vector<int64_t> result;
    for (auto* node = list; node; node = node->next())
        result.push_back(evalInt(interp, node->exp()));
    return result;
}

} // namespace comal::runtime
