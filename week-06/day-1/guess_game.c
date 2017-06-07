#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//project-guessing-game
//Note: the program gets harder, when you set a lower range

int main()
{
	int x, y;
	int count = 0;
	int guess = 0;
	int rand_max;
	int rand_min;
	printf("please add the minimum number!\n");
	scanf("%d", &rand_min);
	printf("please add the maximum number!\n");
	scanf("%d", &rand_max);
	srand(time(NULL));
	int rand_num = rand() % (rand_max + 1 - rand_min) + rand_min;
	y = rand_max - rand_min;
	x = log10(y) / log10(2);

	printf("I have a number between %d and %d. You have %d lives\n", rand_min, rand_max, x);

    while (1) {
        scanf("%d", &guess);
        if (guess == rand_num) {
            printf("Yeeeeey, you did well! It took you %d tires!", count + 1);
            break;
        } else if (guess > rand_num) {
            x--;
            printf("Too big, You have %d, lives left\n", x);
        } else {
            x--;
            printf("Too low, You have %d lives left\n", x);
        }
        if (x == 0) {
            printf("You have used all your lives!");
            break;
        }
        count++;
    }

	return 0;
}
