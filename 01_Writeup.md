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