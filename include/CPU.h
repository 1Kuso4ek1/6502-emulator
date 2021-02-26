#include "Memory.h"
#include <iostream>

class CPU
{
public:
    void Reset(Memory& memory, uint16_t start);
    void Execute(Memory& memory);
    void GetStatus(Memory& memory);
private:
    uint8_t GetByte(Memory& memory);
    uint8_t ReadByte(Memory& memory, uint16_t address);
    void WriteByte(Memory& memory, uint16_t address, uint8_t data);

    uint16_t GetWord(Memory& memory);
    uint16_t ReadWord(Memory& memory, uint16_t address);
    void WriteWord(Memory& memory, uint16_t data, uint16_t address);

    uint16_t GetStackWord(Memory& memory);
    void WriteWordToStack(Memory& memory, uint16_t data);

    uint8_t GetStackByte(Memory& memory);
    void WriteByteToStack(Memory& memory, uint8_t data);

    uint16_t pc; //Program counter
    uint8_t sp; //Stack pointer
    
    //Registers (Accumulator, index register X, index register Y)
    uint8_t A, X, Y;

    union
    {
        uint8_t ps;
        //Processor statuses (Carry flag, zero flag, interrupt disable, decimal mode, unused flag, break command, overflow flag, negative flag)
        struct { uint8_t C : 1, Z : 1, I : 1, D : 1, U : 1, B : 1, V : 1, N : 1; };
    };

    uint32_t cycles;

    //Instructions
    //LDA - Load accumulator
    void LDA_IM(Memory& memory); //LDA immediate
    void LDA_ZP(Memory& memory); //LDA zero page
    void LDA_ZP_X(Memory& memory); //LDA zero page, X
    void LDA_AB(Memory& memory); //LDA absolute
    void LDA_AB_X(Memory& memory); //LDA absolute, X
    void LDA_AB_Y(Memory& memory); //LDA absolute, Y
    void LDA_ID_X(Memory& memory); //LDA indirect, X
    void LDA_ID_Y(Memory& memory); //LDA indirect, Y

    //LDX - Load X Register
    void LDX_IM(Memory& memory); //LDX immediate
    void LDX_ZP(Memory& memory); //LDX zero page
    void LDX_ZP_Y(Memory& memory); //LDX zero page, Y
    void LDX_AB(Memory& memory); //LDX absolute
    void LDX_AB_Y(Memory& memory); //LDX absolute, Y

    //LDY - Load Y Register
    void LDY_IM(Memory& memory); //LDY immediate
    void LDY_ZP(Memory& memory); //LDY zero page
    void LDY_ZP_X(Memory& memory); //LDY zero page, X
    void LDY_AB(Memory& memory); //LDY absolute
    void LDY_AB_X(Memory& memory); //LDY absolute, X

    //STA - Store accumulator
    void STA_ZP(Memory& memory); //STA zero page
    void STA_ZP_X(Memory& memory); //STA zero page, X
    void STA_AB(Memory& memory); //STA absolute
    void STA_AB_X(Memory& memory); //STA absolute, X
    void STA_AB_Y(Memory& memory); //STA absolute, Y
    void STA_ID_X(Memory& memory); //STA indirect, X
    void STA_ID_Y(Memory& memory); //STA indirect, Y

    //STX - Store X register
    void STX_ZP(Memory& memory); //STX zero page
    void STX_ZP_Y(Memory& memory); //STX zero page, Y
    void STX_AB(Memory& memory); //STX absolute

    //STY - Store Y register
    void STY_ZP(Memory& memory); //STY zero page
    void STY_ZP_X(Memory& memory); //STY zero page, X
    void STY_AB(Memory& memory); //STY absolute

    //JSR - Jump to subroutine
    void JSR_AB(Memory& memory);

    //RTS - Return from subroutine
    void RTS_IP(Memory& memory);

    //JMP - Jump to another location
    void JMP_AB(Memory& memory); //JMP absolute
    void JMP_ID(Memory& memory); //JMP indirect

    //Register transfers
    void TAX_IP(); //Transfer accumulator to X
    void TAY_IP(); //Transfer accumulator to Y
    void TXA_IP(); //Transfer X to accumulator
    void TYA_IP(); //Transfer Y to accumulator

    //Stack operations
    void TSX_IP(); //Transfer stack pointer to X
    void TXS_IP(); //Transfer X to stack pointer
    void PHA_IP(Memory& memory); //Push accumulator on stack
    void PLA_IP(Memory& memory); //Pull accumulator from stack
    void PHP_IP(Memory& memory); //Push processor status on stack
    void PLP_IP(Memory& memory); //Pull processor status from stack

    //Status flag changes
    void CLC_IP(); //Clear carry flag
    void CLD_IP(); //Clear decimal mode flag
    void CLI_IP(); //Clear interrupt disable flag
    void CLV_IP(); //Clear overflow flag
    void SEC_IP(); //Set carry flag
    void SED_IP(); //Set decimal model flag
    void SEI_IP(); //Set interrupt disable flag
};