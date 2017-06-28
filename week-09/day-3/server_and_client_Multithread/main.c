#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <process.h>
#include <windows.h>
#include "file.h"

#include <winsock2.h>
#include <ws2tcpip.h>


void thread_server();
void thread_client();

int main()
{

    _beginthread(thread_server, 0, NULL);
    printf("Reached threading.\n");
    _beginthread(thread_client, 0, NULL);

    while (1) {

    }

    return 0;
}

void thread_server()
{
    while (1) {
        WSADATA data;
        WORD ver = MAKEWORD(2, 2);
        int wsResult = WSAStartup(ver, &data);
        if (wsResult != 0) {
            printf("WINSock could not initialize properly. Err #: %d\n", wsResult);
        }
        printf("WINSOCK initialized for Server.\n");
        Sleep(100);

         //Create server socket
        SOCKET server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        //Bind socket to IP Address and Port
        struct sockaddr_in server;
        server.sin_addr.s_addr = inet_addr("127.0.0.1");
        server.sin_family = AF_INET;
        server.sin_port = htons(100);

        /** Init Server **/
        printf("Server startup...\n");
        Sleep(100);

        if (server_socket == INVALID_SOCKET) {
            printf("Cant't create socket. Err #%d.\n", GetLastError());
        }

        printf("Socket created.\n");

        if (bind(server_socket, (struct sockaddr*) &server,  sizeof(server)) == INVALID_SOCKET) {
            printf("Cant't bind socket. Err #%d.\n", GetLastError());
        }

        printf("Server socket bound.\n");
        Sleep(100);

        //Tell WinSock the socket is for listening
        if (listen(server_socket, SOMAXCONN) == INVALID_SOCKET) {
            printf("Error listening on socket. Err #%d.\n", GetLastError());
        }
        //Wait for connection

        SOCKET temporary_client_socket;
        printf("Server waiting for client...\n");
        Sleep(100);

        temporary_client_socket = SOCKET_ERROR;

        while ( temporary_client_socket == SOCKET_ERROR ) {
            temporary_client_socket = accept(server_socket, NULL, NULL);
        }

        printf( "Client Connected.\n");
        server_socket = temporary_client_socket;


        char log_message1[] = "Client Connected.";
        char log_message2[] = "Server sending message back.";
        int file_ok = get_write_file_name();
        write_data_to_file(log_message1);

        // While loop: accept and echo message
        int bytesSent;
        int bytesRecv = SOCKET_ERROR;
        char sendbuf[200] = "Server: Sending Data.";
        char recvbuf[200] = "";
        char exit[] = "exit app";
        int exit_cntr = 0;

        bytesRecv = recv(server_socket, recvbuf, 200, 0 );
        printf( "Message received: %s\n", recvbuf);

        write_data_to_file(recvbuf);
        send(server_socket, sendbuf, strlen(sendbuf), 0 );

        while(1) {
            bytesRecv = recv(server_socket, recvbuf, 200, 0 );
            recvbuf[bytesRecv] = 0;
            write_data_to_file(recvbuf);
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

            write_data_to_file(log_message2);
            send(server_socket, sendbuf, strlen(sendbuf), 0 );
            printf( "Send message: %s\n", sendbuf);

        }
    }
}

void thread_client()
{
    while (1) {

        WSADATA data;
        WORD ver = MAKEWORD(2, 2);
        int wsResult = WSAStartup(ver, &data);
        if (wsResult != 0) {
            printf("WINSock could not initialize properly. Err #: %d\n", wsResult);
        }

        printf("WINSOCK initialized for Client.\n");
        Sleep(200);

        //Create socket
        SOCKET client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        //Fill in a hint structure
        struct sockaddr_in server;
        server.sin_addr.s_addr = inet_addr("127.0.0.1");
        server.sin_family = AF_INET;
        server.sin_port = htons(100);

        /** Init Client **/
        printf("Initializing client...\n");
        Sleep(200);

        if (client_socket == INVALID_SOCKET) {
            printf("Cant't create socket. Err #%d.\n", GetLastError());
        }

        if (connect(client_socket, (SOCKADDR*) &server, sizeof(server) ) == SOCKET_ERROR) {
            printf( "Failed to connect. ERROR #%d\n", GetLastError());
            WSACleanup();
        }
        printf("Connected to server.\n");
        Sleep(500);
        // Send and receive data.
        int bytesSent;
        int bytesRecv = SOCKET_ERROR;
        char sendbuf[200] = "Client: Sending data.";
        char recvbuf[200] = "";
        char exit[] = "exit app";
        int exit_cntr = 0;

        bytesSent = send(client_socket, sendbuf, strlen(sendbuf), 0 );
        if (bytesSent < 0) {
            printf("Error sending message.\n");
            Sleep(200);
        } else {
            printf("Sending message: '%s'\n", sendbuf);
            Sleep(200);
        }

        bytesRecv = recv(client_socket, recvbuf, 200, 0 );
        if (bytesRecv < 0) {
            printf("Error receiving message.\n");
            Sleep(500);
        } else {
            recvbuf[bytesRecv] = 0;
            printf("Message received: '%s'\n", recvbuf);
            Sleep(500);
        }

        while (1) {
            printf("Please type new message:\t");
            Sleep(500);
            gets(sendbuf);

            /**Send**/
            bytesSent = send(client_socket, sendbuf, strlen(sendbuf), 0 );
            if (bytesSent < 0) {
                printf("Error sending message.\n");
                Sleep(500);
            } else {
                printf("Sending message: '%s'\n", sendbuf);
                Sleep(500);
            }

            /**check whether user wants to quit**/
            for (int i = 0; i < strlen(exit); i++) {
                if (exit[i] == sendbuf[i])
                    exit_cntr++;
            }

            if (exit_cntr == strlen(exit)) {
                printf("Exiting...");
                break;
            }

            exit_cntr = 0;

            /**Receive**/
            bytesRecv = recv(client_socket, recvbuf, 200, 0 );
            if (bytesRecv < 0) {
                printf("Error receiving message.\n");
                Sleep(500);
            } else {
                recvbuf[bytesRecv] = 0;
                printf("Message received: '%s'\n", recvbuf);
                Sleep(500);
            }
        }
    }
}
