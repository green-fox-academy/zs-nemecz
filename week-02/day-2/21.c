#include <stdio.h>
#include <stdint.h>

int main() {
	uint8_t ab = 123;
	uint8_t credits = 100;
	uint8_t is_bonus = 0;	// This means "false"

	// if credits are at least 50,
	// and is_bonus is false decrement ab by 2
	if ((credits >= 50) && (is_bonus == 0)) {

        ab += 2;

	}

	// if credits are smaller than 50,
	// and is_bonus is false decrement ab by 1
	else if ((credits <= 50) && (is_bonus == 0)) {

        ab -= 1;

	}


	// if is_bonus is true ab should remain the same
    else if (is_bonus == 1) {

        ab = ab;

	}

    // print result
    printf("%d\n", ab);

	return 0;
}
