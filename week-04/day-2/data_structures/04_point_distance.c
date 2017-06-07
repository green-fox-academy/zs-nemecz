#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x;
    int y;
} point_t;

// TODO:
// Create a function the constructs a Point (returns a pointer to a new point)
// It should take it's x and y coordinate as parameter
point_t *points(int x, int y);
// TODO:
// Create a function that takes 2 Points as a pointer and returns the distance between them
float point_distance(point_t *j, point_t *k);

int main()
{
    point_t p1 = {2, 3};
    point_t *pP1 = &p1;
    point_t p2 = {4, 2};
    point_t *pP2 = &p2;
    point_t *new_point = points(4, 9);
    printf("%d", new_point->y);
    //printf("%.2f", point_distance(pP1, pP2));
    return 0;
}

point_t *points(int x, int y)
{
    point_t* point = (point_t*)malloc(sizeof(point_t));
    point->x = x;
    point->y = y;
    return point;
}

float point_distance(point_t *j, point_t *k)
{
    float a;
    float b;
    float c;

    int x1 = j->x;
    int x2 = k->x;

    int y1 = j->y;
    int y2 = k->y;

    a = x1 - x2;
    b = y1 - y2;
    float a_sqr = a * a;
    float b_sqr = b * b;
    float c_sqr = a_sqr + b_sqr;
    c = sqrt(c_sqr);

    return c;
}
