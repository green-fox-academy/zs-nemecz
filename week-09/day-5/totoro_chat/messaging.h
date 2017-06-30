#ifndef _SERVERS_H
#define _SERVERS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <process.h>
#include <windows.h>
#include "file.h"
#include "users.h"

#include <ws2tcpip.h>
void message_listener();
void send_message();

#endif
