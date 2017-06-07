#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Print out the addresses with and without pointer
print out the values with and without pointer
 */


int main()
{
    int number = 2017;
    int *pnumber = &number;
    float Pi = 3.14;
    float *pPi = &Pi;
    char letter = 't';
    char *pletter = &letter;
    //***print addresses***//
    printf("%p\t", &number);
    printf("%p\n", pnumber);
    printf("%p\t", &Pi);
    printf("%p\n", pPi);
    printf("%p\t", &letter);
    printf("%p\n", pletter);
    //***print values***//
    printf("%d\t", number);
    printf("%d\n", *pnumber);
    printf("%.2f\t", Pi);
    printf("%.2f\n", *pPi);
    printf("%c\t", letter);
    printf("%c\n", *pletter);

    return 0;
}
