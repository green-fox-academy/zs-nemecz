#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
- generate a random number x: rand();
- make the user give an input: int user_input
- while or for loop with 5 lives
-

*/
int main()
{
    printf("Hello Player!\n");

    int x;
    int i, n;
    time_t t;

    n = 5;

    /* Intializes random number generator */
    srand((unsigned) time(&t));
    x = (rand() % 100);
    int lives = 5;
    int user_input;

    printf("%d\n", x); //print out the number for debugging
    //printf("%d", lives);
    printf("I've the number between 1-100. You have 5 lives.\n");

    while (lives != 0) {
        scanf("%d",&user_input);

        if (user_input < x){
            lives--;
            printf("Too low. You have %d lives left.\n", lives);
            if (lives == 0) {
                printf("You lost.");
            }
        } else if (user_input > x) {
            lives--;
            printf("Too high. You have %d lives left.\n", lives);
                if (lives == 0) {
                    printf("You lost.");
                }
        } else {
            lives = 0;
            printf("Congratulations. You won!");
        }
    }
    return 0;
}
