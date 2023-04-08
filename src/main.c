#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Structs/baseURL.h"
#include "Structs/JobsTable.h"
#include "Structs/JobEntry.h"

#include "HTMLGetter/HTMLGetter.h"
#include "HTMLProcessor/HTMLProcessor.h"

#include "main.h"

int main(void)
{
  const char *memory = GetHTML(baseStruct.baseURL);

  struct JobsTable *data = ProcessData(memory);
  if (data == NULL)
  {
    printf("\nNo Data to Process\n Exiting...");
    return -1;
  }
  
  showResults(data);

  // Cleaning data...
  free((void *)data);

  return 0;
};

void showResults(struct JobsTable *job)
{
  printf("\n\n--------------------------------\n");
  size_t i;
  for (i = 0; i < job->size; i++)
  {
    printf("Date: %s, Position: %s, Location: %s, Business: %s, Link: %s",
           job->memory[i].Date, job->memory[i].Position, job->memory[i].Location, job->memory[i].Group, job->memory[i].Link);
    printf("\n");
  }
}