# 6502 Emulator

This is my first attempt at writing a 6502 emulator. (2021)

## Building (Linux)

1.  **Navigate to the Project Directory:**
    Open your terminal and navigate to the root directory of the 6502 emulator project (the directory containing `CMakeLists.txt`).

2.  **Create a Build Directory:**
    ```bash
    mkdir build
    cd build
    ```

3.  **Configure the Build:**
    ```bash
    cmake ..
    ```

4.  **Build the Emulator:**
    ```bash
    make
    ```

## Creating and Running a 6502 Program

You can create 6502 programs using several methods. The output of these methods will be a raw binary file containing the machine code.

**Methods for Creating 6502 Programs:**

1.  **Online Assembler (masswerk.at):**
    *   Go to: https://www.masswerk.at/6502/assembler.html
    *   Enter your 6502 assembly code in the "src" text box.
    *   Click the "generate code" button.
    *   Copy the generated object code (hexadecimal representation).
    *   Use a hex editor (e.g., Bless) to create a new file and paste the object code into it.
    *   Save the file (e.g., `myprogram.bin`).

2.  **Online Assembler (skilldrick.github.io):**
    *   Go to: https://skilldrick.github.io/easy6502/
    *   Write your 6502 assembly code.
    *   Click the "Assemble" button.
    *   If the code assembles successfully, you'll see a message like "Code assembled successfully, * bytes."
    *   Click the "Hexdump" button.
    *   Copy the hexadecimal output.
    *   Use a hex editor (e.g., Bless) to create a new file and paste the object code into it.
    *   Save the file (e.g., `myprogram.bin`).

3.  **Local Assembler:**
    *   Download a 6502 assembler from a resource like: http://www.6502.org/tools/asm/
    *   Follow the assembler's instructions to assemble your code into a binary file.

**Running Your Program:**

Once you have your program as a binary file (e.g., `myprogram.bin`), you can run it with the emulator:

```bash
./6502 /path/to/bin/myprogram.bin 200 2000
```

> **200** is the starting address in memory where the emulator should load your program. Replace this with the appropriate address for your program.
> **2000** is the starting address (program counter - PC) where the emulator should begin executing your code. Replace this with the appropriate address for your program.

**Command-Line Options:**

For more information on available commands and options, use the --help flag:

```bash
./6502 --help
```
