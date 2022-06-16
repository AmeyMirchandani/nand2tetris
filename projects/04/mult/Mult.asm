// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

// Put your code here.

@R1 //D = R1
D=M
@i //i = R1 <--
M=D

@sum //sum = 0 <--
M=0

(LOOP)
@i //D = i
D=M

@PREEND //if i == 0, jump to PREEND
D;JEQ

@R0 //D = R0
D=M

@sum //sum = sum + R0
M=M+D

@i //i = i - 1
M=M-1

@LOOP //go back to LOOP
0;JMP

(PREEND)
@sum //D = sum
D=M

@R2 //R2 = sum
M=D

(END)
@END
0;JMP