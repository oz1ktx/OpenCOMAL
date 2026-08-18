#include "language_backend.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#ifndef OPENCOMAL_SOURCE_DIR
#error OPENCOMAL_SOURCE_DIR must be defined for test fixtures.
#endif

namespace {

int gPassed = 0;
int gFailed = 0;

#define TEST(name) do { std::cout << "  " #name "... "; std::cout.flush(); } while (0)
#define PASS() do { std::cout << "OK\n"; ++gPassed; } while (0)
#define FAIL(msg) do { std::cout << "FAIL: " << (msg) << "\n"; ++gFailed; } while (0)
#define ASSERT_TRUE(cond, msg) do { if (!(cond)) { FAIL(msg); return; } } while (0)

bool writeComFile(const std::filesystem::path& path, const std::vector<unsigned char>& bytes)
{
    std::ofstream out(path, std::ios::binary);
    if (!out) {
        return false;
    }
    out.write(reinterpret_cast<const char*>(bytes.data()), static_cast<std::streamsize>(bytes.size()));
    return static_cast<bool>(out);
}

bool writeTextFile(const std::filesystem::path& path, const std::string& text)
{
    std::ofstream out(path, std::ios::binary);
    if (!out) {
        return false;
    }
    out.write(text.data(), static_cast<std::streamsize>(text.size()));
    return static_cast<bool>(out);
}

class BreakpointCaptureControl final : public IBackendExecutionControl {
public:
    explicit BreakpointCaptureControl(int breakpointLine)
        : breakpointLine_(breakpointLine)
    {
    }

    bool stopRequested() const override
    {
        return false;
    }

    bool shouldPause(std::uint16_t, int sourceLine) override
    {
        return !paused_ && sourceLine == breakpointLine_;
    }

    void waitUntilResumed(std::uint16_t, int sourceLine, const Z80DebugSnapshot& snapshot) override
    {
        paused_ = true;
        pausedLine_ = sourceLine;
        snapshot_ = snapshot;
    }

    int pausedLine() const
    {
        return pausedLine_;
    }

    const Z80DebugSnapshot& snapshot() const
    {
        return snapshot_;
    }

private:
    int breakpointLine_{0};
    bool paused_{false};
    int pausedLine_{0};
    Z80DebugSnapshot snapshot_;
};

class StepCaptureControl final : public IBackendExecutionControl {
public:
    explicit StepCaptureControl(std::size_t maxPauses)
        : maxPauses_(maxPauses)
    {
    }

    bool stopRequested() const override
    {
        return false;
    }

    bool shouldPause(std::uint16_t, int sourceLine) override
    {
        if (pauseCount_ >= maxPauses_) {
            return false;
        }
        if (allowOneInstruction_) {
            allowOneInstruction_ = false;
            return false;
        }
        return sourceLine > 0;
    }

    void waitUntilResumed(std::uint16_t, int sourceLine, const Z80DebugSnapshot&) override
    {
        pausedLines_.push_back(sourceLine);
        ++pauseCount_;
        allowOneInstruction_ = true;
    }

    const std::vector<int>& pausedLines() const
    {
        return pausedLines_;
    }

private:
    std::size_t maxPauses_{0};
    std::size_t pauseCount_{0};
    bool allowOneInstruction_{false};
    std::vector<int> pausedLines_;
};

void test_assemble_source_and_run(const std::filesystem::path& dir)
{
    TEST(assemble_source_and_run);

    const std::filesystem::path fixturePath =
        std::filesystem::path(OPENCOMAL_SOURCE_DIR) / "tests" / "assembly" / "hello_loop.asm";
    ASSERT_TRUE(std::filesystem::exists(fixturePath), "repository assembly fixture is missing");

    const std::filesystem::path asmPath = dir / "hello_loop.asm";
    std::error_code copyEc;
    std::filesystem::copy_file(fixturePath, asmPath, std::filesystem::copy_options::overwrite_existing, copyEc);
    ASSERT_TRUE(!copyEc, "failed to copy hello_loop.asm fixture into temp directory");

    Z80BackendStub backend;
    BackendRunContext ctx;
    ctx.interpreter = nullptr;
    ctx.programPath = QString::fromStdString(asmPath.string());

    const BackendRunResult result = backend.run(ctx);
    ASSERT_TRUE(result.ok, "assembly-backed run failed unexpectedly");

    const std::filesystem::path comPath = dir / ".opencomal-build" / "hello_loop.com";
    ASSERT_TRUE(std::filesystem::exists(comPath), "expected assembled .COM output was not created");

    const std::string output = result.z80RuntimeOutput.toStdString();
    ASSERT_TRUE(output.find("HelloHelloHelloHello") != std::string::npos,
                "expected Hello output from assembled source not found");

    PASS();
}

void test_hello_prints_four_times(const std::filesystem::path& dir)
{
    TEST(hello_prints_four_times);

    const std::filesystem::path comPath = dir / "hello4.com";
    const std::vector<unsigned char> program = {
        0x06, 0x04,             // LD B,4
        0x0E, 0x09,             // LD C,9 (print string)
        0x11, 0x12, 0x01,       // LD DE,0x0112
        0xCD, 0x05, 0x00,       // CALL 0005h
        0x10, 0xF6,             // DJNZ 0x0102
        0x0E, 0x00,             // LD C,0 (terminate)
        0xCD, 0x05, 0x00,       // CALL 0005h
        0x76,                   // HALT
        'H', 'e', 'l', 'l', 'o', '$'
    };

    ASSERT_TRUE(writeComFile(comPath, program), "failed to write hello4.com test fixture");

    Z80BackendStub backend;
    BackendRunContext ctx;
    ctx.interpreter = nullptr;
    ctx.programPath = QString::fromStdString(comPath.string());

    const BackendRunResult result = backend.run(ctx);
    ASSERT_TRUE(result.ok, "backend run failed unexpectedly");
    const std::string output = result.z80RuntimeOutput.toStdString();
    ASSERT_TRUE(output.find("HelloHelloHelloHello") != std::string::npos,
                "expected repeated Hello output not found");

    PASS();
}

void test_assembly_breakpoint_hits_source_line(const std::filesystem::path& dir)
{
    TEST(assembly_breakpoint_hits_source_line);

    const std::filesystem::path fixturePath =
        std::filesystem::path(OPENCOMAL_SOURCE_DIR) / "tests" / "assembly" / "hello_loop.asm";
    ASSERT_TRUE(std::filesystem::exists(fixturePath), "repository assembly fixture is missing");

    const std::filesystem::path asmPath = dir / "hello_loop_breakpoint.asm";
    std::error_code copyEc;
    std::filesystem::copy_file(fixturePath, asmPath, std::filesystem::copy_options::overwrite_existing, copyEc);
    ASSERT_TRUE(!copyEc, "failed to copy hello_loop.asm fixture into temp directory");

    BreakpointCaptureControl control(/* ld c,9 */ 7);

    Z80BackendStub backend;
    BackendRunContext ctx;
    ctx.interpreter = nullptr;
    ctx.programPath = QString::fromStdString(asmPath.string());
    ctx.executionControl = &control;

    const BackendRunResult result = backend.run(ctx);
    ASSERT_TRUE(result.ok, "assembly-backed breakpoint run failed unexpectedly");
    ASSERT_TRUE(control.pausedLine() == 7, "expected breakpoint pause on source line 7");
    ASSERT_TRUE(!control.snapshot().registers.empty(), "expected register snapshot on breakpoint pause");
    ASSERT_TRUE(!control.snapshot().flags.empty(), "expected flag snapshot on breakpoint pause");
    ASSERT_TRUE(control.snapshot().memory.size() == 0x40, "expected 64-byte memory window on breakpoint pause");
    ASSERT_TRUE(!control.snapshot().disassembly.empty(), "expected disassembly snapshot on breakpoint pause");

    PASS();
}

void test_assembly_single_step_reports_instruction_lines(const std::filesystem::path& dir)
{
    TEST(assembly_single_step_reports_instruction_lines);

    const std::filesystem::path fixturePath =
        std::filesystem::path(OPENCOMAL_SOURCE_DIR) / "tests" / "assembly" / "hello_loop.asm";
    ASSERT_TRUE(std::filesystem::exists(fixturePath), "repository assembly fixture is missing");

    const std::filesystem::path asmPath = dir / "hello_loop_step.asm";
    std::error_code copyEc;
    std::filesystem::copy_file(fixturePath, asmPath, std::filesystem::copy_options::overwrite_existing, copyEc);
    ASSERT_TRUE(!copyEc, "failed to copy hello_loop.asm fixture into temp directory");

    StepCaptureControl control(3);

    Z80BackendStub backend;
    BackendRunContext ctx;
    ctx.interpreter = nullptr;
    ctx.programPath = QString::fromStdString(asmPath.string());
    ctx.executionControl = &control;

    const BackendRunResult result = backend.run(ctx);
    ASSERT_TRUE(result.ok, "assembly-backed single-step run failed unexpectedly");
    const std::vector<int> expectedLines{4, 7, 8};
    ASSERT_TRUE(control.pausedLines() == expectedLines,
                "expected first three stepped instruction lines to be 4, 7, 8");

    PASS();
}

void test_console_input_echo_roundtrip(const std::filesystem::path& dir)
{
    TEST(console_input_echo_roundtrip);

    const std::filesystem::path comPath = dir / "echo_input.com";
    const std::vector<unsigned char> program = {
        0x0E, 0x01,             // LD C,1 (console input with echo)
        0xCD, 0x05, 0x00,       // CALL 0005h
        0x5F,                   // LD E,A
        0x0E, 0x02,             // LD C,2 (console char out)
        0xCD, 0x05, 0x00,       // CALL 0005h
        0x0E, 0x00,             // LD C,0 (terminate)
        0xCD, 0x05, 0x00,       // CALL 0005h
        0x76                    // HALT
    };

    ASSERT_TRUE(writeComFile(comPath, program), "failed to write echo_input.com test fixture");

    Z80BackendStub backend;
    BackendRunContext ctx;
    ctx.interpreter = nullptr;
    ctx.programPath = QString::fromStdString(comPath.string());
    ctx.directCommand = "Z";

    const BackendRunResult result = backend.run(ctx);
    ASSERT_TRUE(result.ok, "backend run failed unexpectedly");
    const std::string output = result.z80RuntimeOutput.toStdString();
    ASSERT_TRUE(output.find("ZZ") != std::string::npos,
                "expected echoed input output (ZZ) not found");

    PASS();
}

void test_bdos_file_and_misc_functions(const std::filesystem::path& dir)
{
    TEST(bdos_file_and_misc_functions);

    const std::filesystem::path dataPath = dir / "DATA.TXT";
    ASSERT_TRUE(writeTextFile(dataPath, "Hello"), "failed to write DATA.TXT fixture");

    const std::filesystem::path comPath = dir / "bdos_file_ops.com";
    std::vector<unsigned char> program = {
        0x11, 0x80, 0x01,       // LD DE,0x0180 (DMA buffer)
        0x0E, 0x1A,             // LD C,26 (set DMA)
        0xCD, 0x05, 0x00,       // CALL 0005h

        0x11, 0xA0, 0x01,       // LD DE,0x01A0 (FCB)
        0x0E, 0x0F,             // LD C,15 (open)
        0xCD, 0x05, 0x00,       // CALL 0005h

        0x11, 0xA0, 0x01,       // LD DE,0x01A0 (FCB)
        0x0E, 0x14,             // LD C,20 (sequential read)
        0xCD, 0x05, 0x00,       // CALL 0005h

        0x21, 0x80, 0x01,       // LD HL,0x0180
        0x06, 0x05,             // LD B,5
        0x5E,                   // loop: LD E,(HL)
        0x0E, 0x02,             // LD C,2 (console output)
        0xCD, 0x05, 0x00,       // CALL 0005h
        0x23,                   // INC HL
        0x10, 0xF7,             // DJNZ loop

        0x0E, 0x19,             // LD C,25 (get current drive)
        0xCD, 0x05, 0x00,       // CALL 0005h
        0xC6, 0x30,             // ADD A,'0'
        0x5F,                   // LD E,A
        0x0E, 0x02,             // LD C,2
        0xCD, 0x05, 0x00,       // CALL 0005h

        0x0E, 0x0C,             // LD C,12 (version)
        0xCD, 0x05, 0x00,       // CALL 0005h
        0x5F,                   // LD E,A (expected 0x22 = '"')
        0x0E, 0x02,             // LD C,2
        0xCD, 0x05, 0x00,       // CALL 0005h

        0x11, 0xA0, 0x01,       // LD DE,0x01A0 (FCB)
        0x0E, 0x10,             // LD C,16 (close)
        0xCD, 0x05, 0x00,       // CALL 0005h

        0x0E, 0x00,             // LD C,0 (terminate)
        0xCD, 0x05, 0x00,       // CALL 0005h
        0x76                    // HALT
    };

    while (program.size() < (0x01A0 - 0x0100)) {
        program.push_back(0x00);
    }

    // FCB at 0x01A0 for DATA.TXT
    const std::vector<unsigned char> fcb = {
        0x00,
        'D', 'A', 'T', 'A', ' ', ' ', ' ', ' ',
        'T', 'X', 'T',
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };
    program.insert(program.end(), fcb.begin(), fcb.end());

    ASSERT_TRUE(writeComFile(comPath, program), "failed to write bdos_file_ops.com test fixture");

    Z80BackendStub backend;
    BackendRunContext ctx;
    ctx.interpreter = nullptr;
    ctx.programPath = QString::fromStdString(comPath.string());

    const BackendRunResult result = backend.run(ctx);
    ASSERT_TRUE(result.ok, "backend run failed unexpectedly");
    const std::string output = result.z80RuntimeOutput.toStdString();
    ASSERT_TRUE(output.find("Hello0\"") != std::string::npos,
                "expected combined output from read/drive/version not found");

    PASS();
}

void test_bdos_sequential_read_reports_eof(const std::filesystem::path& dir)
{
    TEST(bdos_sequential_read_reports_eof);

    const std::filesystem::path dataPath = dir / "EOFTEST.TXT";
    ASSERT_TRUE(writeTextFile(dataPath, "HELLO"), "failed to write EOFTEST.TXT fixture");

    const std::filesystem::path comPath = dir / "bdos_eof_check.com";
    std::vector<unsigned char> program = {
        0x11, 0x80, 0x01,       // LD DE,0x0180 (DMA)
        0x0E, 0x1A,             // LD C,26 (set DMA)
        0xCD, 0x05, 0x00,       // CALL 0005h

        0x11, 0xA0, 0x01,       // LD DE,0x01A0 (FCB)
        0x0E, 0x0F,             // LD C,15 (open)
        0xCD, 0x05, 0x00,       // CALL 0005h

        0x11, 0xA0, 0x01,       // LD DE,0x01A0
        0x0E, 0x14,             // LD C,20 (read #1)
        0xCD, 0x05, 0x00,       // CALL 0005h

        0x1E, 0x80,             // LD E,0x80
        0x16, 0x01,             // LD D,0x01
        0x1A,                   // LD A,(DE)
        0x5F,                   // LD E,A
        0x0E, 0x02,             // LD C,2 (print first DMA byte, expect 'H')
        0xCD, 0x05, 0x00,       // CALL 0005h

        0x11, 0xA0, 0x01,       // LD DE,0x01A0
        0x0E, 0x14,             // LD C,20 (read #2 should be EOF)
        0xCD, 0x05, 0x00,       // CALL 0005h

        0xC6, 0x30,             // ADD A,'0'  (expect '1')
        0x5F,                   // LD E,A
        0x0E, 0x02,             // LD C,2
        0xCD, 0x05, 0x00,       // CALL 0005h

        0x11, 0xA0, 0x01,       // LD DE,0x01A0
        0x0E, 0x10,             // LD C,16 (close)
        0xCD, 0x05, 0x00,       // CALL 0005h

        0x0E, 0x00,             // LD C,0 (terminate)
        0xCD, 0x05, 0x00,       // CALL 0005h
        0x76                    // HALT
    };

    while (program.size() < (0x01A0 - 0x0100)) {
        program.push_back(0x00);
    }

    // FCB at 0x01A0 for EOFTEST.TXT
    const std::vector<unsigned char> fcb = {
        0x00,
        'E', 'O', 'F', 'T', 'E', 'S', 'T', ' ',
        'T', 'X', 'T',
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };
    program.insert(program.end(), fcb.begin(), fcb.end());

    ASSERT_TRUE(writeComFile(comPath, program), "failed to write bdos_eof_check.com test fixture");

    Z80BackendStub backend;
    BackendRunContext ctx;
    ctx.interpreter = nullptr;
    ctx.programPath = QString::fromStdString(comPath.string());

    const BackendRunResult result = backend.run(ctx);
    ASSERT_TRUE(result.ok, "backend run failed unexpectedly");
    const std::string output = result.z80RuntimeOutput.toStdString();
    ASSERT_TRUE(output.find("H1") != std::string::npos,
                "expected first DMA byte + EOF status output ('H1') not found");

    PASS();
}

} // namespace

int main()
{
    const std::filesystem::path tmpDir = std::filesystem::temp_directory_path() / "opencomal-z80-tests";
    std::error_code ec;
    std::filesystem::create_directories(tmpDir, ec);

    std::cout << "Running Z80 backend BDOS tests\n";
    test_assemble_source_and_run(tmpDir);
    test_hello_prints_four_times(tmpDir);
    test_assembly_breakpoint_hits_source_line(tmpDir);
    test_assembly_single_step_reports_instruction_lines(tmpDir);
    test_console_input_echo_roundtrip(tmpDir);
    test_bdos_file_and_misc_functions(tmpDir);
    test_bdos_sequential_read_reports_eof(tmpDir);

    std::cout << "Passed: " << gPassed << " Failed: " << gFailed << "\n";
    return gFailed == 0 ? 0 : 1;
}
