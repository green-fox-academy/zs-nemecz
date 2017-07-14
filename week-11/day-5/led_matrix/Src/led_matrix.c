/* Includes ------------------------------------------------------------------*/
#include "led_matrix.h"
#include "stm32f7xx_hal.h"
#include "lcd_log.h"
#include "cmsis_os.h"
#include "stm32f7xx_hal_gpio.h"
#include "stm32f7xx_hal_adc.h"
#include "socket_server.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

// Each LED state is stored in this 2D array
GPIO_PinState led_matrix_state[LED_MATRIX_ROWS][LED_MATRIX_COLS];

// Mutex definition
osMutexDef(LED_MATRIX_MUTEX_DEF);

// Mutex global variable
osMutexId led_matrix_mutex_id;

//Message thread definition
osMessageQDef(message_adc, 1, uint32_t); // Declare a message queue
osMessageQId (message_adc_id);           // Declare an ID for the message queue

/* Private function prototypes -----------------------------------------------*/
void led_matrix_set(uint8_t row, uint8_t col, uint8_t state);
/* Private functions ---------------------------------------------------------*/


void led_matrix_set(uint8_t row, uint8_t col, uint8_t state)
{
	// Wait for the mutex
	osMutexWait(led_matrix_mutex_id, osWaitForever);
	// Change the LED in the selected row and col to the specified state
	// Use the led_matrix_state 2D array variable!
	led_matrix_state [row][col] = state;
	// Release the mutex
	osMutexRelease(led_matrix_mutex_id);
}

// TODO:
// Write this function!
void led_matrix_update_thread(void const *argument)
{
	// TODO:
	// Initialize the pins as outputs and the led_matrix_state 2D array
	__HAL_RCC_GPIOI_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();

	GPIO_InitTypeDef  gpio_initColumns;
	GPIO_InitTypeDef  gpio_initRows;

	gpio_initRows.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_6 | GPIO_PIN_7; //PI0
	gpio_initRows.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_initRows.Pull = GPIO_NOPULL;
	gpio_initRows.Speed = GPIO_SPEED_FREQ_HIGH;

	gpio_initColumns.Pin = GPIO_PIN_4 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_14 | GPIO_PIN_15; 	//PB15
	gpio_initColumns.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_initColumns.Pull = GPIO_NOPULL;
	gpio_initColumns.Speed = GPIO_SPEED_FREQ_HIGH;

	HAL_GPIO_Init(GPIOI, &gpio_initRows);
	HAL_GPIO_Init(GPIOG, &gpio_initRows);
	HAL_GPIO_Init(GPIOH, &gpio_initRows);
	HAL_GPIO_Init(GPIOB, &gpio_initColumns);

	HAL_GPIO_WritePin(GPIOI, GPIO_PIN_0, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOI, GPIO_PIN_1, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOI, GPIO_PIN_2, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOI, GPIO_PIN_3, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOH, GPIO_PIN_6, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, GPIO_PIN_SET);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);

	uint16_t pin_cols [5] = {
		GPIO_PIN_8,
		GPIO_PIN_14,
		GPIO_PIN_15,
		GPIO_PIN_9,
		GPIO_PIN_4,
	};

	uint16_t pin_rows [7] = {
		GPIO_PIN_1,
		GPIO_PIN_2,
		GPIO_PIN_3,
		GPIO_PIN_0,
		GPIO_PIN_6,
		GPIO_PIN_7,
		GPIO_PIN_6,
	};

	// TODO:
	// Create a mutex
	// Use the LED_MATRIX_MUTEX_DEF
	led_matrix_mutex_id = osMutexCreate(osMutex(LED_MATRIX_MUTEX_DEF));

	//LCD_UsrLog("led_matrix - initialized\n");

	// Infinite loop
	while (1) {
		// TODO:
		// Implement the led matrix updater functionality

		// Step 1:
		// Iterate through every column or row
		for (int r = 0; r < LED_MATRIX_ROWS; r++) {
			// Step 2:
			// Wait for the mutex
			osMutexWait(led_matrix_mutex_id, osWaitForever);

			// Step 3:
			// Turn on the column or row
			if (r < 4) {
					HAL_GPIO_WritePin(GPIOI, pin_rows[r], 0);
				} else if (r == 4 ) {
					HAL_GPIO_WritePin(GPIOH, pin_rows[r], 0);
				} else if (r > 4) {
					HAL_GPIO_WritePin(GPIOG, pin_rows[r], 0);
			}

			// Step 4:
			// Turn on the leds in that column or row
			for (int c = 0; c < LED_MATRIX_COLS; c++) {
				HAL_GPIO_WritePin(GPIOB, pin_cols[c], led_matrix_state[r][c]);
			}

			// Step 5:
			// Release the mutex
			osMutexRelease(led_matrix_mutex_id);

			// Step 6:
			// Delay
			osDelay(1);

			// Step 7:
			// Turn off the column or row
			if (r < 4) {
				HAL_GPIO_WritePin(GPIOI, pin_rows[r], 1);
			} else if (r == 4 ) {
				HAL_GPIO_WritePin(GPIOH, pin_rows[r], 1);
			} else if (r > 4) {
				HAL_GPIO_WritePin(GPIOG, pin_rows[r], 1);
			}

		}
	}

	// Terminating thread
	while (1) {
		LCD_ErrLog("led_matrix - terminating...\n");
		osThreadTerminate(NULL);
	}
}

// Display menu, select animation and set the led_matrix_state accordingly
void led_matrix_set_animation_thread(void const *argument)
{
	display_menu();

	uint8_t previous_action = 0;
	current_action = 0; //Default action: Falling dot animation

	while (1) {

		touch_detect();
		if (current_action != previous_action)
			clear_leds();

		previous_action = current_action;

		/*Play Animation */
		if (current_action == 0) {
			waterfall();
		} else if (current_action == 1) {
			set_LED();
			touch_detect();
			if (current_action != 1)
				clear_leds();
		} else if (current_action == 2) {
			falling_dot();
			touch_detect();
			if (current_action != 2)
				clear_leds();
		} else if (current_action == 3) {
			fill_up();
			touch_detect();
			if (current_action != 3)
				clear_leds();
		} else if (current_action == 4) {
			letters();
			touch_detect();
			if (current_action != 4)
				clear_leds();
		}
	}

	while (1) {
		osThreadTerminate(NULL);
	}
}

void adc_thread(void const *argument)
{
	/* Create message queue */
	message_adc_id = osMessageCreate(osMessageQ(message_adc), NULL);

	__HAL_RCC_ADC3_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	ADC_InitTypeDef adc_init_struc;
	ADC_HandleTypeDef adc_handle;
	ADC_ChannelConfTypeDef adc_channel;

	adc_init_struc.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV8;
	adc_init_struc.Resolution = ADC_RESOLUTION_12B;
	adc_init_struc.DataAlign = ADC_DATAALIGN_RIGHT;
	adc_init_struc.ContinuousConvMode = DISABLE;
	adc_init_struc.DiscontinuousConvMode = DISABLE;
	adc_init_struc.ExternalTrigConv = ADC_SOFTWARE_START;
	adc_init_struc.EOCSelection = DISABLE;

	adc_handle.Instance = ADC3;
	adc_handle.Init = adc_init_struc;

	adc_channel.Channel = ADC_CHANNEL_0;
	adc_channel.Offset = 0;
	adc_channel.Rank = 1;
	adc_channel.SamplingTime = ADC_SAMPLETIME_3CYCLES;

	HAL_ADC_Init(&adc_handle);
	HAL_ADC_ConfigChannel(&adc_handle, &adc_channel);
	HAL_ADC_Start(&adc_handle);

	uint32_t adc_data = 0;

	while (1) {
		//ADC
		//char buff[100];
		HAL_ADC_Start(&adc_handle);
		HAL_ADC_PollForConversion(&adc_handle, HAL_MAX_DELAY);
		adc_data = HAL_ADC_GetValue(&adc_handle);
		//adc_data = 12;
		//sprintf(buff, "ADC data: %d \n", adc_data);
		//LCD_UsrLog((char *)buff);
		osMessagePut(message_adc_id, adc_data, osWaitForever);
		//osDelay(100);
	}

	while (1) {
		LCD_ErrLog("ADC terminating...\n");
		osThreadTerminate(NULL);
	}
}

void display_menu(void)
{
	BSP_LCD_SetFont(&Font16);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(TEXT_START_X, TEXT_START_Y, "Animations", LEFT_MODE);
	BSP_LCD_FillRect(LED_MATRIX_X, LED_MATRIX_Y, LED_MATRIX_W, LED_MATRIX_H);
	BSP_LCD_DisplayStringAt(TEXT_START_X_RIGHT, TEXT_ANI1_Y, "Messages:", LEFT_MODE);

	BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
	BSP_LCD_DisplayStringAt(TEXT_START_X, TEXT_ANI1_Y, "Waterfall", LEFT_MODE);
	BSP_LCD_DisplayStringAt(TEXT_START_X, TEXT_ANI2_Y, "Falling Dot", LEFT_MODE);
	BSP_LCD_DisplayStringAt(TEXT_START_X, TEXT_ANI3_Y, "Fill Up", LEFT_MODE);

	//ROW 1
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
	BSP_LCD_FillCircle(LED_COL_1, LED_ROW_1, LED_R);
	BSP_LCD_FillCircle(LED_COL_2, LED_ROW_1, LED_R);
	BSP_LCD_FillCircle(LED_COL_3, LED_ROW_1, LED_R);
	BSP_LCD_FillCircle(LED_COL_4, LED_ROW_1, LED_R);
	BSP_LCD_FillCircle(LED_COL_5, LED_ROW_1, LED_R);

	//ROW 2
	BSP_LCD_FillCircle(LED_COL_1, LED_ROW_2, LED_R);
	BSP_LCD_FillCircle(LED_COL_2, LED_ROW_2, LED_R);
	BSP_LCD_FillCircle(LED_COL_3, LED_ROW_2, LED_R);
	BSP_LCD_FillCircle(LED_COL_4, LED_ROW_2, LED_R);
	BSP_LCD_FillCircle(LED_COL_5, LED_ROW_2, LED_R);

	//ROW 3
	BSP_LCD_FillCircle(LED_COL_1, LED_ROW_3, LED_R);
	BSP_LCD_FillCircle(LED_COL_2, LED_ROW_3, LED_R);
	BSP_LCD_FillCircle(LED_COL_3, LED_ROW_3, LED_R);
	BSP_LCD_FillCircle(LED_COL_4, LED_ROW_3, LED_R);
	BSP_LCD_FillCircle(LED_COL_5, LED_ROW_3, LED_R);

	//ROW 4
	BSP_LCD_FillCircle(LED_COL_1, LED_ROW_4, LED_R);
	BSP_LCD_FillCircle(LED_COL_2, LED_ROW_4, LED_R);
	BSP_LCD_FillCircle(LED_COL_3, LED_ROW_4, LED_R);
	BSP_LCD_FillCircle(LED_COL_4, LED_ROW_4, LED_R);
	BSP_LCD_FillCircle(LED_COL_5, LED_ROW_4, LED_R);

	//ROW 5
	BSP_LCD_FillCircle(LED_COL_1, LED_ROW_5, LED_R);
	BSP_LCD_FillCircle(LED_COL_2, LED_ROW_5, LED_R);
	BSP_LCD_FillCircle(LED_COL_3, LED_ROW_5, LED_R);
	BSP_LCD_FillCircle(LED_COL_4, LED_ROW_5, LED_R);
	BSP_LCD_FillCircle(LED_COL_5, LED_ROW_5, LED_R);

	//ROW 6
	BSP_LCD_FillCircle(LED_COL_1, LED_ROW_6, LED_R);
	BSP_LCD_FillCircle(LED_COL_2, LED_ROW_6, LED_R);
	BSP_LCD_FillCircle(LED_COL_3, LED_ROW_6, LED_R);
	BSP_LCD_FillCircle(LED_COL_4, LED_ROW_6, LED_R);
	BSP_LCD_FillCircle(LED_COL_5, LED_ROW_6, LED_R);

	//ROW 7
	BSP_LCD_FillCircle(LED_COL_1, LED_ROW_7, LED_R);
	BSP_LCD_FillCircle(LED_COL_2, LED_ROW_7, LED_R);
	BSP_LCD_FillCircle(LED_COL_3, LED_ROW_7, LED_R);
	BSP_LCD_FillCircle(LED_COL_4, LED_ROW_7, LED_R);
	BSP_LCD_FillCircle(LED_COL_5, LED_ROW_7, LED_R);

}

void select_animation(void)
{
	if (TS_State.touchX[0] > 140 && TS_State.touchX[0] < 330) {
		current_action = 1;
	} else if (TS_State.touchX[0] < 140 && TS_State.touchY[0] < 90) {
		clear_lcd_led_display();
		clear_leds();
		current_action = 0;
	} else if (TS_State.touchX[0] < 140 && TS_State.touchY[0] > 90 && TS_State.touchY[0] < 180) {
		clear_lcd_led_display();
		clear_leds();
		current_action = 2;
	} else if (TS_State.touchX[0] < 140 && TS_State.touchY[0] > 180) {
		clear_lcd_led_display();
		clear_leds();
		current_action = 3;
	} else if (TS_State.touchX[0] > 330) {
		current_action = 4;
	}
}

void touch_detect(void)
{
	BSP_TS_GetState(&TS_State);
		if (TS_State.touchDetected > 0)
			select_animation();
}

void clear_leds(void)
{
	for (uint8_t c = 0; c < LED_MATRIX_COLS; c++) {
		for (uint8_t r = 0; r < LED_MATRIX_ROWS; r++) {
			led_matrix_set(r, c, 0);
			}
		}
	osDelay(3);
}

void set_lcd_led_display(void)
{
	uint16_t row_array[7] = {
		LED_ROW_1,
		LED_ROW_2,
		LED_ROW_3,
		LED_ROW_4,
		LED_ROW_5,
		LED_ROW_6,
		LED_ROW_7
	};

	uint16_t col_array[5] = {
		LED_COL_1,
		LED_COL_2,
		LED_COL_3,
		LED_COL_4,
		LED_COL_5,
	};

	for (uint8_t c = 0; c < LED_MATRIX_COLS; c++) {
		for (uint8_t r = 0; r < LED_MATRIX_ROWS; r++) {
			if (led_matrix_state[r][c] == 1) {
				BSP_LCD_SetTextColor(LCD_COLOR_RED);
				BSP_LCD_FillCircle(col_array[c], row_array[r], LED_R);
			} else {
				BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
				BSP_LCD_FillCircle(col_array[c], row_array[r], LED_R);
			}
		}
	}
}

void clear_lcd_led_display(void)
{
	uint16_t row_array[7] = {
		LED_ROW_1,
		LED_ROW_2,
		LED_ROW_3,
		LED_ROW_4,
		LED_ROW_5,
		LED_ROW_6,
		LED_ROW_7
	};

	uint16_t col_array[5] = {
		LED_COL_1,
		LED_COL_2,
		LED_COL_3,
		LED_COL_4,
		LED_COL_5,
	};

	for (uint8_t c = 0; c < LED_MATRIX_COLS; c++) {
		for (uint8_t r = 0; r < LED_MATRIX_ROWS; r++) {
			if (led_matrix_state[r][c] == 1) {
				BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
				BSP_LCD_FillCircle(col_array[c], row_array[r], LED_R);
			}
		}
	}
}

void falling_dot(void)
{
	BSP_LCD_SetTextColor(LCD_COLOR_RED);
	BSP_LCD_DisplayStringAt(TEXT_START_X, TEXT_ANI2_Y, "Falling Dot", LEFT_MODE);
	int32_t delay = 100;
	for (uint8_t c = 0; c < LED_MATRIX_COLS; c++) {
		for (uint8_t r = 0; r < LED_MATRIX_ROWS; r++) {
			//check whether current_action has changed (a touch has been detected)
			touch_detect();
			if (current_action != 2) {
				r = LED_MATRIX_ROWS;
				c = LED_MATRIX_COLS;
				clear_leds();
				display_menu();
			} else {
				led_matrix_set(r, c, 1);
				set_lcd_led_display();
				osEvent event = osMessageGet(message_adc_id, osWaitForever);
				delay = event.value.v / 100;
				osDelay(delay);
				led_matrix_set(r, c, 0);
				set_lcd_led_display();
			}
		}
	}
}

void waterfall(void)
{
	int32_t delay = 100;
	BSP_LCD_SetTextColor(LCD_COLOR_RED);
	BSP_LCD_DisplayStringAt(TEXT_START_X, TEXT_ANI1_Y, "Waterfall", LEFT_MODE);
	for (uint8_t r = 0; r < LED_MATRIX_ROWS - 1; r++) {
		//check whether current_action has changed (a touch has been detected)
		touch_detect();
		if (current_action != 0) {
			r = LED_MATRIX_ROWS;
			clear_leds();
			display_menu();
		} else {
				led_matrix_set(r, 0, 1);
				led_matrix_set(r, 1, 1);
				led_matrix_set(r, 2, 1);
				led_matrix_set(r, 3, 1);
				led_matrix_set(r, 4, 1);
				led_matrix_set(r + 1, 1, 1);
				led_matrix_set(r + 1, 3, 1);
				set_lcd_led_display();
				osEvent event = osMessageGet(message_adc_id, osWaitForever);
				delay = event.value.v / 100;
				osDelay(delay);
		}
	}
	clear_leds();
	set_lcd_led_display();
}

void fill_up(void)
{
	int32_t delay = 100;
	BSP_LCD_SetTextColor(LCD_COLOR_RED);
	BSP_LCD_DisplayStringAt(TEXT_START_X, TEXT_ANI3_Y, "Fill Up", LEFT_MODE);
	for (uint8_t c = 0; c < LED_MATRIX_COLS; c++) {
		for (int8_t i = 6; i > -1; i--) {
			for (uint8_t r = 0; r < LED_MATRIX_ROWS; r++) {
				/*check whether current_action has changed (a touch has been detected)*/
				touch_detect();
				if (current_action != 3) {
					r = LED_MATRIX_ROWS;
					c = LED_MATRIX_COLS;
					i = -1;
					clear_leds();
					display_menu();
				}
				/*end of checking current action*/
				led_matrix_set(r, c, 1);
				set_lcd_led_display();
				osEvent event = osMessageGet(message_adc_id, osWaitForever);
				delay = event.value.v / 100;
				if (i == r) {
					r = LED_MATRIX_ROWS;
				} else {
					osDelay(delay);
					led_matrix_set(r, c, 0);
				}
			}
		}
	}
	clear_leds();
	set_lcd_led_display();
}

void set_LED(void)
{
	uint8_t c;
	uint8_t r;

	uint16_t diffX;
	uint16_t diffY;

	first_ts_coord.x = 0;
	first_ts_coord.y = 0;

	BSP_TS_GetState(&TS_State);
		while(TS_State.touchDetected > 0) {
			diffX =  TS_State.touchX[0] - first_ts_coord.x;
			diffY =  TS_State.touchY[0] - first_ts_coord.y;

			if (abs(diffX) > TS_CLICK_THRESHOLD || abs(diffY) > TS_CLICK_THRESHOLD) {
				last_ts_coord.x = TS_State.touchX[0];
				last_ts_coord.y = TS_State.touchY[0];

				/* Select row */
				if (TS_State.touchY[0] > 17 && TS_State.touchY[0] <= 51)
					r = 0;
				else if (TS_State.touchY[0] > 51 && TS_State.touchY[0] <= 85)
					r = 1;
				else if (TS_State.touchY[0] > 85 && TS_State.touchY[0] <= 119)
					r = 2;
				else if (TS_State.touchY[0] > 119 && TS_State.touchY[0] <= 153)
					r = 3;
				else if (TS_State.touchY[0] > 153 && TS_State.touchY[0] <= 187)
					r = 4;
				else if (TS_State.touchY[0] > 187 && TS_State.touchY[0] <= 221)
					r = 5;
				else if (TS_State.touchY[0] > 221 && TS_State.touchY[0] <= 255)
					r = 6;

				/* Select col */
				if (TS_State.touchX[0] > 140 && TS_State.touchX[0] <= 178)
					c = 0;
				if (TS_State.touchX[0] > 178 && TS_State.touchX[0] <= 216)
					c = 1;
				if (TS_State.touchX[0] > 216 && TS_State.touchX[0] <= 254)
					c = 2;
				if (TS_State.touchX[0] > 254 && TS_State.touchX[0] <= 292)
					c = 3;
				if (TS_State.touchX[0] > 292 && TS_State.touchX[0] <= 380)
					c = 4;

				//Clear whole matrix if outside of range
				if (TS_State.touchY[0] < 17 || TS_State.touchY[0] > 255) {
					clear_leds();
					clear_lcd_led_display();
				} else {
					led_matrix_set(r,c, !(led_matrix_state[r][c]));
					set_lcd_led_display();
				}

				first_ts_coord.x = last_ts_coord.x;
				first_ts_coord.y = last_ts_coord.y;
				touch_detect();
			} else {
				osDelay(50);
				touch_detect();
			}
			if (current_action != 1){
				break;
			}
		}
}

void letters(void)
{
	uint8_t alphabets[130]={
	0x7e, 0x09, 0x09, 0x09, 0x7e, // A
	0x7f, 0x49, 0x49, 0x49, 0x36,  // B
	0x3e, 0x41, 0x41, 0x41, 0x22,
	0x7f, 0x41, 0x41,0x22, 0x1c,
	0x7f, 0x49, 0x49, 0x49, 0x63,
	0x7f, 0x09, 0x09, 0x09, 0x01,
	0x3e, 0x41, 0x41, 0x49, 0x7a,
	0x7f, 0x08, 0x08, 0x08, 0x7f,
	0x00, 0x41, 0x7f, 0x41, 0x00,  // I
	0x20, 0x40, 0x41, 0x3f, 0x01,
	0x7f, 0x08, 0x14, 0x22, 0x41,
	0x7f, 0x40, 0x40, 0x40, 0x60,
	0x7f, 0x02, 0x04, 0x02, 0x7f,
	0x7f, 0x04, 0x08, 0x10, 0x7f,
	0x3e, 0x41, 0x41, 0x41, 0x3e,
	0x7f, 0x09, 0x09, 0x09, 0x06,
	0x3e, 0x41, 0x51, 0x21, 0x5e,
	0x7f, 0x09, 0x19, 0x29, 0x46,
	0x46, 0x49, 0x49, 0x49, 0x31,  // S
	0x01, 0x01, 0x7f, 0x01, 0x01,
	0x3f, 0x40, 0x40, 0x40, 0x3f,
	0x1f, 0x20, 0x40, 0x20, 0x1f,
	0x3f, 0x40, 0x30, 0x40, 0x3f,
	0x63, 0x14, 0x08, 0x14, 0x63,
	0x07, 0x08, 0x70, 0x08, 0x07,
	0x61, 0x51, 0x49, 0x45, 0x43 // Z
	};

	for (uint8_t i = 0; i < strlen(buff); i++) {
	uint8_t abc = (buff[i] - 65) * 5; // index of the letter in the 'alphabets' array based on ASCII value
		for (uint8_t c = 0; c < LED_MATRIX_COLS; c++) {
			 for (uint8_t r = 0; r < LED_MATRIX_ROWS; r++) {
				led_matrix_set(r, c, (alphabets[c + abc] & (1 << r)));
			 }
		}
		//set_lcd_led_display();
		touch_detect();
		if (current_action != 4)
			clear_leds();
		osDelay(800);
	}
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
