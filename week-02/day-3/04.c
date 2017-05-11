#include <stdio.h>

/* Write a non void function which has a paramters (let's say for example x).
The funtion than returns the "xth" fibonaci number.
What the hack is a fibonacci number? Search it on wikipedia!
*/
int Fibonacci(int x);

int main(){

    int fib = 21;

    if (fib > 0) {

        printf("The %d. number in the Fibonacci pattern is:\n", fib);

    }

    Fibonacci(fib);

    return 0;
}


int Fibonacci(int x) {

    int i;
    int a = 0;
    int b = 1;
    int fibX = 0;
    if (x == 0) {

        printf("Please give a number bigger than 0.");
    } else if (x == 1){

        fibX = 0;
        printf("%d\n", fibX);

    } else if (x == 2){

        fibX = 1;
        printf("%d\n", fibX);

    } else {

        for (i = 2; i < x; i++) {

        fibX = a + b;
        a = b;
        b = fibX;

        }
        printf("%d\n", fibX);
    }
   return fibX;
}
