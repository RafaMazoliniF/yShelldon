#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include "utils.h"

void call_internal_command(char command[],char current_path[]) {
    //array of command parts: [0] = command; [1:] = arguments
    char * splitted_command[100];

    //Splits command
    command = strtok(command, " ");
    int i;
    for (i = 0; command != NULL && i < 99; i++) {
        splitted_command[i] = command;
        command = strtok(NULL, " ");
    }

    splitted_command[i] = NULL;

    // for(int j = 0; splitted_command[j] != NULL; j++){
    //     char* a = splitted_command[j];               //testar a primeira letra
    //     printf("%c\n",a[0]); 
    // }
    

    if (strcmp(splitted_command[0], "exit") == 0) {
        exit(0);
    }

    if (strcmp(splitted_command[0], "cd") == 0) {
        //CD -> atualizar o current_path.
        strcat(current_path,"/");
        strcat(current_path,splitted_command[1]);
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
        execl("./ls","./ls",current_path,NULL);}
        else{wait(NULL);}
    }
}