#include <CPU.hpp>

#include <iostream>

void CPU::Reset(uint16_t start)
{
    pc = start;
    sp = 0xFF;
    C = Z = I = D = B = V = N = 0;
    U = 1;
    A = X = Y = 0;
    cycles = 0;
}

bool CPU::Execute() 
{
    if(cycles == 0)
    {
        uint8_t ins = GetByte();
        switch(ins)
        {   
        // LDA - Load accumulator
        case 0xA9: LDA_IM(); break;
        case 0xA5: LDA_ZP(); break;
        case 0xB5: LDA_ZP_X(); break;
        case 0xAD: LDA_AB(); break;
        case 0xBD: LDA_AB_X(); break;
        case 0xB9: LDA_AB_Y(); break;
        case 0xA1: LDA_ID_X(); break;
        case 0xB1: LDA_ID_Y(); break;
        // LDX - Load X Register
        case 0xA2: LDX_IM(); break;
        case 0xA6: LDX_ZP(); break;
        case 0xB6: LDX_ZP_Y(); break;
        case 0xAE: LDX_AB(); break;
        case 0xBE: LDX_AB_Y(); break;
        // LDY - Load Y Register
        case 0xA0: LDY_IM(); break;
        case 0xA4: LDY_ZP(); break;
        case 0xB4: LDY_ZP_X(); break;
        case 0xAC: LDY_AB(); break;
        case 0xBC: LDY_AB_X(); break;
        // STA - Store accumulator
        case 0x85: STA_ZP(); break;
        case 0x95: STA_ZP_X(); break;
        case 0x8D: STA_AB(); break;
        case 0x9D: STA_AB_X(); break;
        case 0x99: STA_AB_Y(); break;
        case 0x81: STA_ID_X(); break;
        case 0x91: STA_ID_Y(); break;
        // STX - Store X register
        case 0x86: STX_ZP(); break;
        case 0x96: STX_ZP_Y(); break;
        case 0x8E: STX_AB(); break;
        // STY - Store Y register
        case 0x84: STY_ZP(); break;
        case 0x94: STY_ZP_X(); break;
        case 0x8C: STY_AB(); break;
        // JSR - Jump to subroutine
        case 0x20: JSR_AB(); break;
        // RTS - Return from subroutine
        case 0x60: RTS_IP(); break;
        // JMP - Jump to another location
        case 0x4C: JMP_AB(); break;
        case 0x6C: JMP_ID(); break;
        // Register transfers 
        case 0xAA: TAX_IP(); break;
        case 0xA8: TAY_IP(); break;
        case 0x8A: TXA_IP(); break;
        case 0x98: TYA_IP(); break;
        // Stack operations
        case 0xBA: TSX_IP(); break;
        case 0x9A: TXS_IP(); break;
        case 0x48: PHA_IP(); break;
        case 0x68: PLA_IP(); break;
        case 0x08: PHP_IP(); break;
        case 0x28: PLP_IP(); break;
        // Status flag changes
        case 0x18: CLC_IP(); break;
        case 0xD8: CLD_IP(); break;
        case 0x58: CLI_IP(); break;
        case 0xB8: CLV_IP(); break;
        case 0x38: SEC_IP(); break;
        case 0xF8: SED_IP(); break;
        case 0x78: SEI_IP(); break;
        // AND - Logical and
        case 0x29: AND_IM(); break;
        case 0x25: AND_ZP(); break;
        case 0x35: AND_ZP_X(); break;
        case 0x2D: AND_AB(); break;
        case 0x3D: AND_AB_X(); break;
        case 0x39: AND_AB_Y(); break;
        case 0x21: AND_ID_X(); break;
        case 0x31: AND_ID_Y(); break;
        // ORA - Logical inclusive or
        case 0x09: ORA_IM(); break;
        case 0x05: ORA_ZP(); break;
        case 0x15: ORA_ZP_X(); break;
        case 0x0D: ORA_AB(); break;
        case 0x1D: ORA_AB_X(); break;
        case 0x19: ORA_AB_Y(); break;
        case 0x01: ORA_ID_X(); break;
        case 0x11: ORA_ID_Y(); break;
        // EOR - Logical exclusive or
        case 0x49: EOR_IM(); break;
        case 0x45: EOR_ZP(); break;
        case 0x55: EOR_ZP_X(); break;
        case 0x4D: EOR_AB(); break;
        case 0x5D: EOR_AB_X(); break;
        case 0x59: EOR_AB_Y(); break;
        case 0x41: EOR_ID_X(); break;
        case 0x51: EOR_ID_Y(); break;
        // BIT - Bit test
        case 0x24: BIT_ZP(); break;
        case 0x2C: BIT_AB(); break;
        // Increments and decrements
        case 0xE6: INC_ZP(); break;
        case 0xF6: INC_ZP_X(); break;
        case 0xEE: INC_AB(); break;
        case 0xFE: INC_AB_X(); break;
        case 0xE8: INX_IP(); break;
        case 0xC8: INY_IP(); break;
        case 0xC6: DEC_ZP(); break;
        case 0xD6: DEC_ZP_X(); break;
        case 0xCE: DEC_AB(); break;
        case 0xDE: DEC_AB_X(); break;
        case 0xCA: DEX_IP(); break;
        case 0x88: DEY_IP(); break;
        // Branches
        case 0x90: BCC_RL(); break;
        case 0xB0: BCS_RL(); break;
        case 0xD0: BNE_RL(); break;
        case 0xF0: BEQ_RL(); break;
        case 0x10: BPL_RL(); break;
        case 0x30: BMI_RL(); break;
        case 0x50: BVC_RL(); break;
        case 0x70: BVS_RL(); break;
        // ADC - Add with carry
        case 0x69: ADC_IM(); break;
        case 0x65: ADC_ZP(); break;
        case 0x75: ADC_ZP_X(); break;
        case 0x6D: ADC_AB(); break;
        case 0x7D: ADC_AB_X(); break;
        case 0x79: ADC_AB_Y(); break;
        case 0x61: ADC_ID_X(); break;
        case 0x71: ADC_ID_Y(); break;
        // SBC - Subtract with carry
        case 0xE9: SBC_IM(); break;
        case 0xE5: SBC_ZP(); break;
        case 0xF5: SBC_ZP_X(); break;
        case 0xED: SBC_AB(); break;
        case 0xFD: SBC_AB_X(); break;
        case 0xF9: SBC_AB_Y(); break;
        case 0xE1: SBC_ID_X(); break;
        case 0xF1: SBC_ID_Y(); break;
        // CMP - Compare accumulator
        case 0xC9: CMP_IM(); break;
        case 0xC5: CMP_ZP(); break;
        case 0xD5: CMP_ZP_X(); break;
        case 0xCD: CMP_AB(); break;
        case 0xDD: CMP_AB_X(); break;
        case 0xD9: CMP_AB_Y(); break;
        case 0xC1: CMP_ID_X(); break;
        case 0xD1: CMP_ID_Y(); break;
        // CPX - Compare X register
        case 0xE0: CPX_IM(); break;
        case 0xE4: CPX_ZP(); break;
        case 0xEC: CPX_AB(); break;
        // CPY - Compare Y register
        case 0xC0: CPY_IM(); break;
        case 0xC4: CPY_ZP(); break;
        case 0xCC: CPY_AB(); break;
        // ASL - Arithmetic shift left
        case 0x0A: ASL_AC(); break;
        case 0x06: ASL_ZP(); break;
        case 0x16: ASL_ZP_X(); break;
        case 0x0E: ASL_AB(); break;
        case 0x1E: ASL_AB_X(); break;
        // LSR - Logical shift right
        case 0x4A: LSR_AC(); break;
        case 0x46: LSR_ZP(); break;
        case 0x56: LSR_ZP_X(); break;
        case 0x4E: LSR_AB(); break;
        case 0x5E: LSR_AB_X(); break;
        // ROL - Rotate left
        case 0x2A: ROL_AC(); break;
        case 0x26: ROL_ZP(); break;
        case 0x36: ROL_ZP_X(); break;
        case 0x2E: ROL_AB(); break;
        case 0x3E: ROL_AB_X(); break;
        // ROR - Rotate right
        case 0x6A: ROR_AC(); break;
        case 0x66: ROR_ZP(); break;
        case 0x76: ROR_ZP_X(); break;
        case 0x6E: ROR_AB(); break;
        case 0x7E: ROR_AB_X(); break;
        // System functions
        case 0x00: BRK_IP(); return 1;
        case 0xEA: NOP_IP(); break;
        case 0x40: RTI_IP(); break;

        default: cycles = 1;
        }           
    }
    cycles--;

    return 0;
}

void CPU::GetStatus()
{
    // I'll leave this "as is" for now...
    std::cout << "Cycles = " << cycles << std::endl;
    std::cout << "Program counter = " << std::hex << (int)pc << std::endl;
    std::cout << "Stack pointer = " << std::hex << (int)sp << std::endl;
    std::cout << "memory.Read(pc) = " << std::hex << (int)memory.Read(pc) << std::endl;
    std::cout << "memory.Read(pc + 1) = " << std::hex << (int)memory.Read(pc + 1) << std::endl;
    std::cout << "A = " << std::hex << (int)A << " X = " << std::hex << (int)X << " Y = " << std::hex << (int)Y << std::endl;
    std::cout << "C = " << std::hex << (int)C << " Z = " << std::hex << (int)Z << " I = " << std::hex << (int)I << " D = " << std::hex << (int)D << " B = " << std::hex << (int)B << " V = " << std::hex << (int)V << " N = " << std::hex << (int)N << std::endl;
}

uint8_t CPU::GetByte()
{
    uint8_t data = memory.Read(pc);
    pc++;
    cycles--;
    return data;
}

uint8_t CPU::ReadByte(uint16_t address)
{
    cycles--;
    return memory.Read(address);
}

void CPU::WriteByte(uint16_t address, uint8_t data)
{
    memory.Write(address, data);
    cycles--;
}

uint16_t CPU::GetWord()
{
    uint16_t data = memory.Read(pc);
    pc++;
    data |= (memory.Read(pc) << 8);
    pc++;
    cycles -= 2;
    return data;
}

uint16_t CPU::ReadWord(uint16_t address)
{
    return (uint16_t)(ReadByte(address) | (ReadByte(address + 1) << 8));
}

void CPU::WriteWord(uint16_t data, uint16_t address)
{
    memory.Write(address, data & 0xFF);
    memory.Write(address + 1, data >> 8);
    cycles -= 2;
}

uint16_t CPU::GetStackWord()
{
    uint16_t data = ReadWord((0x100 | sp) + 1);
    sp += 2;
    cycles--;
    return data;
}

void CPU::WriteWordToStack(uint16_t data)
{
    WriteWord(data, (0x100 | sp) - 1);
    sp -= 2;
}

uint8_t CPU::GetStackByte()
{
    uint8_t data = ReadByte((0x100 | sp) + 1);
    sp++;
    cycles--;
    return data;
}

void CPU::WriteByteToStack(uint8_t data)
{
    WriteByte((0x100 | sp), data);
    sp--;
    cycles--;
}

// LDA - Load accumulator
void CPU::LDA_IM()
{
    cycles = 2;
    A = GetByte();
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::LDA_ZP()
{
    cycles = 3;
    A = ReadByte(GetByte());
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::LDA_ZP_X()
{
    cycles = 4;
    uint8_t data = GetByte();
    data += X;
    cycles--;
    A = ReadByte(data);
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::LDA_AB()
{
    cycles = 4;
    A = ReadByte(GetWord());
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::LDA_AB_X()
{
    cycles = 4;
    uint16_t address = GetWord();
    A = ReadByte(address + X);
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::LDA_AB_Y()
{
    cycles = 4;
    A = ReadByte((uint16_t)(GetWord() + Y));
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::LDA_ID_X()
{
    cycles = 6;
    A = ReadByte(ReadWord((uint16_t)(GetByte() + X)));
    cycles--;
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::LDA_ID_Y()
{
    cycles = 5;
    A = ReadByte(ReadWord((uint16_t)(GetByte())) + Y);
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

// LDX - Load X Register
void CPU::LDX_IM()
{
    cycles = 2;
    X = GetByte();
    Z = (X == 0);
    N = (X & 0b10000000) > 0;
}

void CPU::LDX_ZP()
{
    cycles = 3;
    X = ReadByte(GetByte());
    Z = (X == 0);
    N = (X & 0b10000000) > 0;
}

void CPU::LDX_ZP_Y()
{
    cycles = 4;
    uint8_t data = GetByte();
    data += Y;
    cycles--;
    X = ReadByte(data);
    Z = (X == 0);
    N = (X & 0b10000000) > 0;
}

void CPU::LDX_AB()
{
    cycles = 4;
    X = ReadByte(GetWord());
    Z = (X == 0);
    N = (X & 0b10000000) > 0;
}

void CPU::LDX_AB_Y()
{
    cycles = 4;
    uint16_t address = GetWord();
    X = ReadByte(address + Y);
    Z = (X == 0);
    N = (X & 0b10000000) > 0;
}

// LDY - Load Y Register
void CPU::LDY_IM()
{
    cycles = 2;
    Y = GetByte();
    Z = (Y == 0);
    N = (Y & 0b10000000) > 0;
}

void CPU::LDY_ZP()
{
    cycles = 3;
    Y = ReadByte(GetByte());
    Z = (Y == 0);
    N = (Y & 0b10000000) > 0;
}

void CPU::LDY_ZP_X()
{
    cycles = 4;
    uint8_t data = GetByte();
    data += X;
    cycles--;
    Y = ReadByte(data);
    Z = (Y == 0);
    N = (Y & 0b10000000) > 0;
}

void CPU::LDY_AB()
{
    cycles = 4;
    Y = ReadByte(GetWord());
    Z = (Y == 0);
    N = (Y & 0b10000000) > 0;
}

void CPU::LDY_AB_X()
{
    cycles = 4;
    uint16_t address = GetWord();
    Y = ReadByte(address + X);
    Z = (Y == 0);
    N = (Y & 0b10000000) > 0;
}

// STA - store accumulator
void CPU::STA_ZP()
{
    cycles = 3;
    WriteByte(GetByte(), A);
}

void CPU::STA_ZP_X()
{
    cycles = 4;
    WriteByte(GetByte() + X, A);
    cycles--;
}

void CPU::STA_AB()
{
    cycles = 4;
    WriteByte(GetWord(), A);
}

void CPU::STA_AB_X()
{
    cycles = 5;
    WriteByte(GetWord() + X, A);
    cycles--;
}

void CPU::STA_AB_Y()
{
    cycles = 5;
    WriteByte(GetWord() + Y, A);
    cycles--;
}

void CPU::STA_ID_X()
{
    cycles = 6;
    WriteByte(ReadWord((uint16_t)(GetByte() + X)), A);
    cycles--;
}

void CPU::STA_ID_Y()
{
    cycles = 6;
    WriteByte(ReadWord((uint16_t)(GetByte())) + Y, A);
    cycles--;
}

// STX - Store X register
void CPU::STX_ZP()
{
    cycles = 3;
    WriteByte(GetByte(), X);
}

void CPU::STX_ZP_Y()
{
    cycles = 4;
    WriteByte(GetByte() + Y, X);
    cycles--;
}

void CPU::STX_AB()
{
    cycles = 4;
    WriteByte(GetWord(), X);
}

// STY - Store Y register
void CPU::STY_ZP()
{
    cycles = 3;
    WriteByte(GetByte(), Y);
}

void CPU::STY_ZP_X()
{
    cycles = 4;
    WriteByte(GetByte() + X, Y);
    cycles--;
}

void CPU::STY_AB()
{
    cycles = 4;
    WriteByte(GetWord(), Y);
}

// JSR - Jump to subroutine
void CPU::JSR_AB() 
{
    cycles = 6;
    uint16_t address = GetWord();
    WriteWordToStack(pc - 1);
    pc = address;
    cycles--;
}

// RTS - Return from subroutine
void CPU::RTS_IP()
{
    cycles = 6;
    pc = GetStackWord() + 1;
    cycles -= 2;
}

// JMP - Jump to another location
void CPU::JMP_AB()
{
    cycles = 3;
    pc = GetWord();
}

void CPU::JMP_ID()
{
    cycles = 5;
    pc = ReadWord(GetWord());
}

// Register transfers
void CPU::TAX_IP()
{
    cycles = 2;
    X = A;
    cycles--;
    Z = (X == 0);
    N = (X & 0b10000000) > 0;
}

void CPU::TAY_IP()
{
    cycles = 2;
    Y = A;
    cycles--;
    Z = (Y == 0);
    N = (Y & 0b10000000) > 0;
}

void CPU::TXA_IP()
{
    cycles = 2;
    A = X;
    cycles--;
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::TYA_IP()
{
    cycles = 2;
    A = Y;
    cycles--;
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

// Stack operations
void CPU::TSX_IP()
{
    cycles = 2;
    X = sp;
    cycles--;
    Z = (X == 0);
    N = (X & 0b10000000) > 0;
}

void CPU::TXS_IP()
{
    cycles = 2;
    sp = X;
    cycles--;
}

void CPU::PHA_IP()
{
    cycles = 3;
    WriteByteToStack(A);
}

void CPU::PLA_IP()
{
    cycles = 4;
    A = GetStackByte();
    cycles--;
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::PHP_IP()
{
    cycles = 3;
    WriteByteToStack(ps);
}

void CPU::PLP_IP()
{
    cycles = 4;
    ps = GetStackByte();
    cycles--;
}

// Status flag changes
void CPU::CLC_IP()
{
    cycles = 2;
    C = 0;
    cycles--;
}

void CPU::CLD_IP()
{
    cycles = 2;
    D = 0;
    cycles--;
}

void CPU::CLI_IP()
{
    cycles = 2;
    I = 0;
    cycles--;
}

void CPU::CLV_IP()
{
    cycles = 2;
    V = 0;
    cycles--;
}

void CPU::SEC_IP()
{
    cycles = 2;
    C = 1;
    cycles--;
}

void CPU::SED_IP()
{
    cycles = 2;
    D = 1;
    cycles--;
}

void CPU::SEI_IP()
{
    cycles = 2;
    I = 1;
    cycles--;
}

// AND - Logical and
void CPU::AND_IM()
{
    cycles = 2;
    A &= GetByte();
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::AND_ZP()
{
    cycles = 3;
    A &= ReadByte(GetByte());
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::AND_ZP_X()
{
    cycles = 4;
    uint8_t data = GetByte();
    data += X;
    cycles--;
    A &= ReadByte(data);
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::AND_AB()
{
    cycles = 4;
    A &= ReadByte(GetWord());
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::AND_AB_X()
{
    cycles = 4;
    uint16_t address = GetWord();
    A &= ReadByte(address + X);
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::AND_AB_Y()
{
    cycles = 4;
    A &= ReadByte((uint16_t)(GetWord() + Y));
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::AND_ID_X()
{
    cycles = 6;
    A &= ReadByte(ReadWord((uint16_t)(GetByte() + X)));
    cycles--;
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::AND_ID_Y()
{
    cycles = 5;
    A &= ReadByte(ReadWord((uint16_t)(GetByte())) + Y);
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

// ORA - Logical inclusive or
void CPU::ORA_IM()
{
    cycles = 2;
    A |= GetByte();
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::ORA_ZP()
{
    cycles = 3;
    A |= ReadByte(GetByte());
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::ORA_ZP_X()
{
    cycles = 4;
    uint8_t data = GetByte();
    data += X;
    cycles--;
    A |= ReadByte(data);
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::ORA_AB()
{
    cycles = 4;
    A |= ReadByte(GetWord());
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::ORA_AB_X()
{
    cycles = 4;
    uint16_t address = GetWord();
    A |= ReadByte(address + X);
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::ORA_AB_Y()
{
    cycles = 4;
    A |= ReadByte((uint16_t)(GetWord() + Y));
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::ORA_ID_X()
{
    cycles = 6;
    A |= ReadByte(ReadWord((uint16_t)(GetByte() + X)));
    cycles--;
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::ORA_ID_Y()
{
    cycles = 5;
    A |= ReadByte(ReadWord((uint16_t)(GetByte())) + Y);
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

// EOR - Logical exclusive or
void CPU::EOR_IM()
{
    cycles = 2;
    A ^= GetByte();
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::EOR_ZP()
{
    cycles = 3;
    A ^= ReadByte(GetByte());
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::EOR_ZP_X()
{
    cycles = 4;
    uint8_t data = GetByte();
    data += X;
    cycles--;
    A ^= ReadByte(data);
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::EOR_AB()
{
    cycles = 4;
    A ^= ReadByte(GetWord());
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::EOR_AB_X()
{
    cycles = 4;
    uint16_t address = GetWord();
    A ^= ReadByte(address + X);
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::EOR_AB_Y()
{
    cycles = 4;
    A ^= ReadByte((uint16_t)(GetWord() + Y));
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::EOR_ID_X()
{
    cycles = 6;
    A ^= ReadByte(ReadWord((uint16_t)(GetByte() + X)));
    cycles--;
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::EOR_ID_Y()
{
    cycles = 5;
    A ^= ReadByte(ReadWord((uint16_t)(GetByte())) + Y);
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

// BIT - Bit test
void CPU::BIT_ZP()
{
    cycles = 3;
    uint8_t data = ReadByte(GetByte());
    Z = !(A & data);
    V = (data & 0b01000000) > 0;
    N = (data & 0b10000000) > 0;
}

void CPU::BIT_AB()
{
    cycles = 4;
    uint8_t data = ReadByte(GetWord());
    Z = !(A & data);
    V = (data & 0b01000000) > 0;
    N = (data & 0b10000000) > 0;
}

// INC - Increment a memory location
void CPU::INC_ZP()
{
    cycles = 5;
    uint8_t addr = GetByte(), result = ReadByte(addr) + 1;
    cycles--;
    WriteByte(addr, result);
    Z = (result == 0);
    N = (result & 0b10000000) > 0;
}

void CPU::INC_ZP_X()
{
    cycles = 6;
    uint8_t addr = GetByte() + X, result = ReadByte(addr) + 1;
    cycles -= 2;
    WriteByte(addr, result);
    Z = (result == 0);
    N = (result & 0b10000000) > 0;
}

void CPU::INC_AB()
{
    cycles = 6;
    uint16_t addr = GetWord(), result = ReadByte(addr) + 1;
    cycles--;
    WriteByte(addr, result);
    Z = (result == 0);
    N = (result & 0b10000000) > 0;
}

void CPU::INC_AB_X()
{
    cycles = 7;
    uint16_t addr = GetWord() + X, result = ReadByte(addr) + 1;
    cycles -= 2;
    WriteByte(addr, result);
    Z = (result == 0);
    N = (result & 0b10000000) > 0;
}

void CPU::INX_IP()
{
    cycles = 2;
    X++;
    cycles--;
    Z = (X == 0);
    N = (X & 0b10000000) > 0;
}

void CPU::INY_IP()
{
    cycles = 2;
    Y++;
    cycles--;
    Z = (Y == 0);
    N = (Y & 0b10000000) > 0;
}

// DEC - Decrement a memory location
void CPU::DEC_ZP()
{
    cycles = 5;
    uint8_t addr = GetByte(), result = ReadByte(addr) - 1;
    cycles--;
    WriteByte(addr, result);
    Z = (result == 0);
    N = (result & 0b10000000) > 0;
}

void CPU::DEC_ZP_X()
{
    cycles = 6;
    uint8_t addr = GetByte() + X, result = ReadByte(addr) - 1;
    cycles -= 2;
    WriteByte(addr, result);
    Z = (result == 0);
    N = (result & 0b10000000) > 0;
}

void CPU::DEC_AB()
{
    cycles = 6;
    uint16_t addr = GetWord(), result = ReadByte(addr) - 1;
    cycles--;
    WriteByte(addr, result);
    Z = (result == 0);
    N = (result & 0b10000000) > 0;
}

void CPU::DEC_AB_X()
{
    cycles = 7;
    uint16_t addr = GetWord() + X, result = ReadByte(addr) - 1;
    cycles -= 2;
    WriteByte(addr, result);
    Z = (result == 0);
    N = (result & 0b10000000) > 0;
}

void CPU::DEX_IP()
{
    cycles = 2;
    X--;
    cycles--;
    Z = (X == 0);
    N = (X & 0b10000000) > 0;
}

void CPU::DEY_IP()
{
    cycles = 2;
    Y--;
    cycles--;
    Z = (Y == 0);
    N = (Y & 0b10000000) > 0;
}

// Branches
void CPU::BCC_RL()
{
    cycles = 2;
    uint8_t offset = GetByte();
    pc += (!C) ? static_cast<int8_t>(offset) : 0;
}

void CPU::BCS_RL()
{
    cycles = 2;
    uint8_t offset = GetByte();
    pc += (C) ? static_cast<int8_t>(offset) : 0;
}

void CPU::BNE_RL()
{
    cycles = 2;
    uint8_t offset = GetByte();
    pc += (!Z) ? static_cast<int8_t>(offset) : 0;
}

void CPU::BEQ_RL()
{
    cycles = 2;
    uint8_t offset = GetByte();
    pc += (Z) ? static_cast<int8_t>(offset) : 0;
}

void CPU::BPL_RL()
{
    cycles = 2;
    uint8_t offset = GetByte();
    pc += (!N) ? static_cast<int8_t>(offset) : 0;
}

void CPU::BMI_RL()
{
    cycles = 2;
    uint8_t offset = GetByte();
    pc += (N) ? static_cast<int8_t>(offset) : 0;
}

void CPU::BVC_RL()
{
    cycles = 2;
    uint8_t offset = GetByte();
    pc += (!V) ? static_cast<int8_t>(offset) : 0;
}

void CPU::BVS_RL()
{
    cycles = 2;
    uint8_t offset = GetByte();
    pc += (V) ? static_cast<int8_t>(offset) : 0;
}

// Arithmetic
// ADC - Add with carry
void CPU::ADC_IM()
{
    cycles = 2;
    uint8_t acp = A, op = GetByte();
    uint16_t sum = A + op + C;
    A = (sum & 0xFF);
    C = (sum & 0xFF00) > 0;
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
    V = (((acp & 0b10000000) ^ (op & 0b10000000)) == 0) ? (A & 0b10000000) != (acp & 0b10000000) : 0;
}

void CPU::ADC_ZP()
{
    cycles = 3;
    uint8_t acp = A, op = ReadByte(GetByte());
    uint16_t sum = A + op + C;
    A = (sum & 0xFF);
    C = (sum & 0xFF00) > 0;
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
    V = (((acp & 0b10000000) ^ (op & 0b10000000)) == 0) ? (A & 0b10000000) != (acp & 0b10000000) : 0;
}

void CPU::ADC_ZP_X()
{
    cycles = 4;
    uint8_t acp = A, op = ReadByte(GetByte() + X);
    uint16_t sum = A + op + C;
    A = (sum & 0xFF);
    C = (sum & 0xFF00) > 0;
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
    V = (((acp & 0b10000000) ^ (op & 0b10000000)) == 0) ? (A & 0b10000000) != (acp & 0b10000000) : 0;
}

void CPU::ADC_AB()
{
    cycles = 4;
    uint8_t acp = A, op = ReadByte(GetWord());
    uint16_t sum = A + op + C;
    A = (sum & 0xFF);
    C = (sum & 0xFF00) > 0;
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
    V = (((acp & 0b10000000) ^ (op & 0b10000000)) == 0) ? (A & 0b10000000) != (acp & 0b10000000) : 0;
}

void CPU::ADC_AB_X()
{
    cycles = 4;
    uint8_t acp = A, op = ReadByte(GetWord() + X);
    uint16_t sum = A + op + C;
    A = (sum & 0xFF);
    C = (sum & 0xFF00) > 0;
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
    V = (((acp & 0b10000000) ^ (op & 0b10000000)) == 0) ? (A & 0b10000000) != (acp & 0b10000000) : 0;
}

void CPU::ADC_AB_Y()
{
    cycles = 4;
    uint8_t acp = A, op = ReadByte(GetWord() + Y);
    uint16_t sum = A + op + C;
    A = (sum & 0xFF);
    C = (sum & 0xFF00) > 0;
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
    V = (((acp & 0b10000000) ^ (op & 0b10000000)) == 0) ? (A & 0b10000000) != (acp & 0b10000000) : 0;
}

void CPU::ADC_ID_X()
{
    cycles = 6;
    uint8_t acp = A, op = ReadByte(ReadWord((uint16_t)(GetByte() + X)));
    cycles--;
    uint16_t sum = A + op + C;
    A = (sum & 0xFF);
    C = (sum & 0xFF00) > 0;
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
    V = (((acp & 0b10000000) ^ (op & 0b10000000)) == 0) ? (A & 0b10000000) != (acp & 0b10000000) : 0;
}

void CPU::ADC_ID_Y()
{
    cycles = 5;
    uint8_t acp = A, op = ReadByte(ReadWord((uint16_t)(GetByte())) + Y);
    uint16_t sum = A + op + C;
    A = (sum & 0xFF);
    C = (sum & 0xFF00) > 0;
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
    V = (((acp & 0b10000000) ^ (op & 0b10000000)) == 0) ? (A & 0b10000000) != (acp & 0b10000000) : 0;
}

// SBC - Subtract with carry
void CPU::SBC_IM()
{
    cycles = 2;
    uint8_t acp = A, op = GetByte();
    uint16_t sum = A - op - !C;
    A = (sum & 0xFF);
    C = !((sum & 0xFF00) > 0);
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
    V = (((acp & 0b10000000) ^ (op & 0b10000000)) == 0) ? (A & 0b10000000) != (acp & 0b10000000) : 0;
}

void CPU::SBC_ZP()
{
    cycles = 3;
    uint8_t acp = A, op = ReadByte(GetByte());
    uint16_t sum = A - op - !C;
    A = (sum & 0xFF);
    C = !((sum & 0xFF00) > 0);
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
    V = (((acp & 0b10000000) ^ (op & 0b10000000)) == 0) ? (A & 0b10000000) != (acp & 0b10000000) : 0;
}

void CPU::SBC_ZP_X()
{
    cycles = 4;
    uint8_t acp = A, op = ReadByte(GetByte() + X);
    uint16_t sum = A - op - !C;
    A = (sum & 0xFF);
    C = !((sum & 0xFF00) > 0);
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
    V = (((acp & 0b10000000) ^ (op & 0b10000000)) == 0) ? (A & 0b10000000) != (acp & 0b10000000) : 0;
}

void CPU::SBC_AB()
{
    cycles = 4;
    uint8_t acp = A, op = ReadByte(GetWord());
    uint16_t sum = A - op - !C;
    A = (sum & 0xFF);
    C = !((sum & 0xFF00) > 0);
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
    V = (((acp & 0b10000000) ^ (op & 0b10000000)) == 0) ? (A & 0b10000000) != (acp & 0b10000000) : 0;
}

void CPU::SBC_AB_X()
{
    cycles = 4;
    uint8_t acp = A, op = ReadByte(GetWord() + X);
    uint16_t sum = A - op - !C;
    A = (sum & 0xFF);
    C = !((sum & 0xFF00) > 0);
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
    V = (((acp & 0b10000000) ^ (op & 0b10000000)) == 0) ? (A & 0b10000000) != (acp & 0b10000000) : 0;
}

void CPU::SBC_AB_Y()
{
    cycles = 4;
    uint8_t acp = A, op = ReadByte(GetWord() + Y);
    uint16_t sum = A - op - !C;
    A = (sum & 0xFF);
    C = !((sum & 0xFF00) > 0);
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
    V = (((acp & 0b10000000) ^ (op & 0b10000000)) == 0) ? (A & 0b10000000) != (acp & 0b10000000) : 0;
}

void CPU::SBC_ID_X()
{
    cycles = 6;
    uint8_t acp = A, op = ReadByte(ReadWord((uint16_t)(GetByte() + X)));
    cycles--;
    uint16_t sum = A - op - !C;
    A = (sum & 0xFF);
    C = !((sum & 0xFF00) > 0);
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
    V = (((acp & 0b10000000) ^ (op & 0b10000000)) == 0) ? (A & 0b10000000) != (acp & 0b10000000) : 0;
}

void CPU::SBC_ID_Y()
{
    cycles = 5;
    uint8_t acp = A, op = ReadByte(ReadWord((uint16_t)(GetByte())) + Y);
    uint16_t sum = A - op - !C;
    A = (sum & 0xFF);
    C = !((sum & 0xFF00) > 0);
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
    V = (((acp & 0b10000000) ^ (op & 0b10000000)) == 0) ? (A & 0b10000000) != (acp & 0b10000000) : 0;
}

// CMP - Compare accumulator
void CPU::CMP_IM()
{
    cycles = 2;
    uint8_t op = GetByte();
    uint8_t res = A - op;
    C = (A >= op);
    Z = (A == op);
    N = (res & 0b10000000) > 0;
}

void CPU::CMP_ZP()
{
    cycles = 3;
    uint8_t op = ReadByte(GetByte());
    uint8_t res = A - op;
    C = (A >= op);
    Z = (A == op);
    N = (res & 0b10000000) > 0;
}

void CPU::CMP_ZP_X()
{
    cycles = 4;
    uint8_t op = ReadByte(GetByte() + X);
    cycles--;
    uint8_t res = A - op;
    C = (A >= op);
    Z = (A == op);
    N = (res & 0b10000000) > 0;
}

void CPU::CMP_AB()
{
    cycles = 4;
    uint8_t op = ReadByte(GetWord());
    uint8_t res = A - op;
    C = (A >= op);
    Z = (A == op);
    N = (res & 0b10000000) > 0;
}

void CPU::CMP_AB_X()
{
    cycles = 4;
    uint8_t op = ReadByte(GetWord() + X);
    uint8_t res = A - op;
    C = (A >= op);
    Z = (A == op);
    N = (res & 0b10000000) > 0;
}

void CPU::CMP_AB_Y()
{
    cycles = 4;
    uint8_t op = ReadByte(GetWord() + Y);
    uint8_t res = A - op;
    C = (A >= op);
    Z = (A == op);
    N = (res & 0b10000000) > 0;
}

void CPU::CMP_ID_X()
{
    cycles = 6;
    uint8_t op = ReadByte(ReadWord((uint16_t)(GetByte() + X)));
    cycles--;
    uint8_t res = A - op;
    C = (A >= op);
    Z = (A == op);
    N = (res & 0b10000000) > 0;
}

void CPU::CMP_ID_Y()
{
    cycles = 5;
    uint8_t op = ReadByte(ReadWord((uint16_t)(GetByte())) + Y);
    uint8_t res = A - op;
    C = (A >= op);
    Z = (A == op);
    N = (res & 0b10000000) > 0;
}

// CPX - Compare X register
void CPU::CPX_IM()
{
    cycles = 2;
    uint8_t op = GetByte();
    uint8_t res = X - op;
    C = (X >= op);
    Z = (X == op);
    N = (res & 0b10000000) > 0;
}

void CPU::CPX_ZP()
{
    cycles = 3;
    uint8_t op = ReadByte(GetByte());
    uint8_t res = X - op;
    C = (X >= op);
    Z = (X == op);
    N = (res & 0b10000000) > 0;
}

void CPU::CPX_AB()
{
    cycles = 4;
    uint8_t op = ReadByte(GetWord());
    uint8_t res = X - op;
    C = (X >= op);
    Z = (X == op);
    N = (res & 0b10000000) > 0;
}

// CPY - Compare Y register
void CPU::CPY_IM()
{
    cycles = 2;
    uint8_t op = GetByte();
    uint8_t res = Y - op;
    C = (Y >= op);
    Z = (Y == op);
    N = (res & 0b10000000) > 0;
}

void CPU::CPY_ZP()
{
    cycles = 3;
    uint8_t op = ReadByte(GetByte());
    uint8_t res = Y - op;
    C = (Y >= op);
    Z = (Y == op);
    N = (res & 0b10000000) > 0;
}

void CPU::CPY_AB()
{
    cycles = 4;
    uint8_t op = ReadByte(GetWord());
    uint8_t res = Y - op;
    C = (Y >= op);
    Z = (Y == op);
    N = (res & 0b10000000) > 0;
}

// Shifts
// ASL - Arithmetic shift left
void CPU::ASL_AC()
{
    cycles = 2;
    C = (A & 0b10000000) > 0;
    A <<= 1;
    cycles--;
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::ASL_ZP()
{
    cycles = 5;
    uint8_t addr = GetByte();
    uint8_t data = ReadByte(addr);
    C = (data & 0b10000000) > 0;
    data <<= 1;
    cycles--;
    Z = (data == 0);
    N = (data & 0b10000000) > 0;
    WriteByte(addr, data);
}

void CPU::ASL_ZP_X()
{
    cycles = 6;
    uint8_t addr = GetByte() + X;
    cycles--;
    uint8_t data = ReadByte(addr);
    C = (data & 0b10000000) > 0;
    data <<= 1;
    cycles--;
    Z = (data == 0);
    N = (data & 0b10000000) > 0;
    WriteByte(addr, data);
}

void CPU::ASL_AB()
{
    cycles = 6;
    uint8_t addr = GetWord();
    uint8_t data = ReadByte(addr);
    C = (data & 0b10000000) > 0;
    data <<= 1;
    cycles--;
    Z = (data == 0);
    N = (data & 0b10000000) > 0;
    WriteByte(addr, data);
}

void CPU::ASL_AB_X()
{
    cycles = 7;
    uint8_t addr = GetWord() + X;
    cycles--;
    uint8_t data = ReadByte(addr);
    C = (data & 0b10000000) > 0;
    data <<= 1;
    cycles--;
    Z = (data == 0);
    N = (data & 0b10000000) > 0;
    WriteByte(addr, data);
}

// LSR - Logical shift right
void CPU::LSR_AC()
{
    cycles = 2;
    C = (A & 0b00000001) > 0;
    A >>= 1;
    cycles--;
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::LSR_ZP()
{
    cycles = 5;
    uint8_t addr = GetByte();
    uint8_t data = ReadByte(addr);
    C = (data & 0b00000001) > 0;
    data >>= 1;
    cycles--;
    Z = (data == 0);
    N = (data & 0b10000000) > 0;
    WriteByte(addr, data);
}

void CPU::LSR_ZP_X()
{
    cycles = 6;
    uint8_t addr = GetByte() + X;
    cycles--;
    uint8_t data = ReadByte(addr);
    C = (data & 0b00000001) > 0;
    data >>= 1;
    cycles--;
    Z = (data == 0);
    N = (data & 0b10000000) > 0;
    WriteByte(addr, data);
}

void CPU::LSR_AB()
{
    cycles = 6;
    uint8_t addr = GetWord();
    uint8_t data = ReadByte(addr);
    C = (data & 0b00000001) > 0;
    data >>= 1;
    cycles--;
    Z = (data == 0);
    N = (data & 0b10000000) > 0;
    WriteByte(addr, data);
}

void CPU::LSR_AB_X()
{
    cycles = 7;
    uint8_t addr = GetWord() + X;
    cycles--;
    uint8_t data = ReadByte(addr);
    C = (data & 0b00000001) > 0;
    data >>= 1;
    cycles--;
    Z = (data == 0);
    N = (data & 0b10000000) > 0;
    WriteByte(addr, data);
}

// ROL - Rotate left
void CPU::ROL_AC()
{
    cycles = 2;
    uint8_t cr = C ? 0b00000001 : 0;
    C = (A & 0b10000000) > 0;
    A <<= 1;
    A |= cr;
    cycles--;
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::ROL_ZP()
{
    cycles = 5;
    uint8_t addr = GetByte();
    uint8_t data = ReadByte(addr);
    uint8_t cr = C ? 0b00000001 : 0;
    C = (data & 0b10000000) > 0;
    data <<= 1;
    data |= cr;
    cycles--;
    Z = (data == 0);
    N = (data & 0b10000000) > 0;
    WriteByte(addr, data);
}

void CPU::ROL_ZP_X()
{
    cycles = 6;
    uint8_t addr = GetByte() + X;
    cycles--;
    uint8_t data = ReadByte(addr);
    uint8_t cr = C ? 0b00000001 : 0;
    C = (data & 0b10000000) > 0;
    data <<= 1;
    data |= cr;
    cycles--;
    Z = (data == 0);
    N = (data & 0b10000000) > 0;
    WriteByte(addr, data);
}

void CPU::ROL_AB()
{
    cycles = 6;
    uint8_t addr = GetWord();
    uint8_t data = ReadByte(addr);
    uint8_t cr = C ? 0b00000001 : 0;
    C = (data & 0b10000000) > 0;
    data <<= 1;
    data |= cr;
    cycles--;
    Z = (data == 0);
    N = (data & 0b10000000) > 0;
    WriteByte(addr, data);
}

void CPU::ROL_AB_X()
{
    cycles = 7;
    uint8_t addr = GetWord() + X;
    cycles--;
    uint8_t data = ReadByte(addr);
    uint8_t cr = C ? 0b00000001 : 0;
    C = (data & 0b10000000) > 0;
    data <<= 1;
    data |= cr;
    cycles--;
    Z = (data == 0);
    N = (data & 0b10000000) > 0;
    WriteByte(addr, data);
}

// ROR - Rotate right
void CPU::ROR_AC()
{
    cycles = 2;
    uint8_t cr = C ? 0b10000000 : 0;
    C = (A & 0b00000001) > 0;
    A >>= 1;
    A |= cr;
    cycles--;
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::ROR_ZP()
{
    cycles = 5;
    uint8_t addr = GetByte();
    uint8_t data = ReadByte(addr);
    uint8_t cr = C ? 0b10000000 : 0;
    C = (data & 0b00000001) > 0;
    data >>= 1;
    data |= cr;
    cycles--;
    Z = (data == 0);
    N = (data & 0b10000000) > 0;
    WriteByte(addr, data);
}

void CPU::ROR_ZP_X()
{
    cycles = 6;
    uint8_t addr = GetByte() + X;
    cycles--;
    uint8_t data = ReadByte(addr);
    uint8_t cr = C ? 0b10000000 : 0;
    C = (data & 0b00000001) > 0;
    data >>= 1;
    data |= cr;
    cycles--;
    Z = (data == 0);
    N = (data & 0b10000000) > 0;
    WriteByte(addr, data);
}

void CPU::ROR_AB()
{
    cycles = 6;
    uint8_t addr = GetWord();
    uint8_t data = ReadByte(addr);
    uint8_t cr = C ? 0b10000000 : 0;
    C = (data & 0b00000001) > 0;
    data >>= 1;
    data |= cr;
    cycles--;
    Z = (data == 0);
    N = (data & 0b10000000) > 0;
    WriteByte(addr, data);
}

void CPU::ROR_AB_X()
{
    cycles = 7;
    uint8_t addr = GetWord() + X;
    cycles--;
    uint8_t data = ReadByte(addr);
    uint8_t cr = C ? 0b10000000 : 0;
    C = (data & 0b00000001) > 0;
    data >>= 1;
    data |= cr;
    cycles--;
    Z = (data == 0);
    N = (data & 0b10000000) > 0;
    WriteByte(addr, data);
}

// System functions
void CPU::BRK_IP()
{
    cycles = 7;
    WriteWordToStack(pc);
    WriteByteToStack(ps);
    pc = ReadWord(0xFFFE);
    cycles--;
    B = 1;
}

void CPU::NOP_IP()
{
    cycles = 2;
    cycles--;
}

void CPU::RTI_IP()
{
    cycles = 6;
    ps = GetStackByte();
    pc = GetStackWord();
}