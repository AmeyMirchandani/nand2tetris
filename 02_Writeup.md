# Project 02 Writeup

## Chips
---
### Half-Adder
>Each of the 2 inputs each go into the inputs of an XOR gate and an AND gate, the XOR gate outputs to the sum bit, and the AND gate outputs to the carry bit.\
`Xor(a=a, b=b, out=sum);`\
`And(a=a, b=b, out=carry);`

The XOR gate mirrors how you do bitwise addition for the sum, and the AND gate mirrors it for the carry.

### Full-Adder
>2 inputs go into the inputs of a HalfAdder gate, the output sum of which is used as the input of another HalfAdder gate along with the final input of the FullAdder as the other input. The sum of the second HalfAdder gate is sent to the sum output of the FullAdder, while the carry output is sent to an OR gate, where it is compared to the first HalfAdder gate's carry output, the output of this gate is used as the carry output for the FullAdder gate.\
`HalfAdder(a=a, b=b, sum=midsum, carry=midcarry);`\
`HalfAdder(a=midsum, b=c, sum=sum, carry=finalcarry);`\
`Or(a=midcarry, b=finalcarry, out=carry);`

What's important to realize here is that when you add 2 bits, you can take the sum and then add it to another bit. This result is the final sum no matter what. At the point, the carry that you originally recorded when adding the first 2 bits will either be 0 or 1. If it is 0, then the second carry can either be 0 or 1, if it is 1, the second carry will be 0. Because of this, it cannot break anything, and can be used as the final carry.

### Add16
>Starting with a HalfAdder, the first 2 bits of each 16 bit bus are inputted and the sum is sent to the first bit of the outpus bus, while the carry is used for the next FullAdder chip along with the next 2 bits from the input busses. The sum is sent to the next bit of the output bus, and the carry is used as the third input for the next FullAdder bus. This continues for all bits of the 16 bit input bus.\
`HalfAdder(a=a[0], b=b[0], sum=out[0], carry=c1);`\
`FullAdder(a=a[1], b=b[1], c=c1, sum=out[1], carry=c2);`\
`FullAdder(a=a[2], b=b[2], c=c2, sum=out[2], carry=c3);`\
`FullAdder(a=a[3], b=b[3], c=c3, sum=out[3], carry=c4);`\
`FullAdder(a=a[4], b=b[4], c=c4, sum=out[4], carry=c5);`\
`FullAdder(a=a[5], b=b[5], c=c5, sum=out[5], carry=c6);`\
`FullAdder(a=a[6], b=b[6], c=c6, sum=out[6], carry=c7);`\
`FullAdder(a=a[7], b=b[7], c=c7, sum=out[7], carry=c8);`\
`FullAdder(a=a[8], b=b[8], c=c8, sum=out[8], carry=c9);`\
`FullAdder(a=a[9], b=b[9], c=c9, sum=out[9], carry=c10);`\
`FullAdder(a=a[10], b=b[10], c=c10, sum=out[10], carry=c11);`\
`FullAdder(a=a[11], b=b[11], c=c11, sum=out[11], carry=c12);`\
`FullAdder(a=a[12], b=b[12], c=c12, sum=out[12], carry=c13);`\
`FullAdder(a=a[13], b=b[13], c=c13, sum=out[13], carry=c14);`\
`FullAdder(a=a[14], b=b[14], c=c14, sum=out[14], carry=c15);`\
`FullAdder(a=a[15], b=b[15], c=c15, sum=out[15], carry=c16);`

This wasn't too bad, as long as I made sure not to miss the fact that the initial input had 2 actual bits and not 3, and so used a HalfAdder instead of a FullAdder, it works. This is basically the same as if you were doing bitwise addition on a piece of paper, just this time in a HDL.

### Inc16 (Increment 16 bit)
>The input of the Inc16 gate goes into the first pin of an Add16 chip, the second input is the 16 bit bus containing a 1 in the least significant bit, and 0s eleswhere.\
`Add16(a=in, b[0]=true, out=out);`

This one took some review of the actual rules for the HDL defined in the book, but once I realized that you can directly set bits in a bus to true(1) or false(0), and that the other unspecified bits are automatically set to 0 by default, I can directly pass the input that I wanted (1 in binary) to be added to the input.

### ALU
>x is conditionally zeroed by passing a zeroed version and the non-zeroed version through a Mux16 gate, and allowing "zx" to choose between them. x is then inverted by passing the "notted" version and the unchanged version (after it's been through the zeroing process) into a Mux16 gate and allowing "nx" to choose between them. The same logic is followed for the other input, y, as well as for negating the output with "no". Adding or ANDing is done by using a Mux16 gate and allowing "f" to choose between an ANDed version of x and y, or x + y. The final number is checked to see if it is zero by splitting it in 2 8 bit busses and passing each half to an Or8Way, getting 2 outputs, then ORring them together. The negative is checked by retrieving the highest order bit from the output, and seeing if it's 1, if it is, then the number is negative.\
`And16(a=x, b[0..15]=false, out=zerx);`\
`Mux16(a=x, b=zerx, sel=zx, out=x1); //x1`\
`//nx`\
`Not16(in=x1, out=notx);`\
`Mux16(a=x1, b=notx, sel=nx, out=x2); //x2 <--`\
`//zy`\
`And16(a=y, b[0..15]=false, out=zery);`\
`Mux16(a=y, b=zery, sel=zy, out=y1); //y1`\
`//ny`\
`Not16(in=y1, out=noty);`\
`Mux16(a=y1, b=noty, sel=ny, out=y2); //y2 <--`\
`//f`\
`And16(a=x2, b=y2, out=andxy);`\
`Add16(a=x2, b=y2, out=addxy);`\
`Mux16(a=andxy, b=addxy, sel=f, out=compxy); //compxy <--`\
`//no`\
`Not16(in=compxy, out=nego); //nego`\
`Mux16(a=compxy, b=nego, sel=no, out=out, out[0..7]=olow, out[8..15]=ohigh, out[15]=osign); //olow, ohigh, osign <--`\
`//zr`\
`Or8Way(in=olow, out=leftzr); //leftzr`\
`Or8Way(in=ohigh, out=rightzr); //rightzr`\
`Or(a=leftzr, b=rightzr, out=nonnegzr);`\
`Not(in=nonnegzr, out=zr); //zr <--`\
`//ng`\
`And(a=osign, b=true, out=ng);//ng <--`

This one was also fairly tough initially to think about, but once I figured that you can just pass the two versions of the output you want to choose between to a Mux16 gate, and allow the choice flag to choose through that, then use the output of that as the modified number, it was fairly simple to go through the rest. Learning how to properly format outpus busses was important for this, as doing something like: out[bus_size]=output_pin_name was extremely useful in shaving down output bus sizes to fit certain gates; for example, Or8Way would not be useable if I didn't use the previously mentioned feature of the HDL to split the bus bits into 2 busses with 8 bits each.