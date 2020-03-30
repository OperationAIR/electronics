#ifndef PARSE_UTILS_H
#define PARSE_UTILS_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#ifdef TEST
// required for time.h on linux
#define __USE_XOPEN
#define __GNU_SOURCE
#endif
#include <time.h>

#include "strtof_noheap.h"


/* Parse a string (base-10) as int.
 * Example: parse_int("314", &result) returns true and stores 314 to result.
 *
 * @param string        Input string to parse as int. Expected to start
 *                      with a numeric value. Non-numeric values after the
 *                      numbers are allowed, the longest valid substring is
 *                      used.
 * @param result        The parsed value will be stored here if a valid number
 *                      was parsed. If not, the result is unaffected.
 *
 * @return              True if a valid number was found: the result is
 *                      guaranteed to be updated in this case.
 *                      False if the input string is not a valid int:
 *                      the result is not updated.
 */
bool parse_int(const char *string, long int *result);

/* Parse a string formatted as comma-separated list of floats.
 *
 * @param dst_array     All parsed floats (up to dst_max_count)
 *                      are stored in dst_array
 * @param dst_max_count The maximum amount of floats to be stored in dst_array
 * @param string        Source string, formatted as floats separated by ",".
 *
 * @param res_count     The amount of floats found is stored here
 *                      A count > dst_max_count may be returned to indicate
 *                      dst_array is too small.
 *
 * @return              True on success, false if a parse error occurs.
 */
bool parse_float_csv(size_t *res_count, float *dst_array, size_t dst_max_count,
                     const char *string);


#endif

