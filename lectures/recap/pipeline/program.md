                          0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20
L1: bge   x10, x12, end
    lw    x14, 0(x11)
    addi  x11, x11, 4
    sw    x14, 0(x10)
    addi  x10, x10, 4
    jal   L1
L1: bge   x10, x12, end
    lw    x14, 0(x11)
    addi  x11, x11, 4
    sw    x14, 0(x10)
    addi  x10, x10, 4
    jal   L1