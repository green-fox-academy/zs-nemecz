/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "socket_server.h"
#include "lcd_log.h"
#include "cmsis_os.h"
#include "app_ethernet.h"
#include "lwip/sockets.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define SERVER_IP			"10.27.6.44"
#define QUEUE_SIZE 			1
#define SOCKET_ERROR		-1

/* Private variables ---------------------------------------------------------*/
int msg_cntr = 0;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

// TODO:
// Implement this function!
void socket_server_thread(void const *argument)
{
	// Server address structure initialization
	struct sockaddr_in addr_in;                                 // Inet address structure definition
	addr_in.sin_family = AF_INET;                               // This address is an internet address
	addr_in.sin_port = htons(SERVER_PORT);                      // Server port
	addr_in.sin_addr.s_addr = inet_addr(SERVER_IP);             // Server IP
	struct sockaddr *addr = (struct sockaddr *)&addr_in;        // Make a struct sockaddr pointer, which points to the address stucture

	int master_socket = socket(PF_INET, SOCK_STREAM, 0);
	int flag = bind(master_socket, addr, sizeof(*addr));
	if (flag < 0)
		LCD_ErrLog((char *)"Binding failed.\n");

	flag = listen(master_socket, QUEUE_SIZE);
	// Check is listening is ok
	if (flag < 0)
		LCD_ErrLog((char *)"Listening failed\n");

	LCD_UsrLog((char *)"Server is initialized, waiting for connections.\n");

	// Create variables which will be used in the while loop
	struct sockaddr client_addr;    // Client address structure
	int slave_socket;              // Slave socket definition, this will be used to store the incoming socket
	char buff[SERVER_BUFF_LEN];    // Buffer for incoming and outgoing data
	while (1) {
		// Accept the connection and save the incoming socket
		slave_socket = accept(master_socket, &client_addr, NULL);
		// Check if the socket is valid
		if (slave_socket < 0)
			LCD_ErrLog((char *)"Connection not accepted.\n");

		LCD_UsrLog((char *)"Connection accepted.\n");

		// Receive the data sent by the client
		int received_bytes;
		do {
			received_bytes = recv(slave_socket, buff, SERVER_BUFF_LEN, 0);
			if (received_bytes == 0) {
				LCD_UsrLog("- - - \n");
			} else if (received_bytes == SOCKET_ERROR) {
				LCD_UsrLog((char *)"Something went wrong with the client socket, trying to close it...\n");
				break;
			} else {
				// Terminate the string with zero
				buff[received_bytes] = '\0';
				// Print out the received data
				LCD_UsrLog("Received string: ");
				LCD_UsrLog(buff);
				LCD_UsrLog("\n");
				// Send back the received string
				send(slave_socket, buff, received_bytes, 0);
				msg_cntr++;
			}

			 if (msg_cntr > 5) {
				HAL_Delay(1000);
				msg_cntr = 0;
				LCD_LOG_ClearTextZone();
			}

		} while (received_bytes > 0);

		closesocket(slave_socket);
		//LCD_UsrLog("Client socket closed.\n");
	}
}

void broadcast_server_thread(void const *argument)
{
	//Create socket
	    int broadcast_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	    if (broadcast_socket == SOCKET_ERROR) {
	    	LCD_ErrLog((char *)"Cant't create broadcast socket.\n");
	    }

	    //Bind socket to IP Address and Port
	    struct sockaddr_in broadcast_server;
	    broadcast_server.sin_addr.s_addr = INADDR_ANY;
	    broadcast_server.sin_family = AF_INET;
	    broadcast_server.sin_port = htons(12345);

	    if (bind(broadcast_socket, (struct sockaddr*) &broadcast_server,  sizeof(broadcast_server)) == SOCKET_ERROR) {
	    	LCD_ErrLog((char *)"Cant't bind broadcast server socket.\n");
	    }

	    LCD_UsrLog((char *)"Broadcast server initializing.\n");

	    while (1) {

	        struct sockaddr_in discovery_address;
	        int address_size = sizeof(discovery_address);

	        int bytesRecv = SOCKET_ERROR;
	        char recvbuf[200] = "";

	        bytesRecv = recvfrom(broadcast_socket, recvbuf, 200, 0, &discovery_address, &address_size);

	        if (bytesRecv > 0) {
	        	LCD_UsrLog((char *)"received broadcast request: ");
	        	LCD_UsrLog((char *)recvbuf);
	        	LCD_UsrLog((char *)"\n");
	        	msg_cntr++;
	            /** make sense of message **/
	            char *message_pointer;
	            char discovery_addr[200];
	            int discovery_port = 0;
	            message_pointer = strtok(recvbuf, " ");

	            if (strcmp(message_pointer, "TOTORO") == 0) {
	            	//LCD_UsrLog((char *)"message type: %s\n", message_pointer);
	                message_pointer = strtok(NULL, "\0");
	                //LCD_UsrLog((char *)"port: %s\n", message_pointer);
	                discovery_port = atoi(message_pointer);
	                strcpy(discovery_addr, inet_ntoa(discovery_address.sin_addr));
	                LCD_UsrLog((char *)"IP address: %s\n", discovery_addr);
	                reply_to_discovery_request(discovery_port, discovery_addr);
	            }

	            if (msg_cntr > 5) {
	            	HAL_Delay(1000);
	            	msg_cntr = 0;
	            	LCD_LOG_ClearTextZone();
	            }
	        }
	    }

	    closesocket(broadcast_socket);
}

void reply_to_discovery_request(int discovery_port, char *discovery_address)
{
    //Create socket
    int socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socket == SOCKET_ERROR) {
    	LCD_ErrLog("Cant't create socket.");
    }

    //Fill in a hint structure
    struct sockaddr_in discovery_server;
    discovery_server.sin_addr.s_addr = inet_addr(discovery_address);
    discovery_server.sin_family = AF_INET;
    discovery_server.sin_port = htons(discovery_port);

    if (connect(socket, (const struct sockaddr*) &discovery_server, sizeof(discovery_server) ) == SOCKET_ERROR) {
    	LCD_ErrLog("Failed to connect");
        return;
    }

    // Send data.
    int bytesSent;
    char port_num[] = " 54545";
    char discovery_message[300];

    strcpy(discovery_message, "ZsuzskaBoardja");
    strcat(discovery_message, port_num);

    /**Send**/
    bytesSent = send(socket, discovery_message, strlen(discovery_message), 0);
    if (bytesSent < 0) {
        printf("Error sending message.\n");
        return;
    }
    printf("Reply to discovery request: %s\n", discovery_message);
    closesocket(socket);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
