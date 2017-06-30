#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <process.h>
#include <windows.h>
#include "file.h"
#include "users.h"


#include <ws2tcpip.h>

void message_listener()
{
    //Create socket
    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        printf("Cant't create socket. Err #%d.\n", GetLastError());
    }

    //Bind socket to IP Address and Port
    struct sockaddr_in server;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(13990);

    if (bind(server_socket, (struct sockaddr*) &server,  sizeof(server)) == INVALID_SOCKET) {
        printf("Cant't bind socket. Err #%d.\n", GetLastError());
    }

    //Tell WinSock the socket is for listening
    if (listen(server_socket, SOMAXCONN) == INVALID_SOCKET) {
        printf("Error listening on socket. Err #%d.\n", GetLastError());
    }

    SOCKET temporary_client_socket;

    while (1) {
        temporary_client_socket = SOCKET_ERROR;

        struct sockaddr_in messaging_address;
        int address_size = sizeof(messaging_address);

        while ( temporary_client_socket == SOCKET_ERROR ) {
            temporary_client_socket = accept(server_socket, &messaging_address, &address_size);
        }
        char user_name[255];
        int user_index = find_user(&messaging_address.sin_addr);

        if (user_index != -1) {
            strcpy(user_name, users.u[user_index].name);
        } else {
            strcpy(user_name, "Unknown user");
        }

        int bytesSent;
        int bytesRecv = SOCKET_ERROR;
        char recvbuf[200] = "";

        bytesRecv = recv(temporary_client_socket, recvbuf, 200, 0 );
        printf("%s: '%s'\n", recvbuf);

        closesocket(temporary_client_socket);
    }

}

void send_message()
{
    //Create socket
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        printf("Cant't create socket. Err #%d.\n", GetLastError());
    }

    struct sockaddr_in server;
    char message_to[255];
    printf("Message to:\t");
    gets(message_to);
    int user_index = select_user(message_to);

    if (user_index != -1) {
        //Fill in a hint structure
        server.sin_addr.s_addr = inet_addr(users.u[user_index].IP_address);
        server.sin_family = AF_INET;
        server.sin_port = htons(users.u[user_index].port);
    } else {
        printf("User not found.");
        return;
    }


    if (connect(sock, (SOCKADDR*) &server, sizeof(server) ) == SOCKET_ERROR) {
        printf( "Failed to connect. ERROR #%d\n", GetLastError());
    }

    // Send and receive data.
    int bytesSent;
    int bytesRecv = SOCKET_ERROR;
    char sendbuf[200] = "";

    printf("Type message:\t");
    gets(sendbuf);

    /**Send**/
    bytesSent = send(sock, sendbuf, strlen(sendbuf), 0 );
    if (bytesSent < 0) {
        printf("Error sending message.\n");
    }
    closesocket(sock);
}
