#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "internal_commands.h"

int main() {
    char command[100];
    printf("\x1b[H\x1b[J");

    while (1) {
    
        printf("rafael@bazinga~# ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0'; //Delete the \n character
        
        call_internal_command(command);

    }

    return 0;
}