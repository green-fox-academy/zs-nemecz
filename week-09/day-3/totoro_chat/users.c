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
            printf("%s\t", users.u[i].IP_address);
        }
    }
    return 0;
}
