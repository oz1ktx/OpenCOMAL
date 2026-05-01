/// @file builtins.cpp
/// Built-in function implementations (ABS, SIN, CHR$, LEN, etc.)

#include "comal_builtins.h"
#include "comal_interpreter.h"
#include "comal_functions.h"

#include <cmath>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <unistd.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace comal::runtime {

// ── Helpers ─────────────────────────────────────────────────────────────

static Value makeString(const std::string& s) { return Value(s); }
static Value makeInt(int64_t n) { return Value(n); }
static Value makeFloat(double d) { return Value(d); }

// ── evalBuiltinUnary ────────────────────────────────────────────────────

Value evalBuiltinUnary(Interpreter& interp, int op, const Value& arg) {
    switch (op) {

    // ── Constants ───────────────────────────────────────────────────────
    case _PI:    return makeFloat(M_PI);
    case _TRUE:  return makeInt(1);
    case _FALSE: return makeInt(0);

    // ── Error state ─────────────────────────────────────────────────────
    case _ERR:     return makeInt(static_cast<int64_t>(interp.lastError));
    case _ERRTEXT: return makeString(interp.lastErrorMsg);
    case _ERRLINE: return makeInt(interp.lastErrorLine);

    // ── Math: double → double ───────────────────────────────────────────
    case _ABS: {
        if (arg.isInt()) return makeInt(std::abs(arg.asInt()));
        return makeFloat(std::fabs(arg.toDouble()));
    }
    case _ACS: return makeFloat(std::acos(arg.toDouble()));
    case _ASN: return makeFloat(std::asin(arg.toDouble()));
    case _ATN: return makeFloat(std::atan(arg.toDouble()));
    case _COS: return makeFloat(std::cos(arg.toDouble()));
    case _SIN: return makeFloat(std::sin(arg.toDouble()));
    case _TAN: return makeFloat(std::tan(arg.toDouble()));
    case _EXP: return makeFloat(std::exp(arg.toDouble()));
    case _LN:  return makeFloat(std::log(arg.toDouble()));
    case _LOG: return makeFloat(std::log10(arg.toDouble()));
    case _SQR: return makeFloat(std::sqrt(arg.toDouble()));

    case _INT: return makeInt(static_cast<int64_t>(std::floor(arg.toDouble())));

    case _SGN: {
        double d = arg.toDouble();
        if (d < 0) return makeInt(-1);
        if (d > 0) return makeInt(1);
        return makeInt(0);
    }

    case _DEG: return makeFloat(arg.toDouble() * 180.0 / M_PI);
    case _RAD: return makeFloat(arg.toDouble() * M_PI / 180.0);

    case _FRAC: {
        double intpart;
        return makeFloat(std::modf(arg.toDouble(), &intpart));
    }

    case _ROUND: return makeFloat(std::round(arg.toDouble()));

    case _NOT: return makeInt(arg.toInt() ? 0 : 1);

    // ── String functions ────────────────────────────────────────────────
    case _LEN:
        if (arg.isArray())
            return makeInt(static_cast<int64_t>(arg.asArray().elements.size()));
        return makeInt(static_cast<int64_t>(arg.asString().size()));

    case _ORD: {
        const std::string& s = arg.asString();
        if (s.empty())
            throw ComalError(ErrorCode::Chr, "ORD() of empty string");
        return makeInt(static_cast<int64_t>(static_cast<unsigned char>(s[0])));
    }

    case _CHR: {
        int64_t n = arg.toInt();
        if (n < 0 || n > 255)
            throw ComalError(ErrorCode::Chr,
                "CHR$() argument " + std::to_string(n) + " out of range 0..255");
        return makeString(std::string(1, static_cast<char>(n)));
    }

    case _SPC: {
        int64_t n = arg.toInt();
        if (n < 0)
            throw ComalError(ErrorCode::Spc, "SPC$() argument must be >= 0");
        return makeString(std::string(n, ' '));
    }

    case _STR: {
        // Number → string representation
        if (arg.isInt())
            return makeString(std::to_string(arg.asInt()));
        char buf[64];
        std::snprintf(buf, sizeof(buf), "%g", arg.toDouble());
        return makeString(std::string(buf));
    }

    case _VAL: {
        // String → number
        const std::string& s = arg.asString();
        try {
            size_t pos;
            // Try integer first
            long long ll = std::stoll(s, &pos);
            if (pos == s.size())
                return makeInt(static_cast<int64_t>(ll));
            // Otherwise try float
            double d = std::stod(s, &pos);
            if (pos == s.size())
                return makeFloat(d);
        } catch (...) {}
        throw ComalError(ErrorCode::Val,
            "VAL(\"" + s + "\") — cannot convert to number");
    }

    case _UPPER: {
        std::string s = arg.asString();
        std::transform(s.begin(), s.end(), s.begin(),
                       [](unsigned char c) { return std::toupper(c); });
        return makeString(std::move(s));
    }

    case _LOWER: {
        std::string s = arg.asString();
        std::transform(s.begin(), s.end(), s.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        return makeString(std::move(s));
    }

    // ── I/O functions (stubs) ───────────────────────────────────────────
    case _EOF: {
        int64_t fno = arg.toInt();
        return makeInt(interp.files.isEof(fno) ? 1 : 0);
    }

    case _EOD: {
        // End of DATA?
        return makeInt((interp.dataExp == nullptr) ? 1 : 0);
    }

    case _KEY: {
        // KEY() — not available in batch mode
        return makeString(std::string{});
    }

    case _INKEY: {
        // INKEY$() — not available in batch mode
        return makeString(std::string{});
    }

    // ── RND with zero args → random float in [0,1) ─────────────────────
    case _RND:
        return evalRnd0(interp);

    // ── Directory functions ─────────────────────────────────────────────
    case _DIR: {
        // Return current directory
        char buf[4096];
        if (getcwd(buf, sizeof(buf)))
            return makeString(std::string(buf));
        return makeString(std::string{});
    }

    case _UNIT: {
        // Same as DIR on Linux
        char buf[4096];
        if (getcwd(buf, sizeof(buf)))
            return makeString(std::string(buf));
        return makeString(std::string{});
    }

    default:
        throw ComalError(ErrorCode::UnFunc,
            "Unknown built-in function code " + std::to_string(op));
    }
}

// ── RND ─────────────────────────────────────────────────────────────────

Value evalRnd(Interpreter& interp, const Value& lo, const Value& hi) {
    if (lo.isFloat() || hi.isFloat()) {
        double dlo = lo.toDouble(), dhi = hi.toDouble();
        if (dlo >= dhi)
            throw ComalError(ErrorCode::Rnd, "RND(x,y) argument error (x>=y)");
        std::uniform_real_distribution<double> dist(dlo, dhi);
        return makeFloat(dist(interp.rng));
    }
    int64_t ilo = lo.toInt(), ihi = hi.toInt();
    if (ilo == ihi) return makeInt(ilo);
    if (ilo > ihi)
        throw ComalError(ErrorCode::Rnd, "RND(x,y) argument error (x>=y)");
    std::uniform_int_distribution<int64_t> dist(ilo, ihi);
    return makeInt(dist(interp.rng));
}

Value evalRnd0(Interpreter& interp) {
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    return makeFloat(dist(interp.rng));
}

// ── SYS ─────────────────────────────────────────────────────────────────

Value evalSys(Interpreter& interp, const std::string& cmd_in) {
    (void)interp;
    std::string cmd = cmd_in;
    for (auto& c : cmd) c = std::toupper(static_cast<unsigned char>(c));
    if (cmd == "VERSION") {
        return Value(0.26);  // matches legacy OPENCOMAL_VERSION "0.2.6"
    }
    // Flag queries return 0/1
    if (cmd == "PROG_TRACE")
        return Value(int64_t{interp.trace ? 1 : 0});
    if (cmd == "DEBUG" || cmd == "YYDEBUG" || cmd == "SHOW_EXEC" || cmd == "SHORT_CIRCUIT")
        return Value(int64_t{0});
    throw ComalError(ErrorCode::Sys, "Unknown SYS command: " + cmd);
}

Value evalSyss(Interpreter& interp, const std::string& cmd_in) {
    (void)interp;
    std::string cmd = cmd_in;
    for (auto& c : cmd) c = std::toupper(static_cast<unsigned char>(c));
    if (cmd == "HOST")
        return Value(std::string("Linux"));
    if (cmd == "INTERPRETER")
        return Value(std::string("OpenComal"));
    if (cmd == "VERSION")
        return Value(std::string("0.2.6"));
    // Flag queries return "on"/"off"
    if (cmd == "PROG_TRACE")
        return Value(std::string(interp.trace ? "on" : "off"));
    if (cmd == "DEBUG" || cmd == "YYDEBUG" || cmd == "SHOW_EXEC" || cmd == "SHORT_CIRCUIT")
        return Value(std::string("off"));
    throw ComalError(ErrorCode::Sys, "Unknown SYS$ command: " + cmd);
}

Value evalSplit(Interpreter& interp, const Value& str, const Value& sep, const Value& idx) {
    (void)interp;
    const std::string& s = str.asString();
    const std::string& delim = sep.asString();
    int64_t index = idx.toInt();

    if (index < 1)
        return Value(std::string{});

    if (delim.empty()) {
        // No separator: each character is a substring
        if (index > static_cast<int64_t>(s.size()))
            return Value(std::string{});
        return Value(std::string(1, s[index - 1]));
    }

    // Walk through substrings separated by delim
    int64_t count = 0;
    size_t pos = 0;
    while (pos <= s.size()) {
        size_t next = s.find(delim, pos);
        ++count;
        if (count == index) {
            if (next == std::string::npos)
                return Value(s.substr(pos));
            return Value(s.substr(pos, next - pos));
        }
        if (next == std::string::npos)
            break;
        pos = next + delim.size();
    }

    return Value(std::string{});
}

} // namespace comal::runtime
