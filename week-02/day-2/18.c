#include <stdio.h>
#include <stdint.h>

int main() {
	uint16_t number = 255;
	// if number can't be represented with 8bits
	// print 'longer than 8bits' otherwise print 'ok'

	if (number > 256) {

    printf("%d is longer than 8bits", number);

	} else {

	printf("OK");

	}

	return 0;
}
