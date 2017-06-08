#include <avr/io.h>
#include <string.h>
#include <stdint.h>
#include "TC74_driver.h"

int get_status ()
{	int status = TWSR & (~(0b111));
	return status;
}

void TWI_init(void)
{
	// TODO:
	// Set Prescaler to 4
	TWSR &= ~(1 << TWPS1);
	TWSR |= 1 << TWPS0;
	// TODO:
	// Set SCL frequency = 16000000/ (16 + 2 * 48 * 4) = 27.648Khz
	//So set the correct register to 0x30
	TWBR = 0x30;

	// TODO
	//Enable TWI
	TWCR |= 1 << TWEN;
}

int TWI_start()
{
	//TODO
	//Send start signal
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	
	// TODO:
	// Wait for TWINT Flag set. This indicates that
	//the START condition has been transmitted.
	while(!(TWCR &(1 << TWINT)));

	int status = get_status();
	printf("status after start: %x\n\r", status);
	return status;
}

void TWI_stop(void)
{
	//TODO
	//Send stop signal
	//TWCR |= 1<<TWINT;	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
}

uint8_t TWI_read_ack(void)
{
	//TODO
	//Read byte with ACK
	//Wait for TWINT Flag set. This indicates that
	//the DATA has been transmitted, and ACK/
	//NACK has been received.
	TWCR |= 1 << TWINT;
	TWCR |= 1 << TWEA;
	while(!(TWCR &(1 << TWINT)));

	int status = get_status();
	printf("status after read with ack: %x\n\r", status);
	
	uint8_t data = TWDR;
	return data;
}


uint8_t TWI_read_nack(void)
{
	//TODO
	//Read byte with NACK
	//Wait for TWINT Flag set. This indicates that
	//the DATA has been transmitted, and ACK/
	//NACK has been received.
	TWCR |= 1 << TWINT;
	 
	while(!(TWCR &(1 << TWINT)));
	uint8_t data = TWDR;
	
	int status = get_status();
	printf("status after read with nack: %x\n\r", status);
	
	return data;
}

void TWI_write(uint8_t u8data)
{
	//TODO
	//Load DATA into TWDR Register. Clear TWINT
	//bit in TWCR to start transmission of data.
	//Wait for TWINT Flag set. This indicates that
	//the DATA has been transmitted, and ACK/
	//NACK has been received.
	
	// put data in register
	TWDR = u8data;
	TWCR = (1<<TWINT) | (1<<TWEN);	
	// wait for flag
	while(!(TWCR &(1 << TWINT)));
	
	// print status
	int status = get_status();
	printf("status after write %x\n\r", status);
}

//TODO
//Write a function that communicates with the TC74A0.
//The function need to be take the address of the ic as a parameter.
//datasheet: http://ww1.microchip.com/downloads/en/DeviceDoc/21462D.pdf
//And returns with the temperature.

uint8_t read_temp(uint8_t ic_address)
{
	//create addresses for reading and writing
	uint8_t read_address = ic_address << 1;
	read_address |= 1;
	uint8_t write_address = ic_address << 1;
	
	//start bit
	TWI_start();
	
	//address and write
	TWI_write(write_address);
	
	//write command
	TWI_write(0x00);
	
	//start bit
	TWI_start();
	
	//address and read
	TWI_write(read_address);
	
	//read temp
	uint8_t temp_data = TWI_read_nack();
	
	TWI_stop();
	
	return temp_data;
}


//TODO Advanced:
//Calculate the average of the last 16 data, and returns with that.



//TODO Advanced+:
//Select the outstanding (false data) before average it.
//These data don't needed, mess up your datas, get rid of it.
