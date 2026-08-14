#include "language_backend.h"

#include "z80_com_loader.h"

#include "comal_interpreter.h"
#include "comal_error.h"
#include <Z80.h>

#include <QDir>
#include <QFileInfo>
#include <QStringList>

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <optional>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace comal::runtime;

namespace {

constexpr std::size_t kMaxInstructions = 2'000'000;
constexpr std::uint16_t kBdosCallAddress = 0x0005;
#ifdef OPENCOMAL_SJASMPLUS_PATH
constexpr const char* kSjasmplusPath = OPENCOMAL_SJASMPLUS_PATH;
#else
constexpr const char* kSjasmplusPath = "sjasmplus";
#endif

enum class Z80ExitReason {
    Running,
    Halt,
    WarmBoot,
    BdosTerminate,
    UnsupportedBdos,
    InstructionLimit,
};

struct Z80Machine {
    struct OpenFileState {
        std::vector<std::uint8_t> data;
        std::size_t nextRecord{0};
    };

    std::array<std::uint8_t, Z80ComImage::kMemorySize> memory{};
    Z80* cpu{nullptr};
    Z80ExitReason exitReason{Z80ExitReason::Running};
    std::uint8_t unsupportedBdosFunction{0};
    std::string consoleOutput;
    std::string consoleInput;
    std::size_t consoleInputPos{0};
    std::filesystem::path hostBaseDir;
    std::unordered_map<std::uint16_t, OpenFileState> openFiles;
    std::uint16_t dmaAddress{Z80ComImage::kDefaultDmaAddress};
    std::uint8_t currentDrive{0};
};

static std::string trimRightSpaces(const std::string& s)
{
    std::size_t end = s.size();
    while (end > 0 && s[end - 1] == ' ') {
        --end;
    }
    return s.substr(0, end);
}

static std::string parseFcbFileName(const Z80Machine& machine, std::uint16_t fcbAddr)
{
    std::string name;
    name.reserve(12);

    for (std::size_t i = 1; i <= 8; ++i) {
        char ch = static_cast<char>(machine.memory[(fcbAddr + i) & 0xFFFFu] & 0x7F);
        if (ch >= 'a' && ch <= 'z') {
            ch = static_cast<char>(ch - ('a' - 'A'));
        }
        name.push_back(ch);
    }

    std::string ext;
    ext.reserve(3);
    for (std::size_t i = 9; i <= 11; ++i) {
        char ch = static_cast<char>(machine.memory[(fcbAddr + i) & 0xFFFFu] & 0x7F);
        if (ch >= 'a' && ch <= 'z') {
            ch = static_cast<char>(ch - ('a' - 'A'));
        }
        ext.push_back(ch);
    }

    name = trimRightSpaces(name);
    ext = trimRightSpaces(ext);
    if (name.empty()) {
        return std::string();
    }
    if (!ext.empty()) {
        return name + "." + ext;
    }
    return name;
}

static bool openFcbFile(Z80Machine& machine, std::uint16_t fcbAddr)
{
    const std::string fileName = parseFcbFileName(machine, fcbAddr);
    if (fileName.empty()) {
        return false;
    }

    const std::filesystem::path filePath = machine.hostBaseDir / fileName;
    std::ifstream input(filePath, std::ios::binary);
    if (!input) {
        return false;
    }

    Z80Machine::OpenFileState state;
    state.data.assign(std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>());
    state.nextRecord = machine.memory[(fcbAddr + 32) & 0xFFFFu];
    machine.openFiles[fcbAddr] = std::move(state);
    return true;
}

static bool closeFcbFile(Z80Machine& machine, std::uint16_t fcbAddr)
{
    return machine.openFiles.erase(fcbAddr) > 0;
}

static std::uint8_t sequentialReadFcbFile(Z80Machine& machine, std::uint16_t fcbAddr)
{
    auto it = machine.openFiles.find(fcbAddr);
    if (it == machine.openFiles.end()) {
        return 0xFF;
    }

    constexpr std::size_t kRecordSize = 128;
    const std::size_t offset = it->second.nextRecord * kRecordSize;
    if (offset >= it->second.data.size()) {
        return 0x01;
    }

    for (std::size_t i = 0; i < kRecordSize; ++i) {
        machine.memory[(machine.dmaAddress + static_cast<std::uint16_t>(i)) & 0xFFFFu] = 0x1A;
    }
    const std::size_t available = std::min(kRecordSize, it->second.data.size() - offset);
    for (std::size_t i = 0; i < available; ++i) {
        machine.memory[(machine.dmaAddress + static_cast<std::uint16_t>(i)) & 0xFFFFu] =
            it->second.data[offset + i];
    }

    ++it->second.nextRecord;
    machine.memory[(fcbAddr + 32) & 0xFFFFu] = static_cast<std::uint8_t>(it->second.nextRecord & 0xFFu);
    return 0x00;
}

static std::uint8_t popConsoleInputChar(Z80Machine& machine)
{
    if (machine.consoleInputPos < machine.consoleInput.size()) {
        const unsigned char ch = static_cast<unsigned char>(machine.consoleInput[machine.consoleInputPos]);
        ++machine.consoleInputPos;
        return static_cast<std::uint8_t>(ch);
    }
    // CP/M-style fallback when no input is queued.
    return static_cast<std::uint8_t>('\r');
}

static std::uint8_t z80FetchOpcode(void* context, zuint16 address)
{
    auto* machine = static_cast<Z80Machine*>(context);
    if (!machine) {
        return Z80_NOP;
    }

    if (address == Z80ComImage::kWarmBootAddress) {
        machine->exitReason = Z80ExitReason::WarmBoot;
        if (machine->cpu) {
            z80_break(machine->cpu);
        }
        return Z80_NOP;
    }

    if (address == kBdosCallAddress) {
        if (!machine->cpu) {
            return Z80_RET;
        }

        const std::uint8_t functionId = Z80_C((*machine->cpu));
        switch (functionId) {
        case 0: {
            machine->exitReason = Z80ExitReason::BdosTerminate;
            z80_break(machine->cpu);
            break;
        }
        case 1: {
            const std::uint8_t ch = popConsoleInputChar(*machine);
            Z80_A((*machine->cpu)) = ch;
            // CP/M function 1 echoes the read character.
            machine->consoleOutput.push_back(static_cast<char>(ch));
            break;
        }
        case 2: {
            machine->consoleOutput.push_back(static_cast<char>(Z80_E((*machine->cpu))));
            break;
        }
        case 6: {
            if (Z80_E((*machine->cpu)) == 0xFF) {
                if (machine->consoleInputPos < machine->consoleInput.size()) {
                    Z80_A((*machine->cpu)) = popConsoleInputChar(*machine);
                } else {
                    Z80_A((*machine->cpu)) = 0;
                }
            } else {
                machine->consoleOutput.push_back(static_cast<char>(Z80_E((*machine->cpu))));
                Z80_A((*machine->cpu)) = Z80_E((*machine->cpu));
            }
            break;
        }
        case 9: {
            std::uint16_t addr = Z80_DE((*machine->cpu));
            for (std::size_t i = 0; i < Z80ComImage::kMemorySize; ++i) {
                const std::uint8_t ch = machine->memory[addr];
                if (ch == '$') {
                    break;
                }
                machine->consoleOutput.push_back(static_cast<char>(ch));
                addr = static_cast<std::uint16_t>(addr + 1);
            }
            break;
        }
        case 12: {
            // Report CP/M 2.2-style version code (0x22).
            Z80_A((*machine->cpu)) = 0x22;
            Z80_HL((*machine->cpu)) = 0x0022;
            break;
        }
        case 15: {
            const std::uint16_t fcbAddr = Z80_DE((*machine->cpu));
            Z80_A((*machine->cpu)) = openFcbFile(*machine, fcbAddr) ? 0x00 : 0xFF;
            break;
        }
        case 16: {
            const std::uint16_t fcbAddr = Z80_DE((*machine->cpu));
            Z80_A((*machine->cpu)) = closeFcbFile(*machine, fcbAddr) ? 0x00 : 0xFF;
            break;
        }
        case 20: {
            const std::uint16_t fcbAddr = Z80_DE((*machine->cpu));
            Z80_A((*machine->cpu)) = sequentialReadFcbFile(*machine, fcbAddr);
            break;
        }
        case 25: {
            Z80_A((*machine->cpu)) = machine->currentDrive;
            break;
        }
        case 26: {
            machine->dmaAddress = Z80_DE((*machine->cpu));
            break;
        }
        default:
            machine->unsupportedBdosFunction = functionId;
            machine->exitReason = Z80ExitReason::UnsupportedBdos;
            z80_break(machine->cpu);
            break;
        }

        // Emulate CP/M BDOS call gate at 0005h as a direct RET.
        return Z80_RET;
    }

    return machine->memory[address];
}

static std::uint8_t z80Read(void* context, zuint16 address)
{
    auto* machine = static_cast<Z80Machine*>(context);
    return machine ? machine->memory[address] : 0;
}

static void z80Write(void* context, zuint16 address, zuint8 value)
{
    auto* machine = static_cast<Z80Machine*>(context);
    if (machine) {
        machine->memory[address] = value;
    }
}

static std::uint8_t z80In(void*, zuint16)
{
    // CP/M console input is out-of-scope in this minimal backend.
    return 0xFF;
}

static void z80Out(void*, zuint16, zuint8)
{
    // No external I/O ports are emulated in this minimal backend.
}

static void z80Halt(void* context, zuint8 signal)
{
    auto* machine = static_cast<Z80Machine*>(context);
    if (!machine || !machine->cpu) {
        return;
    }

    if (signal != 0) {
        machine->exitReason = Z80ExitReason::Halt;
        z80_break(machine->cpu);
    }
}

static QString shellQuote(const QString& value)
{
    QString escaped = value;
    escaped.replace("'", "'\"'\"'");
    return "'" + escaped + "'";
}

static std::optional<int> parseLineNumberFromMessage(const QString& line)
{
    const int openParen = line.lastIndexOf('(');
    const int closeParen = line.indexOf(')', openParen + 1);
    if (openParen < 0 || closeParen < 0) {
        return std::nullopt;
    }
    bool ok = false;
    const int lineNumber = line.mid(openParen + 1, closeParen - openParen - 1).toInt(&ok);
    if (!ok) {
        return std::nullopt;
    }
    return lineNumber;
}

static BackendRunResult runZ80ComProgram(const QString& programPath, const QString& consoleInput)
{
    BackendRunResult result;
    result.ok = true;
    result.finished = true;

    Z80ComImage image;
    std::string error;
    if (!loadZ80ComImage(programPath.toStdString(), image, error)) {
        result.ok = false;
        result.finished = false;
        result.errorMessage = QString::fromStdString(error);
        return result;
    }

    Z80Machine machine;
    machine.memory = image.memory;
    machine.consoleInput = consoleInput.toStdString();
    machine.hostBaseDir = std::filesystem::path(programPath.toStdString()).parent_path();

    Z80 cpu{};
    machine.cpu = &cpu;

    cpu.context = &machine;
    cpu.fetch_opcode = z80FetchOpcode;
    cpu.fetch = z80Read;
    cpu.read = z80Read;
    cpu.write = z80Write;
    cpu.in = z80In;
    cpu.out = z80Out;
    cpu.halt = z80Halt;

    z80_power(&cpu, Z_TRUE);
    z80_instant_reset(&cpu);
    Z80_PC(cpu) = image.entryPoint;
    Z80_SP(cpu) = 0xFFFE;

    std::size_t instructionCount = 0;
    while (instructionCount < kMaxInstructions && machine.exitReason == Z80ExitReason::Running) {
        z80_execute(&cpu, 1);
        ++instructionCount;
    }

    if (machine.exitReason == Z80ExitReason::Running) {
        machine.exitReason = Z80ExitReason::InstructionLimit;
    }

    if (machine.exitReason == Z80ExitReason::UnsupportedBdos) {
        result.ok = false;
        result.finished = false;
        std::ostringstream msg;
        msg << "Unsupported BDOS function "
            << static_cast<int>(machine.unsupportedBdosFunction)
            << " requested via CALL 0005h.";
        result.errorMessage = QString::fromStdString(msg.str());
        return result;
    }

    if (machine.exitReason == Z80ExitReason::InstructionLimit) {
        result.ok = false;
        result.finished = false;
        std::ostringstream msg;
        msg << "Z80 execution stopped after reaching instruction limit ("
            << kMaxInstructions << ").";
        result.errorMessage = QString::fromStdString(msg.str());
        return result;
    }

    if (!machine.consoleOutput.empty()) {
        std::ostringstream msg;
        msg << "Z80 program output:\n" << machine.consoleOutput;
        result.errorMessage = QString::fromStdString(msg.str());
    }

    return result;
}

} // namespace

AssemblerResult SjasmplusAssembler::assembleFile(const QString& sourcePath, const QString& outputDirectory)
{
    AssemblerResult result;

    const QFileInfo sourceInfo(sourcePath);
    if (!sourceInfo.exists()) {
        result.diagnostics.push_back({0, 0, "Assembly source file does not exist."});
        return result;
    }

    QDir().mkpath(outputDirectory);

    const QString baseName = sourceInfo.completeBaseName();
    const QString outputPath = QDir(outputDirectory).filePath(baseName + ".com");
    const QString listingPath = QDir(outputDirectory).filePath(baseName + ".lst");
    const QString command = QString("%1 --syntax=abfw --nologo --msg=err --lst=%2 --raw=%3 %4 2>&1")
        .arg(shellQuote(QString::fromUtf8(kSjasmplusPath)))
        .arg(shellQuote(listingPath))
        .arg(shellQuote(outputPath))
        .arg(shellQuote(sourcePath));

    FILE* pipe = popen(command.toUtf8().constData(), "r");
    if (!pipe) {
        result.diagnostics.push_back({0, 0, "Failed to launch sjasmplus assembler."});
        return result;
    }

    QByteArray buffer;
    char readBuf[4096];
    while (std::fgets(readBuf, sizeof(readBuf), pipe)) {
        buffer.append(readBuf);
    }
    const int exitCode = pclose(pipe);

    const QString output = QString::fromUtf8(buffer);
    const QStringList lines = output.split('\n', Qt::SkipEmptyParts);
    for (const QString& rawLine : lines) {
        const QString line = rawLine.trimmed();
        if (line.isEmpty()) {
            continue;
        }
        AssemblerDiagnostic diag;
        diag.message = line;
        if (const auto parsedLine = parseLineNumberFromMessage(line)) {
            diag.line = *parsedLine;
        }
        result.diagnostics.push_back(diag);
    }

    if (exitCode == 0 && QFileInfo::exists(outputPath)) {
        result.ok = true;
        result.outputPath = outputPath;
        result.listingPath = listingPath;
        return result;
    }

    if (result.diagnostics.empty()) {
        result.diagnostics.push_back({0, 0, "sjasmplus failed without diagnostic output."});
    }
    return result;
}

BackendRunResult ComalBackendAdapter::run(const BackendRunContext &ctx)
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
    } catch (const ComalError &e) {
        result.ok = false;
        result.finished = false;
        result.errorMessage = QString::fromStdString(e.what());
        result.errorLine = static_cast<int>(e.line());
        return result;
    } catch (const std::exception &e) {
        result.ok = false;
        result.finished = false;
        result.errorMessage = QString::fromUtf8(e.what());
        result.errorLine = 0;
        return result;
    }

    return result;
}

BackendRunResult Z80BackendStub::run(const BackendRunContext &ctx)
{
    const QString lowerPath = ctx.programPath.toLower();
    if (lowerPath.endsWith(".com")) {
        return runZ80ComProgram(ctx.programPath, ctx.directCommand);
    }

    if (lowerPath.endsWith(".asm") || lowerPath.endsWith(".z80") || lowerPath.endsWith(".s")) {
        SjasmplusAssembler assembler;
        const QString sourceDir = QFileInfo(ctx.programPath).absolutePath();
        const QString buildDir = QDir(sourceDir).filePath(".opencomal-build");
        const AssemblerResult assembled = assembler.assembleFile(ctx.programPath, buildDir);
        if (!assembled.ok) {
            BackendRunResult result;
            result.ok = false;
            result.finished = false;
            if (!assembled.diagnostics.empty()) {
                result.errorMessage = assembled.diagnostics.front().message;
                result.errorLine = assembled.diagnostics.front().line;
            } else {
                result.errorMessage = "Assembly failed.";
            }
            return result;
        }
        return runZ80ComProgram(assembled.outputPath, ctx.directCommand);
    }

    BackendRunResult result;
    result.ok = false;
    result.finished = false;
    result.errorMessage =
        "Z80 backend currently supports .COM execution and .asm/.z80/.s assembly via sjasmplus.";
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
