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


#endif

