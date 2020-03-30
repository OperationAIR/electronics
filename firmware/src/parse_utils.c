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


bool parse_float_csv(size_t *res_count, float *dst_array, size_t dst_max_count,
                     const char *string)
{
    size_t count = 0;

    char tokens[strlen(string)+1];
    strcpy(tokens, string);
    char *strtok_state;
    char *dst = strtok_r(tokens, ",", &strtok_state);
    while(dst) {
        char *endptr;
        float val = strtof_noheap(dst, &endptr);
        if(count < dst_max_count) {
            dst_array[count] = val;
        } else {
            return false;
        }

        if(endptr <= dst) {
            return false;
        }
        count++;
        dst = strtok_r(NULL, ",", &strtok_state);
    }

    *res_count = count;
    return true;
}

