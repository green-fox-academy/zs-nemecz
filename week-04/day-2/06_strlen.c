#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// TODO:
// Create a function which receives a string as parameter, and returns
// the numbers of characters in the string.
// Don't use the strlen() function!
int find_length(char *string);

int main()
{
    char string[6] = "abcdef";
    printf("%d", find_length(string));
    return 0;
}

int find_length(char *string)
{
    int j = 1;
    int i;
    for (i = 0; i < j; i++) {
        j++;
        if (string[i] == '\0') {
            j = 0;
        }
    }
    i -= 2;
    return i;
}
