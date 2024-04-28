#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

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
    printf("\e[1;32m%s@bashinga⚡\e[0m:\e[1;34m%s\e[0m$ ", user, dir);
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

        if (first) 
            print_prompt(user, tilde);
        else 
            print_prompt(user, dir);

        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0;

        char *token = strtok(command, " ");

        if (token != NULL) 
        {
            if (strcmp(token, "cd") == 0) 
            {
                token = strtok(NULL, " ");
                if (token != NULL) 
                {
                    if (chdir(token) == 0) 
                        first = false;
                    else
                        printf("Directory '%s' does not exist.\n", token);
                } 
                else 
                    printf("usage: cd <directory>\n");
            } 
            else if (strcmp(token, "exit") == 0) 
                exit(EXIT_SUCCESS);
            else 
                printf("Unknown command: %s\n", token);
        }
    }

    return 0;
}
