#ifndef COMAL_VALUE_H
#define COMAL_VALUE_H

/// @file comal_value.h
/// Runtime value type for the COMAL interpreter.
/// Replaces legacy VAL_TYPE enum + void* value cells with a type-safe variant.

#include <cstdint>
#include <string>
#include <variant>
#include <vector>
#include <ostream>

#include "comal_error.h"

namespace comal::runtime {

// ── Array descriptor ────────────────────────────────────────────────────

/// One dimension: [bottom..top]
struct ArrayDim {
    int64_t bottom;
    int64_t top;

    int64_t size() const { return top - bottom + 1; }
};

// Forward declaration
class Value;

/// Array storage — flat vector + dimension info
struct ArrayData {
    std::vector<ArrayDim> dims;
    std::vector<Value> elements;     // row-major order
    int64_t string_len{0};           // for string arrays: max element length (0 = unlimited)

    /// Total number of elements
    int64_t totalItems() const;

    /// Convert multi-index to flat offset (bounds-checked)
    int64_t flatIndex(const std::vector<int64_t>& indices) const;
};

// ── Value type ──────────────────────────────────────────────────────────

/// The runtime value: int, float, string, or array.
/// Replaces legacy union var_data + VAL_TYPE enum.
class Value {
public:
    using Data = std::variant<
        int64_t,                 // integer
        double,                  // float
        std::string,             // string
        ArrayData                // array (of int, float, or string)
    >;

    enum class Type : uint8_t { Int, Float, String, Array };

private:
    Data data_;

public:
    // ── Constructors ────────────────────────────────────────────────────
    Value() : data_(int64_t{0}) {}
    explicit Value(int64_t v) : data_(v) {}
    explicit Value(double v) : data_(v) {}
    explicit Value(const std::string& v) : data_(v) {}
    explicit Value(std::string&& v) : data_(std::move(v)) {}
    explicit Value(ArrayData&& a) : data_(std::move(a)) {}

    // ── Type queries ────────────────────────────────────────────────────
    Type type() const { return static_cast<Type>(data_.index()); }
    bool isInt()    const { return type() == Type::Int; }
    bool isFloat()  const { return type() == Type::Float; }
    bool isString() const { return type() == Type::String; }
    bool isArray()  const { return type() == Type::Array; }
    bool isNumeric() const { return isInt() || isFloat(); }

    // ── Value access ────────────────────────────────────────────────────
    int64_t            asInt()    const { return std::get<int64_t>(data_); }
    double             asFloat()  const { return std::get<double>(data_); }
    const std::string& asString() const { return std::get<std::string>(data_); }
    std::string&       asString()       { return std::get<std::string>(data_); }
    const ArrayData&   asArray()  const { return std::get<ArrayData>(data_); }
    ArrayData&         asArray()        { return std::get<ArrayData>(data_); }

    /// Return numeric value as double (int or float). Throws on string/array.
    double toDouble() const;

    /// Return numeric value as int64 (may truncate float). Throws on string/array.
    int64_t toInt() const;

    // ── Arithmetic (returns new Value) ──────────────────────────────────
    Value operator+(const Value& rhs) const;   // also string concat
    Value operator-(const Value& rhs) const;
    Value operator*(const Value& rhs) const;
    Value operator/(const Value& rhs) const;
    Value intDiv(const Value& rhs) const;      // DIV
    Value intMod(const Value& rhs) const;      // MOD
    Value power(const Value& rhs) const;       // ^
    Value negate() const;                      // unary minus

    // ── Comparison ──────────────────────────────────────────────────────
    int compare(const Value& rhs) const;       // <0, 0, >0
    bool operator==(const Value& rhs) const { return compare(rhs) == 0; }
    bool operator!=(const Value& rhs) const { return compare(rhs) != 0; }
    bool operator< (const Value& rhs) const { return compare(rhs) <  0; }
    bool operator<=(const Value& rhs) const { return compare(rhs) <= 0; }
    bool operator> (const Value& rhs) const { return compare(rhs) >  0; }
    bool operator>=(const Value& rhs) const { return compare(rhs) >= 0; }

    // ── Coercion / assignment ───────────────────────────────────────────
    /// Assign from another value, coercing types as COMAL requires:
    ///  int ← float  (truncation), float ← int (promotion),
    ///  string ← string only, etc.
    void assignFrom(const Value& other);

    // ── Display ─────────────────────────────────────────────────────────
    /// Format for PRINT output (matches legacy val_print behaviour)
    std::string printStr() const;

    /// Stream insertion
    friend std::ostream& operator<<(std::ostream& os, const Value& v);
};

// ── Helpers ─────────────────────────────────────────────────────────────

/// Safe double → int64_t, raising ComalError on overflow/frac
int64_t doubleToInt(double d, bool allowTrunc = false);

/// Promote an int Value to float if needed for arithmetic
Value promoteToFloat(const Value& v);

} // namespace comal::runtime

#endif // COMAL_VALUE_H
