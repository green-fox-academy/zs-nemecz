#include <stdio.h>
#include <stdint.h>

int main() {
    uint8_t number = 254;
	uint8_t result;

	result = number + 23;
	// Check the result with printf

    printf("The result is: %d\n", result);

 	// What happened?!
	// Try again with different datatype
	uint16_t result_16 = number + 23;

	// Check the result with printf

    printf("The result_16 is: %d\n", result_16);

	// What happened and why?
    // We used an 8-bit integer to represent a value that can't be represented by 8-bits. This is called overflow.

	//----------------------------------------
	int8_t number_negative = number;

	// Check the result with printf

    printf("The number_negative is: %d\n", number_negative);

	// What happened and why?

    // We created a signed integer, where values range between - 128 and + 127.

    return 0;
}

