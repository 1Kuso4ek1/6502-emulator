#include "CPU.h"
#include <fstream>
#include <string.h>

bool ReadFile(std::string path, Memory& memory)
{
    std::ifstream file(path, std::ios::binary);
    if(file.is_open())
    {
        file >> std::noskipws;
        uint8_t data;
        uint16_t offset = 0x7FFF;
        while (file >> data) {
            memory[++offset] = data;
        }
        return true;
    }
    return false;
}

int main(int argc, char** argv)
{
    CPU cpu;
    Memory m;
    cpu.Reset(m, 0x8000);
    std::string action;
    bool memoryControl;
    memoryControl = (strcmp(argv[1], "--memory-control") == 0); 
    if(strcmp(argv[1], "--help") == 0)
    {
        std::cout << "Usage: ./6502 [option] *file path* *number of executions*" << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "--help - Display this information" << std::endl;
        std::cout << "--help-debug - Display help " << std::endl;
        std::cout << "--memory-control - Enable runtime memory control mode" << std::endl;
        exit(EXIT_SUCCESS);
    }
    if(strcmp(argv[1], "--help-memory-control") == 0)
    {
        std::cout << "stack - Display stack content" << std::endl;
        std::cout << "read (next line - absolute address) - Display memory content at absolute address" << std::endl;
        std::cout << "write (next line - absolute address, second line - data) - Write data at absolute address" << std::endl;
        exit(EXIT_SUCCESS);
    }
    if(!ReadFile(argv[(int)(memoryControl + 1)], m))
    {
        std::cout << "Error: can't read file" << std::endl;
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < atoi(argv[(int)(memoryControl + 2)]); i++) 
    {
        cpu.GetStatus(m);
        cpu.Execute(m);
        if(memoryControl)
        {
            (std::cin >> action).get();
            if(action == "stack")
            {
                for(int i = 0; i < 256; i++)
                {
                    std::cout << std::hex << (int)m[0x0100 + i] << " ";
                }
                std::cout << std::endl;
                std::cin.get();
            }
            else if(action == "read")
            {
                uint16_t addr;
                std::cin >> std::hex >> addr;
                std::cout << "memory content in 0x" << std::hex << (int)addr << " = " << (int)m[addr] << std::endl;
                std::cin.get();
            }
            else if(action == "write")
            {
                uint16_t addr;
                uint8_t data;
                std::cin >> addr;
                std::cin >> data;
                m[addr] = data;
                std::cin.get();
            }
        }
        //cpu.GetStatus(m);
    } 
}