#pragma once
#include <MemoryBus.hpp>

#include <vector>

class SystemMemory : public MemoryBus
{
public:
    SystemMemory(uint32_t size);
    virtual ~SystemMemory() = default;

    virtual uint8_t Read(uint16_t address) override;
    virtual void Write(uint16_t address, uint8_t data) override;

private:
    std::vector<uint8_t> ram;

};
