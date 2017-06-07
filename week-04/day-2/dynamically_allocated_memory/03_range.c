#include <stdio.h>
#include <stdlib.h>

/** TODO:
 * Create a function called "range" that creates a new array and returns a pointer to it.
 * It should fill the array with numbers based on it's paramters.
 * It should take 3 paramters:
 * int from: the first number in the array
 * int to: it will fill the array till it would reach this number (so this number is not in the array)
 * int step: the step between the numbers
 *
 * Examples:
 * range(0, 10, 2) -> {0, 2, 4, 6, 8}
 * range(1, -8, -3) -> {1, -2, -5}
 *
 * It should delete any dynamically allocated resource before the program exits.
 */
int *range(int first, int upto, int step);

int main()
{
    int* array1 = range(0, 10, 2);
    for (int i = 0; i < 5; i++) {
        printf("%d\n", array1[i]);
    }
    return 0;
}

int *range(int first, int upto, int step)
{
    int len;
    len = (upto - first) / step;
    if (upto % 2 != 0)
        len++;
    int *array = (int*)calloc(len, sizeof(int));
    for (int i = 0; i < len; i++) {
        array[i] = first + (step * i);
        //printf("%d\t", array[i]);
    }
    return array;
}
