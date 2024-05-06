#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>
#include "utils.h"

void call_internal_command(char command[], char current_path[]) {
    //array of command parts: [0] = command; [1:] = arguments
    char *splitted_command[100];
    char* previous_path = (char *)malloc(100 * sizeof(char));

    command = strtok(command, " ");
    int i;
    for (i = 0; command != NULL && i < 99; i++) {
        splitted_command[i] = command;
        command = strtok(NULL, " ");
    }

    splitted_command[i] = NULL;

    //printf("%s\n%s\n", splitted_command[0], splitted_command[1]);

    if (strcmp(splitted_command[0], "exit") == 0)
    {
        exit(0);
    }

    strcpy(previous_path, current_path);
    strcat(current_path, "/"); // CD -> atualizar o current_path.
    strcat(current_path, splitted_command[1]);

    //splitted_command[1] = /home/vini/Desktop

    if (strcmp(splitted_command[0], "cd") == 0) {
        //printf("%s\n", splitted_command[1]);
        if (splitted_command[1] != NULL) {
            struct stat path_stat;            

            if (stat(current_path, &path_stat) == 0) {
                if (chdir(current_path) != 0) {
                    printf("error: failed to change directory to '%s'\n", splitted_command[1]);
                    strcpy(current_path, previous_path);
                } 
            } else {
                printf("'%s' is not a valid directory\n", splitted_command[1]);
                strcpy(current_path, previous_path);
            }
        } /*else if (strcmp(splitted_command[1], "..") == 0) {
            strcpy(current_path, previous_path);
        }*/ else {
            printf("usage: cd <directory>\n");
        }
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
            execl("./ls","./ls", current_path, splitted_command[1], NULL);
        }
        else {
            wait(NULL);
        }
    }
}