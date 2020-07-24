#pragma once

#include <cstdint>
#include <array>
#include <memory>

#include "CPU.h"
#include "PPU.h"
#include "Cartridge.h"

using std::uint8_t, std::uint16_t, std::uint32_t;

class Bus
{
private:
    uint32_t systemClockCounter;

public:
    Bus();
    ~Bus();

    CPU cpu;
    PPU ppu;

    std::array<uint8_t, 2048> ram;
    std::shared_ptr<Cartridge> cart;

    uint8_t cpuRead(uint16_t addr, bool readOnly = false);
    void cpuWrite(uint16_t addr, uint8_t data);

    uint8_t ppuRead(uint16_t addr, bool readOnly = false);
    void ppuWrite(uint16_t addr, uint8_t data);

    void insertCart(const std::shared_ptr<Cartridge> &cart);
    void clock();
    void reset();
};