#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// Clear the entire terminal
void clearScreen() {
    printf("\ec\e[3J");   //Clear screen
}

//Print the default user format
void printUserFormat(char current_path[]) {
    printf("\e[1;32m%s@bashinga⚡\e[0m:\e[1;34m~%s\e[0m$ ", getlogin(), current_path);
}
