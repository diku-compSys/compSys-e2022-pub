# Out of order

Antagelser:

ALU-op: Fa Fb Fc De Fu Al Rn Qu pk rd ex wb Ca Cb
branch: Fa Fb Fc De Fu Al Rn Qu pk rd ex Ca Cb

load:  Fa Fb Fc De Fu Al Rn Qu pk rd ag ma mb mc wb Ca Cb
store: Fa Fb Fc De Fu Al Rn Qu pk rd ag ma mb mc -- Ca Cb   // addresse
       -                    Q* -- -- -- -- pk rd st C*      // data

inorder: Fa, Fb, Fc, De, Fu, Al, Rn, Qu, Ca, Cb
outoforder: pk, rd, ex, wb

Resourcer: Fa:2, Fb:2, Fc:2, De:2, Fu:2, Al:2, Rn:2 [Qu-Ca]:2, Ca:2, Cb:2

Branch prediction causes only single cycle delay!

```
                          0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22
L1: bge   x10, x12, end   Fa Fb Fc De Fu Al Rn Qu pk rd ex Ca Cb
    lw    x14, 0(x11)        Fa Fb Fc De Fu Al Rn Qu pk rd ag ma mb mc wb Ca Cb
    addi  x11, x11, 4        Fa Fb Fc De Fu Al Rn Qu pk rd ex wb -- -- -- Ca Cb
    sw    x14, 0(x10)           Fa Fb Fc De Fu Al Rn Qu pk rd ag ma mb mc -- Ca Cb
                                                     Q* -- -- -- -- pk rd st C*
    addi  x10, x10, 4           Fa Fb Fc De Fu Al Rn Qu pk rd ex wb -- -- -- Ca Cb
    jal   L1                       Fa Fb Fc De Fu Al Rn Qu pk rd ex wb -- -- -- Ca Cb
L1: bge   x10, x12, end            Fa Fb Fc De Fu Al Rn Qu -- pk rd ex -- -- -- Ca Cb
    lw    x14, 0(x11)                 Fa Fb Fc De Fu Al Rn Qu pk rd ag ma mb mc wb Ca Cb
    addi  x11, x11, 4                 Fa Fb Fc De Fu Al Rn Qu -- pk rd ex wb -- -- Ca Cb
    sw    x14, 0(x10)                    Fa Fb Fc De Fu Al Rn Qu pk rd ag ma mb mc -- Ca Cb
                                                              Q* -- -- -- -- pk rd st C*
    addi  x10, x10, 4                    Fa Fb Fc De Fu Al Rn Qu -- pk rd ex wb -- -- -- Ca Cb
    jal   L1                                Fa Fb Fc De Fu Al Rn Qu pk rd ex wb -- -- -- Ca Cb
```