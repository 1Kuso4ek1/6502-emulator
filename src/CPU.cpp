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
        case 0xA9: LDA_IM(memory); break;
        case 0xA5: LDA_ZP(memory); break;
        case 0xB5: LDA_ZP_X(memory); break;
        case 0xAD: LDA_AB(memory); break;
        case 0xBD: LDA_AB_X(memory); break;
        case 0xB9: LDA_AB_Y(memory); break;
        case 0xA1: LDA_ID_X(memory); break;
        case 0xB1: LDA_ID_Y(memory); break;
        case 0x20: JSR_AB(memory); break; 
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

void CPU::LDA_IM(Memory& memory)
{
    cycles = 2;
    uint8_t data = GetByte(memory);
    A = data;
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
    std::cout << "A = " << std::hex << (int)A << std::endl;
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

void CPU::JSR_AB(Memory& memory) 
{
    cycles = 6;
    uint16_t address = GetWord(memory);
    WriteWord(memory, pc - 1, 0x100 | sp);
    sp -= 2;
    pc = address;
    cycles--;
}

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