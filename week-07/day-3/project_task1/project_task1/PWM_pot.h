#ifndef TC0_PWM_DRIVER_H_
#define TC0_PWM_DRIVER_H_

#include <stdint.h>

void FAST_PWM_init();
void set_PWM_duty(uint8_t duty);

#endif /* TC0_PWM_DRIVER_H_ */
