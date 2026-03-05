#ifndef COMAL_ERROR_H
#define COMAL_ERROR_H

/// @file comal_error.h
/// Runtime error types for the COMAL interpreter.
/// Replaces legacy longjmp(ERRBUF,666) + run_error() with C++ exceptions.

#include <stdexcept>
#include <string>

namespace comal::runtime {

// ── Error codes (matching legacy pdcerr.h) ──────────────────────────────

enum class ErrorCode {
    None        = 0,
    Label       = 1,   // Label not found
    Data        = 2,   // No DATA statements / end of DATA
    Del         = 3,   // Delete file failed
    NoReturn    = 4,   // ENDFUNC without RETURN
    Direct      = 5,   // Direct-mode only error
    F2Int1      = 6,   // Float too large for int
    F2Int2      = 7,   // Float contains fractional part
    Val         = 8,   // VAL() conversion failed
    Chr         = 9,   // CHR$() of <0 or >255
    Div0        = 10,  // Division by zero
    Os          = 12,  // OS command error
    NotImpl     = 13,  // Not yet implemented
    Var         = 14,  // Variable already exists
    Dim         = 15,  // Bad dimension bounds
    Array       = 16,  // Array index out of bounds
    Substr      = 17,  // Substring out of bounds
    For         = 18,  // FOR/ENDFOR mismatch
    UnFunc      = 19,  // Unknown function
    Parm        = 20,  // Parameter error
    Value       = 21,  // Value copy type error
    Open        = 22,  // File open error
    Close       = 23,  // File close error
    Pos         = 24,  // File position error
    Write       = 25,  // File write error
    Eof         = 26,  // EOF check error
    Eod         = 27,  // End of DATA
    Type        = 28,  // Type mismatch
    Read        = 29,  // File read error
    Import      = 30,  // IMPORT error
    Name        = 31,  // NAME error
    Escape      = 32,  // Escape pressed
    Math        = 33,  // Math domain error
    Memory      = 34,  // Memory allocation error
    Select      = 35,  // SELECT INPUT/OUTPUT error
    Using       = 36,  // USING format error
    Input       = 37,  // INPUT error
    Sys         = 39,  // SYS error
    Cmd         = 40,  // Command error
    Run         = 41,  // RUN error
    Cursor      = 42,  // CURSOR error
    Id          = 43,  // Expression ID error
    Lval        = 44,  // Not an lvalue
    Scan        = 45,  // Structure scan error
    Spc         = 49,  // SPC$ error
    DirErr      = 50,  // MKDIR/CHDIR/RMDIR error
    Rnd         = 51,  // RND argument error
};

// ── Exception hierarchy ─────────────────────────────────────────────────

/// Base runtime error — replaces run_error() + longjmp
class ComalError : public std::runtime_error {
    ErrorCode code_;
    long line_;         // line number where error occurred (0 = unknown)

public:
    ComalError(ErrorCode code, const std::string& msg, long line = 0)
        : std::runtime_error(msg), code_(code), line_(line) {}

    ErrorCode code() const noexcept { return code_; }
    long line() const noexcept { return line_; }
};

/// Raised by STOP statement — not an error per se
class StopSignal : public std::exception {
public:
    const char* what() const noexcept override { return "STOP"; }
};

/// Raised by END statement — normal termination
class EndSignal : public std::exception {
public:
    const char* what() const noexcept override { return "END"; }
};

/// Raised by EXIT statement inside a loop
class ExitSignal : public std::exception {
public:
    const char* what() const noexcept override { return "EXIT"; }
};

/// Raised by RETURN statement — carries the sentinel back up the call stack
class ReturnSignal : public std::exception {
public:
    const char* what() const noexcept override { return "RETURN"; }
};

/// Raised by RETRY inside a HANDLER — re-execute the TRAP body
class RetrySignal : public std::exception {
public:
    const char* what() const noexcept override { return "RETRY"; }
};

/// Raised by ESC key (if ESC is allowed)
class EscapeSignal : public std::exception {
public:
    const char* what() const noexcept override { return "ESCAPE"; }
};

} // namespace comal::runtime

#endif // COMAL_ERROR_H
