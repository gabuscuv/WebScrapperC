#pragma once

static struct base baseStruct = {"https://stratos-ad.com/index.php?section=2", "UTF-8"};

static const char *xPathExpr = "//table[@class=\"list onlyDesktop\"]/tr/*[not(self::th) and not(@style=\"border:0\")]";

static const short Fields = 3;
static const short ExtraFields = 1;

int main(void);

struct JobsTable *ProcessData(const char *memory);

void showResults(struct JobEntry *job, int len);