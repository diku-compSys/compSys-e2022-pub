# Exercises

The following exercises are intended to give you experience with basic
RISC-V assembly programming.

You can use one of the following RISC-V interpreters:

* [Web-based interpreter](https://www.cs.cornell.edu/courses/cs3410/2019sp/riscv/interpreter/)

* [RARS](https://github.com/TheThirdOne/rars), which has more features
and supports a bigger memory, but has a more complicated interface.

You should use only the instructions supported by the web-based
interpreter: ADD, ADDI, SUB, AND,ANDI, OR, ORI, XOR, XORI, SLT, SLTI,
SLTU, SLTIU, SRA, SRAI, SRL, SRLI, SLL, SLLI, LW, SW, LB, SB, LUI,
AUIPC, JAL, JALR, BEQ, BNE, BLT, BGE, BLTU, BGEU.

Unfortunately the exercises from the book contains an annoying number
of errors, probably because they have been hastily converted from a
64-bit edition of the book.  We will try to make note of these where
they appear.  Generally, if you see something unexpectedly multiply
with 8 (or talk about "8-byte words, as exercise 2.6), use 4 instead.
Are you perhaps wondering why you have to pay a lot of money for a
book with errors this elementary?  I too am wondering.

## From COD

* Exercise 2.1

* Exercise 2.2

* Exercise 2.3

* Exercise 2.4, but modified such that the code to translate looks like this:

```
sll  x30, x5,  2   // x30 = f * 4
add  x30, x10, x30 // x30 = &A[f]
slli x31, x6,  2   // x31 = g * 4
add  x31, x11, x31 // x31 = &B[g]
lw    x5, 0(x30)   // f = A[f]

addi x12, x30, 4
lw   x30, 0(x12)
add  x30, x30, x5
lw   x30, 0(x31)
```

* Exercise 2.5

* Exercise 2.6

If you finish early, you can continue with more of the chapter 2
exercises - many are surprisingly relevant, and close to what you can
expect at the exam.  Skip the ones about instruction encoding
(e.g. 2.12); this will be covered later in the course.

### Errors in exercises

Exercises 2.10/2.17/2.18/2.21 seem to use 64-bit register values, despite
the current edition of the book being about RISC-V/32.  If you decide
to do these exercises, Ignore the upper 32 bits.

### Solutions

#### 2.1

<details>
<summary>Open this to see the answer</summary>

```
addi x7, x7, -5
add  x5, x6, x7
```

Note that I overwrite the value of `h` - depending on the context,
this may or may not be acceptable.  (Consider: when is it acceptable?)

</details>

#### 2.2

<details>
<summary>Open this to see the answer</summary>

```
f = g + h + i
```

</details>

#### 2.3

<details>
<summary>Open this to see the answer</summary>

Assuming `A` and `B` are byte arrays:

```
sub  x5, x28, x29  // f = i - j
add  x5, x5, x10   // f = f + A
lw   x5, 0(x5)     // f = Mem[f]
sw   x5, 8(x11)    // Mem[B+8] = f
```

If `A` and `B` are `int` arrays, the indexes have to be multiplied by
`sizeof int` (4) to obtain the right memory offset:

```
sub  x5, x28, x29  // f = i - j
slli x5, x5, 2     // f = f * 4
add  x5, x5, x10   // f = f + A
lw   x5, 0(x5)     // f = Mem[f]
sw   x5, 32(x11)   // Mem[B+32] = f
```

</details>

#### 2.4

<details>
<summary>Open this to see the answer</summary>


```
A[A[f+1]]
```

</details>

#### 2.5

<details>
<summary>Open this to see the answer</summary>


Little endian:

```
Address   Byte
0           12
1           ef
2           cd
3           ab
```

Big endian:

```
Address   Byte
0           ab
1           cd
2           ef
3           12
```

</details>

#### 2.6

<details>
<summary>Open this to see the answer</summary>

Multiply the value of each symbol with its *weight*, which is `16**i`
for the *i*ith symbol counting from the right (*least significant
symbol*).

* 0x2 \* 0 = 2
* 0x1 \* 16 = 1
* 0xf \* 256 = 3840
* 0xe \* 4096 = 57344
* ...

2 + 1 + 3840 + 57344 + ... = 2882400018

</details>
