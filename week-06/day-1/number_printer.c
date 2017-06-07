#include <stdio.h>
#include <stdint.h>

void printf_numbers(unsigned long from, unsigned long to) //
{
	for (unsigned long i = from; i < to; i++) {
		printf("%lu\n", i);
	}
}

int main()
{
	printf_numbers(2147483600, 2147484600); //max value for int is +2147483647 2147484600
	return 0;
}
