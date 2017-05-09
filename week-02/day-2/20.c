#include <stdio.h>
#include <stdint.h>

int main() {
	uint8_t z = 13;

	// if z is between 10 and 20 print 'Sweet!'
    if ((z >= 10) && (z <= 20))  {

        printf("Sweet!");

	}
	// if less than 10 print 'More!',
	else if (z < 10) {

        printf("More!");

	}

	// if more than 20 print 'Less!'
	else if (z > 20) {

        printf("More!");

    }


	return 0;
}
