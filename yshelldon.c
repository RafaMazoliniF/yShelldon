#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    while (1) {
        char command[100];

        printf("\x1b[H\x1b[J");
        printf("bazinga# ");
        fgets(command, sizeof(command), stdin);
    }

    return 0;
}