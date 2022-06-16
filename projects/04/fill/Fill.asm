// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.
(END) //Infinite loop
@8192
D=A //D = 8192
@count //count = 8192
M=D

@SCREEN //D = SCREEN address
D=A
@currpos //currpos = SCREEN address
M=D

@KBD //D=KEYBOARD
D=M
@BLACKEN //if KEYBOARD > 0, jump to BLACKEN
D;JGT
@WHITEN //else, jump to WHITEN
0;JMP

(BLACKEN)
@count //D = count
D=M
@END //if count == 0, end loop and go to END
D;JEQ

@currpos
A=M
M=-1 //dereference currpos's held address and set all 16 of it's pixels to black

@count //count = count - 1
M=M-1

@currpos //currpos = currpos + 1
M=M+1

@BLACKEN //BLACKEN
0;JMP
//-------------
(WHITEN)
@count //D = count
D=M
@END //if count == 0, end loop and go to END
D;JEQ

@0
D=A
@currpos
A=M
M=D //dereference currpos's held address and set all 16 of it's pixels to white

@count //count = count - 1
M=M-1

@currpos //currpos = currpos + 1
M=M+1

@WHITEN //WHITEN
0;JMP