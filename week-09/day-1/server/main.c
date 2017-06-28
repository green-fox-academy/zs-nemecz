#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <winsock2.h>
#include <ws2tcpip.h>

int main()
{
    //Initialize WinSock
    printf("Server startup...\n");
    WSADATA data;
    WORD ver = MAKEWORD(2, 2);
    int wsResult = WSAStartup(ver, &data);
    if (wsResult != 0) {
         printf("WINSock could not initialize properly. Err #: %d\n", wsResult);
         return 1;
    }
    printf("WINSOCK initialised.\n");

    //Create socket
    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_socket == INVALID_SOCKET) {
        printf("Cant't create socket. Err #%d.\n", GetLastError());
        return 2;
    }

    printf("Socket created.\n");

    //Bind socket to IP Address and Port
    struct sockaddr_in server;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(99);

    if (bind(server_socket, (struct sockaddr*) &server,  sizeof(server)) == INVALID_SOCKET) {
        printf("Cant't bind socket. Err #%d.\n", GetLastError());
        return 3;
    }

    printf("Socket bound.\n");

    //Tell WinSock the socket is for listening
    if (listen(server_socket, SOMAXCONN) == INVALID_SOCKET) {
        printf("Error listening on socket. Err #%d.\n", GetLastError());
        return 4;
    }
    printf("Listening ...");

    //Wait for connection

    SOCKET temporary_client_socket;
    printf(" and waiting for client...\n");

    while (1) {
        temporary_client_socket = SOCKET_ERROR;

        while ( temporary_client_socket == SOCKET_ERROR ) {
            temporary_client_socket = accept(server_socket, NULL, NULL);
        }

        printf( "Client Connected.\n");
        server_socket = temporary_client_socket;
        break;
    }

    // While loop: accept and echo message
    int bytesSent;
    int bytesRecv = SOCKET_ERROR;
    char sendbuf[200] = "Server: Sending Data.";
    char recvbuf[200] = "";
    char exit[] = "exit app";
    int exit_cntr = 0;

    bytesRecv = recv(server_socket, recvbuf, 200, 0 );
    printf( "Message received: %s\n", recvbuf);

    send(server_socket, sendbuf, strlen(sendbuf), 0 );

    while(1) {
        bytesRecv = recv(server_socket, recvbuf, 200, 0 );
        recvbuf[bytesRecv] = 0;

        //check whether user wants to quit
        for (int i = 0; i < strlen(exit); i++) {
            if (exit[i] == recvbuf[i])
                exit_cntr++;
        }

        if (exit_cntr == strlen(exit))
            break;

        exit_cntr = 0;
        printf( "Bytes Recv: %ld\n", bytesRecv);
        printf( "Message received: %s\n", recvbuf);
        memset(sendbuf, 0, sizeof(sendbuf));
        strcpy(sendbuf, recvbuf);

        send(server_socket, sendbuf, strlen(sendbuf), 0 );
        printf( "Send message: %s\n", sendbuf);

    }


    //Shut down Winsock
    WSACleanup();

    return 0;
}

