# Project 02 Writeup

## Chips
---
### Half-Adder
>Each of the 2 inputs each go into the inputs of an XOR gate and an AND gate, the XOR gate outputs to the sum bit, and the AND gate outputs to the carry bit.\
`Xor(a=a, b=b, out=sum);`
`And(a=a, b=b, out=carry);`

The XOR gate mirrors how you do bitwise addition for the sum, and the AND gate mirrors it for the carry.