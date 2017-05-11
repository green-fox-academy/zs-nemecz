
#include <stdio.h>

int main() {
    char buffer[255];   // Buffer variable for user input

    //TODO:
    // Get the user's name with gets
    printf("Pleae give your name: \t");
    gets(buffer);
    //TODO:
    // Print it out with puts
    puts(buffer);
    //TODO:
    // Get the user's pet name with getch
    printf("Please give your pet's name: \t");
    int c;
    c = getch();

    //TODO:
    // Print it out
    putchar (c);

    return 0;
}
