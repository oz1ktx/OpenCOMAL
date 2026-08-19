#pragma once

#include "z80_com_loader.h"

#include <cstdint>
#include <memory>
#include <QString>
#include <string>
#include <vector>

namespace comal::cpm {

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
    QString consoleOutput;
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

class IExecutionControl {
public:
    virtual ~IExecutionControl() = default;
    virtual bool stopRequested() const = 0;
    virtual bool shouldPause(std::uint16_t programCounter, int sourceLine) = 0;
    virtual void waitUntilResumed(std::uint16_t programCounter,
                                  int sourceLine,
                                  const Z80DebugSnapshot& snapshot) = 0;
};

struct RunRequest {
    QString programPath;
    QString sourceText;
    bool hasSourceText{false};
    QString consoleInput;
    QString hostDirectory;
    IExecutionControl* executionControl{nullptr};
};

struct RunResult {
    bool ok{true};
    bool finished{true};
    QString errorMessage;
    int errorLine{0};
    bool assemblyAttempted{false};
    bool assemblyOk{false};
    QString assemblyOutputPath;
    QString assemblyListingPath;
    double assemblyElapsedSeconds{0.0};
    QString assemblyConsoleOutput;
    std::vector<AssemblerDiagnostic> assemblyDiagnostics;
    QString z80RuntimeOutput;
};

class SjasmplusAssembler final : public IZ80Assembler {
public:
    AssemblerResult assembleFile(const QString& sourcePath, const QString& outputDirectory) override;
};

class Z80CpmBackend final {
public:
    RunResult run(const RunRequest& request) const;
};

} // namespace comal::cpm
