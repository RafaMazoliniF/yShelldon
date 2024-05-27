#include "internal_commands.h"

int main(int argc, char *argv[]) {
    extern char **environ;  //inicializa o ambiente privado
    char atual[1024];
    getcwd(atual,sizeof(atual));    //PEGANDO A PASTA ATUAL COMO PATH
    strcat(atual,"/bin");   //SETANDO O /BIN
    //strcat(atual,":/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin");
    
    setenv("PATH", atual, 1);  //seta nosso bin como path

    char title[100];
    char command[100];
    char permissions[] = "0770";
    char* current_path = (char *)malloc(1024 * sizeof(char));
    char home[] = "/home/";
    strcat(current_path, home); strcat(current_path, getlogin()); // seta o path padrão para /home/user

    sprintf(title, "%s@bashinga⚡", getlogin());
    printf("\033]0;%s\007", title);
    clearScreen();
    
    if (argc >= 2) {   
        char line[100];
        char ch;

        FILE *file = fopen(argv[1], "r");               
        if (file == NULL) {
            printf("fatal error: cannot open file '%s'\n", argv[1]);
            // free(current_path);
            // return 1;
        } else {
            while (fgets(line, sizeof(line), file) != NULL) {
                line[strcspn(line, "\n")] = '\0';

                printf("\e[1;33m%s\e[0m", line);
                printf("\n");

                call_internal_command(line, current_path);
            }

            fclose(file);
        }
    }

    while (true) {
        printUserFormat(current_path);

        if (fgets(command, sizeof(command), stdin) == NULL) {
            break; 
        } 
        else if (strcmp(command, "\n") == 0) {
            continue;
        }

        command[strcspn(command, "\n")] = '\0'; 
        
        call_internal_command(command, current_path);
    }
    free(current_path); 
    return 0;   
}