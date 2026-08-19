#include "z80_com_loader.h"

#include <algorithm>
#include <fstream>
#include <iterator>
#include <vector>

namespace comal::cpm {
namespace {

void initializeCpmVectors(Z80ComImage& image)
{
    image.memory.fill(0);
    image.memory[0x0000] = 0xC3;
    image.memory[0x0001] = 0x00;
    image.memory[0x0002] = 0x00;

    image.memory[0x0005] = 0xC3;
    image.memory[0x0006] = static_cast<std::uint8_t>(Z80ComImage::kBdosEntryAddress & 0x00FF);
    image.memory[0x0007] = static_cast<std::uint8_t>((Z80ComImage::kBdosEntryAddress >> 8) & 0x00FF);
}

} // namespace

bool loadZ80ComImage(const std::string& filePath,
                     Z80ComImage& outImage,
                     std::string& error,
                     std::size_t maxProgramBytes)
{
    std::ifstream input(filePath, std::ios::binary);
    if (!input) {
        error = "Unable to open .COM file: " + filePath;
        return false;
    }

    const std::vector<std::uint8_t> bytes((std::istreambuf_iterator<char>(input)),
                                          std::istreambuf_iterator<char>());
    if (!input.good() && !input.eof()) {
        error = "Failed while reading .COM file: " + filePath;
        return false;
    }

    if (bytes.empty()) {
        error = "Empty .COM file is not allowed";
        return false;
    }

    const std::size_t hardLimit = Z80ComImage::kMemorySize - Z80ComImage::kLoadAddress;
    const std::size_t allowedSize = std::min(maxProgramBytes, hardLimit);
    if (bytes.size() > allowedSize) {
        error = "Program exceeds allowed TPA size";
        return false;
    }

    initializeCpmVectors(outImage);
    outImage.entryPoint = Z80ComImage::kLoadAddress;
    outImage.dmaAddress = Z80ComImage::kDefaultDmaAddress;
    outImage.imageSize = bytes.size();

    std::copy(bytes.begin(),
              bytes.end(),
              outImage.memory.begin() + static_cast<std::size_t>(Z80ComImage::kLoadAddress));

    error.clear();
    return true;
}

} // namespace comal::cpm
