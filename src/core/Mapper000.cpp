#pragma once

#include "Mapper000.h"

Mapper000::Mapper000(uint8_t numPRGBanks, uint8_t numCHRBanks) : Mapper(numPRGBanks, numCHRBanks) {}

Mapper000::~Mapper000() {}

bool Mapper000::cpuMapRead(uint16_t addr, uint32_t &mapped_addr)
{
    mapped_addr = addr & ((numPRGBanks > 1) ? 0x7FFF : 0x3FFF);
    return true;
}

bool Mapper000::cpuMapWrite(uint16_t addr, uint32_t &mapped_addr)
{
    mapped_addr = addr & ((numPRGBanks > 1) ? 0x7FFF : 0x3FFF);
    return true;
}

bool Mapper000::ppuMapRead(uint16_t addr, uint32_t &mapped_addr)
{
    mapped_addr = addr;
    return true;
}

bool Mapper000::ppuMapWrite(uint16_t addr, uint32_t &mapped_addr)
{
    return false;
}