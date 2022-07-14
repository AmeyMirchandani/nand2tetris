# Project 06 Writeup

## Assembler
---
### No Symbol Version
On this one, it took me a bit to figure out how to properly use fgets; once I actually did figure it out, it became much easier to read from the input ".asm" file.\
 >Some notes:\
 -strtok: if " " space delimiter is chosen as part of delimiters, it will not automatically remove it from the front of strings, it does however remove them from the end of strings, replacing any amount with the NUL character "\0". The man page is either weirdly worded or flat out wrong as it says it removes the delimiters at the front of the string. (Still have to test with non space delimiters).\
 -Because of the above problem, it was necessary to write a function that when passed a string, returns a char pointer pointing to the first non space character (skips the spaces before the string like strtok is supposed to).\
 -The symbol table was represented with a LinkedList structure, as it made adding nodes easy (just add to front of list in constant time).\

 For the second pass (implemented first in the no symbol version), the steps were as follows:\
 ``-Read in a line from the input .asm file.``\
 ``-If the line is a comment, () label, or newline character skip it, otherwise remove the newline at the end of the line, if there is one.``\
``-Determine if the line represents a C or A instruction.``\
``-For C instructions, process the instruction by passing each field to a method that determines the output binary code based on the input.``\
``-For an A instruction, assume the value is an integer and output the binary form of that integer.``

### Symbol Version
This implementation primarily depended on the symbol table being set up correctly (In this case, the LinkedList implementation had to work). The rest was just processing the input and figuring out what kind of instruction it was, as well as outputting the corresponding binary code.\
\
The new changes were as follows:\
``-Add all predefined labels to the symbol table.``\
``-Add a "First Pass" section that went through the code and assigned () labels (line starts with "(" ) to map to the address in ROM (instruction memory) of the following instruction.``\
``-The Second Pass was modified to recognize non integer symbols (for A instructions) and resolve them to their numeric addresses.``\
``-It was also modified to recognize user defined variables (not in symbol table). These are given a place in the symbol table starting at address 16 and moving up by one for every new variable (end of the majority of predefined lables -- the other 2 are defined at 16384[screen] and 24576[keyboard]) These can later be looked up and the address returned for output.``