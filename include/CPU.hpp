#pragma once
#include <MemoryBus.hpp>

class CPU
{
public:
    CPU(MemoryBus& memory) : memory(memory) {}

    void Reset(uint16_t start);
    void GetStatus();
    
    bool Execute();

private:
    MemoryBus& memory;

private:
    uint8_t GetByte();
    uint8_t ReadByte(uint16_t address);
    void WriteByte(uint16_t address, uint8_t data);

    uint16_t GetWord();
    uint16_t ReadWord(uint16_t address);
    void WriteWord(uint16_t data, uint16_t address);

    uint16_t GetStackWord();
    void WriteWordToStack(uint16_t data);

    uint8_t GetStackByte();
    void WriteByteToStack(uint8_t data);

    uint16_t pc; // Program counter
    uint8_t sp; // Stack pointer
    
    // Registers (Accumulator, index register X, index register Y)
    uint8_t A, X, Y;

    union
    {
        uint8_t ps;
        // Processor statuses (Carry flag, zero flag, interrupt disable, decimal mode, unused flag, break command, overflow flag, negative flag)
        struct { uint8_t C : 1, Z : 1, I : 1, D : 1, U : 1, B : 1, V : 1, N : 1; };
    };

    uint32_t cycles;

    // Instructions
    // LDA - Load accumulator
    void LDA_IM(); // LDA immediate
    void LDA_ZP(); // LDA zero page
    void LDA_ZP_X(); // LDA zero page, X
    void LDA_AB(); // LDA absolute
    void LDA_AB_X(); // LDA absolute, X
    void LDA_AB_Y(); // LDA absolute, Y
    void LDA_ID_X(); // LDA indirect, X
    void LDA_ID_Y(); // LDA indirect, Y

    // LDX - Load X Register
    void LDX_IM(); // LDX immediate
    void LDX_ZP(); // LDX zero page
    void LDX_ZP_Y(); // LDX zero page, Y
    void LDX_AB(); // LDX absolute
    void LDX_AB_Y(); // LDX absolute, Y

    // LDY - Load Y Register
    void LDY_IM(); // LDY immediate
    void LDY_ZP(); // LDY zero page
    void LDY_ZP_X(); // LDY zero page, X
    void LDY_AB(); // LDY absolute
    void LDY_AB_X(); // LDY absolute, X

    // STA - Store accumulator
    void STA_ZP(); // STA zero page
    void STA_ZP_X(); // STA zero page, X
    void STA_AB(); // STA absolute
    void STA_AB_X(); // STA absolute, X
    void STA_AB_Y(); // STA absolute, Y
    void STA_ID_X(); // STA indirect, X
    void STA_ID_Y(); // STA indirect, Y

    // STX - Store X register
    void STX_ZP(); // STX zero page
    void STX_ZP_Y(); // STX zero page, Y
    void STX_AB(); // STX absolute

    // STY - Store Y register
    void STY_ZP(); // STY zero page
    void STY_ZP_X(); // STY zero page, X
    void STY_AB(); // STY absolute

    // JSR - Jump to subroutine
    void JSR_AB();

    // RTS - Return from subroutine
    void RTS_IP();

    // JMP - Jump to another location
    void JMP_AB(); // JMP absolute
    void JMP_ID(); // JMP indirect

    // Register transfers
    void TAX_IP(); // Transfer accumulator to X
    void TAY_IP(); // Transfer accumulator to Y
    void TXA_IP(); // Transfer X to accumulator
    void TYA_IP(); // Transfer Y to accumulator

    // Stack operations
    void TSX_IP(); // Transfer stack pointer to X
    void TXS_IP(); // Transfer X to stack pointer
    void PHA_IP(); // Push accumulator on stack
    void PLA_IP(); // Pull accumulator from stack
    void PHP_IP(); // Push processor status on stack
    void PLP_IP(); // Pull processor status from stack

    // Status flag changes
    void CLC_IP(); // Clear carry flag
    void CLD_IP(); // Clear decimal mode flag
    void CLI_IP(); // Clear interrupt disable flag
    void CLV_IP(); // Clear overflow flag
    void SEC_IP(); // Set carry flag
    void SED_IP(); // Set decimal model flag
    void SEI_IP(); // Set interrupt disable flag
    
    // Logical operations
    // AND - Logical and
    void AND_IM(); // AND immediate
    void AND_ZP(); // AND zero page
    void AND_ZP_X(); // AND zero page, X
    void AND_AB(); // AND absolute
    void AND_AB_X(); // AND absolute, X
    void AND_AB_Y(); // AND absolute, Y
    void AND_ID_X(); // AND indirect, X
    void AND_ID_Y(); // AND indirect, Y

    // ORA - Logical inclusive or
    void ORA_IM(); // ORA immediate
    void ORA_ZP(); // ORA zero page
    void ORA_ZP_X(); // ORA zero page, X
    void ORA_AB(); // ORA absolute
    void ORA_AB_X(); // ORA absolute, X
    void ORA_AB_Y(); // ORA absolute, Y
    void ORA_ID_X(); // ORA indirect, X
    void ORA_ID_Y(); // ORA indirect, Y

    // EOR - Logical exclusive or
    void EOR_IM(); // EOR immediate
    void EOR_ZP(); // EOR zero page
    void EOR_ZP_X(); // EOR zero page, X
    void EOR_AB(); // EOR absolute
    void EOR_AB_X(); // EOR absolute, X
    void EOR_AB_Y(); // EOR absolute, Y
    void EOR_ID_X(); // EOR indirect, X
    void EOR_ID_Y(); // EOR indirect, Y
    
    // BIT - Bit test
    void BIT_ZP(); // BIT zero page
    void BIT_AB(); // BIT absolute

    // Increments and decrements
    // INC - Increment a memory location
    void INC_ZP(); // INC zero page
    void INC_ZP_X(); // INC zero page, X
    void INC_AB(); // INC absolute
    void INC_AB_X(); // INC absolute, X

    void INX_IP(); // Increment X register
    void INY_IP(); // Increment Y register

    // DEC - Decrement a memory location
    void DEC_ZP(); // DEC zero page
    void DEC_ZP_X(); // DEC zero page, X
    void DEC_AB(); // DEC absolute
    void DEC_AB_X(); // DEC absolute, X

    void DEX_IP(); // Decrement X register
    void DEY_IP(); // Decrement Y register

    // Branches
    void BCC_RL(); // Branch if carry flag clear
    void BCS_RL(); // Branch if carry flag is set
    void BNE_RL(); // Branch if zero flag is clear
    void BEQ_RL(); // Branch if zero flag is set
    void BPL_RL(); // Branch if negative flag is clear
    void BMI_RL(); // Branch if negative flag is set
    void BVC_RL(); // Branch if overflow flag is clear
    void BVS_RL(); // Branch if overflow flag is set

    // Arithmetic
    // ADC - Add with carry
    void ADC_IM(); // ADC immediate
    void ADC_ZP(); // ADC zero page
    void ADC_ZP_X(); // ADC zero page, X
    void ADC_AB(); // ADC absolute
    void ADC_AB_X(); // ADC absolute, X
    void ADC_AB_Y(); // ADC absolute, Y
    void ADC_ID_X(); // ADC indirect, X
    void ADC_ID_Y(); // ADC indirect, Y

    // SBC - Subtract with carry
    void SBC_IM(); // SBC immediate
    void SBC_ZP(); // SBC zero page
    void SBC_ZP_X(); // SBC zero page, X
    void SBC_AB(); // SBC absolute
    void SBC_AB_X(); // SBD absolute, X
    void SBC_AB_Y(); // SBD absolute, Y
    void SBC_ID_X(); // SBD indirect, X
    void SBC_ID_Y(); // SBD indirect, Y

    // CMP - Compare accumulator
    void CMP_IM(); // CMP immediate
    void CMP_ZP(); // CMP zero page
    void CMP_ZP_X(); // CMP zero page, X
    void CMP_AB(); // CMP absolute
    void CMP_AB_X(); // CMP absolute, X
    void CMP_AB_Y(); // CMP absolute, Y
    void CMP_ID_X(); // CMP indirect, X
    void CMP_ID_Y(); // CMP indirect, Y

    // CPX - Compare X register
    void CPX_IM(); // CPX immediate
    void CPX_ZP(); // CPX zero page
    void CPX_AB(); // CPX absolute

    // CPY - Compare Y register
    void CPY_IM(); // CPY immediate
    void CPY_ZP(); // CPY zero page
    void CPY_AB(); // CPY absolute

    // Shifts
    // ASL - Arithmetic shift left
    void ASL_AC(); // ASL accumulator
    void ASL_ZP(); // ASL zero page
    void ASL_ZP_X(); // ASL zero page, X
    void ASL_AB(); // ASL absolute
    void ASL_AB_X(); // ASL absolute, X

    // LSR - Logical shift righ
    void LSR_AC(); // LSR accumulator
    void LSR_ZP(); // LSR zero page
    void LSR_ZP_X(); // LSR zero page, X
    void LSR_AB(); // LSR absolute
    void LSR_AB_X(); // LSR absolute, X

    // ROL - Rotate left
    void ROL_AC(); // ROL accumulator
    void ROL_ZP(); // ROL zero page
    void ROL_ZP_X(); // ROL zero page, X
    void ROL_AB(); // ROL absolute
    void ROL_AB_X(); // ROL absolute, X

    // ROR - Rotate right
    void ROR_AC(); // ROR accumulator
    void ROR_ZP(); // ROR zero page
    void ROR_ZP_X(); // ROR zero page, X
    void ROR_AB(); // ROR absolute
    void ROR_AB_X(); // ROR absolute, X

    // System functions
    void BRK_IP(); // Force an interrupt
    void NOP_IP(); // No operation
    void RTI_IP(); // Return from interrupt

};
