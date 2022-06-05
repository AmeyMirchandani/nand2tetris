# Project 01 Writeup

## Gates
---
### NOT
>input of NOT goes to both inputs of Nand gate, output of Nand gate straight to output of NOT.\
`Nand(a=in, b=in, out=out);`

### And
>input of And goes to both the inputs of a Nand gate, then output of that Nand gate goes to a NOT gate, output of that NOT goes to output of And.\
`Nand(a=a, b=b, out=c);`\
`Not(in=c, out=out);`\

Once I figured out that this was just the opposite of a Nand gate, it was fairly simple to solve.

### Or
>input of OR gate goes to 2 NOT gates, each of their outputs go to the 2 inputs of a Nand gate, the Nand gate's output goes to the output of OR.\
`Not(in=a, out=nota);`\
`Not(in=b, out=notb);`\
`Nand(a=nota, b=notb, out=out);`\

This was similar to And, in that you negate the inputs *before* they go into the inputs of the Nand gate.