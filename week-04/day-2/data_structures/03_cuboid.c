#include <stdio.h>

struct rectangular_cuboid {
    double a;
    double b;
    double c;
};

// TODO:
// Write a function called "GetSurface" that takes a RectangularCuboid
// and returns it's surface
double get_surface(struct rectangular_cuboid c);
// TODO:
// Write a function called "GetVolume" that takes a RectangularCuboid
// and returns it's volume
double get_volume(struct rectangular_cuboid c);

int main()
{
    struct rectangular_cuboid cuboid = {2.1, 3.0, 2.0};
    printf("%.3f\n", get_surface(cuboid));
    printf("%.3f", get_volume(cuboid));
    return 0;
}

double get_surface(struct rectangular_cuboid c)
{
    double surface = (2 * c.a * c.b) + (2 * c.b * c.c) + (2 * c.a * c.c);
    return surface;
}

double get_volume(struct rectangular_cuboid c)
{
    double volume = c.a * c.b *c.c;
    return volume;
}
