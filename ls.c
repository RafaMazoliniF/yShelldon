#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

#define SIZE_COLUMN 10

void command_ls(char* current_path, DIR* diretorio);
void command_ls_a(char* current_path, DIR* diretorio);
void command_ls_l(char* current_path, DIR* diretorio);
void command_ls_la(char* current_path, DIR* diretorio);


int main(int argc, char *argv[]) {
    char* current_path = argv[1];
    char* arg = (argc > 2) ? argv[2] : NULL;
    char* arg2 = argv[3];

    DIR *diretorio = opendir(current_path);
    if (diretorio == NULL) {
        perror("fatal error: cannot open directory");
        return 1;
    }
    
    // printf("Valor de splitted_command[1]: %s\n", arg);
    // printf("Valor de splitted_command[2]: %s\n", arg2);

    if (arg == NULL || strcmp(arg, "") == 0) {
        command_ls(current_path, diretorio);
    }
    else if ((strcmp(arg, "-a") == 0 && arg2 == NULL)) {
        command_ls_a(current_path, diretorio);
    }
    else if (strcmp(arg, "-l") == 0 && arg2 == NULL) {
        command_ls_l(current_path, diretorio);
    }
    else if ((strcmp(arg, "-la") == 0) || (strcmp(arg, "-al") == 0) || ((strcmp(arg, "-a") == 0) && (strcmp(arg2, "-l") == 0)) || ((strcmp(arg, "-l") == 0) && (strcmp(arg2, "-a") == 0))) {
        command_ls_la(current_path, diretorio);
    }

    closedir(diretorio);
  
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

    //printf("\n");
}

void command_ls_a(char* current_path, DIR* diretorio) {
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

        if (files_count == 7) {
            printf("\n");
            files_count = 0; 
        }
    }

    //printf("\n");
}

void command_ls_l(char* current_path, DIR* diretorio) {
    struct dirent *entrada;
    struct stat path_stat;
    int files_count = 0;
    char full_path[1024];
    int max_size = 0;

    while ((entrada = readdir(diretorio)) != NULL) {
        snprintf(full_path, sizeof(full_path), "%s/%s", current_path, entrada->d_name); 

        if (entrada->d_name[0] != '.' && strcmp(entrada->d_name, ".") != 0 && strcmp(entrada->d_name, "..") != 0) {
            stat(full_path, &path_stat);

            int size = snprintf(NULL, 0, "%d", path_stat.st_size);

            if (size > max_size) {
                max_size = size;
            }
        }
    }

    rewinddir(diretorio);

    while ((entrada = readdir(diretorio)) != NULL) {

        snprintf(full_path, sizeof(full_path), "%s/%s", current_path, entrada->d_name); 

        if (entrada->d_name[0] != '.' && strcmp(entrada->d_name, ".") != 0 && strcmp(entrada->d_name, "..") != 0) {
            stat(full_path, &path_stat);

            struct passwd *owner = getpwuid(path_stat.st_uid);
            struct group *group = getgrgid(path_stat.st_gid);

            printf((path_stat.st_mode & S_ISDIR(path_stat.st_mode)) ? "d" : "-");
            printf((path_stat.st_mode & S_IRUSR) ? "r" : "-");
            printf((path_stat.st_mode & S_IWUSR) ? "w" : "-");
            printf((path_stat.st_mode & S_IXUSR) ? "x" : "-");

            printf((path_stat.st_mode & S_IRGRP) ? "r" : "-");
            printf((path_stat.st_mode & S_IWGRP) ? "w" : "-");
            printf((path_stat.st_mode & S_IXGRP) ? "x" : "-");

            printf((path_stat.st_mode & S_IROTH) ? "r" : "-");
            printf((path_stat.st_mode & S_IWOTH) ? "w" : "-");
            printf((path_stat.st_mode & S_IXOTH) ? "x " : "- ");

            char str_link[1024];
            sprintf(str_link, "%lu", path_stat.st_nlink);
            printf((strlen(str_link) == 1) ? " %s " : "%s ", str_link);

            printf("%s ", owner->pw_name);
            printf("%s ", group->gr_name);
            printf("%*d ", max_size, path_stat.st_size);

            char time[100];
            strftime(time, 100, "%H:%M", localtime(&path_stat.st_mtime));
            char str_month[50];
            strftime(str_month, sizeof(str_month), "%b", localtime(&path_stat.st_mtime));
            char str_day[50];
            strftime(str_day, sizeof(str_day), "%d", localtime(&path_stat.st_mtime));

            if (str_day[0] == '0') {
                str_day[0] = ' ';
            }

            if (str_month[0] != '\0') {
                str_month[0] = tolower(str_month[0]); 
            }
            
            printf("%s ", str_month);
            printf("%s ", str_day);
            printf("%s ", time);

            if (S_ISDIR(path_stat.st_mode)) {
                printf("\e[1;34m%s\e[0m\n", entrada->d_name);
            } else {
                printf("%s\n", entrada->d_name);
            }
        }
    }
}

void command_ls_la(char* current_path, DIR* diretorio) {
    struct dirent *entrada;
    struct stat path_stat;
    int files_count = 0;
    char full_path[1024];
    int max_size = 0;

    while ((entrada = readdir(diretorio)) != NULL) {
        snprintf(full_path, sizeof(full_path), "%s/%s", current_path, entrada->d_name); 

        if (entrada->d_name[0] != '.' && strcmp(entrada->d_name, ".") != 0 && strcmp(entrada->d_name, "..") != 0) {
            stat(full_path, &path_stat);

            int size = snprintf(NULL, 0, "%d", path_stat.st_size);

            if (size > max_size) {
                max_size = size;
            }
        }
    }
    
    rewinddir(diretorio);

    while ((entrada = readdir(diretorio)) != NULL) {

        snprintf(full_path, sizeof(full_path), "%s/%s", current_path, entrada->d_name); 

        stat(full_path, &path_stat);

        struct passwd *owner = getpwuid(path_stat.st_uid);
        struct group *group = getgrgid(path_stat.st_gid);

        printf((path_stat.st_mode & S_ISDIR(path_stat.st_mode)) ? "d" : "-");
        printf((path_stat.st_mode & S_IRUSR) ? "r" : "-");
        printf((path_stat.st_mode & S_IWUSR) ? "w" : "-");
        printf((path_stat.st_mode & S_IXUSR) ? "x" : "-");

        printf((path_stat.st_mode & S_IRGRP) ? "r" : "-");
        printf((path_stat.st_mode & S_IWGRP) ? "w" : "-");
        printf((path_stat.st_mode & S_IXGRP) ? "x" : "-");

        printf((path_stat.st_mode & S_IROTH) ? "r" : "-");
        printf((path_stat.st_mode & S_IWOTH) ? "w" : "-");
        printf((path_stat.st_mode & S_IXOTH) ? "x " : "- ");

        char str_link[1024];
        sprintf(str_link, "%lu", path_stat.st_nlink);
        printf((strlen(str_link) == 1) ? " %s " : "%s ", str_link);

        printf("%s ", owner->pw_name);
        printf("%s ", group->gr_name);
        printf("%*d ", max_size, path_stat.st_size);

        char time[100];
        strftime(time, 100, "%H:%M", localtime(&path_stat.st_mtime));
        char str_month[50];
        strftime(str_month, sizeof(str_month), "%b", localtime(&path_stat.st_mtime));
        char str_day[50];
        strftime(str_day, sizeof(str_day), "%d", localtime(&path_stat.st_mtime));

        if (str_day[0] == '0') {
            str_day[0] = ' ';
        }

        if (str_month[0] != '\0') {
            str_month[0] = tolower(str_month[0]); 
        }
        
        printf("%s ", str_month);
        printf("%s ", str_day);
        printf("%s ", time);

        if (S_ISDIR(path_stat.st_mode)) {
            printf("\e[1;34m%s\e[0m\n", entrada->d_name);
        } else {
            printf("%s\n", entrada->d_name);
        }
    }
}

