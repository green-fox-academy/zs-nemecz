#include <stdio.h>

struct RectangularCuboid {
    double a;
    double b;
    double c;
};

// TODO:
// Write a function called "GetSurface" that takes a RectangularCuboid
// and returns it's surface
double GetSurface(struct RectangularCuboid cube);
// TODO:
// Write a function called "GetVolume" that takes a RectangularCuboid
// and returns it's volume
double GetVolume(struct RectangularCuboid cube);

int main() {
    struct RectangularCuboid rect = {1, 2, 3};
    GetSurface(rect);
    GetVolume(rect);

    return 0;
}

double GetSurface(struct RectangularCuboid cube) {
    double Surface;
    Surface = (2*cube.a*cube.b) + (2*cube.a*cube.c) + (2*cube.b*cube.c);
    printf("Surface\t%.2f", Surface);
    return Surface;
}

double GetVolume(struct RectangularCuboid cube) {
    double Volume;
    Volume = cube.a*cube.b*cube.c;
    printf("\nVolume\t%.2f", Volume);
    return Volume;
}
