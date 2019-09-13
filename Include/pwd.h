#if defined(ILIN) || defined(IUNI)
#include "linpwd.h"
#else
#include "dospwd.h"
#endif

#define printe(str, ...) fprintf(stderr, str, ##__VA_ARGS__)
