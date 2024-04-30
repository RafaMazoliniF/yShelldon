#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "internal_commands.h"

int main() {
    char command[100];
    char current_path[100] = "/home/"; strcat(current_path, getlogin()); //Default path "/home/[user]"

    clearScreen();
    while (1) {
        
        printUserFormat(current_path);
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0'; //Delete the \n character
        
        call_internal_command(command);
    }

    return 0;
}