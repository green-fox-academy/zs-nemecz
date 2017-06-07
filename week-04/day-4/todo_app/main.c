#include "todo_list.h"

void clrscr();

int main()
{
    print_usage();
    char command[200];
    char command_to_parse[200];
    char new_todo[TODO_LEN];
    char file_path[80];
    char task_spec[20];
    char prior_spec[20];
    int list_num = 0;
    list_t *list_0 = init_list(list_num);

    while(1) {
        gets(command);
        clrscr();
        print_usage();
        strcpy(command_to_parse, command);
        char *command_pointer;
        command_pointer = strtok(command_to_parse, "- ");
        //select option
        /*** QUIT ***/
        if (strcmp(command_pointer, "q") == 0) {
            list_remove(list_0);
            printf("Exiting...");
            break;
        }

        /*** ADD ITEM ***/
        if (strcmp(command_pointer, "a") == 0) {
            command_pointer = strtok(NULL, "\"");

            if (command_pointer != NULL) {
                strcpy(new_todo, command_pointer);
                add_task(list_0, new_todo);
                printf("Task added!\n");
            } else {
                printf("Unable to add: No task is provided.\n");
            }

        /*** LIST ITEMS ***/
        } else if (strcmp(command_pointer, "l") == 0) {
            print_tasks(list_0);

        /*** WRITE TO FILE ***/
        } else if (strcmp(command_pointer, "wr") == 0) {
            command_pointer = strtok(NULL, "\"");
            strcpy(file_path, command_pointer);
            write_file(list_0, file_path);
            printf("List written to file!\n");

        /*** READ FROM FILE ***/
        } else if (strcmp(command_pointer, "rd") == 0) {
            command_pointer = strtok(NULL, "\"");
            strcpy(file_path, command_pointer);
            read_file(list_0, file_path);

        /*** EMPTY LIST ***/
        } else if (strcmp(command_pointer, "e") == 0) {
            list_empty(list_0);
            printf("List deleted!\n");

        /*** REMOVE SINGLE TASK ***/
        } else if (strcmp(command_pointer, "r") == 0) {
            command_pointer = strtok(NULL, " ");
            //is index input empty?
            if (command_pointer != NULL) {
                strcpy(task_spec, command_pointer);
                //is input a number?
                if (isdigit(task_spec[0])) {
                    int task_num = atof(task_spec);
                    //is it in the range of our task count?
                    if ((task_num <= list_0->task_cnt) && (task_num >= 1)) {
                        task_remove(list_0, task_num);
                        printf("Task %d removed!\n", task_num);
                    } else {
                        printf("Unable to remove: Index is out of bound.\n");
                    }
                } else {
                    printf("Unable to remove: Index is not a number.\n");
                }
            } else {
                printf("Unable to remove: No index is provided.\n");
            }

        /*** TASK DONE ***/
        } else if (strcmp(command_pointer, "c") == 0) {
            command_pointer = strtok(NULL, "\"");
             //is there an input?
             if (command_pointer != NULL) {
                strcpy(task_spec, command_pointer);
                //is input a number?
                if (isdigit(task_spec[0])) {
                    int task_num = atof(task_spec);
                    //is it in the range of our task count?
                    if ((task_num <= list_0->task_cnt) && (task_num >= 1)) {
                        check_task(list_0, task_num);
                        printf("Task %d done!\n", task_num);
                    } else {
                        printf("Unable to check: Index is out of bound.\n");
                    }
                } else {
                    printf("Unable to check: Index is not a number.\n");
                }
            } else {
                printf("Unable to check: No index is provided.\n");
            }

        /*** ADD PRIORITY***/
        } else if (strcmp(command_pointer, "p") == 0) {
            command_pointer = strtok(NULL, "\"");
             //is there an input?
             if (command_pointer != NULL) {
                strcpy(task_spec, command_pointer);
                //is first input a number?
                if (isdigit(task_spec[0])) {
                    int task_num = atof(task_spec);
                    //is it in the range of our task count?
                    if ((task_num <= list_0->task_cnt) && (task_num >= 1)) {
                        command_pointer = strtok(NULL, " ");
                        //is there an input?
                        if (command_pointer != NULL) {
                            strcpy(prior_spec, command_pointer);
                            //is second input a number?
                            if (isdigit(prior_spec[0])) {
                                int prior_num = atof(prior_spec);
                                //is it in the range of our priority scale?
                                if ((prior_num >= 0) && (prior_num <= 9)) {
                                    add_priority(list_0, task_num, prior_num);
                                    printf("Success: Priority %d added to task %d!\n",prior_num, task_num);
                                } else {
                                    printf("Unable to add priority: Priority is out of bound.\n");
                                }
                            } else {
                                printf("Unable to add priority: Priority is not a number.\n");
                            }
                        } else {
                            printf("Unable to add priority: Priority is missing.\n");
                        }
                    } else {
                        printf("Unable to add priority: Index is out of bound.\n");
                    }
                } else {
                    strcpy(new_todo, command_pointer);
                    add_task(list_0, new_todo);
                    command_pointer = strtok(NULL, " ");
                        //is there an input?
                        if (command_pointer != NULL) {
                            strcpy(prior_spec, command_pointer);
                            //is second input a number?
                            if (isdigit(prior_spec[0])) {
                                int prior_num = atof(prior_spec);
                                //is it in the range of our priority scale?
                                if ((prior_num >= 0) && (prior_num <= 9)) {
                                    add_priority(list_0, list_0->task_cnt, prior_num);
                                    printf("Success: Priority %d added to task %d!\n",prior_num, list_0->task_cnt);
                                } else {
                                    printf("Unable to add priority: Priority is out of bound.\n");
                                }
                            } else {
                                printf("Unable to add priority: Priority is not a number.\n");
                            }
                        } else {
                            printf("Unable to add priority: Priority is missing.\n");
                        }
                }
            } else {
                printf("Unable to check: No index is provided.\n");
            }
        } else if (strcmp(command_pointer, "lp") == 0) {
            print_by_prior(list_0);
        } else {
            printf("Unsupported argument.\n");
        }
    }
    return 0;
}

void clrscr()
{
    system("@cls||clear");
}





