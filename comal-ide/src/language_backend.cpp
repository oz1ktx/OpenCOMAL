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
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <optional>
#include <cstdio>
#include <cstdlib>
#include <cctype>
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

struct Z80SourceMap {
    struct Entry {
        int sourceLine{0};
        std::vector<std::uint8_t> bytes;
    };

    std::unordered_map<std::uint16_t, Entry> entries;
    std::vector<std::uint16_t> orderedAddresses;
    std::vector<std::string> sourceLines;

    int lineForAddress(std::uint16_t address) const
    {
        const auto it = entries.find(address);
        return it == entries.end() ? 0 : it->second.sourceLine;
    }

    const Entry* entryForAddress(std::uint16_t address) const
    {
        const auto it = entries.find(address);
        return it == entries.end() ? nullptr : &it->second;
    }

    std::string sourceTextForLine(int line) const
    {
        if (line <= 0 || static_cast<std::size_t>(line) > sourceLines.size()) {
            return std::string();
        }
        return sourceLines[static_cast<std::size_t>(line - 1)];
    }
};

static bool isHexToken(const std::string& token, std::size_t expectedDigits)
{
    if (token.size() != expectedDigits) {
        return false;
    }
    return std::all_of(token.begin(), token.end(), [](unsigned char ch) {
        return std::isxdigit(ch) != 0;
    });
}

static std::optional<Z80SourceMap> loadZ80SourceMap(const QString& listingPath,
                                                    const QString& sourcePath)
{
    std::ifstream input(listingPath.toStdString());
    if (!input) {
        return std::nullopt;
    }

    Z80SourceMap sourceMap;
    if (!sourcePath.isEmpty()) {
        std::ifstream sourceInput(sourcePath.toStdString());
        std::string sourceLine;
        while (std::getline(sourceInput, sourceLine)) {
            sourceMap.sourceLines.push_back(sourceLine);
        }
    }

    std::string rawLine;
    while (std::getline(input, rawLine)) {
        std::istringstream stream(rawLine);
        std::string sourceLineToken;
        std::string addressToken;
        if (!(stream >> sourceLineToken >> addressToken)) {
            continue;
        }
        if (!std::all_of(sourceLineToken.begin(), sourceLineToken.end(), [](unsigned char ch) {
                return std::isdigit(ch) != 0;
            })) {
            continue;
        }
        if (!isHexToken(addressToken, 4)) {
            continue;
        }

        const int sourceLine = std::stoi(sourceLineToken);
        const std::uint16_t address =
            static_cast<std::uint16_t>(std::stoul(addressToken, nullptr, 16));
        std::vector<std::uint8_t> bytes;
        std::string token;
        while (stream >> token) {
            if (!isHexToken(token, 2)) {
                break;
            }
            bytes.push_back(static_cast<std::uint8_t>(std::stoul(token, nullptr, 16)));
        }

        auto [it, inserted] = sourceMap.entries.emplace(address, Z80SourceMap::Entry{sourceLine, bytes});
        if (!inserted) {
            if (!bytes.empty()) {
                it->second.bytes = bytes;
                it->second.sourceLine = sourceLine;
            }
            if (it->second.sourceLine == 0) {
                it->second.sourceLine = sourceLine;
            }
        } else {
            sourceMap.orderedAddresses.push_back(address);
        }
    }

    if (sourceMap.entries.empty()) {
        return std::nullopt;
    }
    std::sort(sourceMap.orderedAddresses.begin(), sourceMap.orderedAddresses.end());
    return sourceMap;
}

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

/// Parse sjasmplus diagnostic output with format: filename(line): [error|warning]: message
/// Returns a diagnostic with extracted line number, severity, and cleaned message
static AssemblerDiagnostic parseAssemblerDiagnostic(const QString& rawLine)
{
    AssemblerDiagnostic diag;
    diag.message = rawLine.trimmed();
    diag.severity = DiagnosticSeverity::Error;  // default to error
    
    // Extract line number from (line) format
    if (const auto lineNum = parseLineNumberFromMessage(rawLine)) {
        diag.line = *lineNum;
    }
    
    // Extract severity level and clean message
    // Format: filename(line): error: message
    const int colonAfterParen = rawLine.indexOf(':', rawLine.indexOf(')'));
    if (colonAfterParen > 0) {
        const int nextColon = rawLine.indexOf(':', colonAfterParen + 1);
        if (nextColon > colonAfterParen) {
            const QString severityPart = rawLine.mid(colonAfterParen + 1, nextColon - colonAfterParen - 1).trimmed();
            const QString messageOnly = rawLine.mid(nextColon + 1).trimmed();
            
            // Set severity based on keyword
            if (severityPart == "error") {
                diag.severity = DiagnosticSeverity::Error;
                diag.message = messageOnly;
            } else if (severityPart == "warning") {
                diag.severity = DiagnosticSeverity::Warning;
                diag.message = messageOnly;
            } else if (severityPart == "note" || severityPart == "info") {
                diag.severity = DiagnosticSeverity::Information;
                diag.message = messageOnly;
            } else {
                // No recognized severity keyword, keep original message
                diag.message = messageOnly;
            }
        }
    }
    
    return diag;
}

static std::string hexValue(std::uint32_t value, int width)
{
    std::ostringstream stream;
    stream << std::uppercase << std::hex << std::setw(width) << std::setfill('0') << value;
    return stream.str();
}

static std::string formatBytes(const std::vector<std::uint8_t>& bytes)
{
    std::ostringstream stream;
    for (std::size_t i = 0; i < bytes.size(); ++i) {
        if (i != 0) {
            stream << ' ';
        }
        stream << hexValue(bytes[i], 2);
    }
    return stream.str();
}

struct DecodedInstruction {
    std::string text;
    std::vector<std::uint8_t> bytes;
};

static std::uint8_t memoryByte(const Z80Machine& machine, std::uint16_t address)
{
    return machine.memory[address];
}

static std::uint16_t memoryWord(const Z80Machine& machine, std::uint16_t address)
{
    const std::uint16_t low = memoryByte(machine, address);
    const std::uint16_t high = memoryByte(machine, static_cast<std::uint16_t>(address + 1));
    return static_cast<std::uint16_t>(low | (high << 8));
}

static DecodedInstruction decodeInstruction(const Z80Machine& machine, std::uint16_t address)
{
    static const std::array<const char*, 8> regs{"B", "C", "D", "E", "H", "L", "(HL)", "A"};

    const std::uint8_t op = memoryByte(machine, address);
    DecodedInstruction decoded;
    decoded.bytes.push_back(op);

    switch (op) {
    case 0x00:
        decoded.text = "NOP";
        return decoded;
    case 0x01: {
        decoded.bytes.push_back(memoryByte(machine, address + 1));
        decoded.bytes.push_back(memoryByte(machine, address + 2));
        decoded.text = "LD BC," + hexValue(memoryWord(machine, address + 1), 4) + "h";
        return decoded;
    }
    case 0x06:
    case 0x0E:
    case 0x16:
    case 0x1E:
    case 0x26:
    case 0x2E:
    case 0x3E: {
        const std::uint8_t imm = memoryByte(machine, address + 1);
        decoded.bytes.push_back(imm);
        const int regIndex = (op >> 3) & 0x07;
        decoded.text = std::string("LD ") + regs[regIndex] + "," + hexValue(imm, 2) + "h";
        return decoded;
    }
    case 0x10: {
        const std::int8_t offset = static_cast<std::int8_t>(memoryByte(machine, address + 1));
        decoded.bytes.push_back(static_cast<std::uint8_t>(offset));
        const std::uint16_t target =
            static_cast<std::uint16_t>(address + 2 + offset);
        decoded.text = "DJNZ " + hexValue(target, 4) + "h";
        return decoded;
    }
    case 0x11: {
        decoded.bytes.push_back(memoryByte(machine, address + 1));
        decoded.bytes.push_back(memoryByte(machine, address + 2));
        decoded.text = "LD DE," + hexValue(memoryWord(machine, address + 1), 4) + "h";
        return decoded;
    }
    case 0x1A:
        decoded.text = "LD A,(DE)";
        return decoded;
    case 0x21: {
        decoded.bytes.push_back(memoryByte(machine, address + 1));
        decoded.bytes.push_back(memoryByte(machine, address + 2));
        decoded.text = "LD HL," + hexValue(memoryWord(machine, address + 1), 4) + "h";
        return decoded;
    }
    case 0x23:
        decoded.text = "INC HL";
        return decoded;
    case 0x31: {
        decoded.bytes.push_back(memoryByte(machine, address + 1));
        decoded.bytes.push_back(memoryByte(machine, address + 2));
        decoded.text = "LD SP," + hexValue(memoryWord(machine, address + 1), 4) + "h";
        return decoded;
    }
    case 0x5F:
        decoded.text = "LD E,A";
        return decoded;
    case 0x76:
        decoded.text = "HALT";
        return decoded;
    case 0xAF:
        decoded.text = "XOR A";
        return decoded;
    case 0xC3: {
        decoded.bytes.push_back(memoryByte(machine, address + 1));
        decoded.bytes.push_back(memoryByte(machine, address + 2));
        decoded.text = "JP " + hexValue(memoryWord(machine, address + 1), 4) + "h";
        return decoded;
    }
    case 0xC6: {
        const std::uint8_t imm = memoryByte(machine, address + 1);
        decoded.bytes.push_back(imm);
        decoded.text = "ADD A," + hexValue(imm, 2) + "h";
        return decoded;
    }
    case 0xC9:
        decoded.text = "RET";
        return decoded;
    case 0xCD: {
        decoded.bytes.push_back(memoryByte(machine, address + 1));
        decoded.bytes.push_back(memoryByte(machine, address + 2));
        decoded.text = "CALL " + hexValue(memoryWord(machine, address + 1), 4) + "h";
        return decoded;
    }
    case 0xDD:
    case 0xFD: {
        const char* indexReg = (op == 0xDD) ? "IX" : "IY";
        const std::uint8_t op2 = memoryByte(machine, address + 1);
        decoded.bytes.push_back(op2);
        if (op2 == 0x21) {
            decoded.bytes.push_back(memoryByte(machine, address + 2));
            decoded.bytes.push_back(memoryByte(machine, address + 3));
            decoded.text = std::string("LD ") + indexReg + "," +
                           hexValue(memoryWord(machine, address + 2), 4) + "h";
            return decoded;
        }
        decoded.text = std::string("DB ") + hexValue(op, 2) + "h, " + hexValue(op2, 2) + "h";
        return decoded;
    }
    default:
        if (op >= 0x40 && op <= 0x7F && op != 0x76) {
            const char* dst = regs[(op >> 3) & 0x07];
            const char* src = regs[op & 0x07];
            decoded.text = std::string("LD ") + dst + "," + src;
            return decoded;
        }
        decoded.text = "DB " + hexValue(op, 2) + "h";
        return decoded;
    }
}

static std::vector<Z80DisassemblyLine> buildDisassembly(const Z80Machine& machine,
                                                        std::uint16_t programCounter,
                                                        const Z80SourceMap* sourceMap)
{
    std::vector<Z80DisassemblyLine> lines;
    if (sourceMap && !sourceMap->orderedAddresses.empty()) {
        auto begin = sourceMap->orderedAddresses.begin();
        auto current = std::lower_bound(begin, sourceMap->orderedAddresses.end(), programCounter);
        std::size_t currentIndex = current == sourceMap->orderedAddresses.end()
            ? sourceMap->orderedAddresses.size() - 1
            : static_cast<std::size_t>(std::distance(begin, current));
        const std::size_t startIndex = currentIndex > 3 ? currentIndex - 3 : 0;
        const std::size_t endIndex = std::min(sourceMap->orderedAddresses.size(), startIndex + 8);
        for (std::size_t index = startIndex; index < endIndex; ++index) {
            const std::uint16_t address = sourceMap->orderedAddresses[index];
            const auto* entry = sourceMap->entryForAddress(address);
            if (!entry) {
                continue;
            }
            const DecodedInstruction fallback = decodeInstruction(machine, address);
            const std::vector<std::uint8_t>& bytes =
                entry->bytes.empty() ? fallback.bytes : entry->bytes;
            const int sourceLine = entry->sourceLine;
            const std::string sourceText = sourceMap->sourceTextForLine(sourceLine);
            lines.push_back(Z80DisassemblyLine{
                address,
                bytes,
                sourceText.empty() ? fallback.text : sourceText,
                sourceLine,
                address == programCounter
            });
        }
        return lines;
    }

    std::uint16_t address = programCounter;
    for (int i = 0; i < 8; ++i) {
        const DecodedInstruction decoded = decodeInstruction(machine, address);
        lines.push_back(Z80DisassemblyLine{address, decoded.bytes, decoded.text, 0, i == 0});
        address = static_cast<std::uint16_t>(address + decoded.bytes.size());
    }
    return lines;
}

static Z80DebugSnapshot buildZ80DebugSnapshot(const Z80Machine& machine,
                                              const Z80SourceMap* sourceMap)
{
    const Z80& cpu = *machine.cpu;
    const std::uint16_t programCounter = Z80_PC(cpu);
    const std::uint8_t flags = Z80_F(cpu);

    Z80DebugSnapshot snapshot;
    snapshot.registers = {
        {"A", Z80_A(cpu), 2}, {"F", flags, 2}, {"B", Z80_B(cpu), 2}, {"C", Z80_C(cpu), 2},
        {"D", Z80_D(cpu), 2}, {"E", Z80_E(cpu), 2}, {"H", Z80_H(cpu), 2}, {"L", Z80_L(cpu), 2},
        {"AF", Z80_AF(cpu), 4}, {"BC", Z80_BC(cpu), 4}, {"DE", Z80_DE(cpu), 4}, {"HL", Z80_HL(cpu), 4},
        {"IX", Z80_IX(cpu), 4}, {"IY", Z80_IY(cpu), 4}, {"SP", Z80_SP(cpu), 4}, {"PC", programCounter, 4},
    };
    snapshot.flags = {
        {"S", (flags & 0x80) != 0},
        {"Z", (flags & 0x40) != 0},
        {"H", (flags & 0x10) != 0},
        {"P/V", (flags & 0x04) != 0},
        {"N", (flags & 0x02) != 0},
        {"C", (flags & 0x01) != 0},
    };

    snapshot.memoryStart = static_cast<std::uint16_t>((programCounter >= 0x20 ? programCounter - 0x20 : 0) & 0xFFF0);
    for (std::size_t i = 0; i < 0x40; ++i) {
        snapshot.memory.push_back(machine.memory[(snapshot.memoryStart + static_cast<std::uint16_t>(i)) & 0xFFFFu]);
    }
    snapshot.disassembly = buildDisassembly(machine, programCounter, sourceMap);
    return snapshot;
}

static BackendRunResult runZ80ComProgram(const QString& programPath,
                                         const QString& consoleInput,
                                         const Z80SourceMap* sourceMap,
                                         IBackendExecutionControl* executionControl)
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
        const std::uint16_t programCounter = Z80_PC(cpu);
        const int sourceLine = sourceMap ? sourceMap->lineForAddress(programCounter) : 0;
        if (executionControl) {
            if (executionControl->stopRequested()) {
                result.finished = true;
                return result;
            }
            if (executionControl->shouldPause(programCounter, sourceLine)) {
                const Z80DebugSnapshot snapshot = buildZ80DebugSnapshot(machine, sourceMap);
                executionControl->waitUntilResumed(programCounter, sourceLine, snapshot);
                if (executionControl->stopRequested()) {
                    result.finished = true;
                    return result;
                }
                continue;
            }
        }

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

    // Capture Z80 runtime output (from BDOS function 9, etc.)
    if (!machine.consoleOutput.empty()) {
        result.z80RuntimeOutput = QString::fromStdString(machine.consoleOutput);
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
    result.consoleOutput = output;  // Store raw output for display
    
    const QStringList lines = output.split('\n', Qt::SkipEmptyParts);
    for (const QString& rawLine : lines) {
        if (rawLine.isEmpty()) {
            continue;
        }
        // Skip the sjasmplus version/header line
        if (rawLine.contains("SjASMPlus") || rawLine.contains("Cross-Assembler")) {
            continue;
        }
        const AssemblerDiagnostic diag = parseAssemblerDiagnostic(rawLine);
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
        return runZ80ComProgram(ctx.programPath, ctx.directCommand, nullptr, ctx.executionControl);
    }

    if (lowerPath.endsWith(".asm") || lowerPath.endsWith(".z80") || lowerPath.endsWith(".s")) {
        // Measure assembly time
        const auto assemblyStart = std::chrono::high_resolution_clock::now();
        
        SjasmplusAssembler assembler;
        const QString sourceDir = QFileInfo(ctx.programPath).absolutePath();
        const QString buildDir = QDir(sourceDir).filePath(".opencomal-build");
        const AssemblerResult assembled = assembler.assembleFile(ctx.programPath, buildDir);
        
        const auto assemblyEnd = std::chrono::high_resolution_clock::now();
        const double assemblyElapsed = 
            std::chrono::duration<double>(assemblyEnd - assemblyStart).count();
        
        if (!assembled.ok) {
            BackendRunResult result;
            result.ok = false;
            result.finished = false;
            result.assemblyAttempted = true;
            result.assemblyOk = false;
            result.assemblyElapsedSeconds = assemblyElapsed;
            result.assemblyConsoleOutput = assembled.consoleOutput;
            result.assemblyDiagnostics = assembled.diagnostics;
            if (!assembled.diagnostics.empty()) {
                result.errorMessage = assembled.diagnostics.front().message;
                result.errorLine = assembled.diagnostics.front().line;
            } else {
                result.errorMessage = "Assembly failed.";
            }
            return result;
        }
        
        // Assembly succeeded
        const std::optional<Z80SourceMap> sourceMap =
            loadZ80SourceMap(assembled.listingPath, ctx.programPath);
        BackendRunResult execResult = runZ80ComProgram(
            assembled.outputPath, ctx.directCommand,
            sourceMap ? &*sourceMap : nullptr, ctx.executionControl);
        execResult.assemblyAttempted = true;
        execResult.assemblyOk = true;
        execResult.assemblyOutputPath = assembled.outputPath;
        execResult.assemblyListingPath = assembled.listingPath;
        execResult.assemblyElapsedSeconds = assemblyElapsed;
        execResult.assemblyConsoleOutput = assembled.consoleOutput;
        return execResult;
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
