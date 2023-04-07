typedef __SIZE_TYPE__ size_t;

// Forward Declaration
struct JobEntry;

struct JobsTable
{
  struct JobEntry *memory;
  size_t size;
};