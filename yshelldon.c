#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include "internal_commands.h"

int main(int argc, char *argv[]) {
    extern char **environ;  //inicializa o ambiente privado

    char current[1024];
    getcwd(current, sizeof(current));   //PEGANDO A PASTA current COMO PATH
    strcat(current, "/bin");   //SETANDO O /BIN
    
    setenv("PATH", current, 1);  //seta nosso bin como path

    char title[100];
    char* current_path = (char *)malloc(100 * sizeof(char));
    if (current_path == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    current_path[0] = '\0'; // Initialize the string to avoid undefined behavior
    char home[] = "/home/"; // Seta o path padrão para /home/user
    strcat(current_path, home); 
    strcat(current_path, getlogin());

    system("gcc -o ls ls.c"); //cria o executável do ls
    system("gcc -o cat cat.c"); //cria o executável do cat
    sprintf(title, "%s@bashinga⚡:~%s", getlogin(), current_path);
    printf("\033]0;%s\007", title);

    char command[100];

    clearScreen();
    do {
        for (;;) {
            
            if (argc >= 2)
            {
                char line[100];

                FILE *file = fopen(argv[1], "r");               
                if (file == NULL) {
                    printf("fatal error: cannot open file %s", argv[1]);
                    free(current_path);
                    return 1;
                }

                while (fgets(line, sizeof(line), file) != NULL) {
                    line[strcspn(line, "\n")] = '\0';
                    //puts(line);
                    call_internal_command(line, current_path);
                }

                fclose(file);
            }

            printUserFormat(current_path);

            if (fgets(command, sizeof(command), stdin) == NULL) {
                break; 
            } 
            else if (strcmp(command, "\n") == 0) {
                break;
            } 
            
            command[strcspn(command, "\n")] = '\0'; 

            if (strcmp(command, "^[[A") == 0) {
                printf("AAAA");
            }

            

            call_internal_command(command, current_path);

        }
    } while (strcmp(command, "\n") == 0);

    free(current_path); 
    return 0;   
}