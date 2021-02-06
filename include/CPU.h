#include "Memory.h"
#include <iostream>

class CPU
{
public:
    void Reset(Memory& memory);
    void Execute(Memory& memory);
    void GetStatus();
private:
    uint8_t GetByte(Memory& memory);
    uint8_t ReadByte(Memory& memory, uint8_t address);

    uint16_t GetWord(Memory& memory);
    void WriteWord(Memory& memory, uint16_t data, uint32_t address);

    uint16_t pc; //Program counter
    uint8_t sp; //Stack pointer
    
    //Registers (Accumulator, index register X, index register Y)
    uint8_t A, X, Y;

    //Processor statuses (Carry flag, zero flag, interrupt disable, decimal mode, break command, overflow flag, negative flag)
    uint8_t C : 1, Z : 1, I : 1, D : 1, B : 1, V : 1, N : 1;

    uint32_t cycles;

    //Instructions
    //LDA - Load accumulator
    void LDA_IM(Memory& memory); //LDA immediate
    void LDA_ZP(Memory& memory); //LDA zero page
    void LDA_ZP_X(Memory& memory); //LDA zero page, X

    //JSR - Jump to subroutine
    void JSR_AB(Memory& memory);
};