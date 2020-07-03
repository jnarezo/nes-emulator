#include <cstdint>

#include "Bus.h"

Bus::Bus()
{
    cpu.ConnectBus(this);
}

Bus::~Bus() {}

uint8_t Bus::cpuRead(uint16_t addr, bool readOnly = false)
{
    if (addr >= 0x0000 && addr <= 0x1FFF)
    {
        // CPU read from RAM
        return ram[addr & 0x07FF];
    } else if (addr >= 0x2000 && addr <= 0x3FFF) {
        // CPU read from PPU
        return ppu.cpuRead(addr & 0x0007)
    } else if (addr >= 0x8000 && addr <= 0xFFFF) {
        // CPU read from cartridge
        return cart->cpuRead(addr);
    }

    return 0;
}

void Bus::cpuWrite(uint16_t addr, uint8_t data)
{
    if (addr >= 0x0000 && addr <= 0x1FFF)
    {
        // CPU write to RAM
        ram[addr & 0x07FF] = data;
    } else if (addr >= 0x2000 && addr <= 0x3FFF) {
        // CPU write to PPU
        ppu.cpuWrite(addr & 0x0007, data)
    } else if (addr >= 0x8000 && addr <= 0xFFFF) {
        // CPU write to cartridge
        cart->cpuWrite(addr, data);
    }
}

uint8_t Bus::ppuRead(uint16_t addr, bool readOnly = false)
{
    
}

void Bus::ppuWrite(uint16_t addr, uint8_t data)
{
    
}

void Bus::insertCart(const std::shared_ptr<Cartridge> &cart)
{
    this->cart = cart;
    ppu.connectCartridge(cart);
}

void Bus::clock()
{
    ppu.clock();
    if (systemClockCounter % 3 == 0) {
        cpu.clock();
    }
    systemClockCounter++;
}

void Bus::reset()
{
    cpu.reset();
    systemClockCounter = 0;
}