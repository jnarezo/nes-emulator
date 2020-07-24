#pragma once

#include <cstdint>
#include <vector>
#include <memory>

#include "Mapper000.h"

using std::uint8_t, std::uint16_t, std::uint32_t;

class Cartridge
{
private:
    std::vector<uint8_t> PRGMemory;
    std::vector<uint8_t> CHRMemory;

    uint8_t mapperID = 0;
    uint8_t numPRGBanks = 0;
    uint8_t numCHRBanks = 0;

    std::shared_ptr<Mapper> mapper;

public:
    Cartridge(const std::string &fileName);
    ~Cartridge();

    bool imageValid();

    // For the CPU
    uint8_t cpuRead(uint16_t addr);
    void cpuWrite(uint16_t addr, uint8_t data);
    
    // For the PPU
    uint8_t ppuRead(uint16_t addr);
    void ppuWrite(uint16_t addr, uint8_t data);
};