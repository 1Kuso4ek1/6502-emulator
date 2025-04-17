#include <SystemMemory.hpp>
#include <CPU.hpp>
#include <Utils.hpp>
#include <CommandLine.hpp>

#include <iostream>
#include <sstream>

int main(int argc, char* argv[])
{
    SystemMemory m(1024 * 64);
    CPU cpu(m);
    
    std::string action;
    std::stringstream a;

    uint16_t addr;
    bool memoryControl{}, status{};
    
    if(help.find(argv[1]) != help.end())
    {
        std::cout << help.at(argv[1]) << std::endl;
        
        return 0;
    }

    for(int i = 0; i < argc; i++)
    {
        memoryControl = (std::string(argv[i]) == "--memory-control" ? true : memoryControl);
        status = (std::string(argv[i]) == "--show-status" ? true : status);
    }

    a << argv[argc - 1];
    a >> std::hex >> addr;

    if(addr == 0)
        addr = 0x2000;

    cpu.Reset(addr);
    
    if(!ReadFile(argv[argc - 2], m, addr))
    {
        std::cout << "Error: can't read file" << std::endl;
        
        return 0;
    }

    while(true)
    {
        if(status)
        {
            system("clear");
            cpu.GetStatus();
        }
        
        if(cpu.Execute())
        {
            std::cout << "BRK Handled" << std::endl;
            
            if(!memoryControl)
                break;
        }

        if(memoryControl)
        {
            (std::cin >> action).get();

            if(action == "stack")
            {
                for(int i = 0; i < 256; i++)
                    std::cout << std::hex << (int)m.Read(0x0100 + i) << " ";
                
                std::cout << std::endl;

                std::cin.get();
            }
            else if(action == "read")
            {
                uint16_t addr;
                
                (std::cin >> std::hex >> addr).get();
                std::cout << "Memory content at 0x" << std::hex << (int)addr << " = " << (int)m.Read(addr) << std::endl;
                
                std::cin.get();
            }
            else if(action == "write")
            {
                uint16_t addr, data;

                (std::cin >> std::hex >> addr >> data).get();
                
                m.Write(addr, static_cast<uint8_t>(data));
            }
            else if(action == "stop")
                return 0;
        }
    } 
}