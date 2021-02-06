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
        case 0x20: JSR_AB(memory); break; 
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

uint8_t CPU::ReadByte(Memory& memory, uint8_t address)
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
    A = ReadByte(memory, GetByte(memory));
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