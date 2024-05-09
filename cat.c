#include <stdio.h>
#include <string.h>
#include <errno.h>

#define MAX_LINE_LENGTH 1024

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s [file1] [file2] ...\n", argv[0]);
        return 1;
        
    } else {
        for (int i = 1; i < argc; i++) {
            FILE *file = fopen(argv[i], "r");
            if (file == NULL) {
                printf("Error opening file '%s': %s\n", argv[i], strerror(errno));
            } else {
                printf("File: %s\n", argv[i]);
                char line[MAX_LINE_LENGTH];
                while (fgets(line, sizeof(line), file) != NULL) {
                    printf("%s", line);
                }
                fclose(file);
            }
        }
    }
    return 0;
}
