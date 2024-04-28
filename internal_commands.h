#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void call_internal_command(char * command) {
    if (strcmp(command, "exit") == 0) {
        exit(0);
    }

    if (strcmp(command, "cd") == 0) {
        //Insert code here
    }

    if (strcmp(command, "path") == 0) {
        //Insert code here
    }

}