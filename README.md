# 6502-emulator
My first attempt to write an emulator
## Building (linux)
Download and build https://github.com/1Kuso4ek1/ibs, move executable near main.cpp, then execute
```
./ibs build.ibs
```
in terminal.
## Creating and running a program
Go to https://www.masswerk.at/6502/assembler.html, in "src" text box write assembler code, then press "generate code" button. Open your hex editor (for example, Bless), write object code and save the file. To run this code write
```
./6502 *yourprogram* *number of executions* *PC address*
```
in terminal, for more commands use --help flag.
