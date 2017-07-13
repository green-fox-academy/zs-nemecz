/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LED_MATRIX_H
#define __LED_MATRIX_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "stm32746g_discovery_ts.h"
#include <stdlib.h>

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define LED_MATRIX_COLS		5
#define LED_MATRIX_ROWS		7

/* TS variables */
#define TS_CLICK_THRESHOLD	25

uint8_t first_touch_flag;
uint8_t possible_click_event;

typedef struct {
    uint16_t x;
    uint16_t y;
} coordinate_t;

coordinate_t last_ts_coord;
coordinate_t first_ts_coord;
TS_StateTypeDef TS_State;
uint8_t current_action; //Variable to select from menu options. Default: Waterfall animation

/*Menu defines*/
//ANIMATIONS
#define TEXT_START_X		5
#define TEXT_START_Y		3
#define TEXT_ANI1_Y			45
#define TEXT_ANI2_Y			135
#define TEXT_ANI3_Y			225
//LED MATRIX
#define LED_MATRIX_X		140
#define LED_MATRIX_Y		17
#define LED_MATRIX_W		190
#define LED_MATRIX_H		238

#define LED_R				14

#define LED_COL_1			159
#define LED_COL_2			197
#define LED_COL_3			235
#define LED_COL_4			273
#define LED_COL_5			311

#define LED_ROW_1			34
#define LED_ROW_2			68
#define LED_ROW_3			102
#define LED_ROW_4			136
#define LED_ROW_5			170
#define LED_ROW_6			204
#define LED_ROW_7			238


/* Exported functions ------------------------------------------------------- */
void led_matrix_update_thread(void const *argument);
void led_matrix_set_animation_thread(void const *argument);
void adc_thread(void const *argument);
void display_menu(void);
void select_animation(void);
void touch_detect(void);
void clear_leds(void);
void set_lcd_led_display(void);
void clear_lcd_led_display(void);
void set_LED(void);
void waterfall(void);
void falling_dot(void);

#endif /* __LED_MATRIX_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
