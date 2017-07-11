/* Includes ------------------------------------------------------------------*/
#include "led_matrix.h"
#include "stm32f7xx_hal.h"
#include "lcd_log.h"
#include "cmsis_os.h"
#include "stm32f7xx_hal_gpio.h"
#include "stm32f7xx_hal_adc.h"

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
osMessageQDef(message_adc, 5, uint32_t); // Declare a message queue
osMessageQId (message_adc_id);           // Declare an ID for the message queue


/* Private function prototypes -----------------------------------------------*/
void led_matrix_set(uint8_t row, uint8_t col, uint8_t state);
/* Private functions ---------------------------------------------------------*/

// TODO:
// Write this function!
void led_matrix_set(uint8_t row, uint8_t col, uint8_t state) {
	// TODO:
	// Wait for the mutex
	osMutexWait(led_matrix_mutex_id, osWaitForever);
	// TODO:
	// Change the LED in the selected row and col to the specified state
	// Use the led_matrix_state 2D array variable!
	led_matrix_state [row][col] = state;
	// TODO:
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

	LCD_UsrLog("led_matrix - initialized\n");

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

// This thread is a waterfall type animation
void led_matrix_waterfall_thread(void const *argument)
{
	int32_t delay = 100;
	while (1) {
		for (uint8_t c = 0; c < LED_MATRIX_COLS; c++) {
			for (uint8_t r = 0; r < LED_MATRIX_ROWS; r++) {
				led_matrix_set(r, c, 1);
				osEvent event = osMessageGet(message_adc_id, osWaitForever);
				delay = event.value.v / 100;
				LCD_UsrLog("delay: %d ms\n", delay);
				osDelay(delay);
				led_matrix_set(r, c, 0);
			}
		}
	}

	while (1) {
		LCD_ErrLog("led_matrix_waterfall - terminating...\n");
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
		char buff[100];
		HAL_ADC_Start(&adc_handle);
		HAL_ADC_PollForConversion(&adc_handle, HAL_MAX_DELAY);
		adc_data = HAL_ADC_GetValue(&adc_handle);
		//sprintf(buff, "ADC data: %d \n", adc_data);
		//LCD_UsrLog((char *)buff);
		osMessagePut(message_adc_id, adc_data, osWaitForever);
		osDelay(100);
	}

	while (1) {
		LCD_ErrLog("ADC terminating...\n");
		osThreadTerminate(NULL);
	}
}



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
