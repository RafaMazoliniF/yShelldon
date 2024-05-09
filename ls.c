#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h> // Para NULL

#define SIZE_COLUMN 10

void command_ls(char* current_path, DIR* diretorio);
void command_ls_a(char* current_path, char* arg, DIR* diretorio);

int main(int argc, char *argv[]) {
    // if (argc < 2) {
    //     printf("Usage: %s <directory>\n", argv[0]);
    //     return 1;
    // }

    char* current_path = argv[1];
    char* arg = (argc > 2) ? argv[2] : NULL; // Verifica se o argumento opcional foi fornecido

    DIR* diretorio = opendir(current_path);
    if (diretorio == NULL) {
        perror("fatal error: can not open directory");
        return 1;
    }

    if (arg == NULL || strcmp(arg, "") == 0) {
        command_ls(current_path, diretorio);
    }
    else if (strcmp(arg, "-a") == 0) {
        command_ls_a(current_path, arg, diretorio);
    }
    else if (strcmp(arg, "-l") == 0) {
        // Implemente a função command_ls_l
    }
    else if ((strcmp(arg, "-la") == 0) || (strcmp(arg, "-al") == 0)) {
        // Implemente a função command_ls_la
    }

    closedir(diretorio);

    printf("\n");

    return 0;
}

void command_ls(char* current_path, DIR* diretorio) {
    struct dirent *entrada;
    struct stat path_stat;
    int files_count = 0;
    char full_path[1024];

    while ((entrada = readdir(diretorio)) != NULL) {
        
        snprintf(full_path, sizeof(full_path), "%s/%s", current_path, entrada->d_name);

        if (entrada->d_name[0] != '.' && strcmp(entrada->d_name, ".") != 0 && strcmp(entrada->d_name, "..") != 0) {
            stat(full_path, &path_stat);

            if (S_ISDIR(path_stat.st_mode)) {
                printf("\e[1;34m%-*s\e[0m", strlen(entrada->d_name)+3, entrada->d_name);
                files_count++;
            } else {
                printf("%-*s", strlen(entrada->d_name)+3, entrada->d_name);
                files_count++;
            }

            if (files_count == 5) {
                printf("\n");
                files_count = 0; 
            }
        }
    }    
}

void command_ls_a(char* current_path, char* arg, DIR* diretorio) {
    struct dirent *entrada;
    struct stat path_stat;
    int files_count = 0;
    char full_path[1024];

    while ((entrada = readdir(diretorio)) != NULL) {
        
        snprintf(full_path, sizeof(full_path), "%s/%s", current_path, entrada->d_name); 

        stat(full_path, &path_stat);

        if (S_ISDIR(path_stat.st_mode)) {
            printf("\e[1;34m%-*s\e[0m", strlen(entrada->d_name)+3, entrada->d_name);
            files_count++;
        } else {
            printf("%-*s", strlen(entrada->d_name)+3, entrada->d_name);
            files_count++;
        }

        if (files_count == 5) {
            printf("\n");
            files_count = 0; 
        }
    } 
}