# Project 04 Writeup

## Assembly Operations
---
### Multiplication
>'i" is given the value of the second operand. "sum" is given the value of 0. For every iteration of the loop, the first operand is added to sum and then i is decremented. Once i is equal to 0, leave the loop.\
`@R1 //D = R1`\
`D=M`\
`@i //i = R1 <--`\
`M=D`
`@sum //sum = 0 <--`\
`M=0`\
`(LOOP)`\
`@i //D = i`\
`D=M`\
`@PREEND //if i == 0, jump to PREEND`\
`D;JEQ`\
`@R0 //D = R0`\
`D=M`\
`@sum //sum = sum + R0`\
`M=M+D`\
`@i //i = i - 1`\
`M=M-1`\
`@LOOP //go back to LOOP`\
`0;JMP`\
`(PREEND)`\
`@sum //D = sum`\
`D=M`\
`@R2 //R2 = sum`\
`M=D`\
`(END)`\
`@END`\
`0;JMP`

This took a short while to actually get used to the fact that I cannot directly reference a memory address AND a commputation step in a single instruction: I have to load it into the A register first with @var_name, and then access the memory location with "M". Also had to make sure that I had a @END with a 0;JMP at the end to keep an infinite loop (standard way to terminate Hack programs).

### Fill Screen
>The screen address is saved in currpos, count is set by default to 8192 (the amount of 16 bit words in the screen). If keyboard is being pressed, then go to the (BLACKEN) label, otherwise go to (WHITEN). Both do similar things: if count is 0, then start the main loop again, otherwise: load D with 65535(16 1s in binary, for all the bits), set A to be the value held by currpos in memory. Then dereference this address and set it to either -1 (blacken) or 0 (whiten). Then decrement count and increment currpos. Then go back to the start of either the WHITEN or BLACKEN loop.\
`(END) //Infinite loop`\
`@8192`\
`D=A //D = 8192`\
`@count //count = 8192`\
`M=D`\
`@SCREEN //D = SCREEN address`\
`D=A`\
`@currpos //currpos = SCREEN address`\
`M=D`\
`@KBD //D=KEYBOARD`\
`D=M`\
`@BLACKEN //if KEYBOARD > 0, jump to BLACKEN`\
`D;JGT`\
`@WHITEN //else, jump to WHITEN`\
`0;JMP`\
`(BLACKEN)`\
`@count //D = count`\
`D=M`\
`@END //if count == 0, end loop and go to END`\
`D;JEQ`\
`@currpos`\
`A=M`\
`M=-1 //dereference currpos's held address and set all 16 of it's pixels to black`\
`@count //count = count - 1`\
`M=M-1`\
`@currpos //currpos = currpos + 1`\
`M=M+1`\
`@BLACKEN //BLACKEN`\
`0;JMP`\
`//-------------`\
`(WHITEN)`\
`@count //D = count`\
`D=M`\
`@END //if count == 0, end loop and go to END`\
`D;JEQ`\
`@0`\
`D=A`\
`@currpos`\
`A=M`\
`M=D //dereference currpos's held address and set all 16` `of it's pixels to white`\
`@count //count = count - 1`\
`M=M-1`\
`@currpos //currpos = currpos + 1`\
`M=M+1`\
`@WHITEN //WHITEN`\
`0;JMP`

The main thing I had to realize was that the words were all 16 bit, and I also had the screen dimensions. This allowed me to multiply the dimentions to get the pixel count for the screen, then divide by 16 to see how many 16 bit words I need to fill. That gave me the amount of times I would have to whiten or blacken 16 bits each time I jumped to (WHITEN) or (BLACKEN). From here the rest was fairly straightforward, with the main issue arising from the fact that when I stored an actual number representing a memory address, I had to actually move it from its word to the A register, so I could then use M to follow it to its own word.