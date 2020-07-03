#pragma once

#include <cstdint>

#include "CPU.h"
#include "Bus.h"

CPU::CPU()
{
    // TODO: Probably use hashtable.
    using c = CPU;
    lookup = {
        {"BRK", &c::BRK, &c::IMP, 7}, {"ORA", &c::ORA, &c::IZX, 6}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"ORA", &c::ORA, &c::ZP0, 3}, {"ASL", &c::ASL, &c::ZP0, 5}, {"???", &c::NOP, &c::IMP, 2}, {"PHP", &c::PHP, &c::IMP, 3}, {"ORA", &c::ORA, &c::IMM, 2}, {"ASL", &c::ASL, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"ORA", &c::ORA, &c::ABS, 4}, {"ASL", &c::ASL, &c::ABS, 6}, {"???", &c::NOP, &c::IMP, 2},
        {"BPL", &c::BPL, &c::REL, 2}, {"ORA", &c::ORA, &c::IZY, 5}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"ORA", &c::ORA, &c::ZPX, 4}, {"ASL", &c::ASL, &c::ZPX, 6}, {"???", &c::NOP, &c::IMP, 2}, {"CLC", &c::CLC, &c::IMP, 2}, {"ORA", &c::ORA, &c::ABY, 4}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"ORA", &c::ORA, &c::ABX, 4}, {"ASL", &c::ASL, &c::ABX, 7}, {"???", &c::NOP, &c::IMP, 2},
        {"JSR", &c::JSR, &c::ABS, 6}, {"AND", &c::AND, &c::IZX, 6}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"BIT", &c::BIT, &c::ZP0, 3}, {"AND", &c::AND, &c::ZP0, 3}, {"ROL", &c::ROL, &c::ZP0, 5}, {"???", &c::NOP, &c::IMP, 2}, {"PLP", &c::PLP, &c::IMP, 4}, {"AND", &c::AND, &c::IMM, 2}, {"ROL", &c::ROL, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"BIT", &c::BIT, &c::ABS, 4}, {"AND", &c::AND, &c::ABS, 4}, {"ROL", &c::ROL, &c::ABS, 6}, {"???", &c::NOP, &c::IMP, 2},
        {"BMI", &c::BMI, &c::REL, 2}, {"AND", &c::AND, &c::IZY, 5}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"AND", &c::AND, &c::ZPX, 4}, {"ROL", &c::ROL, &c::ZPX, 6}, {"???", &c::NOP, &c::IMP, 2}, {"SEC", &c::SEC, &c::IMP, 2}, {"AND", &c::AND, &c::ABY, 4}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"AND", &c::AND, &c::ABX, 4}, {"ROL", &c::ROL, &c::ABX, 7}, {"???", &c::NOP, &c::IMP, 2},
        {"RTI", &c::RTI, &c::IMP, 6}, {"EOR", &c::EOR, &c::IZX, 6}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"EOR", &c::EOR, &c::ZP0, 3}, {"LSR", &c::LSR, &c::ZP0, 5}, {"???", &c::NOP, &c::IMP, 2}, {"PHA", &c::PHA, &c::IMP, 3}, {"EOR", &c::EOR, &c::IMM, 2}, {"LSR", &c::LSR, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"JMP", &c::JMP, &c::ABS, 3}, {"EOR", &c::EOR, &c::ABS, 4}, {"LSR", &c::LSR, &c::ABS, 6}, {"???", &c::NOP, &c::IMP, 2},
        {"BVC", &c::BVC, &c::REL, 2}, {"EOR", &c::EOR, &c::IZY, 5}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"EOR", &c::EOR, &c::ZPX, 4}, {"LSR", &c::LSR, &c::ZPX, 6}, {"???", &c::NOP, &c::IMP, 2}, {"CLI", &c::CLI, &c::IMP, 2}, {"EOR", &c::EOR, &c::ABY, 4}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"EOR", &c::EOR, &c::ABX, 4}, {"LSR", &c::LSR, &c::ABX, 7}, {"???", &c::NOP, &c::IMP, 2},
        {"RTS", &c::RTS, &c::IMP, 6}, {"ADC", &c::ADC, &c::IZX, 6}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"ADC", &c::ADC, &c::ZP0, 3}, {"ROR", &c::ROR, &c::ZP0, 5}, {"???", &c::NOP, &c::IMP, 2}, {"PLA", &c::PLA, &c::IMP, 4}, {"ADC", &c::ADC, &c::IMM, 2}, {"ROR", &c::ROR, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"JMP", &c::JMP, &c::IND, 5}, {"ADC", &c::ADC, &c::ABS, 4}, {"ROR", &c::ROR, &c::ABS, 6}, {"???", &c::NOP, &c::IMP, 2},
        {"BVS", &c::BVS, &c::REL, 2}, {"ADC", &c::ADC, &c::IZY, 5}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"ADC", &c::ADC, &c::ZPX, 4}, {"ROR", &c::ROR, &c::ZPX, 6}, {"???", &c::NOP, &c::IMP, 2}, {"SEI", &c::SEI, &c::IMP, 2}, {"ADC", &c::ADC, &c::ABY, 4}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"ADC", &c::ADC, &c::ABX, 4}, {"ROR", &c::ROR, &c::ABX, 7}, {"???", &c::NOP, &c::IMP, 2},
        {"???", &c::NOP, &c::IMP, 2}, {"STA", &c::STA, &c::IZX, 6}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"STY", &c::STY, &c::ZP0, 3}, {"STA", &c::STA, &c::ZP0, 3}, {"STX", &c::STX, &c::ZP0, 3}, {"???", &c::NOP, &c::IMP, 2}, {"DEY", &c::DEY, &c::IMP, 2}, {"???", &c::NOP, &c::IMM, 2}, {"TXA", &c::TXA, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"STY", &c::STY, &c::ABS, 4}, {"STA", &c::STA, &c::ABS, 4}, {"STX", &c::STX, &c::ABS, 4}, {"???", &c::NOP, &c::IMP, 2},
        {"BCC", &c::BCC, &c::REL, 2}, {"STA", &c::STA, &c::IZY, 6}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"STY", &c::STY, &c::ZPX, 4}, {"STA", &c::STA, &c::ZPX, 4}, {"STX", &c::STX, &c::ZPY, 4}, {"???", &c::NOP, &c::IMP, 2}, {"TYA", &c::TYA, &c::IMP, 2}, {"STA", &c::STA, &c::ABY, 5}, {"TXS", &c::TXS, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"STA", &c::STA, &c::ABX, 5}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2},
        {"LDY", &c::LDY, &c::IMM, 2}, {"LDA", &c::LDA, &c::IZX, 6}, {"LDX", &c::LDX, &c::IMM, 2}, {"???", &c::NOP, &c::IMP, 2}, {"LDY", &c::LDY, &c::ZP0, 3}, {"LDA", &c::LDA, &c::ZP0, 3}, {"LDX", &c::LDX, &c::ZP0, 3}, {"???", &c::NOP, &c::IMP, 2}, {"TAY", &c::TAY, &c::IMP, 2}, {"LDA", &c::LDA, &c::IMM, 2}, {"TAX", &c::TAX, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"LDY", &c::LDY, &c::ABS, 4}, {"LDA", &c::LDA, &c::ABS, 4}, {"LDX", &c::LDX, &c::ABS, 4}, {"???", &c::NOP, &c::IMP, 2},
        {"BCS", &c::BCS, &c::REL, 2}, {"LDA", &c::LDA, &c::IZY, 5}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"LDY", &c::LDY, &c::ZPX, 4}, {"LDA", &c::LDA, &c::ZPX, 4}, {"LDX", &c::LDX, &c::ZPY, 4}, {"???", &c::NOP, &c::IMP, 2}, {"CLV", &c::CLV, &c::IMP, 2}, {"LDA", &c::LDA, &c::ABY, 4}, {"TSX", &c::TSX, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"LDY", &c::LDY, &c::ABX, 4}, {"LDA", &c::LDA, &c::ABX, 4}, {"LDX", &c::LDX, &c::ABY, 4}, {"???", &c::NOP, &c::IMP, 2},
        {"CPY", &c::CPY, &c::IMM, 2}, {"CMP", &c::CMP, &c::IZX, 6}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"CPY", &c::CPY, &c::ZP0, 3}, {"CMP", &c::CMP, &c::ZP0, 3}, {"DEC", &c::DEC, &c::ZP0, 5}, {"???", &c::NOP, &c::IMP, 2}, {"INY", &c::INY, &c::IMP, 2}, {"CMP", &c::CMP, &c::IMM, 2}, {"DEX", &c::DEX, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"CPY", &c::CPY, &c::ABS, 4}, {"CMP", &c::CMP, &c::ABS, 4}, {"DEC", &c::DEC, &c::ABS, 6}, {"???", &c::NOP, &c::IMP, 2},
        {"BNE", &c::BNE, &c::REL, 2}, {"CMP", &c::CMP, &c::IZY, 5}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"CMP", &c::CMP, &c::ZPX, 4}, {"DEC", &c::DEC, &c::ZPX, 6}, {"???", &c::NOP, &c::IMP, 2}, {"CLD", &c::CLD, &c::IMP, 2}, {"CMP", &c::CMP, &c::ABY, 4}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"CMP", &c::CMP, &c::ABX, 4}, {"DEC", &c::DEC, &c::ABX, 7}, {"???", &c::NOP, &c::IMP, 2},
        {"CPX", &c::CPX, &c::IMM, 2}, {"SBC", &c::SBC, &c::IZX, 6}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"CPX", &c::CPX, &c::ZP0, 3}, {"SBC", &c::SBC, &c::ZP0, 3}, {"INC", &c::INC, &c::ZP0, 5}, {"???", &c::NOP, &c::IMP, 2}, {"INX", &c::INX, &c::IMP, 2}, {"SBC", &c::SBC, &c::IMM, 2}, {"NOP", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"CPX", &c::CPX, &c::ABS, 4}, {"SBC", &c::SBC, &c::ABS, 4}, {"INC", &c::INC, &c::ABS, 6}, {"???", &c::NOP, &c::IMP, 2},
        {"BEQ", &c::BEQ, &c::REL, 2}, {"SBC", &c::SBC, &c::IZY, 5}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"SBC", &c::SBC, &c::ZPX, 4}, {"INC", &c::INC, &c::ZPX, 6}, {"???", &c::NOP, &c::IMP, 2}, {"SED", &c::SED, &c::IMP, 2}, {"SBC", &c::SBC, &c::ABY, 4}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"???", &c::NOP, &c::IMP, 2}, {"SBC", &c::SBC, &c::ABX, 4}, {"INC", &c::INC, &c::ABX, 7}, {"???", &c::NOP, &c::IMP, 2},
    };
    bus = nullptr;
}

CPU::~CPU()
{

}

void CPU::ConnectBus(Bus* b)
{
    bus = b;
}

uint8_t CPU::read(uint16_t addr)
{
    return bus->cpuRead(addr, false);
}

void CPU::write(uint16_t addr, uint8_t data)
{
    bus->cpuWrite(addr, data);
}

uint8_t CPU::fetch()
{
    if (lookup[opcode].addrmode != &CPU::IMP) {
        fetched = read(absAddr);
    }
    return fetched;
}

// Addressing Modes

uint8_t CPU::IMP()
{
    fetched = a;
    return 0;
}

uint8_t CPU::IMM()
{
    absAddr = pc;
    pc++;
    return 0;
}

uint8_t CPU::REL()
{
    relAddr = read(pc);
    pc++;

    // Relative address is signed, so if negative, we need int16 signed.
    if (relAddr & 0x80) relAddr |= 0xFF00;
    return 0;
}

uint8_t CPU::ZP0()
{
    absAddr = read(pc);
    pc++;
    
    absAddr &= 0x00FF;
    return 0;
}

uint8_t CPU::ZPX()
{
    absAddr = (read(pc) + x) & 0x00FF;
    pc++;
    return 0;
}

uint8_t CPU::ZPY()
{
    absAddr = (read(pc) + y) & 0x00FF;
    pc++;
    return 0;
}

uint8_t CPU::ABS()
{
    uint8_t low = read(pc);
    pc++;
    uint8_t high = read(pc);
    pc++;

    absAddr = (high << 8) | low; // Place in Big-Endian
    return 0;
}
uint8_t CPU::ABX()
{
    uint8_t low = read(pc);
    pc++;
    uint8_t high = read(pc);
    pc++;

    absAddr = (high << 8) | low; // Place in Big-Endian
    absAddr += x;

    // If the page changed, we need another cycle.
    return (((absAddr & 0xFF00) >> 8) != high) ? 1 : 0;
}

uint8_t CPU::ABY()
{
    uint8_t low = read(pc);
    pc++;
    uint8_t high = read(pc);
    pc++;

    absAddr = (high << 8) | low;  // Place in Big-Endian
    absAddr += y;

    // If the page changed, we need another cycle.
    return (((absAddr & 0xFF00) >> 8) != high) ? 1 : 0;
}

uint8_t CPU::IND()
{
    uint8_t low = read(pc);
    pc++;
    uint8_t high = read(pc);
    uint8_t nextLow = static_cast<uint8_t>(low + 1);
    
    pc = read((high << 8) | nextLow) | read((high << 8) | low);
    return 0;
}

uint8_t CPU::IZX()
{
    uint8_t start = read(pc);
    pc++;

    uint8_t low = read((start + static_cast<uint16_t>(x)) & 0x00FF);
    uint8_t high = read(static_cast<uint16_t>(start + static_cast<uint16_t>(x) + 1) & 0x00FF);

    absAddr = (high << 8) | low;
    return 0;
}

uint8_t CPU::IZY()
{
    uint8_t start = read(pc);
    pc++;

    uint8_t low = read(start & 0x00FF);
    uint8_t high = read(static_cast<uint16_t>(start + 1) & 0x00FF);

    absAddr = (high << 8) | low;
    absAddr += y;

    // If the page changed, we need another cycle.
    return (((absAddr & 0xFF00) >> 8) != high) ? 1 : 0;
}

// Operations

uint8_t CPU::ADC()
{
    fetch();

    uint16_t result = a + fetched + getFlag(C);
    setFlag(C, result & 0xFF00);
    setFlag(Z, (result & 0x00FF) == 0x00);
    setFlag(V, (a ^ result) & (fetched ^ result) & 0x0080);
    setFlag(N, result & 0x0080);
    a = result;
    return 1;
}

uint8_t CPU::AND()
{
    fetch();

    a &= fetched;
    setFlag(Z, a == 0x00);
    setFlag(N, a & 0x80);
    return 1;
}

uint8_t CPU::ASL()
{
    fetch();

    uint8_t data = fetched;
    setFlag(C, data & 0x80);
    data <<= 1;

    write(absAddr, data);
    setFlag(Z, data == 0x00);
    setFlag(N, data & 0x80);
    return 0;
}

uint8_t CPU::BCC()
{
    if (getFlag(C) == 0) {
        cycles++;
        absAddr = pc + relAddr;

        // Another cycle for different page.
        if ((absAddr & 0xFF00) != (pc & 0xFF00))
        {
            cycles++;
        }

        pc = absAddr;
    }
    return 0;
}

uint8_t CPU::BCS()
{
    if (getFlag(C) == 1) {
        cycles++;
        absAddr = pc + relAddr;

        // Another cycle for different page.
        if ((absAddr & 0xFF00) != (pc & 0xFF00))
        {
            cycles++;
        }

        pc = absAddr;
    }
    return 0;
}

uint8_t CPU::BEQ()
{
    if (getFlag(Z) == 1) {
        cycles++;
        absAddr = pc + relAddr;

        // Another cycle for different page.
        if ((absAddr & 0xFF00) != (pc & 0xFF00))
        {
            cycles++;
        }

        pc = absAddr;
    }
    return 0;
}

uint8_t CPU::BIT()
{
    fetch();

    setFlag(Z, a & fetched);
    setFlag(V, fetched & 0x40);
    setFlag(N, fetched & 0x80);
    return 0;
}

uint8_t CPU::BMI()
{
    if (getFlag(N) == 1) {
        cycles++;
        absAddr = pc + relAddr;

        // Another cycle for different page.
        if ((absAddr & 0xFF00) != (pc & 0xFF00))
        {
            cycles++;
        }

        pc = absAddr;
    }
    return 0;
}

uint8_t CPU::BNE()
{
    if (getFlag(Z) == 0) {
        cycles++;
        absAddr = pc + relAddr;

        // Another cycle for different page.
        if ((absAddr & 0xFF00) != (pc & 0xFF00))
        {
            cycles++;
        }

        pc = absAddr;
    }
    return 0;
}

uint8_t CPU::BPL()
{
    if (getFlag(N) == 0) {
        cycles++;
        absAddr = pc + relAddr;

        // Another cycle for different page.
        if ((absAddr & 0xFF00) != (pc & 0xFF00))
        {
            cycles++;
        }

        pc = absAddr;
    }
    return 0;
}

uint8_t CPU::BRK()
{
    // Save state onto the stack.
    write(STACK_ADDRESS + stkp, (pc >> 8) & 0x00FF);
    stkp--;
    write(STACK_ADDRESS + stkp, pc & 0x00FF);
    stkp--;

    setFlag(B, 1);
    write(STACK_ADDRESS + stkp, status);
    stkp--;

    // Find interrupt routine.
    absAddr = IRQ_ADDRESS;
    uint8_t low = read(absAddr);
    uint8_t high = read(absAddr + 1);
    pc = (high << 8) | low;
    
    setFlag(I, 1);
    return 0;
}

uint8_t CPU::BVC()
{
    if (getFlag(V) == 0) {
        cycles++;
        absAddr = pc + relAddr;

        // Another cycle for different page.
        if ((absAddr & 0xFF00) != (pc & 0xFF00))
        {
            cycles++;
        }

        pc = absAddr;
    }
    return 0;
}

uint8_t CPU::BVS()
{
    if (getFlag(V) == 1) {
        cycles++;
        absAddr = pc + relAddr;

        // Another cycle for different page.
        if ((absAddr & 0xFF00) != (pc & 0xFF00))
        {
            cycles++;
        }

        pc = absAddr;
    }
    return 0;
}

uint8_t CPU::CLC()
{
    setFlag(C, false);
    return 0;
}

uint8_t CPU::CLD()
{
    setFlag(D, false);
    return 0;
}

uint8_t CPU::CLI()
{
    setFlag(I, false);
    return 0;
}

uint8_t CPU::CLV()
{
    setFlag(V, false);
    return 0;
}

uint8_t CPU::CMP()
{
    fetch();

    uint16_t temp = a + (~fetched + 1);
    setFlag(C, temp & 0x0100);
    setFlag(Z, (temp & 0x00FF) == 0);
    setFlag(N, temp & 0x0080);
    return 1;
}

uint8_t CPU::CPX()
{
    fetch();

    uint16_t temp = x + (~fetched + 1);
    setFlag(C, temp & 0x0100);
    setFlag(Z, (temp & 0x00FF) == 0);
    setFlag(N, temp & 0x0080);
    return 0;
}

uint8_t CPU::CPY()
{
    fetch();

    uint16_t temp = y + (~fetched + 1);
    setFlag(C, temp & 0x0100);
    setFlag(Z, (temp & 0x00FF) == 0);
    setFlag(N, temp & 0x0080);
    return 0;
}

uint8_t CPU::DEC()
{
    // Decrements by 1.
    fetch();
    fetched += 0XFF;

    write(absAddr, fetched);
    setFlag(Z, fetched == 0x00);
    setFlag(N, fetched & 0x80);
    return 0;
}

uint8_t CPU::DEX()
{
    x += 0xFF;
    setFlag(Z, x == 0x00);
    setFlag(N, x & 0x80);
    return 0;
}

uint8_t CPU::DEY()
{
    y += 0xFF;
    setFlag(Z, y == 0x00);
    setFlag(N, y & 0x80);
    return 0;
}

uint8_t CPU::EOR()
{
    fetch();

    a ^= fetched;
    setFlag(Z, a == 0x00);
    setFlag(N, a & 0x80);
    return 1;
}

uint8_t CPU::INC()
{
    fetch();

    fetched += 0x01;
    write(absAddr, fetched);

    setFlag(Z, fetched == 0x00);
    setFlag(N, fetched & 0x80);
    return 0;
}

uint8_t CPU::INX()
{
    x += 0x01;
    setFlag(Z, x == 0x00);
    setFlag(N, x & 0x80);
    return 0;
}

uint8_t CPU::INY()
{
    y += 0x01;
    setFlag(Z, y == 0x00);
    setFlag(N, y & 0x80);
    return 0;
}

uint8_t CPU::JMP()
{
    fetch();

    pc = fetched;
    return 0;
}

uint8_t CPU::JSR()
{
    fetch();

    // Save program counter onto the stack.
    write(STACK_ADDRESS + stkp, (pc >> 8) & 0x00FF);
    stkp--;
    write(STACK_ADDRESS + stkp, pc & 0x00FF);
    stkp--;

    // Load subroutine.
    pc = fetched;
    return 0;
}

uint8_t CPU::LDA()
{
    fetch();

    a = fetched;
    return 1;
}

uint8_t CPU::LDX()
{
    fetch();

    x = fetched;
    return 1;
}

uint8_t CPU::LDY()
{
    fetch();

    y = fetched;
    return 1;
}

uint8_t CPU::LSR()
{
    setFlag(C, a & 0x01);

    a >>= 1;

    setFlag(Z, a == 0x00);
    setFlag(N, false);
    return 0;
}

uint8_t CPU::NOP()
{
    return 0;
}

uint8_t CPU::ORA()
{
    fetch();

    a |= fetched;
    setFlag(Z, a == 0x00);
    setFlag(N, a & 0x80);
    return 0;
}

uint8_t CPU::PHA()
{
    write(0x0100 + stkp, a);
    stkp--;
    return 0;
}

uint8_t CPU::PHP()
{
    write(0x0100 + stkp, pc);
    stkp--;
    return 0;
}

uint8_t CPU::PLA()
{
    stkp++;
    a = read(0x0100 + stkp);

    setFlag(Z, a == 0x00);
    setFlag(N, a & 0x80);
    return 0;
}

uint8_t CPU::PLP()
{
    stkp++;
    status = read(0x0100 + stkp);

    setFlag(Z, status == 0x00);
    setFlag(N, status & 0x80);
    return 0;
}

uint8_t CPU::ROL()
{
    setFlag(C, a & 0x80);

    a = (a << 1) | getFlag(C);

    setFlag(Z, a == 0x00);
    setFlag(N, a & 0x80);
    return 0;
}

uint8_t CPU::ROR()
{
    setFlag(C, a & 0x01);

    a = (getFlag(C) << 7) | (a >> 1);

    setFlag(Z, a == 0x00);
    setFlag(N, a & 0x80);
    return 0;
}

uint8_t CPU::RTI()
{
    // Retrieve status from stack.
    stkp++;
    status = read(STACK_ADDRESS + stkp);
    setFlag(I, 0);
    setFlag(B, 0);
    setFlag(U, 1);

    // Load program counter from stack.
    stkp++;
    uint8_t low = read(STACK_ADDRESS + stkp);
    stkp++;
    uint8_t high = read(STACK_ADDRESS + stkp);
    pc = (high << 8) | low;
    
    return 0;
}

uint8_t CPU::RTS()
{
    // Load program counter from stack.
    stkp++;
    uint8_t low = read(STACK_ADDRESS + stkp);
    stkp++;
    uint8_t high = read(STACK_ADDRESS + stkp);
    pc = (high << 8) | low;
    
    return 0;
}

uint8_t CPU::SBC()
{
    fetch();
    fetched = ~fetched + 1;

    uint16_t result = a + fetched + getFlag(C);
    setFlag(C, result & 0xFF00);
    setFlag(Z, (result & 0x00FF) == 0x00);
    setFlag(V, (a ^ result) & (fetched ^ result) & 0x0080);
    setFlag(N, result & 0x0080);
    a = result & 0x00FF;
    return 1;
}

uint8_t CPU::SEC()
{
    setFlag(C, true);
    return 0;
}

uint8_t CPU::SED()
{
    setFlag(D, true);
    return 0;
}

uint8_t CPU::SEI()
{
    setFlag(I, true);
    return 0;
}

uint8_t CPU::STA()
{
    write(absAddr, a);
    return 0;
}

uint8_t CPU::STX()
{
    write(absAddr, x);
    return 0;
}

uint8_t CPU::STY()
{
    write(absAddr, y);
    return 0;
}

uint8_t CPU::TAX()
{
    x = a;
    setFlag(Z, x == 0x00);
    setFlag(N, x & 0x80);
    return 0;
}

uint8_t CPU::TAY()
{
    y = a;
    setFlag(Z, y == 0x00);
    setFlag(N, y & 0x80);
    return 0;
}

uint8_t CPU::TSX()
{
    x = stkp;
    setFlag(Z, x == 0x00);
    setFlag(N, x & 0x80);
    return 0;
}

uint8_t CPU::TXA()
{
    a = x;
    setFlag(Z, a == 0x00);
    setFlag(N, a & 0x80);
    return 0;
}

uint8_t CPU::TXS()
{
    stkp = x;
    setFlag(Z, stkp == 0x00);
    setFlag(N, stkp & 0x80);
    return 0;
}

uint8_t CPU::TYA()
{
    a = y;
    setFlag(Z, a == 0x00);
    setFlag(N, a & 0x80);
    return 0;
}

uint8_t CPU::XXX()
{
    // Illegal.
    return 0;
}

void CPU::clock()
{
    // Entire operation performed at once, NOT CLOCK-CYCLE ACCURATE
    if (cycles == 0) {
        // Parse opcode
        opcode = read(pc);
        pc++;

        // Get operation cycle time
        cycles = lookup[opcode].cycles;

        // Prep address and perform operation
        // Perform additional cycles if necessary
        cycles += (this->*lookup[opcode].addrmode)() & (this->*lookup[opcode].operate)();
    }
    cycles--;
}

uint8_t CPU::getFlag(FLAGS6502 flag)
{
    return (status & flag) / flag;
}

void CPU::setFlag(FLAGS6502 flag, bool val)
{
    if (val) {
        status |= flag;
    } else {
        status &= ~flag;
    }
}

void CPU::reset()
{
    a = 0;
    x = 0;
    y = 0;
    stkp = 0xFD;
    status = 0x00 | U;

    absAddr = RESET_ADDRESS;
    uint8_t low = read(absAddr);
    uint8_t high = read(absAddr + 1);
    pc = (high << 8) | low;

    absAddr = 0x0000;
    relAddr = 0x0000;
    fetched = 0x00;
}

void CPU::intrq()
{
    if (getFlag(I) == 0) {
        // Save program counter to stack.
        write(STACK_ADDRESS + stkp, (pc >> 8) & 0x00FF);
        stkp--;
        write(STACK_ADDRESS + stkp, pc & 0x00FF);
        stkp--;

        // Save status to stack.
        setFlag(B, 0);
        setFlag(U, 1);
        setFlag(I, 1);
        write(STACK_ADDRESS + stkp, status);
        stkp--;

        // Find interrupt routine.
        absAddr = IRQ_ADDRESS;
        uint8_t low = read(absAddr);
        uint8_t high = read(absAddr + 1);
        pc = (high << 8) | low;

        cycles = 7;
    }
}

void CPU::nmint()
{
    // Save program counter to stack.
    write(STACK_ADDRESS + stkp, (pc >> 8) & 0x00FF);
    stkp--;
    write(STACK_ADDRESS + stkp, pc & 0x00FF);
    stkp--;

    // Save status to stack.
    setFlag(B, 0);
    setFlag(U, 1);
    setFlag(I, 1);
    write(STACK_ADDRESS + stkp, status);
    stkp--;

    // Find interrupt routine.
    absAddr = NMI_ADDRESS;
    uint8_t low = read(absAddr);
    uint8_t high = read(absAddr + 1);
    pc = (high << 8) | low;

    cycles = 8;
}