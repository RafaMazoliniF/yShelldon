#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/stat.h>

void get_dir(char *dir, size_t size) 
{
    if (getcwd(dir, size) == NULL) 
    {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }
}

void print_prompt(const char *user, const char *dir)
{ 
    printf("\e[1;32m%s@bashinga⚡\e[0m:\e[1;34m~%s\e[0m$ ", user, dir);
}

void list_files(const char *dir)
{
    DIR *directory;
    struct dirent *entry;

    directory = opendir(dir);

    if (directory == NULL) 
    {
        perror("opendir");
        return;
    }

    while ((entry = readdir(directory)) != NULL) 
    {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) 
        {
            if (entry->d_type == DT_DIR) 
            {
                printf("\e[1;34m%s\e[0m\n", entry->d_name);
            } else 
            {
                printf("%s ", entry->d_name);
            }
        }
    }

    //printf("\n");
    closedir(directory);
}

void enter_directory(char *arg, bool first)
{
    arg = strtok(NULL, " ");

    if (arg != NULL) 
    {
        struct stat path_stat;
        if (stat(arg, &path_stat) == 0 && S_ISDIR(path_stat.st_mode)) 
        {
            if (chdir(arg) == 0) 
                first = false;
            else 
                printf("Failed to change directory to '%s'\n", arg);
        } 
        else
            printf("'%s' is not a valid directory.\n", arg);
    } 
    else
        printf("usage: cd <directory>\n");
}

int main() 
{
    char dir[1024];
    char tilde[] = "~";
    char command[1024];
    const char *user = getenv("USER");
    bool first = true;

    system("clear");

    while (1)
    {
        get_dir(dir, sizeof(dir));

        print_prompt(user, dir);

        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0;

        char *arg = strtok(command, " ");

        if (arg != NULL) 
        {
            if (strcmp(arg, "cd") == 0)
                enter_directory(arg, first);
            else if (strcmp(arg, "exit") == 0)
                exit(EXIT_SUCCESS);
            else if (strcmp(arg, "ls") == 0)
                list_files(dir); 
            else 
                printf("Unknown command: %s\n", arg);

        }
    }

    return 0;
}
