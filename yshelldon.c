#include "internal_commands.h"

int main(int argc, char *argv[]) {
    extern char **environ;  //inicializa o ambiente privado
    char atual[1024];
    getcwd(atual,sizeof(atual));    //PEGANDO A PASTA ATUAL COMO PATH
    strcat(atual,"/bin");   //SETANDO O /BIN
    //strcat(atual,":/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin");
    
    setenv("PATH",atual,1);  //seta nosso bin como path

    char title[100];
    char command[100];
    char* current_path = (char *)malloc(1024 * sizeof(char));
    char home[] = "/home/";
    strcat(current_path, home); strcat(current_path, getlogin()); // seta o path padrão para /home/user
    //char *model = get_model();

    //system("gcc ls.c -o ls");
    sprintf(title, "%s@bashinga⚡:~%s", getlogin(), current_path);
    printf("\033]0;%s\007", title);

    clearScreen();
    do{

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
            
            call_internal_command(command, current_path);

        }
    } while (strcmp(command, "\n") == 0);

    free(current_path); 
    return 0;   
}