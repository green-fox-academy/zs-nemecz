#include <stdio.h>
#include <string.h>

enum CarType {VOLVO, TOYOTA, LAND_ROVER, TESLA};

struct Car {
  enum CarType type;
  double km;
  double gas;
};

// TODO:
// Write a function that takes a Car as an argument and prints all it's stats
// If the car is a Tesla it should not print it's gas level
//void PrintCar(struct Car car);

int main() {
    struct Car car1;
    car1.gas = 3.2;
    car1.km = 4.2;
    car1.type = TOYOTA;
    PrintCar(car1);
    return 0;
}

void PrintCar(struct Car car){
    if (car.type == TESLA) {
        printf("%d\n", car.type);
        printf("%.2f\n", car.km);
    } else {
        printf("%d\n", car.type);
        printf("%.2f\n", car.km);
        printf("%.2f\n", car.gas);
    }
    return;
}
