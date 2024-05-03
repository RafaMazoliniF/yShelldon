// Clear the entire terminal
void clearScreen() {
    printf("\x1b[H\x1b[J"); //Clear screen
}

//Print the default user format
void printUserFormat(char current_path[]) {
    printf("\n\e[1;32m%s@bashinga⚡\e[0m:\e[1;34m~%s\e[0m$ ", getlogin(), current_path);
}
