#include "parse_utils.h"
#include <string.h>
#include <stdlib.h>

bool parse_int(const char *string, long int *result)
{
    char *endptr = NULL;
    long int parsed = strtol(string, &endptr, 10);
    if(endptr > string) {
        *result = parsed;
        return true;
    }
    return false;
}

