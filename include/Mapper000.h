#pragma once
#include "Mapper.h"

#include <cstdint>

using std::uint8_t, std::uint16_t, std::uint32_t;

class Mapper000 : public Mapper
{
public:
    Mapper000();
    ~Mapper000();

    bool cpuMapRead(uint16_t addr, uint32_t &mapped_addr) override;
    bool cpuMapWrite(uint16_t addr, uint32_t &mapped_addr) override;
    bool ppuMapRead(uint16_t addr, uint32_t &mapped_addr) override;
    bool ppuMapWrite(uint16_t addr, uint32_t &mapped_addr) override;
}