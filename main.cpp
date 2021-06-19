#include "CPU.h"
#include <fstream>
#include <string.h>
#include <sstream>
#include "Window.h"
bool ReadFile(std::string path, Memory& memory, uint16_t pcpos)
{
    std::ifstream file(path, std::ios::binary);
    if(file.is_open())
    {
        file >> std::noskipws;
        uint8_t data;
        uint16_t offset = pcpos - 1;
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
    std::string action;
    std::stringstream a;
    uint16_t addr;
    bool memoryControl, status, screen;
    if(strcmp(argv[1], "--help") == 0)
    {
        std::cout << "Usage: ./6502 [option] *file path* *PC address*" << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "--help - Display this information" << std::endl;
        std::cout << "--show-screen - Enable virtual screen" << std::endl;
        std::cout << "--help-screen - Display help on using the screen" << std::endl;
        std::cout << "--help-memory-control - Display help on memory control" << std::endl;
        std::cout << "--memory-control - Enable runtime memory control mode" << std::endl;
        std::cout << "--show-status - If enabled, emulator will write current status every step (PC, registers, etc.)" << std::endl;
        exit(EXIT_SUCCESS);
    }
    
    if(strcmp(argv[1], "--help-memory-control") == 0)
    {
        std::cout << "stack - Display stack content" << std::endl;
        std::cout << "read (next line - absolute address) - Display memory content at absolute address" << std::endl;
        std::cout << "write (next line - absolute address, space, data) - Write data at absolute address" << std::endl;
        std::cout << "stop - Exit emulator" << std::endl;
        exit(EXIT_SUCCESS);
    }

    if(strcmp(argv[1], "--help-screen") == 0)
    {
        std::cout << "The screen uses partition 0200 - 03FF as video memory." << std::endl;
        std::cout << "Colors: 0x00 - Black, 0x01 - White, 0x02 - Red, 0x03 - Cyan, 0x04 - Magenta, 0x05 - Green, 0x06 - Blue, 0x07 - Yellow, 0x08 - Orange, 0x09 - Brown, 0x0A - Almost gray :), 0x0B - Gray." << std::endl;
        std::cout << "Also there is a keyboard (Last sf::Keyboard::Key stored in 0xFF) and a random byte (New random number in 0xFE every step)." << std::endl;
        exit(EXIT_SUCCESS);
    }

    memoryControl = (strcmp(argv[1], "--memory-control") == 0) || (strcmp(argv[2], "--memory-control") == 0) || ((argc >= 4) && (strcmp(argv[3], "--memory-control") == 0)); 
    status = (strcmp(argv[1], "--show-status") == 0) || (strcmp(argv[2], "--show-status") == 0) || ((argc >= 4) && (strcmp(argv[3], "--show-status") == 0)); 
    screen = (strcmp(argv[1], "--show-screen") == 0) || (strcmp(argv[2], "--show-screen") == 0) || ((argc >= 4) && (strcmp(argv[3], "--show-screen") == 0)); 

    a << argv[(int)(memoryControl + status + screen + 2)];
    a >> std::hex >> addr;
    cpu.Reset(m, addr);
    
    if(!ReadFile(argv[(int)(memoryControl + status + screen + 1)], m, addr))
    {
        std::cout << "Error: can't read file" << std::endl;
        exit(EXIT_FAILURE);
    }
    if(screen)
    {
        Setup();
        m[0x00ff] = 0xff;
    }
    for(;;) 
    {
        if(status)
        {
            #ifndef WIN_32
            system("clear");
            #else
            system("cls");
            #endif
            cpu.GetStatus(m);
        }
        Events(m);
        if(cpu.Execute(m))
        {
            std::cout << "BRK Handled" << std::endl;
            if(!memoryControl) break;
        }
        if(screen) DrawFrame(m);
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
                (std::cin >> std::hex >> addr).get();
                std::cout << "memory content in 0x" << std::hex << (int)addr << " = " << (int)m[addr] << std::endl;
                std::cin.get();
            }
            else if(action == "write")
            {
                uint16_t addr, data;
                (std::cin >> std::hex >> addr >> data).get();
                m[addr] = static_cast<uint8_t>(data);
            }
            else if(action == "stop")
            {
                exit(EXIT_SUCCESS);
            }
        }
    } 
}