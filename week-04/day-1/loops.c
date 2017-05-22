/*
Create a program which writes down the following sentence 100 times:
"I won't cheat on the test!"

Do it with:
    - for loop
    - while loop
    - do while loop

Also create a funtion which does the same.
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    for (int i = 0; i < 100; i++) {
        printf("%d. I won't cheat on the test!\n", i);
    }

    int count;
    while (1) {
        printf("%d. I won't cheat on the test!\n", count);
        count++;
        if (count == 100) {
            break;
        }
    }

    count = 0;
    do {
        printf("%d. I won't cheat on the test!\n", count);
        count++;
        if (count == 100) {
            break;
        }
    } while (1);

    return 0;
}
