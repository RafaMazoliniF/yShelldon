#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

#define SIZE_COLUMN 15

void command_ls(char* current_path, char* arg, DIR* diretorio);
void command_ls_a(char* current_path, char* arg, DIR* diretorio);
//void command_ls_l(char* current_path, char* arg, DIR* diretorio);
//void command_ls_la(char* current_path, char* arg, DIR* diretorio);

int main(int argc, char *argv[]) {
    char* current_path = argv[1];
    int file_count = 0;
    char* arg = argv[2];

    DIR* diretorio = opendir(current_path);
    if (diretorio == NULL) {
        perror("fatal error: can not open directory");
        return 1;
    }

    //printf("%s\n%s\n%s\n", current_path, argv[1], arg);

    struct dirent *entrada;

    if (arg == NULL) {
        //printar todos os arquivos (menos ocultos)
        command_ls(current_path, arg, diretorio);
    }
    else if (strcmp(arg, "-a") == 0)
    {
        /*printar todos arquivos até ocultos*/
        command_ls_a(current_path, arg, diretorio);
    }
    else if (strcmp(arg, "-l") == 0)
    {
        /*printar todas as infos dos arquivos (menos ocultos)
        - permissões
        - links
        - proprietario do arquivoo
        - grupo do proprietario do arquivo
        - tamanho do arquivo em bytes
        - mes dia horario
        - nome_arquivo*/
    }
    else if ((strcmp(arg, "-la") == 0) || (strcmp(arg, "-al") == 0))
    {
        /*printar todas as infos dos arquivos
        - permissões
        - links
        - proprietario do arquivoo
        - grupo do proprietario do arquivo
        - tamanho do arquivo em bytes
        - mes dia horario
        - nome_arquivo*/
    }

    // Fecha e reabre o diretório para o segundo loop
    closedir(diretorio);

    printf("\n");

    return 0;
}

void command_ls (char* current_path, char* arg, DIR* diretorio) {
    struct dirent *entrada;
    int files_count = 0;

    while ((entrada = readdir(diretorio)) != NULL) {
        if (entrada->d_name[0] != '.' && strcmp(entrada->d_name, ".") != 0 && strcmp(entrada->d_name, "..") != 0) {
            if(entrada->d_type == DT_DIR) {            
                printf("\e[1;34m%-*s\e[0m", SIZE_COLUMN, entrada->d_name);
                files_count++;
            } else {
                printf("%-*s", SIZE_COLUMN, entrada->d_name);
                files_count++;
            }

            if (files_count == 5) {
                printf("\n");
                files_count = 0; 
            }
        }
    }    
}

void command_ls_a (char* current_path, char* arg, DIR* diretorio) {
    struct dirent *entrada;
    int files_count = 0;

    while ((entrada = readdir(diretorio)) != NULL) {
        if(entrada->d_type == DT_DIR) {            
            printf("\e[1;34m%-*s\e[0m", SIZE_COLUMN, entrada->d_name);
            files_count++;
        } else {
            printf("%-*s", SIZE_COLUMN, entrada->d_name);
            files_count++;
        }

        if (files_count == 5) {
            printf("\n");
            files_count = 0; 
        }
    }
}    


