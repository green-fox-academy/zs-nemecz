#include <stdio.h>

int main()
{
    int int_array[] = {1, 654, 987, 654, 31};
    float float_array[] = {1.2, 3.14, 1.41, 0.707, 1.73};

    //TODO:
    // Print out the content of the arrays
    int len = sizeof(int_array)/sizeof(int_array[0]);
    for (int i = 0; i < len; i++) {
        printf("%d", int_array[i]);
        printf("\t%.2f\n", float_array[i]);
    }
    return 0;
}
