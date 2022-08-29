# Exercises

## RISC-V

The following exercises will train you in writing more
complicated RISC-V programs.  They are intended as preparation for A0.
You will be given pseudocode or C programs, and asked to write similar
programs in RISC-V assembly.

It is up to you to decide how to test them.

You should use [RARS](https://github.com/TheThirdOne/rars) to develop,
test, and run these programs.  [See this guide on using
RARS](../../rars.md).

### Fibonacci function

Implement the standard recursive definition of the Fibonacci function:

    fib(n) = if n < 2 then 1 else fib(n-1) + fib(n-2)

*Don't* rewrite it to be an iterative loop instead.  Yes, that's more
efficient, but it will not give you experience with function calls in
RISC-V.

### Array equality

The following C function is a simplified version of the standard C
function ``memcmp``:

```C
int memeq(const unsigned char *p1, const unsigned char *p2, int n) {
  for (int i = 0; i < n; i++) {
    if (p1[i] != p2[i]) {
      return 0;
    }
  }
  return 1;
}
```

It returns 1 if the `n` bytes at `p1` and `p2` are identical, and
otherwise 0.  Recall that C represents *false* as zero and *true* as
non-zero.

Write this function in RISC-V assembly.  Accept `p1`, `p2`, and `n` in
`a0-a2`, and return the result in `a0`.

### Array search

The following C function is a simplified version of the standard C
function `memmem`:

```C
const unsigned char* memfind(const unsigned char *haystack, int haystacklen,
                             const unsigned char *needle, int needlelen) {
  for (int i = 0; i < haystacklen-needlelen; i++) {
    if (memeq(haystack+i,needle,needlelen)) {
      return haystack+i;
    }
  }
  return NULL;
}
```

It tries to find the array `needle` (of length `needlelen`) in the
array `haystack` (of length `haystacklen`).  If it can be found, it
returns the starting address of the match.  Otherwise it returns NULL
(`0`).

Write this function in RISC-V assembly.  Accept parmaeters in `a0-a3`
and return the result in `a0`.  Use your definition of of `memeq` from
the previous exercise as a helper function.
