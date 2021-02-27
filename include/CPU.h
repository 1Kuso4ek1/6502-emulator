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
    
    //Logical operations
    //AND - Logical and
    void AND_IM(Memory& memory); //AND immediate
    void AND_ZP(Memory& memory); //AND zero page
    void AND_ZP_X(Memory& memory); //AND zero page, X
    void AND_AB(Memory& memory); //AND absolute
    void AND_AB_X(Memory& memory); //AND absolute, X
    void AND_AB_Y(Memory& memory); //AND absolute, Y
    void AND_ID_X(Memory& memory); //AND indirect, X
    void AND_ID_Y(Memory& memory); //AND indirect, Y

    //ORA - Logical inclusive or
    void ORA_IM(Memory& memory); //ORA immediate
    void ORA_ZP(Memory& memory); //ORA zero page
    void ORA_ZP_X(Memory& memory); //ORA zero page, X
    void ORA_AB(Memory& memory); //ORA absolute
    void ORA_AB_X(Memory& memory); //ORA absolute, X
    void ORA_AB_Y(Memory& memory); //ORA absolute, Y
    void ORA_ID_X(Memory& memory); //ORA indirect, X
    void ORA_ID_Y(Memory& memory); //ORA indirect, Y

    //EOR - Logical exclusive or
    void EOR_IM(Memory& memory); //EOR immediate
    void EOR_ZP(Memory& memory); //EOR zero page
    void EOR_ZP_X(Memory& memory); //EOR zero page, X
    void EOR_AB(Memory& memory); //EOR absolute
    void EOR_AB_X(Memory& memory); //EOR absolute, X
    void EOR_AB_Y(Memory& memory); //EOR absolute, Y
    void EOR_ID_X(Memory& memory); //EOR indirect, X
    void EOR_ID_Y(Memory& memory); //EOR indirect, Y
    
    //BIT - Bit test
    void BIT_ZP(Memory& memory); //BIT zero page
    void BIT_AB(Memory& memory); //BIT absolute

    //Increments and decrements
    //INC - Increment a memory location
    void INC_ZP(Memory& memory); //INC zero page
    void INC_ZP_X(Memory& memory); //INC zero page, X
    void INC_AB(Memory& memory); //INC absolute
    void INC_AB_X(Memory& memory); //INC absolute, X

    void INX_IP(); //Increment X register
    void INY_IP(); //Increment Y register

    //DEC - Decrement a memory location
    void DEC_ZP(Memory& memory); //DEC zero page
    void DEC_ZP_X(Memory& memory); //DEC zero page, X
    void DEC_AB(Memory& memory); //DEC absolute
    void DEC_AB_X(Memory& memory); //DEC absolute, X

    void DEX_IP(); //Decrement X register
    void DEY_IP(); //Decrement Y register

    //Branches
    void BCC_RL(Memory& memory); //Branch if carry flag clear
    void BCS_RL(Memory& memory); //Branch if carry flag is set
    void BNE_RL(Memory& memory); //Branch if zero flag is clear
    void BEQ_RL(Memory& memory); //Branch if zero flag is set
    void BPL_RL(Memory& memory); //Branch if negative flag is clear
    void BMI_RL(Memory& memory); //Branch if negative flag is set
    void BVC_RL(Memory& memory); //Branch if overflow flag is clear
    void BVS_RL(Memory& memory); //Branch if overflow flag is set

    //Arithmetic
    //ADC - Add with carry
    void ADC_IM(Memory& memory); //ADC immediate
    void ADC_ZP(Memory& memory); //ADC zero page
    void ADC_ZP_X(Memory& memory); //ADC zero page, X
    void ADC_AB(Memory& memory); //ADC absolute
    void ADC_AB_X(Memory& memory); //ACD absolute, X
    void ADC_AB_Y(Memory& memory); //ACD absolute, Y
    void ADC_ID_X(Memory& memory); //ACD indirect, X
    void ADC_ID_Y(Memory& memory); //ACD indirect, Y
};