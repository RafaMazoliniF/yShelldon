#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>
#include <fcntl.h>
#include "utils.h"

void call_internal_command(char command[], char current_path[]) {
    //array of command parts: [0] = command; [1:] = arguments
    char *splitted_command[100];
    char* temp_path = (char *)malloc(100 * sizeof(char));

    command = strtok(command, " ");
    int i;
    for (i = 0; command != NULL && i < 99; i++) {
        splitted_command[i] = command;
        command = strtok(NULL, " ");
    }

    splitted_command[i] = NULL;

    if (strcmp(splitted_command[0], "exit") == 0) {
        free(temp_path);
        exit(0);
    }

    else if (strcmp(splitted_command[0], "cd") == 0) 
    {
        //SE NÃO TEM COMANDO
        if(splitted_command[1] == NULL) {
            char home[] = "/home/";
            strcpy(current_path, home); strcat(current_path, getlogin()); // seta o path padrão para /home/user
        }
        //SE O COMANDO NÃO É .
        else if(strcmp(splitted_command[1], ".") != 0){ //se o comando não for . vai pra isso
            //cria a variavel temp_path
            strcpy(temp_path, current_path);
            strcat(temp_path, "/");
            strcat(temp_path, splitted_command[1]);

            //printf("Temp path: %s\n", temp_path);
            //CRIOU UM PATH TEMP
            
                struct stat path_stat;
                DIR* dir = opendir(temp_path);

                //SE O COMANDO É ..
                if(strcmp(splitted_command[1],"..") == 0) {
                    int tamanho = strlen(current_path);

                    for (int i = tamanho; i >= 0; i--) {
                        if (current_path[i] == '/') {
                            current_path[i] = '\0';
                            closedir(dir);
                            break;
                        }
                    }
                }
                // SE O COMANDO NÃO É ..
                // TESTA SE O CAMINHO É RELATIVO
                else if(stat(temp_path, &path_stat) == 0) { //fala se é um diretório ou não
                    if (dir != NULL) { //fala se o diretório existe
                        closedir(dir);
                        strcpy(current_path, temp_path); //se o dir existe o current path é atualizado
                        //printf("Abriu\n");
                    }
                }
                // AGORA TEM QUE TESTAR SE O CAMINHO É ABSOLUTO
                else {
                    printf("error: directory cannot be found\n");
                    closedir(dir);
                }
                //se o dir não existe manda um erro, não tem que atualizar o current_path
            } //SE O COMANDO NÃO É NULL, NEM ., NEM VÁLIDO
        else {
            printf("error: directory cannot be found\n");
        }
    } 

    else if (strcmp(splitted_command[0], "$PATH") == 0) {

        if(splitted_command[1] != NULL && strcmp(splitted_command[1], "-add") == 0) {
            char* older_path = getenv("PATH");
            size_t path_size = strlen(older_path) + strlen(splitted_command[2]) + 2;
            char* new_path = malloc(path_size);

            strcpy(new_path, older_path);
            strcat(new_path,":"); strcat(new_path, splitted_command[2]);
            setenv("PATH", new_path, 1);
            free(new_path);
            printf("%s\n", getenv("PATH"));
        }

        else if(splitted_command[1] != NULL && strcmp(splitted_command[1], "-rm") == 0) {
            char* older_path = getenv("PATH");
            size_t path_size = strlen(older_path);
            char* new_path = malloc(path_size);
            strcpy(new_path, older_path);

            for (int i = path_size; i >= 0; i--) {
                if (new_path[i] == ':') {
                    new_path[i] = '\0';
                    break;
                }
            }

            setenv("PATH", new_path, 1);
            free(new_path);
            printf("%s\n", getenv("PATH"));
            
        }

        else {
            printf("%s\n", getenv("PATH"));
        }
    }

    else if (strcmp(splitted_command[0], "path") == 0) {
        printf("usage: $PATH [OPTION]\n\n");
        printf("    -add [directory]     \e[0;33madd\e[0m a directory\n");
        printf("    -rm                  \e[0;33mremove\e[0m the last added directory\n");
    }

    else if (strcmp(splitted_command[0], "clear") == 0) {
        if (splitted_command[1] != NULL) {
            printf("usage: clear");
        }
        else {
            clearScreen();
        }
    }

    else if (strcmp(splitted_command[0], "pwd") == 0) {
        printf("%s", current_path);
    }

    else if (strcmp(splitted_command[0], "ls") == 0) {
        pid_t pid = fork();

        if (pid == 0) {
            char *args[] = {"./ls", current_path, splitted_command[1], splitted_command[2], NULL};
            execvp("ls", args);
        }
        else {
            wait(NULL);
        }
    }
    else if (strcmp(splitted_command[0], "cat") == 0) {
        pid_t pid = fork();

        if(pid == 0) {
            char *args[] = { "./cat", current_path, splitted_command[1], splitted_command[2], splitted_command[3], NULL};
            execvp("cat", args);
        }
        else {
            wait(NULL);
        }
    }

    else {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fatal error: fork error");
            exit(1);
        }

        if (pid == 0) {
            if (splitted_command[0][0] == '.' && splitted_command[0][1] == '/') {
                if (execvp(splitted_command[0], splitted_command) == -1) {
                    printf("fatal error: file not found\n");
                    exit(1);
                }
            } else {
                if (execvp(splitted_command[0], splitted_command) == -1) {
                    printf("fatal error: file not found\n");
                    exit(1);
                }
            }
        }
        
        wait(NULL);
    }
}
