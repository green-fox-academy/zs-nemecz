#include <stdio.h>

enum car_type {VOLVO, TOYOTA, LAND_ROVER, TESLA};

struct car {
    enum car_type type;
    double km;
    double gas;
};

// TODO:
// Write a function that takes a Car as an argument and prints all it's stats
// If the car is a Tesla it should not print it's gas level
void print_car(struct car c);

int main()
{
    struct car my_car = {TESLA, 3, 4};
    struct car my_other_car = {VOLVO, 3, 4};
    print_car(my_other_car);
    return 0;
}

void print_car(struct car c)
{
    printf("%d\n", c.type);
    printf("%.2f\n", c.km);
    if (c.type != TESLA) {
        printf("%.2f\n", c.gas);
    }
}
