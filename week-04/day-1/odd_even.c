/*
Write a program that reads a number form the standard input,
than prints "Odd" if the number is odd, or "Even" it it is even.
*/

#include <stdio.h>
#include <stdlib.h>

int odd_even (int x);

int main(){
    int num = 8;
    odd_even(num);
    return 0;
}

int odd_even (int x){
    if (x % 2 == 0.0){
        printf("EVEN\n");
        return 0;
    } else {
        printf("ODD\n");
        return 1;
    }
}
