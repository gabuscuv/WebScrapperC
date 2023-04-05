#include <stdio.h>

#include "libxml2/libxml/HTMLparser.h"
#include "libxml2/libxml/xpath.h"

#include "Structs/baseURL.h"

#include "utils/htmlGetter.h"


static struct base baseStruct = {"https://stratos-ad.com/index.php?section=2","UTF-8"};

static const char  *xPathExpr = "//table[@class=\"list onlyDesktop\"]/tr/*[not(self::th) and not(@style=\"border:0\")]";

int main(void)
{
    const char * keyword;
    
    const char * memory = GetHTML(baseStruct.baseURL);   
   
    htmlDocPtr content = htmlReadDoc(memory,baseStruct.baseURL,baseStruct.encoding,HTML_PARSE_NOERROR);
   
    if(content == NULL){printf("It's a null");return 0;}

    xmlXPathContextPtr context = xmlXPathNewContext(content);;

    xmlXPathObjectPtr result = xmlXPathEvalExpression(xPathExpr, context);
    
    if(xmlXPathNodeSetIsEmpty(result->nodesetval)){
		xmlXPathFreeObject(result);
        printf("No result\n");
        return 0;
        }
    
    size_t i;
    for (i=0; i < result->nodesetval->nodeNr; i++) {
        if(result->nodesetval->nodeTab[i]->children == NULL){continue;}
        if(result->nodesetval->nodeTab[i]->children->content != NULL)
        {
		    printf("keyword: %s\n", result->nodesetval->nodeTab[i]->children->content);
        }
        else
        {
            printf("keyword: %s\n", result->nodesetval->nodeTab[i]->children->children->content);
        }
        
        xmlFree(result->nodesetval->nodeTab[i]);
	}
   return 0;
};



//	keyword = xmlNodeListGetString(context, result->nodesetval->nodeTab[i]->children->content, 1);
