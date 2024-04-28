// Clear the entire terminal
void clearScreen() {
    printf("\x1b[H\x1b[J"); //Clear screen
}

//Print the default user format
void printUserFormat(char current_path[]) {
    printf("%s\n", current_path);
    printf("rafael@bazinga~# ");
}