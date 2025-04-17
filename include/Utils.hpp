#pragma once
#include <MemoryBus.hpp>

#include <string>
#include <fstream>

inline bool ReadFile(const std::string& path, MemoryBus& memory, uint16_t pc)
{
    std::ifstream file(path, std::ios::binary);

    if(file.is_open())
    {
        file >> std::noskipws;
        
        uint8_t data;
        uint16_t offset = pc - 1;
        
        while(file >> data)
            memory.Write(++offset, data);
        
        return true;
    }
    
    return false;
}

