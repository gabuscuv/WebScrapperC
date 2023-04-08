
static const short Fields = 3;
static const short ExtraFields = 1;

static const char *xPathExpr = "//table[@class=\"list onlyDesktop\"]/tr/*[not(self::th) and not(@style=\"border:0\")]";

struct JobsTable *ProcessData(const char *memory);
