#include "lib.h"

unsigned int fib(unsigned int arg) {
  if (arg < 2) return arg;
  return fib(arg - 1) + fib(arg - 2);
}

void main() {
  char buffer[128];
  print_string("Beregn fib() af hvad? ");
  read_string(buffer, 128);
  unsigned int arg = str_to_uns(buffer);
  print_string("Beregner fib(");
  print_string(buffer);
  print_string(") = ");
  unsigned int res = fib(arg);
  uns_to_str(buffer, res);
  print_string(buffer);
  print_string("\n");
}

