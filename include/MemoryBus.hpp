#pragma once
#include <cstdint>

class MemoryBus
{
public:
    virtual ~MemoryBus() = default;

    virtual uint8_t Read(uint16_t address) = 0;
    virtual void Write(uint16_t address, uint8_t data) = 0;

};
