#include <stdio.h>

int main() {
    int high_number = 6655;
    int low_number = 2;

    int* high_number_pointer = &low_number;
    int* low_number_pointer = &high_number;
    //TODO:
    // Please fix the problem and swap where the pointers point,
    // without using the "&" operator.
    int* fix_var = low_number_pointer;
    low_number_pointer = high_number_pointer;
    high_number_pointer = fix_var;

    printf("%p\n", &low_number);
    printf("%p\n", low_number_pointer);

    printf("\n%p\n", &high_number);
    printf("%p\n", high_number_pointer);

    return 0;
}
