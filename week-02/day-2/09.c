#include <stdio.h>

int main() {
	int i = 53625;
	// tell if it has 11 as a divisor
	/* test with another value
	int i = 10;
	*/

	if ((i % 11) == 0) {

        printf("%d has 11 as a divisor.", i);

	} else {

        printf("%d does not have 11 as a divisor.", i);

	}

	return 0;
}
