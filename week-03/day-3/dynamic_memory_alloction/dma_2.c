#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO:
// Please create a program that asks for a count when it starts.
// It should ask for a number count times, then it should print the average of the numbers.
// It should delete any dynamically allocated resource before the program exits.
void dymanic_Avarage ();

int main() {
    dymanic_Avarage ();

    return 0;
}

void dymanic_Avarage () {
    int input;
    int value;
    float avarage = 0;
    printf("How many numbers will you give?\n");
    scanf ("%d",&input);
    int* pointer = NULL;

    pointer = (int*)calloc(input,sizeof(int));
    for (int i = 0; i < input; i++){
        printf("Please give the %d. number\n", i+1);
        scanf ("%d",&value);
        *pointer  = value;
        avarage = avarage + (float)value;
        //printf("%d\n", *pointer); //only for debugging
        pointer++;
    }

    avarage = avarage/(float)input;
    printf("%.2f", avarage);

    free(pointer);
    //printf("%d"; *pointer); //check whether mem is free
}
