#include <stdio.h>

int main() {
    int numbers[] = {5, 6, 7, 8, 9};
    int* number_pointer;
    //TODO:
    // The "number_pointer" should point to the first element of the array called "numbers",
    // than please print its value with it.
    number_pointer = &numbers[0];

    printf("%d\n", *number_pointer); // value
    printf("%p", number_pointer); // address

    return 0;
}
