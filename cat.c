#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h>

int main(int argc, char *argv[]) {
    //arvg0 = nome, argv1 = current_path, argv2 = nome do arquivo, argv3 = >, argv4 = nome do arquivo2

    if (argc != 3 && argc != 5) {
        printf("usage: %s <oringin_file> or %s <origin_file> > <destination_file>\n", argv[0], argv[0]);
        return 1;
    }
    
    char* current_path = argv[1];

    if (chdir(current_path) != 0) {
    perror("chdir");
    return 1;
    }

    FILE *file = fopen(argv[2], "rb");
    if (file == NULL) {
        perror("fatal error: cannot open origin file");
        return 1;
    }
    
    if (argc == 5 && strcmp(argv[3], ">") == 0) {
        char path_dest[100];

        sprintf(path_dest, "%s/%s", argv[1], argv[4]); 

        FILE *destFile = fopen(path_dest, "wb");
        if (destFile == NULL) {
            perror("fatal error: cannot open destination file");
            fclose(file);
            return 1;
        }

        int ch;
        while ((ch = fgetc(file)) != EOF) {
            fputc(ch, destFile);
        }

        fclose(destFile);

    } else { 
        int ch;
        while ((ch = fgetc(file)) != EOF) {
            putchar(ch);
        }
    }

    fclose(file);

    return 0;
}