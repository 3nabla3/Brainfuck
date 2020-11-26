# Brainfuck
Basic brainfuck interpreter written in C

# Usage
Interpreter does not check for errors such as matching brackets before running!
Set `_DEBUG` to `1` in `brainfuck.h` to have a debug output of the running program

$ bin/brainfuck [filename]

# Compile
Source code is in the `src` folder
Intermediate binary is in the `bin-int` folder
Ouput binary is in the `bin` folder

$ make