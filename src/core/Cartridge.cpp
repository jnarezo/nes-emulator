#pragma once

#include <cstdint>
#include <iostream>
#include <fstream>

#include "Cartridge.h"

using std::uint8_t, std::uint16_t, std::uint32_t;

Cartridge::Cartridge(const std::string &fileName)
{
    // iNES Format
    struct sHeader {
        uint8_t prgRomChunks;
        uint8_t chrRomChunks;
        uint8_t mapper1;
        uint8_t mapper2;
        uint8_t prgRamSize;
        uint8_t tvSystem1;
        uint8_t tvSystem2;
        char unusued[5];
    } nesHeader;

    std::ifstream ifs;
    ifs.open(fileName, std::ifstream::binary);
    if (ifs.is_open())
    {
        ifs.read(reinterpret_cast<char*>(&nesHeader), sizeof(sHeader));

        if (nesHeader.mapper1 & 0x04) ifs.seekg(512, std::ios_base::cur);

        // Find mapper ID.
        mapperID = ((nesHeader.mapper2 >> 4) << 4) | (nesHeader.mapper1 >> 4);

        // TODO: Determine file format.
        uint8_t fileType = 1;

        // Read file information.
        if (fileType == 0) {

        } else if (fileType == 1) {
            numPRGBanks = nesHeader.prgRomChunks;
            PRGMemory.resize(numPRGBanks * 16384);
            ifs.read(reinterpret_cast<char*>(PRGMemory.data()), PRGMemory.size());

            numCHRBanks = nesHeader.chrRomChunks;
            CHRMemory.resize(numCHRBanks * 8192);
            ifs.read(reinterpret_cast<char*>(CHRMemory.data()), CHRMemory.size());
        } else if (fileType == 2) {

        }

        switch (mapperID) {
            default:
            case 0:
                mapper = std::make_shared<Mapper000>(numPRGBanks, numCHRBanks);
                break;
        }
    }
    ifs.close();
}

Cartridge::~Cartridge()
{

}

// For the CPU bus
uint8_t Cartridge::cpuRead(uint16_t addr)
{
    uint32_t mapped_addr = 0;
    if (mapper->cpuMapRead(addr, mapped_addr)) {
        return PRGMemory[mapped_addr];
    }
    return 0;
}

void Cartridge::cpuWrite(uint16_t addr, uint8_t data)
{
    uint32_t mapped_addr = 0;
    if (mapper->cpuMapWrite(addr, mapped_addr)) {
        PRGMemory[mapped_addr] = data;
    }
}
    
// For the PPUbus
uint8_t Cartridge::ppuRead(uint16_t addr)
{
    uint32_t mapped_addr = 0;
    if (mapper->ppuMapRead(addr, mapped_addr)) {
        return CHRMemory[mapped_addr];
    }
    return 0;
}

void Cartridge::ppuWrite(uint16_t addr, uint8_t data)
{
    uint32_t mapped_addr = 0;
    if (mapper->ppuMapWrite(addr, mapped_addr)) {
        PRGMemory[mapped_addr] = data;
    }
}