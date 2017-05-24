#include <stdio.h>
#include <stdlib.h>

/*
TODO: Implement a function that concatenates 2 strings (dest and source).
The return value should be the concatenated strings.
*/
char *concat_strings(char *string1, int len1, char *string2, int len2);

int main()
{
    char string1[3] = "abc";
    char string2[4] = "defg";
    char *combined_string = concat_strings(string1, 3, string2, 4);
    return 0;
}

char *concat_strings(char *string1, int len1, char *string2, int len2)
{
    int len = len1 + len2;
    char new_string[len];
    for (int i = 0; i < len1; i++) {
        new_string[i] = string1[i];
        //printf("%c\n", new_string[i]); //for debugging
    }
    for (int j = 0; j < len2; j++) {
        new_string[j + len1] = string2[j];
        //printf("%c\n", new_string[j + len1]); //for debugging
    }
    return *new_string;
}
