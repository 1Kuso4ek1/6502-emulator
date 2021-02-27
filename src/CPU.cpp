#include "CPU.h"

void CPU::Reset(Memory& memory, uint16_t start)
{
    pc = start;
    sp = 0xFF;
    C = Z = I = D = B = V = N = 0;
    U = 1;
    A = X = Y = 0;
    cycles = 0;
    memory.Init();
}

void CPU::Execute(Memory& memory) 
{
    if(cycles == 0)
    {
        uint8_t ins = GetByte(memory);
        switch (ins)
        {   
        //LDA - Load accumulator
        case 0xA9: LDA_IM(memory); break;
        case 0xA5: LDA_ZP(memory); break;
        case 0xB5: LDA_ZP_X(memory); break;
        case 0xAD: LDA_AB(memory); break;
        case 0xBD: LDA_AB_X(memory); break;
        case 0xB9: LDA_AB_Y(memory); break;
        case 0xA1: LDA_ID_X(memory); break;
        case 0xB1: LDA_ID_Y(memory); break;
        //LDX - Load X Register
        case 0xA2: LDX_IM(memory); break;
        case 0xA6: LDX_ZP(memory); break;
        case 0xB6: LDX_ZP_Y(memory); break;
        case 0xAE: LDX_AB(memory); break;
        case 0xBE: LDX_AB_Y(memory); break;
        //LDY - Load Y Register
        case 0xA0: LDY_IM(memory); break;
        case 0xA4: LDY_ZP(memory); break;
        case 0xB4: LDY_ZP_X(memory); break;
        case 0xAC: LDY_AB(memory); break;
        case 0xBC: LDY_AB_X(memory); break;
        //STA - Store accumulator
        case 0x85: STA_ZP(memory); break;
        case 0x95: STA_ZP_X(memory); break;
        case 0x8D: STA_AB(memory); break;
        case 0x9D: STA_AB_X(memory); break;
        case 0x99: STA_AB_Y(memory); break;
        case 0x81: STA_ID_X(memory); break;
        case 0x91: STA_ID_Y(memory); break;
        //STX - Store X register
        case 0x86: STX_ZP(memory); break;
        case 0x96: STX_ZP_Y(memory); break;
        case 0x8E: STX_AB(memory); break;
        //STY - Store Y register
        case 0x84: STY_ZP(memory); break;
        case 0x94: STY_ZP_X(memory); break;
        case 0x8C: STY_AB(memory); break;
        //JSR - Jump to subroutine
        case 0x20: JSR_AB(memory); break;
        //RTS - Return from subroutine
        case 0x60: RTS_IP(memory); break;
        //JMP - Jump to another location
        case 0x4C: JMP_AB(memory); break;
        case 0x6C: JMP_ID(memory); break;
        //Register transfers 
        case 0xAA: TAX_IP(); break;
        case 0xA8: TAY_IP(); break;
        case 0x8A: TXA_IP(); break;
        case 0x98: TYA_IP(); break;
        //Stack operations
        case 0xBA: TSX_IP(); break;
        case 0x9A: TXS_IP(); break;
        case 0x48: PHA_IP(memory); break;
        case 0x68: PLA_IP(memory); break;
        case 0x08: PHP_IP(memory); break;
        case 0x28: PLP_IP(memory); break;
        //Status flag changes
        case 0x18: CLC_IP(); break;
        case 0xD8: CLD_IP(); break;
        case 0x58: CLI_IP(); break;
        case 0xB8: CLV_IP(); break;
        case 0x38: SEC_IP(); break;
        case 0xF8: SED_IP(); break;
        case 0x78: SEI_IP(); break;
        //AND - Logical and
        case 0x29: AND_IM(memory); break;
        case 0x25: AND_ZP(memory); break;
        case 0x35: AND_ZP_X(memory); break;
        case 0x2D: AND_AB(memory); break;
        case 0x3D: AND_AB_X(memory); break;
        case 0x39: AND_AB_Y(memory); break;
        case 0x21: AND_ID_X(memory); break;
        case 0x31: AND_ID_Y(memory); break;
        //ORA - Logical inclusive or
        case 0x09: ORA_IM(memory); break;
        case 0x05: ORA_ZP(memory); break;
        case 0x15: ORA_ZP_X(memory); break;
        case 0x0D: ORA_AB(memory); break;
        case 0x1D: ORA_AB_X(memory); break;
        case 0x19: ORA_AB_Y(memory); break;
        case 0x01: ORA_ID_X(memory); break;
        case 0x11: ORA_ID_Y(memory); break;
        //EOR - Logical exclusive or
        case 0x49: EOR_IM(memory); break;
        case 0x45: EOR_ZP(memory); break;
        case 0x55: EOR_ZP_X(memory); break;
        case 0x4D: EOR_AB(memory); break;
        case 0x5D: EOR_AB_X(memory); break;
        case 0x59: EOR_AB_Y(memory); break;
        case 0x41: EOR_ID_X(memory); break;
        case 0x51: EOR_ID_Y(memory); break;
        //BIT - Bit test
        case 0x24: BIT_ZP(memory); break;
        case 0x2C: BIT_AB(memory); break;
        //Increments and decrements
        case 0xE6: INC_ZP(memory); break;
        case 0xF6: INC_ZP_X(memory); break;
        case 0xEE: INC_AB(memory); break;
        case 0xFE: INC_AB_X(memory); break;
        case 0xE8: INX_IP(); break;
        case 0xC8: INY_IP(); break;
        case 0xC6: DEC_ZP(memory); break;
        case 0xD6: DEC_ZP_X(memory); break;
        case 0xCE: DEC_AB(memory); break;
        case 0xDE: DEC_AB_X(memory); break;
        case 0xCA: DEX_IP(); break;
        case 0x88: DEY_IP(); break;
        //Branches
        case 0x90: BCC_RL(memory); break;
        case 0xB0: BCS_RL(memory); break;
        case 0xD0: BNE_RL(memory); break;
        case 0xF0: BEQ_RL(memory); break;
        case 0x10: BPL_RL(memory); break;
        case 0x30: BMI_RL(memory); break;
        case 0x50: BVC_RL(memory); break;
        case 0x70: BVS_RL(memory); break;
        //Arithmetic
        case 0x69: ADC_IM(memory); break;
        case 0x65: ADC_ZP(memory); break;
        case 0x75: ADC_ZP_X(memory); break;
        case 0x6D: ADC_AB(memory); break;
        case 0x7D: ADC_AB_X(memory); break;
        case 0x79: ADC_AB_Y(memory); break;
        case 0x61: ADC_ID_X(memory); break;
        case 0x71: ADC_ID_Y(memory); break;
        default: cycles = 1;
        }           
    }
    cycles--;
}

void CPU::GetStatus(Memory& memory)
{
    std::cout << "Program counter = " << std::hex << (int)pc << std::endl;
    std::cout << "Stack pointer = " << std::hex << (int)sp << std::endl;
    std::cout << "memory[pc] = " << std::hex << (int)memory[pc] << std::endl;
    std::cout << "A = " << std::hex << (int)A << " X = " << std::hex << (int)X << " Y = " << std::hex << (int)Y << std::endl;
    std::cout << "C = " << std::hex << (int)C << " Z = " << std::hex << (int)Z << " I = " << std::hex << (int)I << " D = " << std::hex << (int)D << " B = " << std::hex << (int)B << " V = " << std::hex << (int)V << " N = " << std::hex << (int)N << std::endl;
}

uint8_t CPU::GetByte(Memory& memory)
{
    uint8_t data = memory[pc];
    pc++;
    cycles--;
    return data;
}

uint8_t CPU::ReadByte(Memory& memory, uint16_t address)
{
    cycles--;
    return memory[address];
}

void CPU::WriteByte(Memory& memory, uint16_t address, uint8_t data)
{
    memory[address] = data;
    cycles--;
}

uint16_t CPU::GetWord(Memory& memory)
{
    uint16_t data = memory[pc];
    pc++;
    data |= (memory[pc] << 8);
    pc++;
    cycles -= 2;
    return data;
}

uint16_t CPU::ReadWord(Memory& memory, uint16_t address)
{
    cycles -= 2;
    return (uint16_t)(ReadByte(memory, address) | (ReadByte(memory, address + 1) << 8));
}

void CPU::WriteWord(Memory& memory, uint16_t data, uint16_t address)
{
    memory[address] = data & 0xFF;
    memory[address + 1] = data >> 8;
    cycles -= 2;
}

uint16_t CPU::GetStackWord(Memory& memory)
{
    uint16_t data = ReadWord(memory, (0x100 | sp) + 1);
    sp += 2;
    cycles--;
    return data;
}

void CPU::WriteWordToStack(Memory& memory, uint16_t data)
{
    WriteWord(memory, data, (0x100 | sp) - 1);
    sp -= 2;
    cycles--;
}

uint8_t CPU::GetStackByte(Memory& memory)
{
    uint8_t data = ReadByte(memory, (0x100 | sp) + 1);
    sp++;
    cycles--;
    return data;
}

void CPU::WriteByteToStack(Memory& memory, uint8_t data)
{
    WriteByte(memory, (0x100 | sp), data);
    sp--;
    cycles--;
}

//LDA - Load accumulator
void CPU::LDA_IM(Memory& memory)
{
    cycles = 2;
    A = GetByte(memory);
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::LDA_ZP(Memory& memory)
{
    cycles = 3;
    A = ReadByte(memory, GetByte(memory));
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::LDA_ZP_X(Memory& memory)
{
    cycles = 4;
    uint8_t data = GetByte(memory);
    data += X;
    cycles--;
    A = ReadByte(memory, data);
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::LDA_AB(Memory& memory)
{
    cycles = 4;
    A = ReadByte(memory, GetWord(memory));
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::LDA_AB_X(Memory& memory)
{
    cycles = 4;
    uint16_t address = GetWord(memory);
    A = ReadByte(memory, address + X);
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::LDA_AB_Y(Memory& memory)
{
    cycles = 4;
    A = ReadByte(memory, (uint16_t)(GetWord(memory) + Y));
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::LDA_ID_X(Memory& memory)
{
    cycles = 6;
    A = ReadByte(memory, ReadWord(memory, (uint16_t)(GetByte(memory) + X)));
    cycles--;
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::LDA_ID_Y(Memory& memory)
{
    cycles = 5;
    A = ReadByte(memory, ReadWord(memory, (uint16_t)(GetByte(memory))) + Y);
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

//LDX - Load X Register
void CPU::LDX_IM(Memory& memory)
{
    cycles = 2;
    X = GetByte(memory);
    Z = (X == 0);
    N = (X & 0b10000000) > 0;
}

void CPU::LDX_ZP(Memory& memory)
{
    cycles = 3;
    X = ReadByte(memory, GetByte(memory));
    Z = (X == 0);
    N = (X & 0b10000000) > 0;
}

void CPU::LDX_ZP_Y(Memory& memory)
{
    cycles = 4;
    uint8_t data = GetByte(memory);
    data += Y;
    cycles--;
    X = ReadByte(memory, data);
    Z = (X == 0);
    N = (X & 0b10000000) > 0;
}

void CPU::LDX_AB(Memory& memory)
{
    cycles = 4;
    X = ReadByte(memory, GetWord(memory));
    Z = (X == 0);
    N = (X & 0b10000000) > 0;
}

void CPU::LDX_AB_Y(Memory& memory)
{
    cycles = 4;
    uint16_t address = GetWord(memory);
    X = ReadByte(memory, address + Y);
    Z = (X == 0);
    N = (X & 0b10000000) > 0;
}

//LDY - Load Y Register
void CPU::LDY_IM(Memory& memory)
{
    cycles = 2;
    Y = GetByte(memory);
    Z = (Y == 0);
    N = (Y & 0b10000000) > 0;
}

void CPU::LDY_ZP(Memory& memory)
{
    cycles = 3;
    Y = ReadByte(memory, GetByte(memory));
    Z = (Y == 0);
    N = (Y & 0b10000000) > 0;
}

void CPU::LDY_ZP_X(Memory& memory)
{
    cycles = 4;
    uint8_t data = GetByte(memory);
    data += X;
    cycles--;
    Y = ReadByte(memory, data);
    Z = (Y == 0);
    N = (Y & 0b10000000) > 0;
}

void CPU::LDY_AB(Memory& memory)
{
    cycles = 4;
    Y = ReadByte(memory, GetWord(memory));
    Z = (Y == 0);
    N = (Y & 0b10000000) > 0;
}

void CPU::LDY_AB_X(Memory& memory)
{
    cycles = 4;
    uint16_t address = GetWord(memory);
    Y = ReadByte(memory, address + X);
    Z = (Y == 0);
    N = (Y & 0b10000000) > 0;
}

//STA - store accumulator
void CPU::STA_ZP(Memory& memory)
{
    cycles = 3;
    WriteByte(memory, GetByte(memory), A);
}

void CPU::STA_ZP_X(Memory& memory)
{
    cycles = 4;
    WriteByte(memory, GetByte(memory) + X, A);
    cycles--;
}

void CPU::STA_AB(Memory& memory)
{
    cycles = 4;
    WriteByte(memory, GetWord(memory), A);
}

void CPU::STA_AB_X(Memory& memory)
{
    cycles = 5;
    WriteByte(memory, GetWord(memory) + X, A);
    cycles--;
}

void CPU::STA_AB_Y(Memory& memory)
{
    cycles = 5;
    WriteByte(memory, GetWord(memory) + Y, A);
    cycles--;
}

void CPU::STA_ID_X(Memory& memory)
{
    cycles = 6;
    WriteByte(memory, ReadWord(memory, (uint16_t)(GetByte(memory) + X)), A);
    cycles--;
}

void CPU::STA_ID_Y(Memory& memory)
{
    cycles = 6;
    WriteByte(memory, ReadWord(memory, (uint16_t)(GetByte(memory))) + Y, A);
    cycles--;
}

//STX - Store X register
void CPU::STX_ZP(Memory& memory)
{
    cycles = 3;
    WriteByte(memory, GetByte(memory), X);
}

void CPU::STX_ZP_Y(Memory& memory)
{
    cycles = 4;
    WriteByte(memory, GetByte(memory) + Y, X);
    cycles--;
}

void CPU::STX_AB(Memory& memory)
{
    cycles = 4;
    WriteByte(memory, GetWord(memory), X);
}

//STY - Store Y register
void CPU::STY_ZP(Memory& memory)
{
    cycles = 3;
    WriteByte(memory, GetByte(memory), Y);
}

void CPU::STY_ZP_X(Memory& memory)
{
    cycles = 4;
    WriteByte(memory, GetByte(memory) + X, Y);
    cycles--;
}

void CPU::STY_AB(Memory& memory)
{
    cycles = 4;
    WriteByte(memory, GetWord(memory), Y);
}

//JSR - Jump to subroutine
void CPU::JSR_AB(Memory& memory) 
{
    cycles = 6;
    uint16_t address = GetWord(memory);
    WriteWordToStack(memory, pc - 1);
    pc = address;
}

//RTS - Return from subroutine
void CPU::RTS_IP(Memory& memory)
{
    cycles = 6;
    pc = GetStackWord(memory) + 1;
}

//JMP - Jump to another location
void CPU::JMP_AB(Memory& memory)
{
    cycles = 3;
    pc = GetWord(memory);
}

void CPU::JMP_ID(Memory& memory)
{
    cycles = 5;
    pc = ReadWord(memory, GetWord(memory));
}

//Register transfers
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

//Stack operations
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

void CPU::PHA_IP(Memory& memory)
{
    cycles = 3;
    WriteByteToStack(memory, A);
}

void CPU::PLA_IP(Memory& memory)
{
    cycles = 4;
    A = GetStackByte(memory);
    cycles--;
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::PHP_IP(Memory& memory)
{
    cycles = 3;
    WriteByteToStack(memory, ps);
}

void CPU::PLP_IP(Memory& memory)
{
    cycles = 4;
    ps = GetStackByte(memory);
    cycles--;
}

//Status flag changes
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

//AND - Logical and
void CPU::AND_IM(Memory& memory)
{
    cycles = 2;
    A &= GetByte(memory);
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::AND_ZP(Memory& memory)
{
    cycles = 3;
    A &= ReadByte(memory, GetByte(memory));
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::AND_ZP_X(Memory& memory)
{
    cycles = 4;
    uint8_t data = GetByte(memory);
    data += X;
    cycles--;
    A &= ReadByte(memory, data);
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::AND_AB(Memory& memory)
{
    cycles = 4;
    A &= ReadByte(memory, GetWord(memory));
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::AND_AB_X(Memory& memory)
{
    cycles = 4;
    uint16_t address = GetWord(memory);
    A &= ReadByte(memory, address + X);
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::AND_AB_Y(Memory& memory)
{
    cycles = 4;
    A &= ReadByte(memory, (uint16_t)(GetWord(memory) + Y));
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::AND_ID_X(Memory& memory)
{
    cycles = 6;
    A &= ReadByte(memory, ReadWord(memory, (uint16_t)(GetByte(memory) + X)));
    cycles--;
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::AND_ID_Y(Memory& memory)
{
    cycles = 5;
    A &= ReadByte(memory, ReadWord(memory, (uint16_t)(GetByte(memory))) + Y);
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

//ORA - Logical inclusive or
void CPU::ORA_IM(Memory& memory)
{
    cycles = 2;
    A |= GetByte(memory);
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::ORA_ZP(Memory& memory)
{
    cycles = 3;
    A |= ReadByte(memory, GetByte(memory));
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::ORA_ZP_X(Memory& memory)
{
    cycles = 4;
    uint8_t data = GetByte(memory);
    data += X;
    cycles--;
    A |= ReadByte(memory, data);
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::ORA_AB(Memory& memory)
{
    cycles = 4;
    A |= ReadByte(memory, GetWord(memory));
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::ORA_AB_X(Memory& memory)
{
    cycles = 4;
    uint16_t address = GetWord(memory);
    A |= ReadByte(memory, address + X);
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::ORA_AB_Y(Memory& memory)
{
    cycles = 4;
    A |= ReadByte(memory, (uint16_t)(GetWord(memory) + Y));
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::ORA_ID_X(Memory& memory)
{
    cycles = 6;
    A |= ReadByte(memory, ReadWord(memory, (uint16_t)(GetByte(memory) + X)));
    cycles--;
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::ORA_ID_Y(Memory& memory)
{
    cycles = 5;
    A |= ReadByte(memory, ReadWord(memory, (uint16_t)(GetByte(memory))) + Y);
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

//EOR - Logical exclusive or
void CPU::EOR_IM(Memory& memory)
{
    cycles = 2;
    A ^= GetByte(memory);
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::EOR_ZP(Memory& memory)
{
    cycles = 3;
    A ^= ReadByte(memory, GetByte(memory));
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::EOR_ZP_X(Memory& memory)
{
    cycles = 4;
    uint8_t data = GetByte(memory);
    data += X;
    cycles--;
    A ^= ReadByte(memory, data);
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::EOR_AB(Memory& memory)
{
    cycles = 4;
    A ^= ReadByte(memory, GetWord(memory));
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::EOR_AB_X(Memory& memory)
{
    cycles = 4;
    uint16_t address = GetWord(memory);
    A ^= ReadByte(memory, address + X);
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::EOR_AB_Y(Memory& memory)
{
    cycles = 4;
    A ^= ReadByte(memory, (uint16_t)(GetWord(memory) + Y));
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::EOR_ID_X(Memory& memory)
{
    cycles = 6;
    A ^= ReadByte(memory, ReadWord(memory, (uint16_t)(GetByte(memory) + X)));
    cycles--;
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::EOR_ID_Y(Memory& memory)
{
    cycles = 5;
    A ^= ReadByte(memory, ReadWord(memory, (uint16_t)(GetByte(memory))) + Y);
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

//BIT - Bit test
void CPU::BIT_ZP(Memory& memory)
{
    cycles = 3;
    uint8_t data = ReadByte(memory, GetByte(memory));
    Z = !(A & data);
    V = (data & 0b01000000) > 0;
    N = (data & 0b10000000) > 0;
}

void CPU::BIT_AB(Memory& memory)
{
    cycles = 4;
    uint8_t data = ReadByte(memory, GetWord(memory));
    Z = !(A & data);
    V = (data & 0b01000000) > 0;
    N = (data & 0b10000000) > 0;
}

//INC - Increment a memory location
void CPU::INC_ZP(Memory& memory)
{
    cycles = 5;
    uint8_t addr = GetByte(memory), result = ReadByte(memory, addr) + 1;
    cycles--;
    WriteByte(memory, addr, result);
    Z = (result == 0);
    N = (result & 0b10000000) > 0;
}

void CPU::INC_ZP_X(Memory& memory)
{
    cycles = 6;
    uint8_t addr = GetByte(memory) + X, result = ReadByte(memory, addr) + 1;
    cycles -= 2;
    WriteByte(memory, addr, result);
    Z = (result == 0);
    N = (result & 0b10000000) > 0;
}

void CPU::INC_AB(Memory& memory)
{
    cycles = 6;
    uint16_t addr = GetWord(memory), result = ReadByte(memory, addr) + 1;
    cycles--;
    WriteByte(memory, addr, result);
    Z = (result == 0);
    N = (result & 0b10000000) > 0;
}

void CPU::INC_AB_X(Memory& memory)
{
    cycles = 7;
    uint16_t addr = GetWord(memory) + X, result = ReadByte(memory, addr) + 1;
    cycles -= 2;
    WriteByte(memory, addr, result);
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

//DEC - Decrement a memory location
void CPU::DEC_ZP(Memory& memory)
{
    cycles = 5;
    uint8_t addr = GetByte(memory), result = ReadByte(memory, addr) - 1;
    cycles--;
    WriteByte(memory, addr, result);
    Z = (result == 0);
    N = (result & 0b10000000) > 0;
}

void CPU::DEC_ZP_X(Memory& memory)
{
    cycles = 6;
    uint8_t addr = GetByte(memory) + X, result = ReadByte(memory, addr) - 1;
    cycles -= 2;
    WriteByte(memory, addr, result);
    Z = (result == 0);
    N = (result & 0b10000000) > 0;
}

void CPU::DEC_AB(Memory& memory)
{
    cycles = 6;
    uint16_t addr = GetWord(memory), result = ReadByte(memory, addr) - 1;
    cycles--;
    WriteByte(memory, addr, result);
    Z = (result == 0);
    N = (result & 0b10000000) > 0;
}

void CPU::DEC_AB_X(Memory& memory)
{
    cycles = 7;
    uint16_t addr = GetWord(memory) + X, result = ReadByte(memory, addr) - 1;
    cycles -= 2;
    WriteByte(memory, addr, result);
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

//Branches
void CPU::BCC_RL(Memory& memory)
{
    cycles = 2;
    uint8_t offset = GetByte(memory);
    pc += (!C) ? static_cast<int8_t>(offset) : 0;
}

void CPU::BCS_RL(Memory& memory)
{
    cycles = 2;
    uint8_t offset = GetByte(memory);
    pc += (C) ? static_cast<int8_t>(offset) : 0;
}

void CPU::BNE_RL(Memory& memory)
{
    cycles = 2;
    uint8_t offset = GetByte(memory);
    pc += (!Z) ? static_cast<int8_t>(offset) : 0;
}

void CPU::BEQ_RL(Memory& memory)
{
    cycles = 2;
    uint8_t offset = GetByte(memory);
    pc += (Z) ? static_cast<int8_t>(offset) : 0;
}

void CPU::BPL_RL(Memory& memory)
{
    cycles = 2;
    uint8_t offset = GetByte(memory);
    pc += (!N) ? static_cast<int8_t>(offset) : 0;
}

void CPU::BMI_RL(Memory& memory)
{
    cycles = 2;
    uint8_t offset = GetByte(memory);
    pc += (N) ? static_cast<int8_t>(offset) : 0;
}

void CPU::BVC_RL(Memory& memory)
{
    cycles = 2;
    uint8_t offset = GetByte(memory);
    pc += (!V) ? static_cast<int8_t>(offset) : 0;
}

void CPU::BVS_RL(Memory& memory)
{
    cycles = 2;
    uint8_t offset = GetByte(memory);
    pc += (V) ? static_cast<int8_t>(offset) : 0;
}

//Arithmetic
void CPU::ADC_IM(Memory& memory)
{
    cycles = 2;
    uint8_t acp = A, op = GetByte(memory);
    uint16_t sum = A + op + C;
    A = (sum & 0xFF);
    C = (sum & 0xFF00) > 0;
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
    V = (((acp & 0b10000000) ^ (op & 0b10000000)) == 0) ? (A & 0b10000000) != (acp & 0b10000000) : 0;
}

void CPU::ADC_ZP(Memory& memory)
{
    cycles = 3;
    uint8_t acp = A, op = ReadByte(memory, GetByte(memory));
    uint16_t sum = A + op + C;
    A = (sum & 0xFF);
    C = (sum & 0xFF00) > 0;
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
    V = (((acp & 0b10000000) ^ (op & 0b10000000)) == 0) ? (A & 0b10000000) != (acp & 0b10000000) : 0;
}

void CPU::ADC_ZP_X(Memory& memory)
{
    cycles = 4;
    uint8_t acp = A, op = ReadByte(memory, GetByte(memory) + X);
    uint16_t sum = A + op + C;
    A = (sum & 0xFF);
    C = (sum & 0xFF00) > 0;
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
    V = (((acp & 0b10000000) ^ (op & 0b10000000)) == 0) ? (A & 0b10000000) != (acp & 0b10000000) : 0;
}

void CPU::ADC_AB(Memory& memory)
{
    cycles = 4;
    uint8_t acp = A, op = ReadByte(memory, GetWord(memory));
    uint16_t sum = A + op + C;
    A = (sum & 0xFF);
    C = (sum & 0xFF00) > 0;
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
    V = (((acp & 0b10000000) ^ (op & 0b10000000)) == 0) ? (A & 0b10000000) != (acp & 0b10000000) : 0;
}

void CPU::ADC_AB_X(Memory& memory)
{
    cycles = 4;
    uint8_t acp = A, op = ReadByte(memory, GetWord(memory) + X);
    uint16_t sum = A + op + C;
    A = (sum & 0xFF);
    C = (sum & 0xFF00) > 0;
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
    V = (((acp & 0b10000000) ^ (op & 0b10000000)) == 0) ? (A & 0b10000000) != (acp & 0b10000000) : 0;
}

void CPU::ADC_AB_Y(Memory& memory)
{
    cycles = 4;
    uint8_t acp = A, op = ReadByte(memory, GetWord(memory) + Y);
    uint16_t sum = A + op + C;
    A = (sum & 0xFF);
    C = (sum & 0xFF00) > 0;
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
    V = (((acp & 0b10000000) ^ (op & 0b10000000)) == 0) ? (A & 0b10000000) != (acp & 0b10000000) : 0;
}

void CPU::ADC_ID_X(Memory& memory)
{
    cycles = 6;
    uint8_t acp = A, op = ReadByte(memory, ReadWord(memory, (uint16_t)(GetByte(memory) + X)));
    cycles--;
    uint16_t sum = A + op + C;
    A = (sum & 0xFF);
    C = (sum & 0xFF00) > 0;
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
    V = (((acp & 0b10000000) ^ (op & 0b10000000)) == 0) ? (A & 0b10000000) != (acp & 0b10000000) : 0;
}

void CPU::ADC_ID_Y(Memory& memory)
{
    cycles = 5;
    uint8_t acp = A, op = ReadByte(memory, ReadWord(memory, (uint16_t)(GetByte(memory))) + Y);
    uint16_t sum = A + op + C;
    A = (sum & 0xFF);
    C = (sum & 0xFF00) > 0;
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
    V = (((acp & 0b10000000) ^ (op & 0b10000000)) == 0) ? (A & 0b10000000) != (acp & 0b10000000) : 0;
}