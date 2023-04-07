#include <stdio.h>
#include <string.h>

#include "libxml2/libxml/HTMLparser.h"
#include "libxml2/libxml/xpath.h"

#include "Structs/baseURL.h"
#include "Structs/JobEntry.h"
#include "Enums/Categories.h"

#include "utils/htmlGetter.h"

static struct base baseStruct = {"https://stratos-ad.com/index.php?section=2","UTF-8"};

static const char  *xPathExpr = "//table[@class=\"list onlyDesktop\"]/tr/*[not(self::th) and not(@style=\"border:0\")]";

static const short Fields = 3;

int main(void)
{    
    const char * memory = GetHTML(baseStruct.baseURL);   
   
    htmlDocPtr content = htmlReadDoc(memory,baseStruct.baseURL,baseStruct.encoding,HTML_PARSE_NOERROR);
   
    if(content == NULL){printf("It's a null");return 0;}

    xmlXPathContextPtr context = xmlXPathNewContext(content);;

    xmlXPathObjectPtr result = xmlXPathEvalExpression(xPathExpr, context);
    
    if(xmlXPathNodeSetIsEmpty(result->nodesetval))
    {
		  xmlXPathFreeObject(result);
      printf("No result, Is XPath Expression right or Is the content empty?\n");
      return -1;
    }

   xmlFree(content);xmlFree(context);
    
    size_t i,j,mem;
    struct JobEntry job;
    struct JobEntry jobTable[result->nodesetval->nodeNr/Fields];
   // struct GArray * array = g_array_new(FALSE, FALSE, sizeof(struct JobEntry));

    const char * tmp[Fields];
    
    for (i=0; i < result->nodesetval->nodeNr; i+=Fields+1) {
        if(result->nodesetval->nodeTab[i]->children == NULL){continue;}

        for (j=0; j <= Fields ;j++){
            if(result->nodesetval->nodeTab[i+j]->children->content != NULL)
            {
                tmp[j] = (const char *)result->nodesetval->nodeTab[i+j]->children->content;
            }
            else
            {
                tmp[j] = (const char *)result->nodesetval->nodeTab[i+j]->children->children->content;
            }            

            xmlFree(result->nodesetval->nodeTab[i+j]);
        }
       
        strcpy(job.Date,tmp[0]);
        strcpy(job.Position,tmp[1]);
        strcpy(job.Location,tmp[2]);
        strcpy(job.Group,tmp[3]);

        jobTable[mem] = job;        
        mem++;
	}
  ~i,~j;
  xmlFree(result);

  showResults(jobTable,mem);
  return 0;
};

void showResults(struct JobEntry *job, int len )
{
  printf("\n\n--------------------------------\n");
  size_t i;
  for (i = 0; i < len; i++)
  {
            printf("Date: %s, Position: %s, Location %s, Business:%s\n",job[i].Date,job[i].Position,job[i].Location,job[i].Group);
  }
}