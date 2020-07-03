#pragma once

#include <cstdint>
#include <string>
#include <vector>

class Bus;

class CPU
{
public:
    enum FLAGS6502
    {
        C = (1 << 0),   // Carry Bit
        Z = (1 << 1),   // Zero Bit
        I = (1 << 2),   // Disable Interrupts Bit
        D = (1 << 3),   // Decimal Mode (unused in NES)
        B = (1 << 4),   // Break Bit
        U = (1 << 5),   // Unused Bit
        V = (1 << 6),   // Overflow Bit
        N = (1 << 7),   // Negative Bit
    };

    // Registers
    uint8_t a = 0x00;       // Accumulator Register
    uint8_t x = 0x00;       // X Register
    uint8_t y = 0x00;       // Y Register
    uint8_t stkp = 0x00;    // Stack Pointer Offset (Bus)
    uint16_t pc = 0x0000;   // Program Counter
    uint8_t status = 0x00;  // Status Register (Flags)

private:
    const uint16_t STACK_ADDRESS = 0x0100;
    const uint16_t NMI_ADDRESS = 0xFFFA;
    const uint16_t RESET_ADDRESS = 0xFFFC;
    const uint16_t IRQ_ADDRESS = 0xFFFE;

    struct INSTRUCTION
    {
        std::string name;
        uint8_t (CPU::*operate)(void) = nullptr;
        uint8_t (CPU::*addrmode)(void) = nullptr;
        uint8_t cycles = 0;
    };

    Bus* bus;

    std::vector<INSTRUCTION> lookup;

    /**
     * @brief Reads data from the address on the main bus.
     * 
     * @param addr 16-bit address
     * @return uint8_t 8-bit data
     */
    uint8_t read(uint16_t addr);
    
    /**
     * @brief Writes data to the address on the main bus.
     * 
     * @param addr 16-bit address
     * @param data 8-bit data
     */
    void write(uint16_t addr, uint8_t data);

    uint8_t getFlag(FLAGS6502 flag);
    void setFlag(FLAGS6502 flag, bool val);

public:
    CPU();
    ~CPU();

    uint16_t absAddr = 0x0000;
    uint16_t relAddr = 0x0000;
    uint8_t opcode = 0x00;
    uint8_t cycles = 0;

    uint8_t fetched = 0x00;

    // Addressing Modes
    uint8_t IMP();  uint8_t IMM();  uint8_t REL();
    uint8_t ZP0();  uint8_t ZPX();  uint8_t ZPY();
    uint8_t ABS();  uint8_t ABX();  uint8_t ABY();
    uint8_t IND();  uint8_t IZX();  uint8_t IZY();

    // Operations
    uint8_t ADC();   uint8_t AND();  uint8_t ASL();  uint8_t BCC();
    uint8_t BCS();   uint8_t BEQ();  uint8_t BIT();  uint8_t BMI();
    uint8_t BNE();   uint8_t BPL();  uint8_t BRK();  uint8_t BVC();
    uint8_t BVS();   uint8_t CLC();  uint8_t CLD();  uint8_t CLI();
    uint8_t CLV();   uint8_t CMP();  uint8_t CPX();  uint8_t CPY();
    uint8_t DEC();   uint8_t DEX();  uint8_t DEY();  uint8_t EOR();
    uint8_t INC();   uint8_t INX();  uint8_t INY();  uint8_t JMP();
    uint8_t JSR();   uint8_t LDA();  uint8_t LDX();  uint8_t LDY();
    uint8_t LSR();   uint8_t NOP();  uint8_t ORA();  uint8_t PHA();
    uint8_t PHP();   uint8_t PLA();  uint8_t PLP();  uint8_t ROL();
    uint8_t ROR();   uint8_t RTI();  uint8_t RTS();  uint8_t SBC();
    uint8_t SEC();   uint8_t SED();  uint8_t SEI();  uint8_t STA();
    uint8_t STX();   uint8_t STY();  uint8_t TAX();  uint8_t TAY();
    uint8_t TSX();   uint8_t TXA();  uint8_t TXS();  uint8_t TYA();
    uint8_t XXX();

    // Internal Methods
    uint8_t fetch();

    // External Pins
    void clock();
    void reset();
    void intrq();
    void nmint();

    // External Actions
    void ConnectBus(Bus* b);
};