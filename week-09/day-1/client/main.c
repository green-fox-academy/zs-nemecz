#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <winsock2.h>
#include <Ws2tcpip.h>

//Create a client app that ping the google.com to get than latency, and print it out.
int inet_pton(int af, const char *src, void *dst);
const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);


int main()
{
    printf("Initializing client...\n");
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
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(99);

    if (connect(sock, (SOCKADDR*) &server, sizeof(server) ) == SOCKET_ERROR) {
        printf( "Failed to connect. ERROR #%d\n", GetLastError());
        WSACleanup();
        return 0;
    }
    printf("Connected to server.\n");

    // Send and receive data.
    int bytesSent;
    int bytesRecv = SOCKET_ERROR;
    char sendbuf[200] = "Client: Sending data.";
    char recvbuf[200] = "";
    char exit[] = "exit app";
    int exit_cntr = 0;

    bytesSent = send(sock, sendbuf, strlen(sendbuf), 0 );
    if (bytesSent < 0) {
        printf("Error sending message.\n");
    } else {
        printf("Sending message: '%s'\n", sendbuf);
    }

    bytesRecv = recv(sock, recvbuf, 200, 0 );
    if (bytesRecv < 0) {
        printf("Error receiving message.\n");
    } else {
        recvbuf[bytesRecv] = 0;
        printf("Message received: '%s'\n", recvbuf);
    }

    while (1) {
        printf("Please type new message:\t");
        gets(sendbuf);

        /**Send**/
        bytesSent = send(sock, sendbuf, strlen(sendbuf), 0 );
        if (bytesSent < 0) {
            printf("Error sending message.\n");
        } else {
            printf("Sending message: '%s'\n", sendbuf);
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
        bytesRecv = recv(sock, recvbuf, 200, 0 );
        if (bytesRecv < 0) {
            printf("Error receiving message.\n");
        } else {
            recvbuf[bytesRecv] = 0;
            printf("Message received: '%s'\n", recvbuf);
        }
    }

    return 0;
}

/** extra functons **/

int inet_pton(int af, const char *src, void *dst)
{
  struct sockaddr_storage ss;
  int size = sizeof(ss);
  char src_copy[INET6_ADDRSTRLEN+1];

  ZeroMemory(&ss, sizeof(ss));
  /* stupid non-const API */
  strncpy (src_copy, src, INET6_ADDRSTRLEN+1);
  src_copy[INET6_ADDRSTRLEN] = 0;

  if (WSAStringToAddress(src_copy, af, NULL, (struct sockaddr *)&ss, &size) == 0) {
    switch(af) {
      case AF_INET:
    *(struct in_addr *)dst = ((struct sockaddr_in *)&ss)->sin_addr;
    return 1;
      case AF_INET6:
    *(struct in6_addr *)dst = ((struct sockaddr_in6 *)&ss)->sin6_addr;
    return 1;
    }
  }
  return 0;
}

const char *inet_ntop(int af, const void *src, char *dst, socklen_t size)
{
  struct sockaddr_storage ss;
  unsigned long s = size;

  ZeroMemory(&ss, sizeof(ss));
  ss.ss_family = af;

  switch(af) {
    case AF_INET:
      ((struct sockaddr_in *)&ss)->sin_addr = *(struct in_addr *)src;
      break;
    case AF_INET6:
      ((struct sockaddr_in6 *)&ss)->sin6_addr = *(struct in6_addr *)src;
      break;
    default:
      return NULL;
  }
  /* cannot direclty use &size because of strict aliasing rules */
  return (WSAAddressToString((struct sockaddr *)&ss, sizeof(ss), NULL, dst, &s) == 0)?
          dst : NULL;
}
