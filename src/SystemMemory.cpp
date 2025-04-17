#include <SystemMemory.hpp>

SystemMemory::SystemMemory(uint32_t size)
{
    ram.resize(size);
}

uint8_t SystemMemory::Read(uint16_t address)
{
    // May add some "partitions" for various devices
    return ram[address];
}

void SystemMemory::Write(uint16_t address, uint8_t data)
{
    ram[address] = data;
}
