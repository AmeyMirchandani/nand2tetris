# Project 02 Writeup

## Gate
---
### Bit (1 bit register)
>The DFF gate is built in, so we can use it. The DFF's input is fed from a MUX gate that chooses whether or not to pass on the Bit gate input or the previous output of the DFF gate (based on the load bit). DFF gate output goes to Bit gate output.\
`Mux(a=dffout, b=in, sel=load, out=muxout);`\
`DFF(in=muxout, out=dffout, out=out);`

Textbook had the specification for this, but it's important to get that the load bit is the one that chooses what that MUX gate lets in, and in this way, allows the register to keep an actual storage. If you don't load anything it would keep outputting the input from the previous clock cycle (which in this case would be the previous output), leading to a repeat of the exact same value over and over again, creating "storage".

### Register (16 bit register)
>Each bit in the input bus is sent to a separate Bit gate's input, with each gate's load bit being set to the load input. Each Bit gate outputs to a separate bit in the output bus.\
`Bit(in=in[0], load=load, out=out[0]);`\
`Bit(in=in[1], load=load, out=out[1]);`\
`Bit(in=in[2], load=load, out=out[2]);`\
`Bit(in=in[3], load=load, out=out[3]);`\
`Bit(in=in[4], load=load, out=out[4]);`\
`Bit(in=in[5], load=load, out=out[5]);`\
`Bit(in=in[6], load=load, out=out[6]);`\
`Bit(in=in[7], load=load, out=out[7]);`\
`Bit(in=in[8], load=load, out=out[8]);`\
`Bit(in=in[9], load=load, out=out[9]);`\
`Bit(in=in[10], load=load, out=out[10]);`\
`Bit(in=in[11], load=load, out=out[11]);`\
`Bit(in=in[12], load=load, out=out[12]);`\
`Bit(in=in[13], load=load, out=out[13]);`\
`Bit(in=in[14], load=load, out=out[14]);`\
`Bit(in=in[15], load=load, out=out[15]);`

This is just creating a 16 bit version of the previous 1 bit register by essentially creating an array with 16 spots, each containing a 1 bit register. Since they share a load bit, they all load or don't load their individual bit at the same time, essentially letting you work with 16 bit data.

### RAM8 (8 register memory)
>DMux8Way gate takes load as the bit to pass on, and address as the selection bit. The outputs are used to decide which register will be loaded. Each register takes the RAM8 input as input and uses the DMux8Way given load bit. All of their outputs are sent to a Mux8Way16 which uses a selection bit set to address to decide which register output to pass on to the RAM8 output.\
`DMux8Way(in=load, sel=address, a=l1, b=l2, c=l3, d=l4, e=l5, f=l6, g=l7, h=l8); //load bit for registers`\
`Register(in=in[0..15], load=l1, out=o1);`\
`Register(in=in[0..15], load=l2, out=o2);`\
`Register(in=in[0..15], load=l3, out=o3);`\
`Register(in=in[0..15], load=l4, out=o4);`\
`Register(in=in[0..15], load=l5, out=o5);`\
`Register(in=in[0..15], load=l6, out=o6);`\
`Register(in=in[0..15], load=l7, out=o7);`\
`Register(in=in[0..15], load=l8, out=o8);`\
`Mux8Way16(a=o1, b=o2, c=o3, d=o4, e=o5, f=o6, g=o7, h=o8, sel=address, out=out); //choose which register's value to output`

The DMux8Way takes care of sending the correct load bit to the correct register (only one is allowed to have a load bit of 1 - they can all be 0 though). At the other end, the Mux8Way16 makes sure there is a combinational way to return the output of the registers (in the case where load is 0, you will still get the value of the register at the given address instantaneously).

### RAM64 (64 register memory)
>DMux8Way gate takes load as the bit to pass on, and the 3 lower order bits of the address as the selection bit. The outputs are used to decide which register will be loaded. Each register takes the RAM64 input as input and uses the DMux8Way given load bit. The address bit of the RAM8 gates are set to the last 3 bits of the address. All of their outputs are sent to a Mux8Way16 which uses a selection bit set to the 3 lower order bits of the address to decide which register output to pass on to the RAM64 output.\
`DMux8Way(in=load, sel=address[0..2], a=l1, b=l2, c=l3, d=l4, e=l5, f=l6, g=l7, h=l8); //load bit for registers`\
`RAM8(in=in, load=l1, address=address[3..5], out=o1);`\
`RAM8(in=in, load=l2, address=address[3..5], out=o2);`\
`RAM8(in=in, load=l3, address=address[3..5], out=o3);`\
`RAM8(in=in, load=l4, address=address[3..5], out=o4);`\
`RAM8(in=in, load=l5, address=address[3..5], out=o5);`\
`RAM8(in=in, load=l6, address=address[3..5], out=o6);`\
`RAM8(in=in, load=l7, address=address[3..5], out=o7);`\
`RAM8(in=in, load=l8, address=address[3..5], out=o8);`\
`Mux8Way16(a=o1, b=o2, c=o3, d=o4, e=o5, f=o6, g=o7, h=o8, sel=address[0..2], out=out); //choose which register's value to output`

Very similar to the RAM8 gate implementation, but in the case, you use 8 RAM8 gates instead of 8 single registers. The address is also segmented to have the 3 lower order bits be able to index to the 8 RAM8 registers, and the last 3 bits being used to get the single specific register within each of the RAM8 gates's 8 registers.

### RAM512 (512 register memory)
>DMux8Way gate takes load as the bit to pass on, and the 3 lower order bits of the address as the selection bit. The outputs are used to decide which register will be loaded. Each register takes the RAM512 input as input and uses the DMux8Way given load bit. The address bit of the RAM64 gates are set to the last 6 bits of the address. All of their outputs are sent to a Mux8Way16 which uses a selection bit set to the 3 lower order bits of the address to decide which register output to pass on to the RAM512 output.\
`DMux8Way(in=load, sel=address[0..2], a=l1, b=l2, c=l3, d=l4, e=l5, f=l6, g=l7, h=l8); //load bit for registers`\
`RAM64(in=in, load=l1, address=address[3..8], out=o1);`\
`RAM64(in=in, load=l2, address=address[3..8], out=o2);`\
`RAM64(in=in, load=l3, address=address[3..8], out=o3);`\
`RAM64(in=in, load=l4, address=address[3..8], out=o4);`\
`RAM64(in=in, load=l5, address=address[3..8], out=o5);`\
`RAM64(in=in, load=l6, address=address[3..8], out=o6);`\
`RAM64(in=in, load=l7, address=address[3..8], out=o7);`\
`RAM64(in=in, load=l8, address=address[3..8], out=o8);`\
`Mux8Way16(a=o1, b=o2, c=o3, d=o4, e=o5, f=o6, g=o7, h=o8, sel=address[0..2], out=out); //choose which register's value to output`

Again, exactly the same as the RAM64 implementation, except for the fact that you use the last **6** bits of the address as the input for the sub-registers, instead of the last 3 bits.

### RAM4K (4096 register memory)
>DMux8Way gate takes load as the bit to pass on, and the 3 lower order bits of the address as the selection bit. The outputs are used to decide which register will be loaded. Each register takes the RAM4K input as input and uses the DMux8Way given load bit. The address bit of the RAM512 gates are set to the last 9 bits of the address. All of their outputs are sent to a Mux8Way16 which uses a selection bit set to the 3 lower order bits of the address to decide which register output to pass on to the RAM4K output.\
`DMux8Way(in=load, sel=address[0..2], a=l1, b=l2, c=l3, d=l4, e=l5, f=l6, g=l7, h=l8); //load bit for registers`\
`RAM512(in=in, load=l1, address=address[3..11], out=o1);`\
`RAM512(in=in, load=l2, address=address[3..11], out=o2);`\
`RAM512(in=in, load=l3, address=address[3..11], out=o3);`\
`RAM512(in=in, load=l4, address=address[3..11], out=o4);`\
`RAM512(in=in, load=l5, address=address[3..11], out=o5);`\
`RAM512(in=in, load=l6, address=address[3..11], out=o6);`\
`RAM512(in=in, load=l7, address=address[3..11], out=o7);`\
`RAM512(in=in, load=l8, address=address[3..11], out=o8);`\
`Mux8Way16(a=o1, b=o2, c=o3, d=o4, e=o5, f=o6, g=o7, h=o8, sel=address[0..2], out=out); //choose which register's value to output`

Again, exactly the same as the RAM512 implementation, except for the fact that you use the last **9** bits of the address as the input for the sub-registers, instead of the last 6 bits.

### RAM16K (16384 register memory)
>DMux4Way gate takes load as the bit to pass on, and the 2 lower order bits of the address as the selection bit. The outputs are used to decide which register will be loaded. Each register takes the RAM16K input as input and uses the DMux8Way given load bit. The address bit of the RAM4K gates are set to the last 12 bits of the address. All of their outputs are sent to a Mux8Way16 which uses a selection bit set to the 2 lower order bits of the address to decide which register output to pass on to the RAM16K output.\
`DMux4Way(in=load, sel=address[0..1], a=l1, b=l2, c=l3, d=l4); //load bit for registers`\
`RAM4K(in=in, load=l1, address=address[2..13], out=o1);`\
`RAM4K(in=in, load=l2, address=address[2..13], out=o2);`\
`RAM4K(in=in, load=l3, address=address[2..13], out=o3);`\
`RAM4K(in=in, load=l4, address=address[2..13], out=o4);`\
`Mux4Way16(a=o1, b=o2, c=o3, d=o4, sel=address[0..1], out=out); //choose which register's value to output`

Slightly different than the RAM4K chip, as you now only need 4 sub-register gates, and you only need 2 lower order bits to index them. The rest is the same, except the remaining bits after the initial 2 go up to **12** bits instead of 9.

### PC (16 bit program counter)
>The output of a Register(16 bit) is sent to both the PC chip output and the input of a MUX16 gate. This gate chooses between incrementing the output, then takes the chosen one and passes it to another MUX16 which decides whether or not to load new input, then passes it to a final MUX16 that chooses whether or not to reset the input to 0. This is sent in as the input of the 16 bit Register mentioned before.\
`//Or(a=reset, b=load, out=resetorload);`\
`//Or(a=resetorload, b=inc, out=changedin); //register load bit <-- ignore this line and above`\
`Inc16(in=feedback, out=incin); //incremented input`\
`Mux16(a=feedback, b=incin, sel=inc, out=incmux); //increment mux (feedback used to be [in] when above logic existed)`\
`Mux16(a=incmux, b=in, sel=load, out=loadmux); //load mux`\
`Mux16(a=loadmux, b=false, sel=reset, out=finalo); //reset mux`\
`Register(in=finalo, load=true, out=out, out=feedback);`

Where I got confused here is if I actually needed to have the load bit of the register be different in different cases, but then I realized that the way I had built the logic had the chain of 3 MUX16 gates already choosing for me, even the option of not doing any different and using the same output as the previous clock cycle was handled.