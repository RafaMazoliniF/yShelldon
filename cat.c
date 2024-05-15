#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para a função strcmp()

int main(int argc, char *argv[]) {
    // Verifica se foi fornecido um arquivo como argumento
    if (argc != 2 && argc != 5) {
        printf("Uso: %s <arquivo_origem> ou %s <arquivo_origem> > <arquivo_destino>\n", argv[0], argv[0]);
        return 1;
    }

    // Abre o arquivo de origem para leitura binária
    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo de origem");
        return 1;
    }
    // Se houver redirecionamento para um novo arquivo
    if (argc == 5 && strcmp(argv[2], ">") == 0) {
        char path_dest[100]; // Supondo que o caminho do diretório não exceda 100 caracteres
        sprintf(path_dest, "%s/%s", argv[4], argv[3]); // Substitua "caminho/para/seu/diretorio" pelo diretório desejado
        FILE *destFile = fopen(path_dest, "wb");
        if (destFile == NULL) {
            perror("Erro ao criar o arquivo de destino");
            fclose(file);
            return 1;
        }

        // Lê o conteúdo do arquivo de origem e escreve no arquivo de destino
        int ch;
        while ((ch = fgetc(file)) != EOF) {
            fputc(ch, destFile);
        }

        // Fecha o arquivo de destino
        fclose(destFile);
    } else { // Se não houver redirecionamento, imprime na saída padrão
        // Lê e imprime o conteúdo do arquivo de origem
        int ch;
        while ((ch = fgetc(file)) != EOF) {
            putchar(ch);
        }
    }

    // Fecha o arquivo de origem
    fclose(file);

    return 0;
}
