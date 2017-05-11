
#include <stdio.h>

int main() {
    int high_number = 2;
    int low_number = 6655;

    int* hight_number_pointer = &high_number;
    int* low_number_pointer = &low_number;
    //TODO:
    // Please fix the problem and swap the value of the variables,
    // without using the "high_number" and the "low_number" variables.
    int fix_high_number = *low_number_pointer;
    *low_number_pointer = *hight_number_pointer;
    printf("%d\n", low_number);

    *hight_number_pointer = fix_high_number;
    printf("%d\n", high_number);

    return 0;
}
