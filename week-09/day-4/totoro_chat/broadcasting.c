#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <process.h>
#include <windows.h>
#include "users.h"

#include <ws2tcpip.h>

void reply_to_discovery_request(int discovery_port, char *discovery_address);

void server_discover()
{
    //Create socket
    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_socket == INVALID_SOCKET) {
        printf("Cant't create socket. Err #%d.\n", GetLastError());
    }

    //Bind socket to IP Address and Port
    struct sockaddr_in server;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(23900);

    if (bind(server_socket, (struct sockaddr*) &server,  sizeof(server)) == INVALID_SOCKET) {
        printf("Cant't bind socket. Err #%d.\n", GetLastError());
    }

    //Tell WinSock the socket is for listening
    if (listen(server_socket, SOMAXCONN) == INVALID_SOCKET) {
        printf("Error listening on socket. Err #%d.\n", GetLastError());
    }

    SOCKET temporary_client_socket;
    int i = 0;

    while (1) {
        temporary_client_socket = SOCKET_ERROR;

        struct sockaddr_in messaging_address;
        int address_size = sizeof(messaging_address);

        while ( temporary_client_socket == SOCKET_ERROR ) {
            temporary_client_socket = accept(server_socket, &messaging_address, &address_size);
        }

        //server_socket = temporary_client_socket;
        char recvbuf[200] = "";


        int bytesRecv = recv(temporary_client_socket, recvbuf, 200, 0);
        //printf("Discovery board message: %s\n", recvbuf);

        char *message_pointer;
        char copy_of_recvbuf[200];
        strcpy(copy_of_recvbuf, recvbuf);
        char messaging_addr[50];
        int messaging_port = 0;
        message_pointer = strtok(copy_of_recvbuf, " ");

        if (bytesRecv > 0) {
            printf("Discovery reply from: %s\n", message_pointer);

            /** check whether my user list is empty**/
            if (users.cntr == 0) {
                strcpy(users.u[i].name, message_pointer);
                message_pointer = strtok(NULL, "\0");
                printf("Messaging port: %s\n", message_pointer);
                messaging_port = atoi(message_pointer);
                users.u[i].port = messaging_port;
                strcpy(messaging_addr, inet_ntoa(messaging_address.sin_addr));
                printf("IP address received: %s\n", messaging_addr);
                strcpy(users.u[i].IP_address, messaging_addr);
                i++;
                users.cntr = i;
            } else {
                /** check whether user is already on the list
                -if not, add to the list**/
                if (check_user(message_pointer) == 0) {
                    strcpy(users.u[i].name, message_pointer);
                    message_pointer = strtok(NULL, "\0");
                    printf("Messaging port: %s\n", message_pointer);
                    messaging_port = atoi(message_pointer);
                    users.u[i].port = messaging_port;
                    strcpy(messaging_addr, inet_ntoa(messaging_address.sin_addr));
                    printf("IP address received: %s\n", messaging_addr);
                    strcpy(users.u[i].IP_address, messaging_addr);
                    i++;
                    users.cntr = i;
                }//if name is not already on the list

            } //else (if user list is not empty)
        } // if there was a message

        closesocket(temporary_client_socket);
    } //while (1)
}

void server_broadcast()
{
    //Create socket
    SOCKET server_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (server_socket == INVALID_SOCKET) {
        printf("Cant't create broadcast socket. Err #%d.\n", GetLastError());
    }

    //char broadcast_on = 1;
    //int set_sock_error = setsockopt(server_socket, SOL_SOCKET, SO_BROADCAST, &broadcast_on, sizeof(broadcast_on));

    //Bind socket to IP Address and Port
    struct sockaddr_in broadcast_server;
    broadcast_server.sin_addr.s_addr = INADDR_ANY;
    broadcast_server.sin_family = AF_INET;
    broadcast_server.sin_port = htons(12345);

    if (bind(server_socket, (struct sockaddr*) &broadcast_server,  sizeof(broadcast_server)) == INVALID_SOCKET) {
        printf("Cant't bind broadcast server socket. Err #%d.\n", GetLastError());
    }

    while (1) {

        struct sockaddr_in discovery_address;
        int address_size = sizeof(discovery_address);

        int bytesRecv = SOCKET_ERROR;
        char recvbuf[200] = "";

        bytesRecv = recvfrom(server_socket, recvbuf, 200, 0, &discovery_address, &address_size);

        if (bytesRecv > 0) {
            printf("received broadcast request: %s\n", recvbuf);

            /** make sense of message **/
            char *message_pointer;
            char discovery_addr[200];
            int discovery_port = 0;
            message_pointer = strtok(recvbuf, " ");

            if (strcmp(message_pointer, "TOTORO") == 0) {
                printf("message type: %s\n", message_pointer);
                message_pointer = strtok(NULL, "\0");
                printf("port: %s\n", message_pointer);
                discovery_port = atoi(message_pointer);
                strcpy(discovery_addr, inet_ntoa(discovery_address.sin_addr));
                printf("IP address: %s\n", discovery_addr);
                reply_to_discovery_request(discovery_port, discovery_addr);
            }
        }
    }

    closesocket(server_socket);
}

void reply_to_discovery_request(int discovery_port, char *discovery_address)
{
    //Create socket
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        printf("Cant't create socket. Err #%d.\n", GetLastError());
    }

    //Fill in a hint structure
    struct sockaddr_in discovery_server;
    discovery_server.sin_addr.s_addr = inet_addr(discovery_address);
    discovery_server.sin_family = AF_INET;
    discovery_server.sin_port = htons(discovery_port);

    if (connect(sock, (SOCKADDR*) &discovery_server, sizeof(discovery_server) ) == SOCKET_ERROR) {
        printf( "Failed to connect. ERROR #%d\n", GetLastError());
        return;
    }

    // Send data.
    int bytesSent;
    char port_num[] = " 13990";
    char discovery_message[300];

    if (this_user.name == NULL) {
        printf("Please enter your user name:\t");
        scanf("%s\n", this_user.name);
    }

    strcpy(discovery_message, this_user.name);
    strcat(discovery_message, port_num);

    /**Send**/
    bytesSent = send(sock, discovery_message, strlen(discovery_message), 0);
    if (bytesSent < 0) {
        printf("Error sending message.\n");
        return;
    }
    printf("Reply to discovery request: %s\n", discovery_message);
    closesocket(sock);
}

void send_discovery_request()
{
    //Create socket
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET) {
        printf("Cant't create socket. Err #%d.\n", GetLastError());
    }

    char broadcast_on = 1;
    int set_sock_error = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcast_on, sizeof(broadcast_on));
    if (set_sock_error > 0)
        printf("Error setting socket. Error #%d", GetLastError());

    //Fill in a hint structure
    struct sockaddr_in broadcast_server;
    broadcast_server.sin_addr.s_addr = inet_addr("255.255.255.255");
    broadcast_server.sin_family = AF_INET;
    broadcast_server.sin_port = htons(12345);

    // Send data.
    int bytesSent;

    char discovery_request[] = "TOTORO 23900";

    /**Send**/

    bytesSent = sendto(sock, discovery_request, strlen(discovery_request), 0, (SOCKADDR*) &broadcast_server, sizeof(broadcast_server));
    if (bytesSent < 0) {
        printf("Error sending message.\n");
    }
    closesocket(sock);
}
