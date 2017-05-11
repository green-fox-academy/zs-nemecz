#include <stdio.h>

int main() {
    char char_array[] = {'a', 'b', 'c', 'd'};
    char char_array_the_same[] = "abcd";

	//TODO:
    // Print out the two arrays character-by-character
     for (int i = 0; i < sizeof(char_array); i++) {

        printf("%c\n", char_array[i]);
    }

        printf("\n");

     for (int i = 0; i < sizeof(char_array_the_same); i++) {

        printf("%c\n", char_array[i]);
    }
	//TODO:
    // What is the difference between the arrays?
    //One is defined char by char, and thus has no 0 at the end, while the second is a zero terminated string.

    return 0;
}
