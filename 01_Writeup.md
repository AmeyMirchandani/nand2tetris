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