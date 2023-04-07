#include <stdio.h>
#include "JobEntry.h"

struct jobTable {
  struct JobEntry *memory[0];
  size_t size;
};