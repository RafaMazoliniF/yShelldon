#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include "internal_commands.h"

int main(int argc, char *argv[]) {
   
    char title[100];
    char* current_path = (char *)malloc(100 * sizeof(char));
    if (current_path == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    current_path[0] = '\0'; // Initialize the string to avoid undefined behavior
    char home[] = "/home/"; // seta o path padrão para /home/user
    strcat(current_path, home); 
    strcat(current_path, getlogin());

    system("gcc -o ls ls.c");
    system("gcc -o cat cat.c");
    sprintf(title, "%s@bashinga⚡:~%s", getlogin(), current_path);
    printf("\033]0;%s\007", title);

    char command[100];
    bool flag;

    //clearScreen();
    for (;;) {
        
        if (argc = 2)
        {
            char line[100];
            flag = true;

            FILE *file = fopen(argv[1], "r");               
            if (file == NULL) {
                printf("fatal error: cannot open file %s", argv[1]);
                free(current_path);
                return 1;
            }

            while (fgets(line, sizeof(line), file)) {
                line[strcspn(line, "\n")] = '\0';
                //printf("%s", line);
                call_internal_command(line, current_path, flag);
            }

            fclose(file);
        }

        printUserFormat(current_path);

        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0'; 

        call_internal_command(command, current_path, flag);

    }

    free(current_path); 
    return 0;   
}
