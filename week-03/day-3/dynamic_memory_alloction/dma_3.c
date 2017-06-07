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

int* powerRanger(int first, int end, int step);

int main() {
    int first = 8;
    int to = 23;
    int step = 2;

    int* address = powerRanger(first, to, step);
    printf("Address: %p\n", address);
    printf("Value: %d", *address);

    return 0;
}

int* powerRanger (int first, int end, int step) {
    int num_elements;
    if (end % 2 == 0) {
        num_elements = (end - first)/step;
    } else {
        num_elements = ((end + 1) - first)/step;
    }

    int value;
    int myArray[num_elements];
    int* pointer = &myArray;

    for (int i = 0; i < num_elements; i++){
        value = first + (i * step);
        myArray[i]  = value;
        printf("%d\n", value); //print array
    }
    return &myArray;
}
