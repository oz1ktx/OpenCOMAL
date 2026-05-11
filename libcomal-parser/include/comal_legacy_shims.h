/// @file comal_legacy_shims.h
/// Accessor functions for legacy C AST types (id_rec, string).
///
/// Runtime code must call these instead of accessing legacy struct fields
/// directly. This creates a clean isolation boundary so that comal_ast.h
/// can be eliminated from the runtime include path during Phase 3 of the
/// AST modernization plan (see docs/AST_MODERNIZATION.md).
///
/// This header may include comal_ast.h because it lives in the parser library
/// which owns those types. Runtime code must NOT include comal_ast.h directly.

#pragma once

#include "comal_ast.h"

#include <cstddef>
#include <string>

/// Return the name of a legacy id_rec, or nullptr if id is null.
inline const char* comal_id_name(const struct id_rec* id) {
    return id ? id->name : nullptr;
}

/// Return true when the id_rec is declared as a FLOAT-typed variable.
inline bool comal_id_is_float(const struct id_rec* id) {
    return id && id->type == V_FLOAT;
}

/// Return true when the id_rec is declared as a STRING-typed variable.
inline bool comal_id_is_string(const struct id_rec* id) {
    return id && id->type == V_STRING;
}

/// Convert a pool-allocated legacy string to a C++ std::string.
inline std::string comal_string_to_cpp(const struct string* str) {
    if (!str) return {};
    return std::string(str->s, static_cast<std::size_t>(str->len));
}
