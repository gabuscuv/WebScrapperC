#include <stdio.h>

struct Memory;

const char *GetHTML(const char *url);

size_t WriteMemoryCallback(void *content, size_t size, size_t nmemb, void *userp);
