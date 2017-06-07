#include <stdio.h>

struct Pirate {
    char name[256];
    int has_wooden_leg;
    short int gold_count;
};

// TODO:
// Create a function that takes an array of pirates (and it's length) then returns the sum of the golds of all pirate
int SumOfGolds (struct Pirate* array, int len){
        int val = 0;
        for (int i = 0; i < len; i++){
            //printf("%s has %d number of golds\r\n", array[i].name, array[i].gold_count);
             val = val + array[i].gold_count;
        }
    printf("The sum of gold coins is: %d\n", val);
    return val;
}
// TODO:
// Create a function that takes an array of pirates (and it's length) then returns the average of the gold / pirate
float AvarageOfGolds (struct Pirate* array, int len){
        int mean = 0;
        int val = 0;
        for (int i = 0; i < len; i++){
             val = val + array[i].gold_count;
        }
    mean = val/len;
    printf("The mean number of gold coins is: %d\n", mean);
    return mean;
}

// TODO:
// Create a function that takes an array of pirates (and it's length) then returns the name of the
// richest that has wooden leg

char* RichestPirate (struct Pirate* array, int len){
        int highest = 0;
        int counter = 0;
        for (int i = 0; i < len; i++){
           if ((array[i].gold_count > highest) && (array[i].has_wooden_leg == 1)){
                highest = array[i].gold_count;
                counter = i;
           }
        }
    printf("The richest pirate with a wooden leg is %s and he has %d gold coins\n", array[counter].name, highest);
    return array[counter].name;
}

int main() {
    struct Pirate pirates[] = {
        {"Jack", 0, 18},
        {"Uwe", 1, 8},
        {"Hook", 1, 12},
        {"Halloween kid", 0, 0},
        {"Sea Wolf", 1, 14},
        {"Morgan", 0, 1}
    };
    SumOfGolds(pirates, 6);
    AvarageOfGolds(pirates, 6);
    RichestPirate(pirates, 6);

    return 0;
}


