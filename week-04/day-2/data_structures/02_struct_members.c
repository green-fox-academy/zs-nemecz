#include <stdio.h>
#include <stdint.h>

struct computer {
    float cpu_speed_GHz;
    int ram_size_GB;
    int bits;
};

int main()
{
    struct computer comp = {3.2, 8, 32};

    //TODO: Change the bits to 64
    comp.bits = 64;
    //TODO: print out the structure members
    printf("cpu_speed_GHz: %.2f\n", comp.cpu_speed_GHz);
    printf("ram_size_GB: %d\n", comp.ram_size_GB);
    printf("bits: %d\n", comp.bits);
    return 0;
}
