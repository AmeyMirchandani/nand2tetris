# Project 05 Writeup

## Chips
---
### Memory
>A DMux4Way chooses where to send the load bit based on the last 2 bits of the Memory input address. It is either sent to RAM16K, Screen, or Keyboard. All 3 of these chips take the input as input, the DMux4Way load output as their load input, and RAM16K takes the first 14 bits of input address as its address, and Screen takes the first 13. The outputs of these 3 chips are sent to a Mux4Way16 and the last 2 bits of memory's input address are again used to choose which one to send on to Memory's output.\
`DMux4Way(in=load, sel=address[13..14], a=ramload1, b=ramload2, c=screenload, d=throwaway); //load DMux`\
`Or(a=ramload1, b=ramload2, out=ramload); //combine both ram loads (on 00 or 01)`\
`RAM16K(in=in, load=ramload, address=address[0..13], out=ramout); //RAM16K`\
`Screen(in=in, load=screenload, address=address[0..12], out=screenout); //Screen Memory Map`\
`Keyboard(out=kbdout); //Keyboard Memory Map`\
`Mux4Way16(a=ramout, b=ramout, c=screenout, d=kbdout, sel=address[13..14], out=out); //choose output DMux`

This one was rough, as it took me a little while to realize that when you get the first 14 bits to 1, in addition to being the max that RAM16K can address to, if you go one more bit, you hit the 0th bit of Screen (as you only take the first 13 bits, and the one that is carried is being pushed over to the 15th bit). This cannot overflow, as Screen will max at 13 1 bits on the first 13 bits. After this, you end up with 2 1s in the last 2 bits (14 and 15th bit). This is the max you can go AND the address for Keyboard.

### CPU
>A register is sent input through a Mux16, which chooses between the instruction input and the ALU output. The ALU output is chosen as A's input if the executing instruction was a C instruction AND the destination includes the A register. The output for the A register is then sent through another Mux16, which decides whether or not to take A or M and pass it along to be one of the inputs for the ALU. This is based on the "a" bit in the instruction. The ALU's other input is the D register's output, which takes the ALU output as input, and loads it if the executing instruction was a C instruction AND the destination includes the D register. The ALU takes the various control bits derived from the instruction bits and sends out the usual ZR (output was 0) and NG (output was negative) status bits. The PC takes the A register's output as input, and loads it if executing instruction was a C instruction AND the jump bits are set AND the output would satisfy at least one jump bit that is set to 1. reset is connected to the PC reset, and when the PC does not load, it increments, when it loads, it does not increment. PC output goes to CPU output.\
`And(a=instruction[15], b=instruction[5], out=takeALUout); //if C instruction AND destination includes A register`\
`Mux16(a=instruction, b=ALUout, sel=takeALUout, out=Ainput);`\
`Not(in=instruction[15], out=Ains); //A instruction`\
`Or(a=takeALUout, b=Ains, out=loadA); //if C instruction AND destination includes A register |OR| A instruction`\
`ARegister(in=Ainput, load=loadA, out=Aout);`\
`And16(a=true, b=Aout, out[0..14]=addressM); //resize A register output to go in addresssM output for CPU chip`\
`Mux16(a=Aout, b=inM, sel=instruction[12], out=AMtoALU); //choose between A and M`\
`ALU(x=AMtoALU, y=DtoALU, zx=instruction[11], nx=instruction[10], zy=instruction[9], ny=instruction[8], f=instruction[7], no=instruction[6], out=outM, out=ALUout, zr=ZRout, ng=NGout);`\
`And(a=ZRout, b=instruction[1], out=jmpEQ); //output is == 0 AND jeq == true <--`\
`And(a=NGout, b=instruction[2], out=jmpLT); //output is < 0 AND jlt == true <--`\
`Or(a=jmpEQ, b=jmpLT, out=EQorLT); //output is either == 0 OR < 0`\
`Not(in=EQorLT, out=pos); //output is positive (not == 0 AND not < 0) (Demorgan's Rule)`\
`And(a=pos, b=instruction[0], out=jmpGT); //output is > 0 AND jgt == true <--`\
`Or(a=EQorLT, b=jmpGT, out=EQorLTorGT); //output is == 0 OR < 0 OR > 0`\
`And(a=instruction[15], b=EQorLTorGT, out=loadPC); //load PC if C instruction AND output is == 0 OR < 0 OR > 0, also the jump bits have to be set`\
`Not(in=loadPC, out=notLoad); //increment PC when not loading`\
`PC(in=Aout, load=loadPC, inc=notLoad, reset=reset, out[0..14]=pc);`\
`And(a=instruction[15], b=instruction[4], out=loadD); //if C instruction AND destination includes D register`\
`DRegister(in=ALUout, load=loadD, out=DtoALU);`\
`And(a=instruction[15], b=instruction[3], out=writeM); // <-- writeM`

This one was the toughest so far, the logic of thinking is gates is often counterintuitive and initially I misunderstood how the CPU was supposed to work in general. Once I figured out how it worked, there was some confusion with how clock cycles worked, and how there are often more than one chip that are "clocked" connected to each other, and how that might cause interaction with data more than one clock cycle prior. I do still need to do more research on this, but at this point I knew enough to complete the implementation with some help from the internet. I just had to be careful to make sure to constantly check whether or not the input instruction was a C or an A instruction.