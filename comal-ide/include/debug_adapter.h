#pragma once

#include <QString>
#include <QVariantList>
#include <QByteArray>
#include <memory>

namespace comal::runtime { class Interpreter; }

/// Interface for debugging a language runtime.
/// Different backends (COMAL, Z80) provide different debug capabilities.
class IDebugAdapter {
public:
    virtual ~IDebugAdapter() = default;

    /// Get the current list of variables (COMAL only).
    /// Returns empty list for non-COMAL backends.
    virtual QVariantList getVariables() const = 0;

    /// Get the current call stack (COMAL only).
    /// Returns empty list for non-COMAL backends.
    virtual QVariantList getCallStack() const = 0;

    /// Get the CPU register state (Z80 only).
    /// Returns a list of {name, value} pairs.
    /// Returns empty list for non-Z80 backends.
    virtual QVariantList getRegisters() const = 0;

    /// Get flags (Z80 only).
    /// Returns {z: bool, n: bool, h: bool, pv: bool, c: bool}
    /// Returns empty map for non-Z80 backends.
    virtual QVariantList getFlags() const = 0;

    /// Get memory contents (Z80 only).
    /// Returns raw bytes from memory[address] for count bytes.
    /// Returns empty array for non-Z80 backends.
    virtual QByteArray getMemory(std::uint16_t address, std::size_t count) const = 0;

    /// Get disassembly around current PC (Z80 only).
    /// Returns a list of {address, instruction, source_line} objects.
    /// Returns empty list for non-Z80 backends.
    virtual QVariantList getDisassembly(std::uint16_t address, std::size_t count) const = 0;

    /// Get the current program counter or line number.
    /// For COMAL: returns COMAL line number.
    /// For Z80: returns PC address.
    virtual std::uint16_t getCurrentLocation() const = 0;
};

/// Factory for creating debug adapters.
class DebugAdapterFactory {
public:
    /// Create a debug adapter for the COMAL interpreter.
    static std::unique_ptr<IDebugAdapter> createComalAdapter(comal::runtime::Interpreter* interp);

    /// Create a debug adapter for Z80 machine state.
    /// The adapter does not own the state; the caller must ensure it remains valid.
    static std::unique_ptr<IDebugAdapter> createZ80Adapter(void* z80Machine);
};
