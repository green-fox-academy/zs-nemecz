#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <process.h>
#include <windows.h>
#include "file.h"
#include "users.h"
#include "messaging.h"
#include "broadcasting.h"

#include <ws2tcpip.h>
#define EXIT_COMMAND    'e'

void print_info();
void clrscr();

int main()
{
    users.cntr = 0;
    char command;
    /** Set user name **/
    printf("Please enter your user name: \t");
    gets(this_user.name);
    clrscr();

    print_info();

    WSADATA data;
    WORD ver = MAKEWORD(2, 2);
    int wsResult = WSAStartup(ver, &data);
    if (wsResult != 0) {
         printf("WINSock could not initialize properly. Err #: %d\n", wsResult);
    }


    /** Begin server threads **/
    _beginthread(message_listener, 0, NULL);
    _beginthread(server_broadcast, 0, NULL);
    _beginthread(server_discover, 0, NULL);

    while(1) {
        command = getch();

        if (command == EXIT_COMMAND)
            break;

        switch (command) {
            case 'h':
                print_info();
                break;
            case 'n':
                clrscr();
                print_info();
                printf("Please enter your user name: \t");
                gets(this_user.name);
                this_user.port = 9319;
                printf("Your user name is: %s\n", this_user.name);
                break;
            case 'l':
                clrscr();
                print_info();
                list_users();
                break;
            case 'm':
                clrscr();
                print_info();
                send_message();
                break;
            case 'd':
                clrscr();
                print_info();
                send_discovery_request();
                break;
            default:
                clrscr();
                print_info();
                printf("Unrecognized command.\n");
                break;
        }
    }

    //Shut down Winsock
    WSACleanup();

    return 0;
}

void print_info()
{
    printf("TOTORO CHAT\n");
    printf("====================\n");
    printf("Current user:\t%s\n", this_user.name);
    printf("Commands:\n");
    printf("h   Display this help info\n");
    printf("e   Exit\n");
    printf("n   Set user name\n");
    printf("l   List known users\n");
    printf("d   Send discovery request\n");
    printf("m   Send message\n");
    printf("l   Start logging\n");
}

void clrscr()
{
    system("@cls||clear");
}

