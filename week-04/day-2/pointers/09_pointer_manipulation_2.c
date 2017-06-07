#include <stdio.h>

int main()
{
    int high_number = 6655;
    int low_number = 2;

    int* hight_number_pointer = &low_number;
    int* low_number_pointer = &high_number;
    int* fix = hight_number_pointer;
    hight_number_pointer = low_number_pointer;
    low_number_pointer = fix;
    //TODO:
    // Please fix the problem and swap where the pointers point,
    // without using the "&" operator.
    printf("low number - %p:\t %d\n", &low_number, low_number);
    printf("low number - %p:\t %d\n\n", low_number_pointer, low_number);
    printf("high number - %p:\t %d\n", &high_number, high_number);
    printf("high number - %p:\t %d\n", hight_number_pointer, high_number);
    return 0;
}
