# Project 01 Writeup

## Gates
---
### NOT
>input of NOT goes to both inputs of Nand gate, output of Nand gate straight to output of NOT.\
`Nand(a=in, b=in, out=out);`

### And
>input of And goes to both the inputs of a Nand gate, then output of that Nand gate goes to a NOT gate, output of that NOT goes to output of And.\
`Nand(a=a, b=b, out=c);`\
`Not(in=c, out=out);`

Once I figured out that this was just the opposite of a Nand gate, it was fairly simple to solve.

### Or
>input of OR gate goes to 2 NOT gates, each of their outputs go to the 2 inputs of a Nand gate, the Nand gate's output goes to the output of OR.\
`Not(in=a, out=nota);`\
`Not(in=b, out=notb);`\
`Nand(a=nota, b=notb, out=out);`

This was similar to And, in that you negate the inputs *before* they go into the inputs of the Nand gate.

### Xor
>Both inputs of Xor gate each go to and AND gate and an OR gate. The output of the OR gate is sent through a NOT gate and then piped into a final OR gate, the AND gate's output from before is sent here without changes. The output of this OR gate is sent through another NOT gate and then sent to the output of the Xor gate.\
`And(a=a, b=b, out=and); //one side of OR`\
`Or(a=a, b=b, out=or); //opposite of what we want`\
`Not(in=or, out=notor); //second side of OR`\
`Or(a=and, b=notor, out=finalOr);`\
`Not(in=finalOr, out=out);`

I took this one in steps, using the AND gate to return true for all 1,1 inputs, and the OR gate, combined with a NOT to return true for all 0,0 inputs. If I send both outputs through an OR gate and it returned true, then the set of inputs was either 1,1 or 0,0. I needed it to be the opposite, (true when it was either 0,1 or 1,0), so I sent it through another NOT gate.

### Mux
>The selector input is inverted with a NOT gate. Both inputs are sent to separate AND gates, where the second input for one AND gate is the selector input and the second input for the other is the inverted selector input. Both outputs for the AND gates feed into an OR gate, the output of which goes to the output of the MUX gate.\
`Not(in=sel, out=notsel);`\
`And(a=sel, b=b, out=band);`\
`And(a=notsel, b=a, out=aand);`\
`Or(a=band, b=aand, out=out);`

Had to check online for this one, I thought that it was likely that you had to somehow compare each MUX input with the selector input, but wasn't sure how. I knew that if you AND a value with 1, you get that value, so if I used b for that value, I could pass it on, whereas if I did the opposite for a, using 0 as one of the inputs, it would automatically output 0. Using this logic, I would need to invert the selector to provide the ability to pass its value, and its opposite each to separate gates. b was put in the AND gate recieving the selector value, as if it was 1, I wanted to pass on b, and negate a by returning 0. I would then later need to compare the values using OR, as one of then would definitely be 0 (from the gate getting the 0 selector input), and pass on the value of the selected pin.

### DMux
>The selector input is inverted with a NOT gate. Two AND gates are set up, both of which take the input as one argument; One of them takes the selector input and the other takes the negation, the one that takes the negation has an output to "a" and the non-negated one goes to the "b" output for DMux.\
`Not(in=sel, out=notsel);`\
`And(a=sel, b=in, out=b); //b output gate`\
`And(a=notsel, b=in, out=a); //a output gate`

After having done the Mux gate, this one was a bit easier, as I better knew how to structure the logic for using AND gates to pass along values that I want and filter out those that I don't. I just needed to be able to change my "filter" variable (sel), which in this case I inverted, to be able to plug both 0 and 1 into two AND gates, both taking the input for Dmux, which resulted in giving me the value of the variable with 1 for sel plugged in, and 0 for the one with 0 for sel plugged in. I could just then pass them on directly.

### Not16
>16 NOT gates each take a bit from the input bus and output it to a bit in the output bus.\
`Not(in=in[0], out=out[0]);`\
`Not(in=in[1], out=out[1]);`\
`Not(in=in[2], out=out[2]);`\
`Not(in=in[3], out=out[3]);`\
`Not(in=in[4], out=out[4]);`\
`Not(in=in[5], out=out[5]);`\
`Not(in=in[6], out=out[6]);`\
`Not(in=in[7], out=out[7]);`\
`Not(in=in[8], out=out[8]);`\
`Not(in=in[9], out=out[9]);`\
`Not(in=in[10], out=out[10]);`\
`Not(in=in[11], out=out[11]);`\
`Not(in=in[12], out=out[12]);`\
`Not(in=in[13], out=out[13]);`\
`Not(in=in[14], out=out[14]);`\
`Not(in=in[15], out=out[15]);`

Fairly simple for this one, just apply the NOT gate for each bit in the 16 bit bus.

### And16
>16 AND gates each take a bit from each of the input buses and output it to a bit in the output bus.\
`And(a=a[0], b=b[0], out=out[0]);`\
`And(a=a[1], b=b[1], out=out[1]);`\
`And(a=a[2], b=b[2], out=out[2]);`\
`And(a=a[3], b=b[3], out=out[3]);`\
`And(a=a[4], b=b[4], out=out[4]);`\
`And(a=a[5], b=b[5], out=out[5]);`\
`And(a=a[6], b=b[6], out=out[6]);`\
`And(a=a[7], b=b[7], out=out[7]);`\
`And(a=a[8], b=b[8], out=out[8]);`\
`And(a=a[9], b=b[9], out=out[9]);`\
`And(a=a[10], b=b[10], out=out[10]);`\
`And(a=a[11], b=b[11], out=out[11]);`\
`And(a=a[12], b=b[12], out=out[12]);`\
`And(a=a[13], b=b[13], out=out[13]);`\
`And(a=a[14], b=b[14], out=out[14]);`\
`And(a=a[15], b=b[15], out=out[15]);`

Simple for this too, same as Not16, but with AND gates.

### Or16
>16 OR gates each take a bit from each of the input buses and output it to a bit in the output bus.\
`Or(a=a[0], b=b[0], out=out[0]);`\
`Or(a=a[1], b=b[1], out=out[1]);`\
`Or(a=a[2], b=b[2], out=out[2]);`\
`Or(a=a[3], b=b[3], out=out[3]);`\
`Or(a=a[4], b=b[4], out=out[4]);`\
`Or(a=a[5], b=b[5], out=out[5]);`\
`Or(a=a[6], b=b[6], out=out[6]);`\
`Or(a=a[7], b=b[7], out=out[7]);`\
`Or(a=a[8], b=b[8], out=out[8]);`\
`Or(a=a[9], b=b[9], out=out[9]);`\
`Or(a=a[10], b=b[10], out=out[10]);`\
`Or(a=a[11], b=b[11], out=out[11]);`\
`Or(a=a[12], b=b[12], out=out[12]);`\
`Or(a=a[13], b=b[13], out=out[13]);`\
`Or(a=a[14], b=b[14], out=out[14]);`\
`Or(a=a[15], b=b[15], out=out[15]);`

Exact same as And16, but with OR gates instead.

### Mux16
>16 Mux gates each take a bit from each of the input buses, use the selector input pin value as each of their selector pin values and output it to a bit in the output bus.\
`Mux(a=a[0], b=b[0], sel=sel, out=out[0]);`\
`Mux(a=a[1], b=b[1], sel=sel, out=out[1]);`\
`Mux(a=a[2], b=b[2], sel=sel, out=out[2]);`\
`Mux(a=a[3], b=b[3], sel=sel, out=out[3]);`\
`Mux(a=a[4], b=b[4], sel=sel, out=out[4]);`\
`Mux(a=a[5], b=b[5], sel=sel, out=out[5]);`\
`Mux(a=a[6], b=b[6], sel=sel, out=out[6]);`\
`Mux(a=a[7], b=b[7], sel=sel, out=out[7]);`\
`Mux(a=a[8], b=b[8], sel=sel, out=out[8]);`\
`Mux(a=a[9], b=b[9], sel=sel, out=out[9]);`\
`Mux(a=a[10], b=b[10], sel=sel, out=out[10]);`\
`Mux(a=a[11], b=b[11], sel=sel, out=out[11]);`\
`Mux(a=a[12], b=b[12], sel=sel, out=out[12]);`\
`Mux(a=a[13], b=b[13], sel=sel, out=out[13]);`\
`Mux(a=a[14], b=b[14], sel=sel, out=out[14]);`\
`Mux(a=a[15], b=b[15], sel=sel, out=out[15]);`

This was just a variation of the 16 bit bus problems done before.

### Or8Way
>The first OR gate takes the first and second bit from the input bus and sends the output to another OR gate that takes the third input from the input bus, etc... till you process the eighth input from the input bus, and then send the result to the output of the Or8Way gate.\
`Or(a=in[0], b=in[1], out=r1);`\
`Or(a=r1, b=in[2], out=r2);`\
`Or(a=r2, b=in[3], out=r3);`\
`Or(a=r3, b=in[4], out=r4);`\
`Or(a=r4, b=in[5], out=r5);`\
`Or(a=r5, b=in[6], out=r6);`\
`Or(a=r6, b=in[7], out=out);`

This was just a matter of chaining OR gates together. Not too bad because if you hit a 1, it carried over till the end.