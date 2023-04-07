#include <stdio.h>
#include <string.h>

#include "libxml2/libxml/HTMLparser.h"
#include "libxml2/libxml/xpath.h"

#include "Structs/baseURL.h"
#include "Structs/JobEntry.h"
#include "Structs/JobsTable.h"
#include "Enums/Categories.h"

#include "utils/htmlGetter.h"

#include "main.h"

int main(void)
{
  const char *memory = GetHTML(baseStruct.baseURL);

  struct JobsTable *data;
  data = ProcessData(memory);

  showResults(data->memory, data->size);

  return 0;
};

struct JobsTable *ProcessData(const char *memory)
{
  htmlDocPtr content = htmlReadDoc(memory, baseStruct.baseURL, baseStruct.encoding, HTML_PARSE_NOERROR);

  if (content == NULL)
  {
    printf("It's null");
    return NULL;
  }

  xmlXPathContextPtr context = xmlXPathNewContext(content);

  xmlXPathObjectPtr result = xmlXPathEvalExpression(xPathExpr, context);

  if (xmlXPathNodeSetIsEmpty(result->nodesetval))
  {
    xmlXPathFreeObject(result);
    printf("No result, Is XPath Expression right or Is the content empty?\n");
    return NULL;
  }

  xmlFree(content);
  xmlFree(context);

  size_t i, j, Arraycounter = 0;
  struct JobEntry job;
  struct JobEntry jobTable[result->nodesetval->nodeNr / Fields];

  const char *tmp[Fields];

  for (i = 0; i < result->nodesetval->nodeNr; i += Fields + 1)
  {
    if (result->nodesetval->nodeTab[i]->children == NULL)
    {
      continue;
    }

    for (j = 0; j <= Fields; j++)
    {
      if (result->nodesetval->nodeTab[i + j]->children->content != NULL)
      {
        tmp[j] = (const char *)result->nodesetval->nodeTab[i + j]->children->content;
      }
      else
      {
        tmp[j] = (const char *)result->nodesetval->nodeTab[i + j]->children->children->content;
      }

      xmlFree(result->nodesetval->nodeTab[i + j]);
    }

    strcpy(job.Date, tmp[0]);
    strcpy(job.Position, tmp[1]);
    strcpy(job.Location, tmp[2]);
    strcpy(job.Group, tmp[3]);

    free((void *)tmp[0]);
    free((void *)tmp[1]);
    free((void *)tmp[2]);
    free((void *)tmp[3]);

    jobTable[Arraycounter] = job;
    Arraycounter++;
  }
  ~i, ~j;
  xmlFree(result);

  struct JobsTable *output = malloc(sizeof(struct JobsTable));
  output->memory = malloc(sizeof(struct JobEntry) * Arraycounter);
  output->memory = jobTable;
  output->size = Arraycounter;

  return output;
}

void showResults(struct JobEntry *job, int len)
{
  printf("\n\n--------------------------------\n");
  size_t i;
  for (i = 0; i < len; i++)
  {
    printf("Date: %s, Position: %s, Location %s, Business:%s\n", job[i].Date, job[i].Position, job[i].Location, job[i].Group);
  }
}