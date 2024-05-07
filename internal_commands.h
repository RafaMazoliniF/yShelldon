#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>
#include "utils.h"

void call_internal_command(char command[], char current_path[]) {
    //array of command parts: [0] = command; [1:] = arguments
    char *splitted_command[100];
    char* previous_path = (char *)malloc(100 * sizeof(char));
    char* temp_path = (char *)malloc(100 * sizeof(char));

    command = strtok(command, " ");
    int i;
    for (i = 0; command != NULL && i < 99; i++) {
        splitted_command[i] = command;
        command = strtok(NULL, " ");
    }

    splitted_command[i] = NULL;

    if (strcmp(splitted_command[0], "exit") == 0)
    {
        exit(0);
    }


    if (strcmp(splitted_command[0], "cd") == 0) 
    {

        //SE NÃO TEM COMANDO
        if(splitted_command[1] == NULL){
            char home[] = "/home/";
            strcpy(current_path, home); strcat(current_path, getlogin()); // seta o path padrão para /home/user
        }
        //SE O COMANDO NÃO É .
        else if(strcmp(splitted_command[1], ".") != 0){ //se o comando não for . vai pra isso

            //cria a variavel temp_path
            strcpy(temp_path, current_path);
            strcat(temp_path, "/");
            strcat(temp_path, splitted_command[1]);

            printf("Temp path: %s\n", temp_path);
            //CRIOU UM PATH TEMP
            
                struct stat path_stat;
                DIR* dir = opendir(temp_path);

                //SE O COMANDO É ..
                if(strcmp(splitted_command[1],"..") == 0){
                    printf("\nVoltando..");
                    int tamanho = strlen(current_path);

                    for (int i = tamanho; i >= 0; i--) {
                        if (current_path[i] == '/') {
                            current_path[i] = '\0';
                            break;
                        }
                    }
                }
                // SE O COMANDO NÃO É ..
                // TESTA SE O CAMINHO É RELATIVO
                else if(stat(temp_path, &path_stat) == 0){ //fala se é um diretório ou não
                    if (dir != NULL) { //fala se o diretório existe
                        closedir(dir);
                        strcpy(current_path,temp_path); //se o dir existe o current path é atualizado
                        printf("Abriu\n");
                    }
                }
                // AGORA TEM QUE TESTAR SE O CAMINHO É ABSOLUTO
                else{printf("error: failed to change directory");
                closedir(dir);}
                //se o dir não existe manda um erro, não tem que atualizar o current_path
            } //SE O COMANDO NÃO É NULL, NEM ., NEM VÁLIDO
        else {printf("\nerror: directory cannot be found\n");} 
    } 

    if (strcmp(splitted_command[0], "path") == 0) {
        //Insert code here
    }

    if (strcmp(splitted_command[0], "clear") == 0) {
        if (splitted_command[1] != NULL) {
            printf("Implement error massage with --help\n");
        }
        else {
            clearScreen();
        }
    }

    if (strcmp(splitted_command[0], "pwd") == 0) {
        printf("%s\n", current_path);
    }

    if (strcmp(splitted_command[0], "ls") == 0) {
        pid_t pid = fork();

        if (pid == 0) {
            execl("./ls","./ls", current_path, NULL);
        }
        else {
            wait(NULL);
        }
    }

}