#include <stdio.h>
#include <stdlib.h>

// TODO:
// Create a function that takes a double array as a parameter, and the length of the array.
// This function should calculate the avarage of the elements.
double element_average(double *a, int len);
// TODO:
// Create an other function that takes a double array as a parameter, and the length of the array.
// It calculates how much elements are under the avarage, and returns with that.
int count_under_avrg(double *a, int len);
// TODO:
// Create an other function that takes a double array as a parameter, and the length of the array.
// It allocates a new array, and loads into it the elements which are under the average.
// It returns a pointer to the new array.
double *numbers_under_avrg(double *a, int len);

int main()
{
    double array[3];
    array[0] = 2.6;
    array[1] = 1.5;
    array[2] = 1.7;
    printf("%.2f\n", element_average(array, 3));
    printf("%d\n", count_under_avrg(array, 3));
    printf("%.2f\n", *numbers_under_avrg(array, 3));
    printf("%p\n", numbers_under_avrg(array, 3));
    return 0;
}

double element_average(double *a, int len)
{
    double val;
    for (int i = 0; i < len; i++) {
        val += a[i];
        //printf("%.2f\n", val); //for debugging
    }
    val /= (double)len;
    return val;
}

int count_under_avrg(double *a, int len)
{
    int count = 0;
    double mean = element_average(a, len);
    for (int i = 0; i < len; i++) {
        if (a[i] < mean)
            count++;
    }
    return count;
}

double *numbers_under_avrg(double *a, int len)
{
    int new_len = count_under_avrg(a, len);
    double mean = element_average(a, len);
    double *new_array = (double*) calloc (new_len, sizeof(double));
    int j = 0;
    for (int i = 0; i < new_len; i++) {
        if (a[i] < mean) {
            new_array[j] = a[i];
            j++;
        }
    }
    return new_array;
}
