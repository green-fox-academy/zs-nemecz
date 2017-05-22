#include <stdio.h>
#include <stdlib.h>

/* Write a function which is called "get_fibonacci_number". It returns the "N"th
 * Fibonacci number, where "N" is received as a paramter.
 * For example:
 *  - get_fibonacci_number(1) returns 0
 *  - get_fibonacci_number(2) returns 1
 *  - get_fibonacci_number(3) returns 1
 *  - get_fibonacci_number(4) returns 2
 *  - get_fibonacci_number(5) returns 3
 *  - get_fibonacci_number(6) returns 5
 *
 *  If the function gets invalid parameter it returns -1.
 */

/*
Using that function create a program, which gets a number from the user, and
prints out the "N"th Fibonacci number, where "N" is the user given number.

Alert the user if he/she entered invalid value.
*/
int get_fibonacci_number (int n);

int main()
{
    printf("%d\n", get_fibonacci_number(6));
    return 0;
}

int get_fibonacci_number (int n) {
    int n_fib;
    int a = 0;
    int b = 1;
    if (n < 1) {
        return -1;
    } else if (n == 1 ) {
        return 0;
    } else if (n == 2 ){
        return 1;
    } else {
        for (int i = 2; i < n; i++) {
            n_fib = a + b;
            a = b;
            b = n_fib;
        }
        return n_fib;
    }
}
