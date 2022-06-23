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