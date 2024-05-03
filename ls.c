#include <stdio.h>
#include <unistd.h>
#include <dirent.h>

int main(int argc, char *argv[]){

    char* current_path = argv[1];   //recebe o current_path

    struct dirent *entrada; //inicializa a estrutura de dados dos diretórios -> perguntar pro isaias se isso pode

    DIR* diretorio = opendir(current_path); //a estrutura diretório, chamada diretorio abre o diretorio ptr (ponteiro)
    
    while ((entrada = readdir(diretorio)) != NULL) {    //enquanto o diretório apontar que tem alg coisa,
        printf("%s \t", entrada->d_name);                //printe o nome dos arquivos
    }

    closedir(diretorio);                                //fecha o uso do diretório.

    return 0;
}