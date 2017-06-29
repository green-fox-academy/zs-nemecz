#ifndef _USERS_H
#define _USERS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <process.h>
#include <windows.h>
#include "file.h"
#include "users.h"
#include "messaging.h"

#include <ws2tcpip.h>

/** STRUCTURES AND VARS **/
typedef struct {
    char name[255];
    char IP_address[100];
    int port;
}user_type;

typedef struct {
    user_type u[50];
    int cntr;
}user_list;

user_type this_user;
user_list users;

/** FUNCTIONS **/
int list_users();

#endif // _USERS

