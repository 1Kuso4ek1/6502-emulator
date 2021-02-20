#include "CPU.h"

void CPU::Reset(Memory& memory)
{
    pc = 0x8000;
    sp = 0xFF;
    C = Z = I = D = B = V = N = 0;
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
        //JSR - Jump to subroutine
        case 0x20: JSR_AB(memory); break;
        //Register transfers 
        case 0xAA: TAX_IP(); break;
        case 0xA8: TAY_IP(); break;
        case 0x8A: TXA_IP(); break;
        case 0x98: TYA_IP(); break;
        default: cycles = 1;
        }           
    }
    cycles--;
}

void CPU::GetStatus()
{
    std::cout << "Program counter = " << std::hex << (int)pc << std::endl;
    std::cout << "Stack pointer = " << std::hex << (int)sp << std::endl;
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

void CPU::WriteWord(Memory& memory, uint16_t data, uint32_t address)
{
    memory[address] = data & 0xFF;
    memory[address + 1] = data >> 8;
    cycles -= 2;
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

//JSR - Jump to subroutine
void CPU::JSR_AB(Memory& memory) 
{
    cycles = 6;
    uint16_t address = GetWord(memory);
    WriteWord(memory, pc - 1, 0x100 | sp);
    sp -= 2;
    pc = address;
    cycles--;
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