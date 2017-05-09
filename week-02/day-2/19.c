#include <stdio.h>
#include <stdint.h>

int main() {
	uint64_t a = 654;
	uint64_t b = 654987312;
	// Tell if the reminder of b devided by a is 3

    if ((b % a) == 3) {

        printf("the reminder of %d devided by %d is 3", (int)b, (int)a);

    } else {

        printf("the reminder of %d devided by %d is not 3", (int)b, (int)a);

    }

	return 0;
}

