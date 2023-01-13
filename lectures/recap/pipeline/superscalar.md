# Two-way superscalar

Antagelser:

load:  "Fe De Ag Mm Wb"
store: "Fe De Ag Mm"
andre: "Fe De Ex Wb"

Fe:2, De:2, Ex:2, Ag:1, Mm:1, Wb:2

Husk: kun en instruktion _for hvert register_ fra ex og frem.

Perfekt hopforudsigelse, Forudsiges i `De`.
Fuld forwarding.

```
                          0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20
L1: bge   x10, x12, end   Fe De Ex Wb
    lw    x14, 0(x11)           Fe De Ag Mm Wb
    addi  x11, x11, 4           Fe De Ex Wb
    sw    x14, 0(x10)              Fe De Ag Mm
    addi  x10, x10, 4              Fe De Ex Wb
    jal   L1                          Fe De Ex Wb
L1: bge   x10, x12, end               Fe De Ex Wb
    lw    x14, 0(x11)                       Fe De Ag Mm Wb
    addi  x11, x11, 4                       Fe De Ex Wb
    sw    x14, 0(x10)                          Fe De Ag Mm
    addi  x10, x10, 4                          Fe De Ex Wb
    jal   L1                                      Fe De Ex Wb
```