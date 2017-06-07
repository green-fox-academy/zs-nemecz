#include "todo_list.h"

void print_usage()
{
    FILE *fp;
    char usage[256];

    fp = fopen("usage.txt", "r");
    while(fgets(usage, 256, fp) != NULL) {
        usage[strlen(usage)-1] = '\0';
        printf("%s\n", usage);
    }
    fclose(fp);
}
