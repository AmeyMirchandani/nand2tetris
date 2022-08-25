# Project 07 Writeup

## VM Translator
---
### Stack Arithmetic Commands
This one wasn't too bad as long as I completely understood what the assembly commands I was writing did. Properly understanding one level of indirection in registers can be tough sometimes, but once I realied that something like "@R5" would literally put the number 5 in the A register, and that I needed to follow that address to get the actual contents of the A register (in the case of something like a stack pointer, this would be another address -- this time in the heap), it became a lot easier to understand.

The implementation details relating opening files 

### Memory Access Commands
This implementation primarily depended on the symbol table being set up correctly (In this case, the LinkedList implementation had to work). The rest was just processing the input and figuring out what kind of instruction it was, as well as outputting the corresponding binary code.\
\
The new changes were as follows:\
``-Add all predefined labels to the symbol table.``\
``-Add a "First Pass" section that went through the code and assigned () labels (line starts with "(" ) to map to the address in ROM (instruction memory) of the following instruction.``\
``-The Second Pass was modified to recognize non integer symbols (for A instructions) and resolve them to their numeric addresses.``\
``-It was also modified to recognize user defined variables (not in symbol table). These are given a place in the symbol table starting at address 16 and moving up by one for every new variable (end of the majority of predefined lables -- the other 2 are defined at 16384[screen] and 24576[keyboard]) These can later be looked up and the address returned for output.``