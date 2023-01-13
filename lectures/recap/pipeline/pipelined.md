# Simple 5-stage pipelined

Antagelser:

alle: "Fe De Ex Mm Wb"
Fe: 1, De: 1, Ex: 1, Mm: 1, Wb: 1

Perfekt hopforudsigelse. Forudsiges i De.
Fuld forwarding.

```
                          0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17
L1: bge   x10, x12, end   Fe De Ex Mm Wb
    lw    x14, 0(x11)           Fe De Ex Mm Wb
    addi  x11, x11, 4              Fe De Ex Mm Wb
    sw    x14, 0(x10)                 Fe De Ex Mm Wb
    addi  x10, x10, 4                    Fe De Ex Mm Wb
    jal   L1                                Fe De Ex Mm Wb
L1: bge   x10, x12, end                        Fe De Ex Mm Wb
    lw    x14, 0(x11)                                Fe De Ex Mm Wb
    addi  x11, x11, 4                                   Fe De Ex Mm Wb
    sw    x14, 0(x10)                                      Fe De Ex Mm Wb
    addi  x10, x10, 4                                         Fe De Ex Mm Wb
    jal   L1                                                     Fe De Ex Mm Wb
```