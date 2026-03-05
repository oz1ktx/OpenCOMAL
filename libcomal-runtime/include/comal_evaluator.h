#ifndef COMAL_EVALUATOR_H
#define COMAL_EVALUATOR_H

/// @file comal_evaluator.h
/// Expression evaluator — walks the modern Expression AST and produces
/// runtime Values.  Replaces legacy calc_exp / exptab[] dispatch.

#include "comal_value.h"

// Forward declarations from parser
namespace comal {
class Expression;
class ExpList;
}

namespace comal::runtime {

class Interpreter;   // forward — evaluator needs access to interpreter state

/// Evaluate a single expression tree into a Value.
/// The Interpreter reference provides access to variables, files, etc.
Value evaluate(Interpreter& interp, const comal::Expression* expr);

/// Evaluate an expression and require an integer result.
int64_t evalInt(Interpreter& interp, const comal::Expression* expr);

/// Evaluate an expression and require a float result (int → promoted).
double evalFloat(Interpreter& interp, const comal::Expression* expr);

/// Evaluate an expression and require a string result.
std::string evalString(Interpreter& interp, const comal::Expression* expr);

/// Evaluate an expression list into a vector of Values.
std::vector<Value> evalList(Interpreter& interp, const comal::ExpList* list);

/// Evaluate an expression list and return the count of elements.
std::vector<int64_t> evalIntList(Interpreter& interp, const comal::ExpList* list);

} // namespace comal::runtime

#endif // COMAL_EVALUATOR_H
