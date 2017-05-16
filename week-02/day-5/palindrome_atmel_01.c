#include <avr/io.h>			// This header contains the definitions for the io registers
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define F_CPU	16000000	// This definition tells to _delay_ms() that the CPU runs at 16MHz
#include <util/delay.h>		// This header contains the _delay_ms() function

void Palindrome_Gen ();

void UART_Init() {
	// Write this function
	// See the datasheet on page 246 for hints and table 25-9.

	//TODO:
	// At first set the baud rate to 9600
	// The CPU clock frequency is 16MHz
	uint16_t ubbr = 103;
	UBRR0H = ubbr >> 8;
	UBRR0L = ubbr;

	//TODO:
	// Set the following frame format: 8N1
	// It is set to 8N1 by default

	//TODO:
	// Enable TX
	UCSR0B |= 1 << TXEN0;

	//TODO:
	// Enable RX
	UCSR0B |= 1 << RXEN0;
}

void UART_SendCharacter(char character) {
	// Write this function, which can send a character through UART will polling method
	// See page 247 of the datasheet for hints, be aware that the code in the datasheet has a problem :)

	//TODO:
	// Wait for empty buffer
	while ( !( UCSR0A & (1<<UDRE0)) );

	//TODO:
	// Put data to buffer
	UDR0 = character;
}

char UART_GetCharacter() {
	// Write this function, which waits for a character and returns when one is received
	// See page 249 of the datasheet for hints, be aware that the code in the datasheet has a problem :)

	//TODO:
	// Wait for data received
	while ( !(UCSR0A & (1<<RXC0)) );

	//TODO:
	// Put data to buffer
	return UDR0;
}

int main(void) {
	//char buffer[100];

	//Don't forget to call the init function :)
	UART_Init();

	// Setting up STDIO input and output buffer
	// You don't have to understand this!
	//----- START OF STDIO IO BUFFER SETUP
	FILE UART_output = FDEV_SETUP_STREAM(UART_SendCharacter, NULL, _FDEV_SETUP_WRITE);
	stdout = &UART_output;
	FILE UART_input = FDEV_SETUP_STREAM(NULL, UART_GetCharacter, _FDEV_SETUP_READ);
	stdin = &UART_input;
	//----- END OF STDIO IO BUFFER SETUP

	//TODO:
	// Try printf
	printf("Startup...\r\n");

	// Loop that runs forever
	while (1) {
		//TODO:
		// With gets and puts create a loopback, use the buffer variable!
		Palindrome_Gen ();
	}
}


void Palindrome_Gen (){

	char buffer[255];
	printf("\r\nPlease give a word: ");
	gets(buffer);
	printf("\r\nThe original word is: %s", buffer);
	//puts(word);
	//printf("%s", word);
	int string_len = strlen(buffer);
	int string_index = string_len - 1;
	//printf("\nstring length is: %d", strlen(word)); // check string len for debugging
	char palindrome [string_len];

	for (int i = 0; i < string_len; i++) {
		//printf("\n%d%c", string_index,palindrome[i]);
		palindrome[i] = buffer[string_index];
		string_index--;
		//printf("%c",palindrome[i]);

		//printf("\n%d", i);
	}
	printf("\r\nYour palindrome is: ");
	for (int i = 0; i < string_len; i++) {
		putchar(palindrome[i]);
	}
	/*for (int i = 0; i < string_len; i++) {
		putchar(buffer[i]);
	}*/
	return;
}
