#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

struct Z80ComImage {
    static constexpr std::size_t kMemorySize = 65536;
    static constexpr std::uint16_t kLoadAddress = 0x0100;
    static constexpr std::uint16_t kWarmBootAddress = 0x0000;
    static constexpr std::uint16_t kBdosVectorAddress = 0x0005;
    static constexpr std::uint16_t kBdosEntryAddress = 0xF000;
    static constexpr std::uint16_t kDefaultDmaAddress = 0x0080;

    std::array<std::uint8_t, kMemorySize> memory{};
    std::uint16_t entryPoint{kLoadAddress};
    std::uint16_t dmaAddress{kDefaultDmaAddress};
    std::size_t imageSize{0};
};

bool loadZ80ComImage(const std::string &filePath,
                     Z80ComImage &outImage,
                     std::string &error,
                     std::size_t maxProgramBytes = Z80ComImage::kMemorySize - Z80ComImage::kLoadAddress);
