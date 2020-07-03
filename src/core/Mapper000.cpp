#pragma once

#include "Mapper000.h"

Mapper::Mapper(uint8_t numPRGBanks, uint8_t numCHRBanks)
{
    this->numPRGBanks = numPRGBanks;
    this->numCHRBanks = numCHRBanks;
}

Mapper::~Mapper() {}

bool cpuMapRead(uint16_t addr, uint32_t &mapped_addr)
{
    mapped_addr = addr & ((numPRGBanks > 1) ? 0x7FFF : 0x3FFF);
    return true;
}

bool cpuMapWrite(uint16_t addr, uint32_t &mapped_addr)
{
    mapped_addr = addr & ((numPRGBanks > 1) ? 0x7FFF : 0x3FFF);
    return true;
}

bool ppuMapRead(uint16_t addr, uint32_t &mapped_addr)
{
    mapped_addr = addr;
    return true;
}

bool ppuMapWrite(uint16_t addr, uint32_t &mapped_addr)
{
    return false;
}