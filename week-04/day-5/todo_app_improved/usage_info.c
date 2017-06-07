#include "todo_list.h"
char info[1000] = ("\0");
char usage[256];

void load_usage()
{
    FILE *fp;


    fp = fopen("usage.txt", "r");
    while(fgets(usage, 256, fp) != NULL) {
        strcat(info, usage);
    }
    fclose(fp);
}

void print_usage()
{
    printf("%s", info);
}
