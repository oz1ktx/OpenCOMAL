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

/// SYS(cmd) — numeric system function (cmd is identifier name, e.g. "VERSION")
Value evalSys(Interpreter& interp, const std::string& cmd);

/// SYS$(cmd) — string system function (cmd is identifier name, e.g. "HOST")
Value evalSyss(Interpreter& interp, const std::string& cmd);

/// SPLIT$(str, sep, index) — return the index'th substring of str split by sep.
Value evalSplit(Interpreter& interp, const Value& str, const Value& sep, const Value& idx);

} // namespace comal::runtime

#endif // COMAL_BUILTINS_H
