/* Includes ------------------------------------------------------------------*/
#include "socket_server.h"
#include "socket_client.h"
#include "stm32746g_discovery_ts.h"
#include "lcd_log.h"
#include "cmsis_os.h"
#include "app_ethernet.h"
#include "lwip/sockets.h"
#include "stm32746g_discovery_ts.h"
#include <string.h>

/* Private typedef -----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/
typedef struct {
	uint16_t x;
	uint16_t y;
} coordinate_t;

/* Private define ------------------------------------------------------------*/
#define LCD_FRAME_BUFFER			SDRAM_DEVICE_ADDR
#define RGB_565_BYTE_PER_PIXEL		2
#define ARGB_BYTE_PER_PIXEL			4
#define BUTTON_X					456
#define BUTTON1_Y					22
#define BUTTON2_Y					62
#define BUTTON3_Y					124
#define BUTTON_SIZE					20

/* Private macro -------------------------------------------------------------*/
#define SERVER_IP			"10.27.6.120"
#define QUEUE_SIZE 			1
#define SOCKET_ERROR		-1
/* Private variables ---------------------------------------------------------*/
int msg_cntr = 0;
TS_StateTypeDef  TS_State;
coordinate_t touch_current;
coordinate_t touch_previous;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void display_Menu(void);

// TODO:
// Implement this function!
void socket_server_thread(void const *argument)
{
	// Server address structure initialization
	struct sockaddr_in addr_in;                                 // Inet address structure definition
	addr_in.sin_family = AF_INET;                               // This address is an internet address
	addr_in.sin_port = htons(54545);                      		// Server port
	addr_in.sin_addr.s_addr = 0;             					// Server IP
	struct sockaddr *addr = (struct sockaddr *)&addr_in;        // Make a struct sockaddr pointer, which points to the address stucture

	int master_socket = socket(PF_INET, SOCK_STREAM, 0);
	int flag = bind(master_socket, addr, sizeof(*addr));
	if (flag < 0)
		LCD_ErrLog((char *)"Binding failed.\n");

	flag = listen(master_socket, QUEUE_SIZE);
	// Check is listening is ok
	if (flag < 0)
		LCD_ErrLog((char *)"Listening failed\n");

	// Create variables which will be used in the while loop
	struct sockaddr client_addr;    		// Client address structure
	int slave_socket;              			// Slave socket definition, this will be used to store the incoming socket
	uint8_t buff[SERVER_BUFF_LEN];    		// Buffer for incoming and outgoing data
	screen_t paint;			//structure containing info about the LCD screen
	display_Menu();

	while (1) {
		osDelay(10);

		// Accept the connection and save the incoming socket
		slave_socket = accept(master_socket, &client_addr, NULL);
		// Check if the socket is valid
		if (slave_socket < 0) {
			//LCD_ErrLog((char *)"Connection not accepted.\n");
			osDelay(5);
		}

		//LCD_UsrLog((char *)"Connection accepted.\n");

		// Receive the data sent by the client
		int received_bytes;
		do {
			received_bytes = recv(slave_socket, buff, SERVER_BUFF_LEN, 0);
			if (received_bytes == 0) {
				osDelay(5);
			} else if (received_bytes == SOCKET_ERROR) {
				osDelay(10);
				break;
			} else {
				// Print out the received data
				deserialize_screen_data(buff, &paint);
				touch_current.x = paint.x;
				touch_current.y = paint.y;
				BSP_LCD_FillCircle(touch_current.x, touch_current.y, 12);
			}
		} while (received_bytes > 0);

		closesocket(slave_socket);

		}
}

void display_Menu(void)
{
	BSP_LCD_LayerDefaultInit(2, LCD_FRAME_BUFFER);
	BSP_LCD_SetLayerVisible(2, ENABLE);
	BSP_LCD_SelectLayer(2);
	BSP_LCD_SetTextColor(LCD_COLOR_RED);
	BSP_LCD_FillCircle(BUTTON_X, BUTTON1_Y, BUTTON_SIZE);
	BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
	BSP_LCD_FillCircle(BUTTON_X, BUTTON2_Y, BUTTON_SIZE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
	BSP_LCD_FillCircle(BUTTON_X, BUTTON3_Y, BUTTON_SIZE);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
