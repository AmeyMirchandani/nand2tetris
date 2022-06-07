# Project 02 Writeup

## Chips
---
### Half-Adder
>Each of the 2 inputs each go into the inputs of an XOR gate and an AND gate, the XOR gate outputs to the sum bit, and the AND gate outputs to the carry bit.\
`Xor(a=a, b=b, out=sum);`\
`And(a=a, b=b, out=carry);`

The XOR gate mirrors how you do bitwise addition for the sum, and the AND gate mirrors it for the carry.

### Full-Adder
>2 inputs go into the inputs of a HalfAdder gate, the output sum of which is used as the input of another HalfAdder gate along with the final input of the FullAdder as the other input. The sum of the second HalfAdder gate is sent to the sum output of the FullAdder, while the carry output is sent to an OR gate, where it is compared to the first HalfAdder gate's carry output, the output of this gate is used as the carry output for the FullAdder gate.
`HalfAdder(a=a, b=b, sum=midsum, carry=midcarry);`
`HalfAdder(a=midsum, b=c, sum=sum, carry=finalcarry);`
`Or(a=midcarry, b=finalcarry, out=carry);`

What's important to realize here is that when you add 2 bits, you can take the sum and then add it to another bit. This result is the final sum no matter what. At the point, the carry that you originally recorded when adding the first 2 bits will either be 0 or 1. If it is 0, then the second carry can either be 0 or 1, if it is 1, the second carry will be 0. Because of this, it cannot break anything, and can be used as the final carry.