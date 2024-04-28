#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "internal_commands.h"
#include "utils.h"

int main() {
    char command[100];
    clearScreen();

    while (1) {
    
        printUserFormat();
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0'; //Delete the \n character
        
        call_internal_command(command);

    }

    return 0;
}