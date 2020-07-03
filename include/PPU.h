#pragma once

#include <cstdint>

#include "Cartridge.h"

using std::uint8_t, std::uint16_t, std::uint32_t;

class PPU
{
private:
    uint8_t tblName[2][1024];   // VRAM - 2KB
    uint8_t tblPalette[32];     // Color Palettes - 32B

    int32_t scanline;
    uint16_t cycle;

    uint16_t *currentBuffer;
    uint16_t *outputBuffers[2];

    std::shared_ptr<Cartridge> cart;

public:
    static constexpr uint32_t screenWidth = 256;
    static constexpr uint32_t screenHeight = 240;
    static constexpr uint32_t pixelCount = screenWidth * screenHeight;
    static constexpr uint32_t outputBufferSize = pixelCount * 2;
    static constexpr uint32_t decayCycleCount = 3000;

    PPU();
    ~PPU();

    // For the main bus
    uint8_t cpuRead(uint16_t addr, bool readOnly = false);
    bool cpuWrite(uint16_t addr, uint8_t data);

    // For the GPU bus
    uint8_t ppuRead(uint16_t addr, bool readOnly = false);
    bool ppuWrite(uint16_t addr, uint8_t data);

    void connectCartridge(const std::shared_ptr<Cartridge> &cart);
    void clock();
}