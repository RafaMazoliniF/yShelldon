#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include "internal_commands.h"

int main(int argc, char *argv[]) {
    setenv("PATH", "/bin:/sbin:/usr/bin:/usr/sbin:/user/local/bin:/user/local/sbin", 1);
    
    char title[100];
    char* current_path = (char *)malloc(100 * sizeof(char));
    char home[] = "/home/"; // seta o path padrão para /home/user
    strcat(current_path, home); strcat(current_path, getlogin());
    char path_command[100];

    system("gcc -o ls ls.c");
    system("gcc -o cat cat.c");
    sprintf(title, "%s@bashinga⚡:~%s", getlogin(), current_path);
    printf("\033]0;%s\007", title);

    // fazer if de '$PATH add'/ '$PATH rm'/ '$PATH'

    clearScreen();
    do {
        printUserFormat(current_path);

        fgets(path_command, sizeof(path_command), stdin);
        path_command[strcspn(path_command, "\n")] = '\0';

        if(strcmp(path_command, "$PATH add") != 0) {
            printf("error: cannot find this command\n");
            printf("try using: '$PATH add'\n");
        }
    } while (strcmp(path_command, "$PATH add") != 0);

    

    if (argv[1] == NULL) {
        char command[100];

        for (;;) {

            printUserFormat(current_path);

            fgets(command, sizeof(command), stdin);
            command[strcspn(command, "\n")] = '\0'; //Delete the \n character

            call_internal_command(command, current_path);
        }

    } else {
        char line[100];
        char *splitted_command[100];

        //clearScreen();

        FILE *file = fopen(argv[1], "r");
        if (file == NULL) {
            printf("fatal error: cannot open file %s", argv[1]);
            return 1;
        }

        while (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\n")] = '\0';
            printf("%s", line);
            char *aux = strtok(line, " ");

            for (int i = 0; aux != NULL && i < 99; i++) {
                splitted_command[i] = strdup(aux);
                aux = strtok(NULL, " ");
            }

            //printf("sp_comm0:%s\nsp_comm1:%s\n", splitted_command[0], splitted_command[1]);
            //splitted_command[0] -> comando
            //splitted_command[1] -> argumento
            
            execlp(splitted_command[0], splitted_command[0], splitted_command[1], NULL);
            call_internal_command(line, current_path);
        }
        
        fclose(file);
    }   

    return 0;   
}