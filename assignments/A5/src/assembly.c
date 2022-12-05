#include "assembly.h"
#include <stdlib.h>
#include <string.h>

struct entry
{
  int valid;
  int addr;
  const char *text;
};

struct assembly
{
  int table_size;
  struct entry *lookup_table;
};

void assembly_set(struct assembly *as, int addr, const char *text)
{
  int k = addr % as->table_size;
  while (as->lookup_table[k].valid)
  {
    // conflict - rehash
    int old_size = as->table_size;
    int new_size = 2 * old_size;
    struct entry *old_table = as->lookup_table;
    as->lookup_table = calloc(sizeof(struct entry), new_size);
    as->table_size = new_size;
    for (int i = 0; i < old_size; ++i)
    {
      if (old_table[i].valid)
        assembly_set(as, old_table[i].addr, old_table[i].text);
    }
    free(old_table);
    k = addr % as->table_size;
  }
  struct entry *e = as->lookup_table + k;
  e->addr = addr;
  e->text = strdup(text);
  e->valid = 1;
}

const char *assembly_get(struct assembly *as, int addr)
{
  int k = addr % as->table_size;
  struct entry *e = as->lookup_table + k;
  if (e->valid && e->addr == addr)
    return e->text;
  return NULL;
}

struct assembly *assembly_create()
{
  struct assembly *as = (struct assembly *)malloc(sizeof(struct assembly));
  int size = 256;
  as->table_size = size;
  struct entry *table = calloc(sizeof(struct entry), size);
  as->lookup_table = table;
  return as;
}

void assembly_delete(struct assembly *as)
{
  for (int k = 0; k < as->table_size; ++k)
  {
    struct entry *e = as->lookup_table + k;
    if (e->valid)
    {
      free((void *)e->text);
      e->valid = 0;
    }
  }
  free(as->lookup_table);
  free(as);
}
