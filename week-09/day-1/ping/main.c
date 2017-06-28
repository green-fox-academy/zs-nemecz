#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <Ws2tcpip.h>

//Create a client app that ping the google.com to get than latency, and print it out.


int main()
{
    system("ping 8.8.8.8");

    return 0;
}

