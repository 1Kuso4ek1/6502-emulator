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