/*
Create a program which ask for a name and an age.
From the age it tells the user when he or she will be 100 years old.
You should only take care of the years (don't bother with the months or days).
*/

#include <stdio.h>
#include <stdlib.h>

int main () {
    printf("Hello User! What's your name?\n");
    char name [100];
    gets(name);
    int age;
    int hundred_yrs_old;
    printf("What's your age?\n");
    scanf("%d", &age);
    hundred_yrs_old = 2017 + (100 - age);
    printf("You'll be a 100 years old in %d.", hundred_yrs_old);
    return 0;
}
