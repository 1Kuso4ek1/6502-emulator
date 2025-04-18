#pragma once
#include <unordered_map>
#include <string>

static std::unordered_map<std::string, std::string> help =
{
    { "--help", "Usage: ./6502 [options] *file path* *memory start address* *PC address*\n"
                    "Options:\n"
                    "--help - Display this information\n"
                    "--help-memory-control - Display help on memory control\n"
                    "--memory-control - Enable runtime memory control mode\n"
                    "--show-status - If enabled, emulator will write current status every step (PC, registers, etc.)\n" },
    { "--help-memory-control", "stack - Display stack content\n"
                                   "read (next line - absolute address) - Display memory content at absolute address\n"
                                   "write (next line - absolute address, space, data) - Write data at absolute address\n"
                                   "stop - Exit emulator\n" }
};
