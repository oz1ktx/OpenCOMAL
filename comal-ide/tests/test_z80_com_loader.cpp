#include "z80_com_loader.h"

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>

namespace {

using comal::cpm::Z80ComImage;
using comal::cpm::loadZ80ComImage;

int gPassed = 0;
int gFailed = 0;

#define TEST(name) do { std::cout << "  " #name "... "; std::cout.flush(); } while (0)
#define PASS() do { std::cout << "OK\n"; ++gPassed; } while (0)
#define FAIL(msg) do { std::cout << "FAIL: " << (msg) << "\n"; ++gFailed; } while (0)
#define ASSERT_TRUE(cond, msg) do { if (!(cond)) { FAIL(msg); return; } } while (0)

void test_load_fixture_success(const std::filesystem::path &fixturePath)
{
    TEST(load_fixture_success);
    Z80ComImage image;
    std::string error;
    const bool ok = loadZ80ComImage(fixturePath.string(), image, error);
    ASSERT_TRUE(ok, error);
    ASSERT_TRUE(image.entryPoint == 0x0100, "entry point must be 0x0100");
    ASSERT_TRUE(image.dmaAddress == 0x0080, "DMA default must be 0x0080");
    ASSERT_TRUE(image.imageSize > 0, "image size should be non-zero");
    PASS();
}

void test_low_memory_vectors(const std::filesystem::path &fixturePath)
{
    TEST(low_memory_vectors);
    Z80ComImage image;
    std::string error;
    const bool ok = loadZ80ComImage(fixturePath.string(), image, error);
    ASSERT_TRUE(ok, error);
    ASSERT_TRUE(image.memory[0x0000] == 0xC3, "warm boot vector opcode mismatch");
    ASSERT_TRUE(image.memory[0x0001] == 0x00 && image.memory[0x0002] == 0x00,
                "warm boot vector target mismatch");
    ASSERT_TRUE(image.memory[0x0005] == 0xC3, "BDOS vector opcode mismatch");
    ASSERT_TRUE(image.memory[0x0006] == 0x00 && image.memory[0x0007] == 0xF0,
                "BDOS vector target mismatch");
    PASS();
}

void test_program_bytes_loaded_at_0100(const std::filesystem::path &fixturePath)
{
    TEST(program_bytes_loaded_at_0100);
    Z80ComImage image;
    std::string error;
    const bool ok = loadZ80ComImage(fixturePath.string(), image, error);
    ASSERT_TRUE(ok, error);

    ASSERT_TRUE(image.memory[0x0100] == 0x11, "expected LD DE opcode at 0x0100");
    ASSERT_TRUE(image.memory[0x0101] == 0x0D && image.memory[0x0102] == 0x01,
                "expected message address immediate for LD DE");
    ASSERT_TRUE(image.memory[0x0103] == 0x0E && image.memory[0x0104] == 0x09,
                "expected LD C,9 sequence");
    ASSERT_TRUE(image.memory[0x0105] == 0xCD && image.memory[0x0106] == 0x05 && image.memory[0x0107] == 0x00,
                "expected CALL 0005h sequence");
    PASS();
}

void test_reject_tpa_overflow(const std::filesystem::path &fixturePath)
{
    TEST(reject_tpa_overflow);
    Z80ComImage image;
    std::string error;
    const bool ok = loadZ80ComImage(fixturePath.string(), image, error, 8);
    ASSERT_TRUE(!ok, "expected failure when maxProgramBytes is too small");
    ASSERT_TRUE(!error.empty(), "expected non-empty error message");
    PASS();
}

} // namespace

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cerr << "Usage: test_z80_com_loader <path-to-demo.com>\n";
        return 2;
    }

    const std::filesystem::path fixturePath(argv[1]);
    if (!std::filesystem::exists(fixturePath)) {
        std::cerr << "Fixture not found: " << fixturePath << "\n";
        return 2;
    }

    std::cout << "Running Z80 COM loader tests\n";
    test_load_fixture_success(fixturePath);
    test_low_memory_vectors(fixturePath);
    test_program_bytes_loaded_at_0100(fixturePath);
    test_reject_tpa_overflow(fixturePath);

    std::cout << "Passed: " << gPassed << " Failed: " << gFailed << "\n";
    return gFailed == 0 ? 0 : 1;
}
