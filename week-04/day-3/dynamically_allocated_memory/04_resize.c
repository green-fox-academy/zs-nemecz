#include <stdio.h>
#include <stdlib.h>

// TODO:
/**
 * Create a function called "resize" that takes a pointer to an int array, it's size and it's new size,
 * then it should return a new pointer that points to the new resized array.
 * It should copy all the elements to the new array, if the array is bigger it should fill all the new slots with zeros.
 * It should delete the old array.
 */
int *resize(int *array, int len, int new_len);
int main()
{
    int my_array[6] = {12, 4, 3, 4, 5, 67};
    int newlen = 8;
    int *new_array = resize(my_array, 6, newlen);
    for (int i = 0; i < newlen; i++) {
        printf("%d\t", new_array[i]);
    }

    //free the memory
    free(new_array);

    return 0;
}

int *resize(int *array, int len, int new_len)
{
    //allocate memory the size of the original array
    int* new_array = (int*)calloc(len, sizeof(int));

    //fill up with the elements of the array
    int i;
    for (i = 0; i < len; i++) {
        new_array[i] = array[i];
    }

    // get new size based on new length
    int size = new_len * sizeof(int);

    //allocate extra memory
    new_array = (int*)realloc(new_array, size);

    //fill up the remaining elements with zero-s
    for (i = len; i < new_len; i++) {
        new_array[i] = 0;
    }

    //delete old array
    free(array);

    return new_array;
}
