#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
  uint8_t* pointer = NULL;

  // TODO:
  // Please allocate a 5 long array and fill it with numbers from 0 to 4, then print the whole array
  // Please delete the array before the program exits
  pointer = (uint8_t*)calloc(5,sizeof(uint8_t));
  for (uint8_t i; i < 5; i++){
        *pointer  = 0 + i;
        printf("%d\n", *pointer);
        pointer++;
  }
  free(pointer);
  return 0;
}
