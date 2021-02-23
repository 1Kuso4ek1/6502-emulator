#include "CPU.h"
#include <fstream>

void ReadFile(std::string path, Memory& memory)
{
    std::ifstream file("Mario.nes", std::ios::binary);
    file >> std::noskipws;
    uint8_t data;
    int offset = 0x8000;
    while (file >> data) {
        memory[offset++] = data;
    }
}

int main()
{
    CPU cpu;
    Memory m;
    cpu.Reset(m);
    //Simple program
    m[0x8000] = 0xA9; m[0x8001] = 0x23; m[0x8002] = 0x20; m[0x8003] = 0x22; m[0x8004] = 0x22; m[0x2222] = 0xA2; m[0x2223] = 0x55;
    m[0x2224] = 0x60; m[8005] = 0x8A; m[0x8006] = 0x48; m[0x8007] = 0xA9; m[0x8008] = 0xAA; m[0x8009] = 0x68;

    for(int i = 0; i < 8; i++) {
        //cpu.GetStatus(m);
        cpu.Execute(m);
        cpu.GetStatus(m);
    } 
}