#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

int main(int argc, char *argv[]) {

    if (argc != 2 && argc != 5) {
        printf("usage: %s <oringin_file> ou %s <origin_file> > <destination_file>\n", argv[0], argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        perror("fatal error: cannot open origin file");
        return 1;
    }
    
    if (argc == 5 && strcmp(argv[2], ">") == 0) {
        char path_dest[100];

        sprintf(path_dest, "%s/%s", argv[4], argv[3]); 

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