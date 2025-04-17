cmake_minimum_required(VERSION 3.20)

project(6502-emulator)

add_executable(6502 main.cpp src/CPU.cpp src/SystemMemory.cpp)

include_directories(include/)
