#pragma once
#include <MemoryBus.hpp>

#include <string>
#include <fstream>

inline bool ReadFile(const std::string& path, MemoryBus& memory, uint16_t start = 0)
{
    std::ifstream file(path, std::ios::binary);

    if(file.is_open())
    {
        file >> std::noskipws;
        
        uint8_t data;
        uint16_t index = start > 0 ? start - 1 : 0;
        
        while(file >> data)
            memory.Write(++index, data);
        
        return true;
    }
    
    return false;
}

