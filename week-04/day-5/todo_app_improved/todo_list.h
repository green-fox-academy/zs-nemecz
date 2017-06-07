#ifndef TODO_LIST_H
#define TODO_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

#define TODO_LEN 255
#define MAX_PRIOR 9
#define PRIOR_SCALE 10

/***
***TYPE DEFS
***/

typedef struct {
    int num;
    char todo[TODO_LEN];
    int check;
    int priority;
} task_t;

typedef struct {
    task_t *task;
    int task_cnt;
    int list_num;
} list_t;

/***
***FUNC DFES
***/

void print_usage();
list_t *init_list(int list_num);
int add_task(list_t *list_n, char *new_todo);
void print_tasks(list_t *a_list);
int read_file(list_t *a_list, char *path);
int write_file(list_t *a_list, char *path);
int list_empty(list_t *a_list);
int list_remove(list_t *a_list);
int task_remove(list_t *a_list, int task_num);
int check_task(list_t *a_list, int task_id);
int add_priority(list_t *a_list, int task_id, int prior_num);
void print_by_prior(list_t *a_list);
void load_usage();

#endif // TODO_LIST_H

