#include <stdio.h>

void safe_union(int *a, int l_a, int *b, int l_b, int *result, int l_res)
{
    for (int i = 0; i < l_a; i++) {
        result[i] = a[i];
    }
    for (int j = 0; j < l_b; j++) {
        result[j + l_a] = b[j];
    }
    return;
}

int main(int argc, char** argv)
{
    int a[3] = {1,2,3};
    int b[4] = {4,5,6,7};
    int c[7];
    safe_union(a,3,b,4,c,7);
    for (int i = 0; i<7; i++) {
        printf("%d\n", c[i]);
    }
    return 0;
}
