// Multiple inclusion guard
#ifndef _TC74_DRIVER_H
#define _TC74_DRIVER_H

#include <stdint.h>

#define TC_WRITE	0
#define TC_READ		1
//TODO
//Define the TC74A0 address
#define TC74A0_address  0b1001000;

void TWI_init(void);
int TWI_start();
void TWI_write(uint8_t u8data);
void TWI_stop(void);
uint8_t TWI_read_nack(void);
uint8_t TWI_read_ack(void);
uint8_t read_temp(uint8_t ic_address);
get_status();

#endif // _TC74_DRIVER_H
