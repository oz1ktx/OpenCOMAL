#ifndef COMAL_BUILTINS_H
#define COMAL_BUILTINS_H

/// @file comal_builtins.h
/// Built-in function implementations (ABS, SIN, CHR$, LEN, etc.)
/// Maps legacy _ABS.._SPLIT function codes to C++ implementations.

#include "comal_value.h"
#include <string>

namespace comal::runtime {

class Interpreter;   // forward

/// Evaluate a built-in unary function/constant by its function code.
/// @param op  legacy function code (_ABS, _SIN, etc. from comal_functions.h)
/// @param arg the evaluated argument (or dummy for constants like PI, TRUE, FALSE)
Value evalBuiltinUnary(Interpreter& interp, int op, const Value& arg);

/// Evaluate built-in binary operator RND(lo, hi).
Value evalRnd(Interpreter& interp, const Value& lo, const Value& hi);

/// Evaluate RND with no arguments (returns float in [0,1)).
Value evalRnd0(Interpreter& interp);

/// SYS(n) — numeric system function
Value evalSys(Interpreter& interp, const Value& arg);

/// SYS$(n) / SYS$(n, arg) — string system function
Value evalSyss(Interpreter& interp, const Value& arg);

} // namespace comal::runtime

#endif // COMAL_BUILTINS_H
