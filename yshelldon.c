#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include "internal_commands.h"

char *get_model() {
    char *model = (char *)malloc(256 * sizeof(char));
    char *space;
 
    FILE *file = fopen("/sys/class/dmi/id/product_name", "r");

    fgets(model, 256, file);
    model[strcspn(model, "\n")] = '\0';

    while ((space = strchr(model, ' ')) != NULL) {
        *space = '-';
    }

    return model;
}

int main() {
    char title[100];
    char command[100];
    char* current_path = (char *)malloc(100 * sizeof(char));
    char home[] = "/home/";
    strcat(current_path, home); strcat(current_path, getlogin()); // seta o path padrão para /home/user
    char *model = get_model();

    system("gcc -o ls ls.c");
    system("gcc -o cat cat.c");
    sprintf(title, "⚡BAZINGA⚡ - %s@%s:~%s", getlogin(), model, current_path);
    printf("\033]0;%s\007", title);

    clearScreen();
    while (1) {
        
        printUserFormat(current_path);

        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0'; //Delete the \n character
        
        call_internal_command(command, current_path);
        
    }
    
    return 0;   
}