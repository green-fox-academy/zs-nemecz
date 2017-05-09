#include <stdio.h>

int main() {
	float d = 125;

	// please divide by 5 d's value

	int c = 5 / d; // solution with decimal
	printf("new value is %d\n", c);

	float e = 5 / d;
    printf("new value is %.2f\n", e); //solution with float

	return 0;
}
