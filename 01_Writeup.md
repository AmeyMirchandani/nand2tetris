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

### Mux4Way16
>The first 2 input busses are passed to a Mux16 gate, and on the rightmost bit of the selection number being 0, it returns the first bus, and on 1, it returns the second. This is also done for the third and fourth bus with a second Mux16 gate. The outputs of these 2 Mux16 gates are put into the input of a third Mux16, which evaluates the leftmost bit of the selection number, on it being 0, returns the first bus, and on a 1, returns the second bus.\
`Mux16(a=a, b=b, sel=sel[0], out=r1);`\
`Mux16(a=c, b=d, sel=sel[0], out=r2);`\
`Mux16(a=r1, b=r2, sel=sel[1], out=out);`

This was essentially just a composition of multiple Mux16 gates, we choose one bus that could be chosen for each gate on the rightmost selection bit being a 0, and one bus for it being a 1. Once you do this, both gates will either output a bus for selection bit 0 or both will output one for selection bit 1 (not different). Once you have the rightmost bit the same for both busses, you do the same for the leftmost bit, passing the remaining busses into a final Mux16 gate. This will get you the gate with the correct leftmost bit as well.

### Mux8Way16
>The first 4 input busses are passed to a Mux4Way16 gate, and depending on the rightmost 2 bits of the selection number, it picks one of the 4 busses and outputs it. This is done another time for the other 4 busses with another Mux4Way16 gate. The outputs of these 2 Mux4Way16 gates are put into the input of a Mux16 gate, which evaluates the leftmost bit of the selection number (third bit), on it being 0, returns the first bus, and on a 1, returns the second bus.\
`Mux4Way16(a=a, b=b, c=c, d=d, sel=sel[0..1], out=r1);`\
`Mux4Way16(a=e, b=f, c=g, d=h, sel=sel[0..1], out=r2);`\
`Mux16(a=r1, b=r2, sel=sel[2], out=out);`

This was very similar to the Mux4Way16 implementation, as I just used 2 4Way gates instead of the regular 2 way that Mux16 deal with. The Mux4Way16 let me deal with the right 2 digits of the selection number, and the last Mux16 let me deal with the last one on the left.

### DMux4Way
>Input is fed into a Dmux gate, with the selection pin being the first bit of sel (rightmost 0 or 1). The first output represents a and c (0 as rightmost bit), and the second represents b and d (1 as rightmost bit). Each output is then fed into another Dmux gate, which takes the second bit of sel (leftmost 0 or 1), the first gate chooses between a and c, the second between b and d.\
`DMux(in=in, sel=sel[0], a=r1, b=r2);`\
`DMux(in=r1, sel=sel[1], a=a, b=c);`\
`DMux(in=r2, sel=sel[1], a=b, b=d);`

This one took a bit, but once I figured out that I am just choosing like a Dmux gate, but in parts, it became easy to see that I could just choose first 0 or 1 for right bit, and then choose between 0 or 1 for left bit, the output for the right bit I don't choose will always be 0, so I don't have to worry about checking the left bit messing with anything.

### DMux8Way
>Input is fed into a Dmux4Way gate, with the selection pin being the first two bits of sel (rightmost 2 bits). The first output represents a and e (00 as rightmost bits), and the second represents b and f (01 as rightmost bits), the third is cg (10 as rightmost bits), and the fourth is dh (11 as rightmost bits). Each output is then fed into another Dmux gate, which takes the last bit of sel (leftmost 0 or 1), the first gate chooses between a and e, the second between b and f, the third between c and g, and the fourth between d and h.\
`DMux4Way(in=in, sel=sel[0..1], a=ae, b=bf, c=cg, d=dh);`\
`DMux(in=ae, sel=sel[2], a=a, b=e);`\
`DMux(in=bf, sel=sel[2], a=b, b=f);`\
`DMux(in=cg, sel=sel[2], a=c, b=g);`\
`DMux(in=dh, sel=sel[2], a=d, b=h);`

Similarly to the DMux4Way gate, we have to split the input into outputs that each represent 2 of the final outputs. Each of these 4 are then split into single outputs, connecting to the outputs of the DMux8Way gate. Almost the same as DMux4Way, where you have to split 2 outputs into 4 as opposed to 4 into 8 as we do here.