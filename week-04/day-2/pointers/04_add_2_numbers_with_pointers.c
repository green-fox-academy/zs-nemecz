#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Add two numbers using pointers

*/


int main()
{

    int a  = 20;
    int b = 17;
    int *p_a = &a;
    int *p_b = &b;
    int c = *p_a + *p_b;
    printf("%d", c);

    return 0;
}
