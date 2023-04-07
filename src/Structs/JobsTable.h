#include <stdio.h>
#include "JobEntry.h"

struct JobsTable {
  struct JobEntry * memory[max_align_t];
  size_t size;
};