#include <string.h>

#include "libxml2/libxml/HTMLparser.h"
#include "libxml2/libxml/xpath.h"

#include "Structs/JobEntry.h"
#include "Structs/JobsTable.h"

#include "Enums/Fields.h"

#include "HTMLProcessor.h"


struct JobsTable *ProcessData(const char *memory)
{
  htmlDocPtr content = htmlReadDoc(memory, NULL, "UTF-8", HTML_PARSE_NOERROR);

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

  const char *tmp[Fields + ExtraFields];

  for (i = 0; i < result->nodesetval->nodeNr; i += Fields + 1)
  {
    for (j = 0; j <= Fields; j++)
    {
      if (result->nodesetval->nodeTab[i + j]->children->content != NULL)
      {
        tmp[j] = (const char *)result->nodesetval->nodeTab[i + j]->children->content;
      }
      else
      {
        if (j == Fields_Position)
        {
          tmp[Fields_Link] = (const char *)result->nodesetval->nodeTab[i + j]->children->properties->children->content;
        };
        tmp[j] = (const char *)result->nodesetval->nodeTab[i + j]->children->children->content;
      }

      xmlFree(result->nodesetval->nodeTab[i + j]);
    }

    strcpy(job.Link, tmp[Fields_Link]);

    strcpy(job.Date, tmp[Fields_Date]);
    strcpy(job.Position, tmp[Fields_Position]);
    strcpy(job.Location, tmp[Fields_Location]);
    strcpy(job.Group, tmp[Fields_Group]);

    for (j = 0; j < Fields + ExtraFields; j++)
    {
      free((void *)tmp[j]);
    }

    jobTable[Arraycounter] = job;
    Arraycounter++;
  }
  ~i, ~j;
  xmlFree(result);

  struct JobsTable *output = malloc(sizeof(struct JobsTable));
  output->memory = malloc(sizeof(struct JobEntry) * Arraycounter);
  output->memory = jobTable;
  output->size = Arraycounter;

  ~Arraycounter;

  return output;
}