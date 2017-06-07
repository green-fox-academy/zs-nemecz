#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// TODO:
// Create a struct called CircularBuffer
// It should store:
// A pointer that points to the start of a dynamically allocated array of ints (could be null) (head pointer)
// A pointer that points to the end of the dynamically allocated array of ints (could be null) (tail pointer)
// A pointer that points to the currently readable buffer item (could be null) (read pointer))
// A pointer that points to the currently writable buffer item (could be null) (write pointer)
// The lenght of the buffer

struct CircularBuffer {
    int *head_p;
    int *tail_p;
    int *read_p;
    int *write_p;
    int length;
};

// TODO:
// Create a function that returns a dynamically allocated CircularBuffer (the buffer itself should be allocated as well, not just the array inside)
// It should take a normal array and it's length as argument, and it should fill all the buffer values from the array
struct CircularBuffer *make_ring_buffer(int *array, int len);
// TODO:
// Create a function that resizes a CircularBuffer, it should take a CircularBuffer as a pointer and change that buffers length and reallocate it's array as well. (copying it's values)
struct CircularBuffer *resize_ring_buffer(struct CircularBuffer *ring_buffer, int new_len);
// TODO:
// Create a function that takes a CircularBuffer and returns a new CircularBuffer that only contains the even numbers from the old CircularBuffer
struct CircularBuffer *store_even_buffer(struct CircularBuffer *ring_buffer);
// TODO:
// Try all the functions in the main function, plase deallocate any buffer and the array inside it after using them


int main()
{
    int my_array[5] = {1, 6, 8, 4, 5};
    struct CircularBuffer *my_buffer = make_ring_buffer(my_array, 5);
    //test the buffer by printing head and tail
    printf("First element of the array in the buffer: %d\n", *(my_buffer->head_p));
    printf("Last element of the array in the buffer: %d\n\n", *(my_buffer->tail_p));

    //test the even number buffer function
    struct CircularBuffer *my_even_nmbr_buffer = store_even_buffer(my_buffer);
    printf("The first even number is: %d\n", *my_even_nmbr_buffer->head_p);
    printf("The last even number is: %d\n\n", *my_even_nmbr_buffer->tail_p);

    //test the resize function
    my_buffer = resize_ring_buffer(my_buffer, 8);
    printf("Bigger buffer - the memory address of the head: %d\n", (my_buffer->head_p));
    printf("Bigger buffer - the memory address of the tail: %d\n\n", (my_buffer->tail_p));

    free(my_even_nmbr_buffer);
    free(my_buffer);

    return 0;
}

struct CircularBuffer *make_ring_buffer(int *array, int len)
{
    int *buffer = (int*)calloc(len, sizeof(int));
    for (int i = 0; i < len; i++) {
        buffer[i] = array[i];
    }

    struct CircularBuffer *ring_buffer = (struct CircularBuffer*)malloc(sizeof(struct CircularBuffer));
    ring_buffer->head_p = buffer;
    ring_buffer->tail_p = &buffer[len - 1];
    ring_buffer->read_p = buffer;
    ring_buffer->write_p = buffer;
    ring_buffer->length = len;

    return ring_buffer;
}

struct CircularBuffer *resize_ring_buffer(struct CircularBuffer *ring_buffer, int new_len)
{
    int new_size = new_len * (sizeof(int));
    int read_index = ring_buffer->read_p - ring_buffer->head_p;
	int write_index = ring_buffer->write_p - ring_buffer->head_p;

    ring_buffer->head_p = realloc(ring_buffer->head_p, new_size);
    ring_buffer->write_p = &(ring_buffer->head_p[write_index]);
    ring_buffer->read_p = &(ring_buffer->head_p[read_index]);
    ring_buffer->tail_p = &(ring_buffer->head_p[new_len - 1]);
    ring_buffer->length = new_len;
    return ring_buffer;
};

struct CircularBuffer *store_even_buffer(struct CircularBuffer *ring_buffer)
{
    int length = ring_buffer->length;
    int stored_array[length];
    int *pointer = ring_buffer->head_p;
    int cntr = 0;

    //fill up stored array and count how many even numbers it has
    for (int i = 0; i < length; i++)
    {
        stored_array[i] = *pointer;
        //printf("%d\n", stored_array[i]);
        pointer++;
        if (stored_array[i] % 2 == 0)
            cntr++;
    }

    //allocate memory for even numbers
    int *even_numbers = (int*)calloc(cntr, sizeof(int));
    int k = 0;
    for (int j = 0; j < length; j++)
    {
        if (stored_array[j] % 2 == 0) {
            even_numbers[k] = stored_array[j];
            k++;
        }
    }

    //create buffer
     struct CircularBuffer *even_number_buffer = (struct CircularBuffer*)malloc(sizeof(struct CircularBuffer));
     even_number_buffer->head_p = &even_numbers[0];
     even_number_buffer->write_p = &even_numbers[0];
     even_number_buffer->read_p = &even_numbers[0];
     even_number_buffer->tail_p = &even_numbers[cntr - 1];
     even_number_buffer->length = cntr;

     return even_number_buffer;
};
