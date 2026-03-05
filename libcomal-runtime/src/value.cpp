/// @file value.cpp
/// Runtime Value implementation — arithmetic, comparison, coercion, printing.

#include "comal_value.h"

#include <cmath>
#include <algorithm>
#include <sstream>
#include <cstdio>
#include <climits>
#include <numeric>

namespace comal::runtime {

// ── ArrayData ───────────────────────────────────────────────────────────

int64_t ArrayData::totalItems() const {
    if (dims.empty()) return 0;
    int64_t n = 1;
    for (auto& d : dims) n *= d.size();
    return n;
}

int64_t ArrayData::flatIndex(const std::vector<int64_t>& indices) const {
    if (indices.size() != dims.size())
        throw ComalError(ErrorCode::Array, "Wrong number of array indices");

    int64_t offset = 0;
    int64_t stride = 1;
    // Row-major: last index varies fastest
    for (int i = static_cast<int>(dims.size()) - 1; i >= 0; --i) {
        int64_t idx = indices[i];
        if (idx < dims[i].bottom || idx > dims[i].top)
            throw ComalError(ErrorCode::Array,
                "Array index " + std::to_string(idx) +
                " out of bounds [" + std::to_string(dims[i].bottom) +
                ".." + std::to_string(dims[i].top) + "]");
        offset += (idx - dims[i].bottom) * stride;
        stride *= dims[i].size();
    }
    return offset;
}

// ── doubleToInt ─────────────────────────────────────────────────────────

int64_t doubleToInt(double d, bool allowTrunc) {
    if (!std::isfinite(d))
        throw ComalError(ErrorCode::F2Int1, "Cannot convert infinity/NaN to integer");

    if (!allowTrunc) {
        double intpart;
        double frac = std::modf(d, &intpart);
        if (frac != 0.0)
            throw ComalError(ErrorCode::F2Int2,
                "Float " + std::to_string(d) + " has fractional part");
    }

    if (d > static_cast<double>(INT64_MAX) || d < static_cast<double>(INT64_MIN))
        throw ComalError(ErrorCode::F2Int1,
            "Float too large to convert to integer");

    return static_cast<int64_t>(d);
}

Value promoteToFloat(const Value& v) {
    if (v.isFloat()) return v;
    if (v.isInt())   return Value(static_cast<double>(v.asInt()));
    throw ComalError(ErrorCode::Type, "Cannot promote non-numeric value to float");
}

// ── Value::toDouble / toInt ─────────────────────────────────────────────

double Value::toDouble() const {
    if (isFloat()) return asFloat();
    if (isInt())   return static_cast<double>(asInt());
    throw ComalError(ErrorCode::Type, "Expected numeric value, got string");
}

int64_t Value::toInt() const {
    if (isInt())   return asInt();
    if (isFloat()) return doubleToInt(asFloat(), true);
    throw ComalError(ErrorCode::Type, "Expected numeric value, got string");
}

// ── Arithmetic helpers (int promotion) ──────────────────────────────────

// When both operands are int, try int arithmetic; on overflow, promote to float.
static Value intOp(int64_t a, int64_t b, char op) {
    switch (op) {
    case '+': {
        // Overflow check
        if ((b > 0 && a > INT64_MAX - b) || (b < 0 && a < INT64_MIN - b))
            return Value(static_cast<double>(a) + static_cast<double>(b));
        return Value(a + b);
    }
    case '-': {
        if ((b < 0 && a > INT64_MAX + b) || (b > 0 && a < INT64_MIN + b))
            return Value(static_cast<double>(a) - static_cast<double>(b));
        return Value(a - b);
    }
    case '*': {
        // Simple overflow detection via double
        double result = static_cast<double>(a) * static_cast<double>(b);
        if (result > static_cast<double>(INT64_MAX) ||
            result < static_cast<double>(INT64_MIN))
            return Value(result);
        return Value(a * b);
    }
    default:
        return Value(int64_t{0});
    }
}

static Value floatOp(double a, double b, char op) {
    switch (op) {
    case '+': return Value(a + b);
    case '-': return Value(a - b);
    case '*': return Value(a * b);
    case '/':
        if (b == 0.0) throw ComalError(ErrorCode::Div0, "Division by zero");
        return Value(a / b);
    default:
        return Value(0.0);
    }
}

// ── Value arithmetic ────────────────────────────────────────────────────

Value Value::operator+(const Value& rhs) const {
    // String concatenation
    if (isString() && rhs.isString())
        return Value(asString() + rhs.asString());

    if (isInt() && rhs.isInt())
        return intOp(asInt(), rhs.asInt(), '+');

    return floatOp(toDouble(), rhs.toDouble(), '+');
}

Value Value::operator-(const Value& rhs) const {
    if (isInt() && rhs.isInt())
        return intOp(asInt(), rhs.asInt(), '-');
    return floatOp(toDouble(), rhs.toDouble(), '-');
}

Value Value::operator*(const Value& rhs) const {
    if (isInt() && rhs.isInt())
        return intOp(asInt(), rhs.asInt(), '*');
    return floatOp(toDouble(), rhs.toDouble(), '*');
}

Value Value::operator/(const Value& rhs) const {
    // Division always produces float in COMAL (like legacy)
    double b = rhs.toDouble();
    if (b == 0.0) throw ComalError(ErrorCode::Div0, "Division by zero");
    return Value(toDouble() / b);
}

Value Value::intDiv(const Value& rhs) const {
    int64_t b = rhs.toInt();
    if (b == 0) throw ComalError(ErrorCode::Div0, "Division by zero");
    return Value(toInt() / b);
}

Value Value::intMod(const Value& rhs) const {
    int64_t b = rhs.toInt();
    if (b == 0) throw ComalError(ErrorCode::Div0, "Division by zero");
    return Value(toInt() % b);
}

Value Value::power(const Value& rhs) const {
    return Value(std::pow(toDouble(), rhs.toDouble()));
}

Value Value::negate() const {
    if (isInt())   return Value(-asInt());
    if (isFloat()) return Value(-asFloat());
    throw ComalError(ErrorCode::Type, "Cannot negate non-numeric value");
}

// ── Comparison ──────────────────────────────────────────────────────────

int Value::compare(const Value& rhs) const {
    // String vs string
    if (isString() && rhs.isString())
        return asString().compare(rhs.asString());

    // Both numeric
    if (isNumeric() && rhs.isNumeric()) {
        double a = toDouble(), b = rhs.toDouble();
        if (a < b) return -1;
        if (a > b) return  1;
        return 0;
    }

    throw ComalError(ErrorCode::Type, "Cannot compare values of different types");
}

// ── Coercion / assignment ───────────────────────────────────────────────

void Value::assignFrom(const Value& other) {
    // Same type: direct copy
    if (type() == other.type()) {
        data_ = other.data_;
        return;
    }

    // Numeric coercions
    if (isFloat() && other.isInt()) {
        data_ = static_cast<double>(other.asInt());
        return;
    }
    if (isInt() && other.isFloat()) {
        data_ = doubleToInt(other.asFloat(), true);
        return;
    }

    // If the target is default-constructed (int 0), adopt the source type.
    // This handles first assignment to untyped variables.
    if (isInt() && asInt() == 0 && other.isString()) {
        data_ = other.data_;
        return;
    }

    throw ComalError(ErrorCode::Value,
        "Cannot assign " + other.printStr() + " to variable of incompatible type");
}

// ── Display ─────────────────────────────────────────────────────────────

std::string Value::printStr() const {
    switch (type()) {
    case Type::Int:
        return std::to_string(asInt());
    case Type::Float: {
        char buf[64];
        std::snprintf(buf, sizeof(buf), "%g", asFloat());
        return buf;
    }
    case Type::String:
        return asString();
    case Type::Array:
        return "<array>";
    }
    return "<unknown>";
}

std::ostream& operator<<(std::ostream& os, const Value& v) {
    return os << v.printStr();
}

} // namespace comal::runtime
