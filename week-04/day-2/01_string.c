#include <stdio.h>
#include <string.h>

int main()
{
    char my_name_array[] = "My Name";

    //TODO:
    // Print out the array character-by-character
    int len = strlen(my_name_array);
    for (int i = 0; i < len; i++) {
        printf("%c\n", my_name_array[i]);
    }
    return 0;
}
