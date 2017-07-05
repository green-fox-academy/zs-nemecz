/* Includes ------------------------------------------------------------------*/
#include "socket_client.h"
#include "socket_server.h"
#include "lcd_log.h"
#include "cmsis_os.h"
#include "app_ethernet.h"
#include "lwip/sockets.h"
#include "stm32746g_discovery_ts.h"
#include <string.h>

/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

// TODO:
// Implement this function!
void socket_client_thread(void const *argument)
{
	char remote_ip[20] = "10.27.6.120";
	int remote_port = 54545;
	uint8_t send_buffer_size = 8;
	uint8_t send_buffer[send_buffer_size];

	char test_buffer[100] = "hello Zsuzska!";
	int test_buffer_size = 14;

	// Wait for IP address
	while(!is_ip_ok())
		osDelay(100);

	// Create a client socket
	int client_socket;
	client_socket = lwip_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (client_socket < 0) {
		LCD_ErrLog((char*) "Cannot create client socket\n");
		LCD_ErrLog((char*) "Closing application\n");
		osThreadTerminate(NULL);
	}

	// Create client address structure
	struct sockaddr_in client_addr;
	client_addr.sin_family = AF_INET;
	client_addr.sin_addr.s_addr = inet_addr(remote_ip);
	client_addr.sin_port = htons(remote_port);

	// Connect to server
	int connection_result = lwip_connect(client_socket, (struct sockaddr*) &client_addr, sizeof(client_addr));
	if (connection_result < 0) {
		LCD_ErrLog((char*) "Cannot connect to server\n");
		LCD_ErrLog((char*) "Closing application\n");
		lwip_close(client_socket);
		osThreadTerminate(NULL);
	}

	// Send data
	int cnt = 0;
	while (1) {

		// Give processor time to other threads too
		osDelay(10);

		int send_result = lwip_send(client_socket, send_buffer, send_buffer_size, 0);
		if (send_result <= 0) {
			LCD_ErrLog((char*) "Could not send all data.\n");
			LCD_ErrLog((char*) "Closing application\n");
			break;
		} else {
			LCD_DbgLog((char*) "Msg sent\n");
		}
		cnt++;
		if (cnt > 2)
			break;
	}

	// Close socket
	lwip_close(client_socket);

	// End thread
	while (1) {
		osThreadTerminate(NULL);
	}
}

uint8_t* serialize_uint32(uint8_t *buffer, uint32_t value)
{
  // Write big-endian int value into buffer
  // Assumes 32-bit int and 8-bit char.
    buffer[0] = value >> 24;
    buffer[1] = value >> 16;
    buffer[2] = value >> 8;
    buffer[3] = value;
    return buffer + 4;
}

uint8_t* serialize_uint16(uint8_t *buffer, uint16_t value)
{
  // Write big-endian int value into buffer
  // Assumes 32-bit int and 8-bit char.
    buffer[0] = value >> 8;
    buffer[1] = value;
    return buffer + 2;
}

uint8_t* serialize_uint8(uint8_t *buffer, uint8_t value)
{
    buffer[0] = value;
    return buffer + 1;
}

uint8_t* serialize_screen_data(uint8_t *buffer, screen_t* screen_data)
{
    buffer = serialize_uint8(buffer, screen_data->touch);
    buffer = serialize_uint16(buffer, screen_data->x);
    buffer = serialize_uint16(buffer, screen_data->y);
    buffer = serialize_uint8(buffer, screen_data->color);
    buffer = serialize_uint8(buffer, screen_data->l_weight);
    buffer = serialize_uint8(buffer, screen_data->clr_scr);

    return buffer;
}

uint8_t send_screen(int socket, screen_t* screen_data)
{
    uint8_t buffer[12];
    uint8_t* ptr;

    ptr = serialize_screen_data(buffer, screen_data);
    return (lwip_send(socket, buffer, ptr - buffer, 0) == ptr - buffer);
}

uint8_t deserialize_screen_data(uint8_t* buffer, screen_t* screen_data)
{
    screen_data->touch = buffer[0];
    screen_data->x = buffer[1] << 8 | buffer[2];
    screen_data->y = buffer[3] << 8 | buffer[4];
    screen_data->color = buffer[5];
    screen_data->l_weight = buffer[6];
    screen_data->clr_scr = buffer[7];

    return 0;
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
