#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <process.h>
#include <windows.h>

#include <ws2tcpip.h>

void discover()
{
    //Initialize WinSock
    WSADATA data;
    WORD ver = MAKEWORD(2, 2);
    int wsResult = WSAStartup(ver, &data);
    if (wsResult != 0) {
         printf("WINSock could not initialize properly. Err #: %d\n", wsResult);
    }

    //Create socket
    SOCKET server_socket = socket(AF_INET, SOCK_STREA, IPPROTO_TCP);
    if (server_socket == INVALID_SOCKET) {
        printf("Cant't create socket. Err #%d.\n", GetLastError());
    }

    //Bind socket to IP Address and Port
    struct sockaddr_in server;
    server.sin_addr.s_addr = inet_addr("10.27.6.51");
    server.sin_family = AF_INET;
    server.sin_port = htons(6666);

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

        while ( temporary_client_socket == SOCKET_ERROR ) {
            temporary_client_socket = accept(server_socket, NULL, NULL);
        }

        //server_socket = temporary_client_socket;

        int bytesSent;
        int bytesRecv = SOCKET_ERROR;
        char recvbuf[200] = "";

        bytesRecv = recv(temporary_client_socket, recvbuf, 200, 0);
        printf("Message received: %s\n", recvbuf);

        closesocket(temporary_client_socket);
    }

    //Shut down Winsock
    WSACleanup();

}

void broadcast()
{
    //Initialize WinSock
    WSADATA data;
    WORD ver = MAKEWORD(2, 2);
    int wsResult = WSAStartup(ver, &data);
    if (wsResult != 0) {
         printf("WINSock could not initialize properly. Err #: %d\n", wsResult);
    }

    //Create socket
    SOCKET server_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (server_socket == INVALID_SOCKET) {
        printf("Cant't create socket. Err #%d.\n", GetLastError());
    }
    setsockopt(server_socket, SOL_SOCKET, SO_BROADCAST, FALSE, 0);
    //Bind socket to IP Address and Port
    struct sockaddr_in server;
    server.sin_addr.s_addr = inet_addr("255.255.255.255");
    server.sin_family = AF_INET;
    server.sin_port = htons(12345);

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

        while ( temporary_client_socket == SOCKET_ERROR ) {
            temporary_client_socket = accept(server_socket, NULL, NULL);
        }

        int bytesSent;
        int bytesRecv = SOCKET_ERROR;
        char recvbuf[200] = "";

        bytesRecv = recvfrom(temporary_client_socket, recvbuf, 200, 0, );
        printf("Message received: %s\n", recvbuf);

        closesocket(temporary_client_socket);
    }

    //Shut down Winsock
    WSACleanup();

}
