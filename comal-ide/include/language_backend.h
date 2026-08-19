#pragma once

#include <cstdint>
#include <memory>
#include <QString>
#include <string>
#include <vector>
#include "comal_cpm_backend.h"
#include "language_profile.h"

namespace comal::runtime { class Interpreter; }

using DiagnosticSeverity = comal::cpm::DiagnosticSeverity;
using AssemblerDiagnostic = comal::cpm::AssemblerDiagnostic;
using AssemblerResult = comal::cpm::AssemblerResult;
using IZ80Assembler = comal::cpm::IZ80Assembler;
using Z80DebugRegister = comal::cpm::Z80DebugRegister;
using Z80DebugFlag = comal::cpm::Z80DebugFlag;
using Z80DisassemblyLine = comal::cpm::Z80DisassemblyLine;
using Z80DebugSnapshot = comal::cpm::Z80DebugSnapshot;
using IBackendExecutionControl = comal::cpm::IExecutionControl;

struct BackendRunContext {
    comal::runtime::Interpreter *interpreter;
    QString source;
    bool hasSourceText{false};
    QString directCommand;
    QString programPath;
    QString cpmDrivePath;
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

/// Factory for creating language backends based on language ID.
class BackendFactory {
public:
    /// Create a backend adapter for the specified language.
    /// Returns nullptr if language is not supported.
    static std::unique_ptr<ILanguageBackend> createBackend(LanguageId language);
};
