#ifndef COMAL_EXECUTOR_H
#define COMAL_EXECUTOR_H

/// @file comal_executor.h
/// Statement executor — walks ComalLine linked list and dispatches
/// each statement.  Replaces legacy exec_seq / exec_line.

#include "comal_value.h"  // for Value

namespace comal {
class ComalLine;
class ExpList;
}

namespace comal::runtime {

class Interpreter;

/// Execute a sequence of lines starting at `start`.
/// Runs until END, STOP, or the last line in the chain.
/// Throws ComalError on runtime errors.
void execSeq(Interpreter& interp, comal::ComalLine* start);

/// Execute a single statement line.
void execLine(Interpreter& interp, comal::ComalLine* line);

/// Call a user-defined FUNC and return its result.
Value execFuncCall(Interpreter& interp, const std::string& name,
                   const comal::ExpList* args);

} // namespace comal::runtime

#endif // COMAL_EXECUTOR_H
