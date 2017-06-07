#include <stdio.h>

int main()
{
    int high_number = 2;
    int low_number = 6655;

    int* hight_number_pointer = &high_number;
    int* low_number_pointer = &low_number;
    int fix = *hight_number_pointer;
    printf("%p\n", hight_number_pointer);
    printf("%p\n", low_number_pointer);
    //TODO:
    // Please fix the problem and swap the value of the variables,
    // without using the "high_number" and the "low_number" variables.
    *hight_number_pointer = low_number;
    *low_number_pointer = fix;
    printf("high number: %d\n", high_number);
    printf("low number: %d\n", low_number);
    return 0;
}
