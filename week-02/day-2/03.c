#include <stdio.h>

int main() {
	int c = 44;
	// please double c's value

	// solution with multiplying
	//c *= 2;

	//solution with shifting
	c <<= 1;
	//print the new value
	printf("new value is %d\n", c);

	return 0;
}
