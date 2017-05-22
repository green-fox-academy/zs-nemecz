//make it work
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int number = 1;
    int *pointer = &number;
    int choice;

    printf("\t**********\n\tHello User\n\t**********\nYou have an integer named 'number'\n");
    printf("- for it's memory address please press 1\n");
    printf("- for it's current value please press 2\n");
    printf("- to double it's value please press 3\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1 :
            printf("%p\n", pointer);
            break;
        case 2 :
            printf("%d\n", *pointer);
            break;
        case 3 :
            number *= 2;
            printf("%d\n", *pointer);
            break;
        default :
            printf("No such option\n");
            break;
    }

    return 0;
}
