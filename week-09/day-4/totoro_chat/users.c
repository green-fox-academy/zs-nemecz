#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <process.h>
#include <windows.h>
#include "file.h"
#include "users.h"

#include <ws2tcpip.h>

int list_users ()
{
    printf("NAME\tPORT\tIP\n");
    if (users.cntr != 0) {
        for (int i = 0; i < users.cntr; i++) {
            printf("%s\t", users.u[i].name);
            printf("%d\t", users.u[i].port);
            printf("%s\t\n", users.u[i].IP_address);
        }
    }
    return 0;
}

int check_user (char *user_name)
{
    int cnt = 0;
    for (int i = 0; i < users.cntr; i++) {
        if (strcmp(user_name, users.u[i].name) == 0)
            cnt++;
    }
    return cnt;
}

int select_user (char *user_name)
{
    int user_index = -1;
    for (int i = 0; i < users.cntr; i++) {
        if (strcmp(user_name, users.u[i].name) == 0)
            user_index = i;
    }
    return user_index;
}

int find_user (struct in_addr *IP_address)
{
    int user_index = -1;
    char user_IP = inet_ntoa(*IP_address);
    for (int i = 0; i < users.cntr; i++) {
        if (strcmp(user_IP, users.u[i].IP_address) == 0)
            user_index = i;
    }
    return user_index;
}
