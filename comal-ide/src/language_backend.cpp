#include "language_backend.h"

#include "comal_error.h"
#include "comal_interpreter.h"

#include <exception>

using namespace comal::runtime;

BackendRunResult ComalBackendAdapter::run(const BackendRunContext& ctx)
{
    BackendRunResult result;

    try {
        if (!ctx.directCommand.isEmpty()) {
            ctx.interpreter->executeDirect(ctx.directCommand.toStdString());
        } else {
            ctx.interpreter->resetRunState();
            ctx.interpreter->loadSource(ctx.source.toStdString());
            ctx.interpreter->run();
        }
    } catch (const StopSignal&) {
        result.finished = true;
        return result;
    } catch (const EndSignal&) {
        result.finished = true;
        return result;
    } catch (const EscapeSignal&) {
        result.finished = true;
        return result;
    } catch (const ComalError& e) {
        result.ok = false;
        result.finished = false;
        result.errorMessage = QString::fromStdString(e.what());
        result.errorLine = static_cast<int>(e.line());
        return result;
    } catch (const std::exception& e) {
        result.ok = false;
        result.finished = false;
        result.errorMessage = QString::fromUtf8(e.what());
        result.errorLine = 0;
        return result;
    }

    return result;
}

BackendRunResult Z80BackendStub::run(const BackendRunContext& ctx)
{
    const comal::cpm::Z80CpmBackend backend;
    const comal::cpm::RunResult cpmResult = backend.run(
        comal::cpm::RunRequest{ctx.programPath, ctx.directCommand, ctx.cpmDrivePath, ctx.executionControl});

    BackendRunResult result;
    result.ok = cpmResult.ok;
    result.finished = cpmResult.finished;
    result.errorMessage = cpmResult.errorMessage;
    result.errorLine = cpmResult.errorLine;
    result.assemblyAttempted = cpmResult.assemblyAttempted;
    result.assemblyOk = cpmResult.assemblyOk;
    result.assemblyOutputPath = cpmResult.assemblyOutputPath;
    result.assemblyListingPath = cpmResult.assemblyListingPath;
    result.assemblyElapsedSeconds = cpmResult.assemblyElapsedSeconds;
    result.assemblyConsoleOutput = cpmResult.assemblyConsoleOutput;
    result.assemblyDiagnostics = cpmResult.assemblyDiagnostics;
    result.z80RuntimeOutput = cpmResult.z80RuntimeOutput;
    return result;
}

std::unique_ptr<ILanguageBackend> BackendFactory::createBackend(LanguageId language)
{
    switch (language) {
    case LanguageId::Comal:
        return std::make_unique<ComalBackendAdapter>();
    case LanguageId::Z80Assembly:
        return std::make_unique<Z80BackendStub>();
    default:
        return nullptr;
    }
}
