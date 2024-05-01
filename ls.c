#include <stdio.h>
#include <unistd.h>
#include <dirent.h>

int main(void){
    char cwd[1024]; //pega o nome do diretório -> ver com isaias se tem limite de caracters
    void* ptr; //ponteiro do diretório
    struct dirent *entrada; //inicializa a estrutura de dados dos diretórios -> perguntar pro isaias se isso pode

    ptr = getcwd(cwd, sizeof(cwd)); //salva o ponteiro do diretório

    DIR* diretorio = opendir(ptr); //a estrutura diretório, chamada diretorio abre o diretorio ptr (ponteiro)

    while ((entrada = readdir(diretorio)) != NULL) {    //enquanto o diretório apontar que tem alg coisa,
        printf("%s \t", entrada->d_name);                //printe o nome dos arquivos
    }

    closedir(diretorio);                                //fecha o uso do diretório.

    return 0;
}