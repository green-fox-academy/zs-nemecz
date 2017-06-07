#include <stdio.h>
#include <stdlib.h>

// TODO:
// Please create a program that asks for a count when it starts.
// It should ask for a number count times, then it shoud print the average of the numbers.
// It should delete any dynamically allocated resource before the program exits.

int main()
{
    printf("How many numbers will you give?\n");
    int input;
    scanf("%d", &input);
    int *array = (int*)calloc(input, sizeof(int));
    float mean_val = 0;
    float val;
    for (int i = 0; i < input; i++) {
        printf("numer %d:\n ", i+1);
        scanf("%f", &val);
        array[i] = val;
        mean_val += val;
    }
    mean_val /= (float)input;
    printf("The mean of these numbers is: %.2f\n", mean_val);
    return 0;
}
