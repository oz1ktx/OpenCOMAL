#pragma once

#include <optional>
#include <QString>
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
    std::vector<AssemblerDiagnostic> diagnostics;
};

class IZ80Assembler {
public:
    virtual ~IZ80Assembler() = default;
    virtual AssemblerResult assembleFile(const QString& sourcePath, const QString& outputDirectory) = 0;
};

struct BackendRunContext {
    comal::runtime::Interpreter *interpreter;
    QString source;
    QString directCommand;
    QString programPath;
};

struct BackendRunResult {
    bool ok{true};
    bool finished{true};
    QString errorMessage;
    int errorLine{0};
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
