#include <stdio.h>
#include <stdlib.h>

/*
Write a program which receives a number between 0-10 from the user.
It prints out the english word for that number on the screen.
For example if the user enters 8, the program prints out "Eight".

Use switch-case in this task!
Handle the invalid user input!
*/

int main () {
    int num = 6;
    switch (num) {
        case 1 :
            printf("ONE\n");
            break;
        case 2 :
            printf("TWO\n");
            break;
        case 3 :
            printf("THREE\n");
            break;
        case 4 :
            printf("FOUR\n");
            break;
        case 5 :
            printf("FIVE\n");
            break;
        case 6 :
            printf("SIX\n");
            break;
        case 7 :
            printf("SEVEN\n");
            break;
        case 8 :
            printf("EIGHT\n");
            break;
        case 9 :
            printf("NINE\n");
            break;
        case 10 :
            printf("TEN\n");
            break;
        default :
            printf("Invalid number\n");
            break;
    }
    return 0;
}
