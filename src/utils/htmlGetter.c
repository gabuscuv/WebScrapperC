#include "curl/curl.h"
#include "curl/easy.h"

#include <stdio.h>

#include "htmlGetter.h"

#include "../Structs/memory.h"
#include <string.h>

#include "stdlib.h"

static struct Memory memory;

const char *GetHTML(const char *url)
{
  memory.memory = malloc(1);
  memory.size = 0;

  CURL *curl = curl_easy_init();
  CURLcode res;

  if (curl)
  {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &memory);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
  };
  return memory.memory;
}

size_t WriteMemoryCallback(void *content, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct Memory *mem = (struct Memory *)userp;
  char *ptr = realloc(mem->memory, mem->size + realsize + 1);

  if (!ptr)
  {
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), content, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}
