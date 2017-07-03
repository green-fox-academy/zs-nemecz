/* Includes ------------------------------------------------------------------*/

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
				LCD_UsrLog((char *)"Connection closed, waiting for an other connection!\n");
			} else if (received_bytes == SOCKET_ERROR) {
				LCD_UsrLog((char *)"Something went wrong with the client socket, trying to close it...\n");
				break;
			} else {
				// Terminate the string with zero
				buff[received_bytes] = '\0';
				// Print out the received data
				LCD_UsrLog((char *)"Received string: ");
				LCD_UsrLog((char *)buff);
				LCD_UsrLog((char *)"\n");
				// Send back the received string
				send(slave_socket, buff, received_bytes, 0);
			}
		} while (received_bytes > 0);

		closesocket(slave_socket);
		LCD_UsrLog((char *)"Client socket closed.\n");
	}
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
