#include "cli.h"
#include <stdint.h>
#include <string.h>
#include <stdbool.h>


#define MAX_MSG_LEN 64

static struct {
    CliCommand *commands;
    size_t N;
    write_fn write;
} CLI;

static void cli_help() {
    CLI.write("%-14s\t%s", "Command", "Description");
    CLI.write("%-14s\t%s", "=======", "===========");
    for (uint32_t i=0; i < CLI.N; i++) {
        CliCommand cmd = CLI.commands[i];
        CLI.write("%-14s\t%s", cmd.cmd, cmd.help);
    }
}

void cli_init(CliCommand *commands, size_t num_commands, write_fn write)
{
    CLI.commands = commands;
    CLI.N = num_commands;
    CLI.write = write;
}

void cli_remove_enter(char *str, uint32_t l) {
    int i = strnlen(str, l)  - 1;
    while (i >= 0) {
        if (str[i] == '\r' || str[i] == '\n') {
            str[i] = 0;
        }
        i--;
    }
}

void cli_exec(char* cmd, size_t l) {

    cli_remove_enter(cmd, l);
    bool match = false;
    for (uint32_t i=0; i < CLI.N; i++) {
        CliCommand candidate = CLI.commands[i];
        char *ptr = strnstr(cmd, candidate.cmd, l);
        // only accept matches at start of command string
        if (ptr == cmd) {
            match = true;
            candidate.function(ptr + strlen(candidate.cmd) + 1);
            break;
        }
    }

    if (!match) {
        char *ptr = strnstr(cmd, "help", l);
        if (ptr == cmd) {
            cli_help();
        } else {
            CLI.write("Unknown command '%s'", cmd);
            CLI.write("Type 'help' for an overview of available cmds\r\n");
        }
    }
}

