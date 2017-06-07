#include <stdio.h>

int main()
{
    char char_array[] = {'a', 'b', 'c', 'd'};
    char char_array_the_same[] = "abcd";

    //TODO:
    // Print out the two arrays character-by-character
    int len = strlen(char_array_the_same);
    for (int i = 0; i < len; i++) {
        printf("%c\n", char_array[i]);
        printf("%c\n", char_array_the_same[i]);
    }
    //TODO:
    // What is the difference between the arrays?
    // Strings in "" have closing characters (a zero)

    return 0;
}
