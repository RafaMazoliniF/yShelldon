#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include "internal_commands.h"

int main() {
    char command[100];
    char* current_path = (char *)malloc(100 * sizeof(char));
    char home[] = "/home/";
    strcat(current_path,home); strcat(current_path, getlogin()); //seta o path padrão para /home/user

    clearScreen();
    while (1) {
        
        printUserFormat(current_path);

        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0'; //Delete the \n character
        
        call_internal_command(command, current_path);
    }
    
    return 0;   
}