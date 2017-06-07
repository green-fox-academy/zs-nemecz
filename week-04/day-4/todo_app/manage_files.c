#include "todo_list.h"

int write_file(list_t *a_list, char *path)
{
    if (a_list == NULL || path == NULL)
        return -1;

    FILE *file = fopen(path, "w");
    if (file == NULL)
        return -1;
    for (int i = 0; i < a_list->task_cnt; i++) {
        fprintf(file, "%d\t%s\n", a_list->task[i].num, a_list->task[i].todo);
    }

    fclose(file);
    return 0;
}

int read_file(list_t *a_list, char *path)
{
    if (a_list == NULL || path == NULL)
        return -1;

    FILE *file = fopen(path, "r");
    if (file == NULL)
        return -1;

    char todo[TODO_LEN];
    int num;

    while(fscanf(file, "%d %s\n", &num, todo) == 2) {
        add_task(a_list, todo);
    }

    fclose(file);
    return 0;
}
