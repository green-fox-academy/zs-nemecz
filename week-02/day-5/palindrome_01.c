#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Palindrome_Gen ();

int main(){
    Palindrome_Gen();
    return 0;
}

void Palindrome_Gen (){

    char word[255];
    printf("Please give a word: ");
    gets(word);
    int string_len = strlen(word);
    int string_index = string_len - 1;
    //printf("\nstring length is: %d", strlen(word)); // check string len for debugging
    char palindrome [string_len];

    for (int i = 0; i < string_len; i++) {
        palindrome[i] = word[string_index];
        string_index--;
    }
    printf("\nYour palindrome is: ");
    for (int i = 0; i < string_len; i++) {
        putch(palindrome[i]);
    }
    return;
}
