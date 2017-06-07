#include "todo_list.h"

list_t *init_list(int list_num)
{
    list_t *new_list = (list_t*)malloc(sizeof(list_t));
    task_t *task_memory = NULL;
    new_list->list_num = list_num;
    new_list->task = task_memory;
    new_list->task_cnt = 0;

    return new_list;
}

int add_task(list_t *a_list, char *new_todo)
{
        a_list->task_cnt++;
        //printf("task count changed: %d\n", a_list->task_cnt);
        int task_index = a_list->task_cnt - 1;
        int new_size = ((a_list->task_cnt) * (sizeof(task_t)));
        a_list->task = realloc(a_list->task, new_size);
        a_list->task[task_index].num = a_list->task_cnt;
        a_list->task[task_index].check = 0;
        a_list->task[task_index].priority = 0;
        strcpy(a_list->task[task_index].todo, new_todo);

        return 0;
}

void print_tasks(list_t *a_list)
{
    if (a_list->task_cnt != 0) {
        int len = a_list->task_cnt;
        printf("List by number\n");
        printf("====================\n");
        printf("Num\t|\tTasks\t|\tPrio\n");

        for (int i = 0; i < len; i++) {
            if (a_list->task[i].priority != 0) {
                if (a_list->task[i].check > 0) {
                    printf("%d -  [X] %s \t-%d\n", a_list->task[i].num, a_list->task[i].todo, a_list->task[i].priority);
                } else if (a_list->task[i].check == 0) {
                    printf("%d -  [ ] %s \t-%d\n", a_list->task[i].num, a_list->task[i].todo, a_list->task[i].priority);
                }
            } else {
                if (a_list->task[i].check == 1) {
                    printf("%d -  [X] %s   \n", a_list->task[i].num, a_list->task[i].todo);
                } else {
                    printf("%d -  [ ] %s   \n", a_list->task[i].num, a_list->task[i].todo);
                }
            }
        }

    } else {
        printf("There are no tasks for today. :)\n");
    }
}

int list_empty(list_t *a_list)
{
    if (a_list->task_cnt != 0) {
        free(a_list->task);
        a_list->task_cnt = 0;
    }
    printf("There are no tasks for today. :)\n");

    return 0;
}

int list_remove(list_t *a_list)
{
    if (a_list->task_cnt != 0) {
        free(a_list->task);
        printf("List deleted.\n");
    }
    //free(a_list); //WHY WOULD YOU WANT TO REMOVE THE WHOLE STRUCTURE

    return 0;
}

int task_remove(list_t *a_list, int task_num)
{
    int len = a_list->task_cnt;
    int i;
    int j;
    for (i = 0; i < len; i++) {
        if (a_list->task[i].num == task_num) {
            j = i;
            for (; i < len; i++) {
                j++;
                a_list->task[i].check = a_list->task[j].check;
                a_list->task[i].priority = a_list->task[j].priority;
                strcpy(a_list->task[i].todo, a_list->task[j].todo);
            }
        }
    }
    a_list->task_cnt = len - 1;
    int new_size = ((a_list->task_cnt) * (sizeof(task_t)));
    a_list->task = realloc(a_list->task, new_size);
    //printf("task count changed: %d\n", a_list->task_cnt);

    return 0;
}

int check_task(list_t *a_list, int task_id)
{
    int task_index = task_id - 1;
    a_list->task[task_index].check = 1;

    return 0;
}

int add_priority(list_t *a_list, int task_id, int prior_num)
{
    int task_index = task_id - 1;
    a_list->task[task_index].priority = prior_num;

    return 0;
}

void print_by_prior(list_t *a_list)
{
    if (a_list->task_cnt != 0) {
        int len = a_list->task_cnt;
        int i;
        int j;
        int max_priority = MAX_PRIOR;

        printf("List by priority\n");
        printf("====================\n");
        printf("Num\t|\tTasks\t|\tPrio\n");

        for (j = 0; j < PRIOR_SCALE; j++) {
            for (i = 0; i < len; i++) {
                if ((a_list->task[i].priority == max_priority) && (a_list->task[i].priority != 0)) {
                    if (a_list->task[i].check > 0) {
                        printf("%d -  [X] %s \t-%d\n", a_list->task[i].num, a_list->task[i].todo, a_list->task[i].priority);
                    } else if (a_list->task[i].check == 0) {
                        printf("%d -  [ ] %s \t-%d\n", a_list->task[i].num, a_list->task[i].todo, a_list->task[i].priority);
                    }
                } else if ((a_list->task[i].priority == 0) && (a_list->task[i].priority == max_priority)) {
                    if (a_list->task[i].check == 1) {
                        printf("%d -  [X] %s   \n", a_list->task[i].num, a_list->task[i].todo);
                    } else {
                        printf("%d -  [ ] %s   \n", a_list->task[i].num, a_list->task[i].todo);
                    }
                }
            }
            max_priority--;
        }

    } else {
        printf("There are no tasks for today. :)\n");
    }
}

