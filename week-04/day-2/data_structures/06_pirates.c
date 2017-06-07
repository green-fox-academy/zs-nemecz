#include <stdio.h>

struct pirate {
    char name[256];
    int has_wooden_leg;
    short int gold_count;
};

// TODO:
// Create a function that takes an array of pirates (and it's length) then returns the sum of the golds of all pirates
int sum_of_golds(struct pirate *p, int len);
// TODO:
// Create a function that takes an array of pirates (and it's length) then returns the average of the gold / pirate
float mean_of_golds(struct pirate *p, int len);
// TODO:
// Create a function that takes an array of pirates (and it's length) then returns the name of the
//richest that has wooden leg
char *richest_pirate(struct pirate *p, int len);

int main()
{
    struct pirate pirates[] = {
        {"Jack", 0, 18},
        {"Uwe", 1, 8},
        {"Hook", 1, 12},
        {"Halloween kid", 0, 0},
        {"Sea Wolf", 1, 14},
        {"Morgan", 0, 1}
    };

    printf("%d\n", sum_of_golds(pirates, 6));
    printf("%.2f\n", mean_of_golds(pirates, 6));
    printf("%s\n", richest_pirate(pirates, 6));
    return 0;
}

int sum_of_golds(struct pirate *p, int len)
{
    int gold = 0;
    for (int i = 0; i < len; i++) {
        gold += p[i].gold_count;
    }
    //printf("%d\n", gold);
    return gold;
}

float mean_of_golds(struct pirate *p, int len)
{
    float mean = ((float)sum_of_golds(p, len))/(float)len;
    return mean;
}

char *richest_pirate(struct pirate *p, int len)
{
    int most_gold = 0;
    int rich_i = 0;
    for (int i = 0; i < len; i++) {
            if ((p[i].has_wooden_leg == 1) && (p[i].gold_count > most_gold)) {
                most_gold = p[i].gold_count;
                rich_i = i;
            }
    }
    //printf("%d\n", most_gold);

    return (p[rich_i].name);
}
