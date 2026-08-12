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

    const std::string output = result.errorMessage.toStdString();
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
    const std::string output = result.errorMessage.toStdString();
    ASSERT_TRUE(output.find("HelloHelloHelloHello") != std::string::npos,
                "expected repeated Hello output not found");

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
    const std::string output = result.errorMessage.toStdString();
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
    const std::string output = result.errorMessage.toStdString();
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
    const std::string output = result.errorMessage.toStdString();
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
    test_console_input_echo_roundtrip(tmpDir);
    test_bdos_file_and_misc_functions(tmpDir);
    test_bdos_sequential_read_reports_eof(tmpDir);

    std::cout << "Passed: " << gPassed << " Failed: " << gFailed << "\n";
    return gFailed == 0 ? 0 : 1;
}
