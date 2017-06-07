#include <stdio.h>

int main()
{
    int numbers[] = {5, 6, 7, 8, 9};
    int* number_pointer = &numbers[2];
    //TODO:
    // The "number_pointer" should point to the third element of the array called "numbers",
    // than please print its value with it. Solve the problem without reusiong the "&" operator
    // for geting the address of the third element.
    printf("%d\t", *number_pointer);
    return 0;
}
