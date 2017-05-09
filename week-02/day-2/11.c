#include <stdio.h>

  int main() {
 	int k = 1521;
 	// tell if k is dividable by 3 or 5
    if (((k % 3) == 0) || ((k % 5) == 0)) {
        printf("%d is dividable by 3 or 5\n", k);
    }else {
        printf("%d is not dividable by 0 or 5 \n", k);
    }

 	int b = 100;
 	// make it smaller by 7
    b -= 100;
    printf("new value is %d \n", b);

  	return 0;
  }
