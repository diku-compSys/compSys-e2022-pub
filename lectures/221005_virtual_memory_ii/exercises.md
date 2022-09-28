# Exercises

## Memory mapping

Given an input file `input.txt`, with the contents `"CompSys\n"`,
write a C program that uses `mmap` to change the contents to
`"DumbSys\n"`.

## Improving compsys_malloc.c (The Fun One)

The provided `compsys_malloc.c` allocates out of a fixed-size heap
(256 bytes by default).  Rewrite it to use `mmap()` to instead request
memory from the kernel as necessary.
