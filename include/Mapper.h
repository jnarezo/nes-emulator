#pragma once

#include <cstdint>

using std::uint8_t, std::uint16_t, std::uint32_t;

class Mapper
{
protected:
    uint8_t numPRGBanks = 0;
    uint8_t numCHRBanks = 0;

public:
    Mapper(uint8_t numPRGBanks, uint8_t numCHRBanks);
    ~Mapper();

    virtual bool cpuMapRead(uint16_t addr, uint32_t &mapped_addr) = 0;
    virtual bool cpuMapWrite(uint16_t addr, uint32_t &mapped_addr) = 0;
    virtual bool ppuMapRead(uint16_t addr, uint32_t &mapped_addr) = 0;
    virtual bool ppuMapWrite(uint16_t addr, uint32_t &mapped_addr) = 0;
};