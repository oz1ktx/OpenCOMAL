#pragma once

#include <cstdint>
#include <optional>
#include <QString>
#include <string>
#include <vector>
#include "language_profile.h"

namespace comal::runtime { class Interpreter; }

enum class DiagnosticSeverity {
    Error,
    Warning,
    Information,
    Hint,
};

struct AssemblerDiagnostic {
    int line{0};
    int column{0};
    QString message;
    DiagnosticSeverity severity{DiagnosticSeverity::Error};
};

struct AssemblerResult {
    bool ok{false};
    QString outputPath;
    QString listingPath;
    QString consoleOutput;  // Raw stdout/stderr from assembler
    std::vector<AssemblerDiagnostic> diagnostics;
};

class IZ80Assembler {
public:
    virtual ~IZ80Assembler() = default;
    virtual AssemblerResult assembleFile(const QString& sourcePath, const QString& outputDirectory) = 0;
};

struct Z80DebugRegister {
    std::string name;
    std::uint16_t value{0};
    int width{4};
};

struct Z80DebugFlag {
    std::string name;
    bool value{false};
};

struct Z80DisassemblyLine {
    std::uint16_t address{0};
    std::vector<std::uint8_t> bytes;
    std::string instruction;
    int sourceLine{0};
    bool current{false};
};

struct Z80DebugSnapshot {
    std::vector<Z80DebugRegister> registers;
    std::vector<Z80DebugFlag> flags;
    std::uint16_t memoryStart{0};
    std::vector<std::uint8_t> memory;
    std::vector<Z80DisassemblyLine> disassembly;
};

class IBackendExecutionControl {
public:
    virtual ~IBackendExecutionControl() = default;

    /// Return true when the currently running program should stop promptly.
    virtual bool stopRequested() const = 0;

    /// Return true when execution should suspend before running the instruction
    /// at the supplied source location / program counter.
    virtual bool shouldPause(std::uint16_t programCounter, int sourceLine) = 0;

    /// Notify the control object that execution suspended, provide a debug
    /// snapshot, and let it block until the program should resume.
    virtual void waitUntilResumed(std::uint16_t programCounter,
                                  int sourceLine,
                                  const Z80DebugSnapshot& snapshot) = 0;
};

struct BackendRunContext {
    comal::runtime::Interpreter *interpreter;
    QString source;
    QString directCommand;
    QString programPath;
    IBackendExecutionControl *executionControl{nullptr};
};

struct BackendRunResult {
    bool ok{true};
    bool finished{true};
    QString errorMessage;
    int errorLine{0};
    
    // Assembly phase results (Z80 only)
    bool assemblyAttempted{false};
    bool assemblyOk{false};
    QString assemblyOutputPath;
    QString assemblyListingPath;
    double assemblyElapsedSeconds{0.0};
    QString assemblyConsoleOutput;  // Raw stdout/stderr from sjasmplus
    std::vector<AssemblerDiagnostic> assemblyDiagnostics;
    
    // Z80 runtime output (BDOS function 9 print)
    QString z80RuntimeOutput;
};

class ILanguageBackend {
public:
    virtual ~ILanguageBackend() = default;
    virtual BackendRunResult run(const BackendRunContext &ctx) = 0;
};

class ComalBackendAdapter final : public ILanguageBackend {
public:
    BackendRunResult run(const BackendRunContext &ctx) override;
};

class Z80BackendStub final : public ILanguageBackend {
public:
    BackendRunResult run(const BackendRunContext &ctx) override;
};

class SjasmplusAssembler final : public IZ80Assembler {
public:
    AssemblerResult assembleFile(const QString& sourcePath, const QString& outputDirectory) override;
};

/// Factory for creating language backends based on language ID.
class BackendFactory {
public:
    /// Create a backend adapter for the specified language.
    /// Returns nullptr if language is not supported.
    static std::unique_ptr<ILanguageBackend> createBackend(LanguageId language);
};
