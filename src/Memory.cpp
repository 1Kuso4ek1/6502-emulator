#include "Memory.h"

void Memory::Init()
{
    for(auto& i : data) i = 0x00;
}

uint8_t& Memory::operator[](uint32_t pos)
{
    return data[pos];
}