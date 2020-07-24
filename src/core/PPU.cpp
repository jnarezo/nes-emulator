#pragma once

#include "PPU.h"

using std::uint8_t, std::uint16_t, std::uint32_t;

PPU::PPU()
{
    outputBuffers[0] = new uint16_t[pixelCount];
    outputBuffers[1] = new uint16_t[pixelCount];
    currentBuffer = outputBuffers[0];
}

PPU::~PPU() {}

uint8_t PPU::cpuRead(uint16_t addr, bool readOnly)
{
    switch (addr) {
        case 0x0000:    // Control
            break;
        case 0x0001:    // Mask
            break;
        case 0x0002:    // Status
            break;
        case 0x0003:    // OAM Address
            break;
        case 0x0004:    // OAM Data
            break;
        case 0x0005:    // Scroll
            break;
        case 0x0006:    // PPU Address
            break;
        case 0x0007:    // PPU Data
            break;
        default:
            break;
    }
}

bool PPU::cpuWrite(uint16_t addr, uint8_t data)
{
    switch (addr) {
        case 0x0000:    // Control
            break;
        case 0x0001:    // Mask
            break;
        case 0x0002:    // Status
            break;
        case 0x0003:    // OAM Address
            break;
        case 0x0004:    // OAM Data
            break;
        case 0x0005:    // Scroll
            break;
        case 0x0006:    // PPU Address
            break;
        case 0x0007:    // PPU Data
            break;
        default:
            break;
    }
}

uint8_t PPU::ppuRead(uint16_t addr, bool readOnly)
{
    // Max $3FFF
    addr &= 0x3FFF;

    if (addr >= 0x0000 && addr <= 0x1FFF) {
        // PPU read from Pattern (Cartridge)
        return cart->ppuRead(addr & 0x07FF);
    } else if (addr >= 0x2000 && addr <= 0x3EFF) {
        // PPU read from nametables
        return tblName[addr >> 4][addr & 0x03FF];
    } else if (addr >= 0x3F00 && addr <= 0x3FFF) {
        // PPU read from palettes
        addr &= 0x001F;
        // Mirroring (?)
        addr &= 0x000F;
        return tblPalette[addr];
    }
    return 0x00;
}

bool PPU::ppuWrite(uint16_t addr, uint8_t data)
{
    // Max $3FFF
    addr &= 0x3FFF;

    if (addr >= 0x0000 && addr <= 0x1FFF) {
        // PPU read from Pattern (Cartridge)
        cart->ppuWrite(addr & 0x07FF, data);
    } else if (addr >= 0x2000 && addr <= 0x3EFF) {
        // PPU read from nametables
        tblName[addr >> 4][addr & 0x03FF] = data;
    } else if (addr >= 0x3F00 && addr <= 0x3FFF) {
        // PPU read from palettes
        addr &= 0x001F;
        // Mirroring (?)
        addr &= 0x000F;
        tblPalette[addr] = data;
    }
}

void PPU::connectCartridge(const std::shared_ptr<Cartridge> &cart)
{
    this->cart = cart;
}

void PPU::clock()
{
    cycle++;
    if (cycle > 340) {
        cycle = 0;
        scanline++;
        if (scanline > 260) {
            scanline = -1;
            // TODO
        }
    }
}