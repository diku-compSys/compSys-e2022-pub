#include "memory.h"
#include "assembly.h"
#include "read_exec.h"
#include "simulate.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void terminate(const char *error)
{
  printf("%s\n", error);
  printf("RISC-V Simulator. Usage:\n");
  printf("  sim riscv-dis            // no log\n");
  printf("  sim riscv-dis -l log     // log each instruction\n");
  printf("  sim riscv-dis -s log     // log only summary\n");
  exit(-1);
}

int main(int argc, char *argv[])
{
  if (argc == 2 || argc == 4)
  {
    struct memory *mem = memory_create();
    struct assembly *as = assembly_create();
    FILE *log_file = NULL;
    if (argc == 4 && !strcmp(argv[2], "-l"))
    {
      log_file = fopen(argv[3], "w");
      if (log_file == NULL)
      {
        terminate("Could not open logfile, terminating.");
      }
    }
    int start_addr = read_exec(mem, as, argv[1], log_file);
    clock_t before = clock();
    long int num_insns = simulate(mem, as, start_addr, log_file);
    clock_t after = clock();
    int ticks = after - before;
    double mips = (1.0 * num_insns * CLOCKS_PER_SEC) / ticks / 1000000;
    if (argc == 4 && !strcmp(argv[2], "-s"))
    {
      log_file = fopen(argv[3], "w");
      if (log_file == NULL)
      {
        terminate("Could not open logfile, terminating.");
      }
    }
    if (log_file)
    {
      fprintf(log_file, "\nSimulated %ld instructions in %d ticks (%f MIPS)\n", num_insns, ticks, mips);
      fclose(log_file);
    }
    else
    {
      printf("\nSimulated %ld instructions in %d ticks (%f MIPS)\n", num_insns, ticks, mips);
    }
    assembly_delete(as);
    memory_delete(mem);
  }
}
