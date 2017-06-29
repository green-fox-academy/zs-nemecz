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
    //Initialize WinSock
    printf("Listening for messages...\n");
    WSADATA data;
    WORD ver = MAKEWORD(2, 2);
    int wsResult = WSAStartup(ver, &data);
    if (wsResult != 0) {
         printf("WINSock could not initialize properly. Err #: %d\n", wsResult);
    }

    //Create socket
    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_socket == INVALID_SOCKET) {
        printf("Cant't create socket. Err #%d.\n", GetLastError());
    }

    //Bind socket to IP Address and Port
    struct sockaddr_in server;
    server.sin_addr.s_addr = inet_addr("10.27.6.51");
    server.sin_family = AF_INET;
    server.sin_port = htons(9999);

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

        bytesRecv = recv(temporary_client_socket, recvbuf, 200, 0 );
        printf("Message received: %s\n", recvbuf);

        closesocket(temporary_client_socket);
    }

    //Shut down Winsock
    WSACleanup();

}

void send_message()
{
    //Initialize WinSock
    WSADATA data;
    WORD ver = MAKEWORD(2, 2);
    int wsResult = WSAStartup(ver, &data);
    if (wsResult != 0) {
         printf("WINSock could not initialize properly. Err #: %d\n", wsResult);
    }

    //Create socket
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        printf("Cant't create socket. Err #%d.\n", GetLastError());
        return 0;
    }

    //Fill in a hint structure
    struct sockaddr_in server;
    server.sin_addr.s_addr = inet_addr("10.27.6.51");
    server.sin_family = AF_INET;
    server.sin_port = htons(9999);

    if (connect(sock, (SOCKADDR*) &server, sizeof(server) ) == SOCKET_ERROR) {
        printf( "Failed to connect. ERROR #%d\n", GetLastError());
        WSACleanup();
        return 0;
    }

    // Send and receive data.
    int bytesSent;
    int bytesRecv = SOCKET_ERROR;
    char sendbuf[200] = "";

    printf("Please type new message:\t");
    gets(sendbuf);

    /**Send**/
    bytesSent = send(sock, sendbuf, strlen(sendbuf), 0 );
    if (bytesSent < 0) {
        printf("Error sending message.\n");
    }
    closesocket(sock);
}
