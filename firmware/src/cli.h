#ifndef CLI_H_
#define CLI_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef void (*cli_function)(char *args);
typedef bool (*write_fn)(const char format[], ...);


typedef struct {
    char *cmd;
    char *help;
    cli_function function;
} CliCommand;

void cli_init(CliCommand *commands, size_t num_commands, write_fn write);
void cli_exec(char* cmd, size_t l);

/**
 * Replaces all '\n' and '\r' chars in str with '\0'
 */
void cli_remove_enter(char *str, uint32_t l);
#endif