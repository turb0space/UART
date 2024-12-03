/*
 * uart1.c
 *
 * Created: 29/11/2024 2:46:52 pm
 *  Author: Yu Heng
 */ 

#include <uart.h>
#include <uart1.h>
#include <avr/io.h>
#include <avr/interrupt.h>

char rx1_buffer[RX1_BUFFER_SIZE];
uint8_t rx1_read_pos = 0;
uint8_t rx1_write_pos = 0;

#define FOSC 16000000UL// Clock Speed
#define BAUD 9600
#define MYUBRR (FOSC/16/BAUD-1)

void uart1_init (void) {
	// set baud rate
	UBRR1H = (unsigned char)(MYUBRR>>8);
	UBRR1L = (unsigned char)MYUBRR;
	
	// enable
	UCSR1B = (1<<RXEN1) | (1<<TXEN1) | (1 << RXCIE1);;
	
	UCSR1C = (1<<UCSZ11) | (1<<UCSZ10);
}

void uart1_tx_char(char c) {
	loop_until_bit_is_set(UCSR1A, UDRE1);
	UDR1 = c;
}

void uart1_tx_string(char str[]) {
	for (int i = 0; i < strlen(str); i++) {
		uart1_tx_char(str[i]);
	}

	uart1_tx_char('\r');
	uart1_tx_char('\n');
}

ISR(USART1_RX_vect) {
	DDRB = 0b11111111;
	PORTB ^= (1 << PB7);
	char data = UDR1;  // Read received data
	rx1_buffer[rx1_write_pos++] = data;
	if (rx1_write_pos >= RX1_BUFFER_SIZE) {
		rx1_write_pos = 0;  // Wrap around
	}
}

char uart1_rx_char(void) {
	char ret = '\0';
	if (rx1_read_pos != rx1_write_pos) {
		ret = rx1_buffer[rx1_read_pos++];
		
		if (rx1_read_pos >= RX1_BUFFER_SIZE) {
			rx1_read_pos = 0;	
		}
	}
	
	return ret;
}

const uint8_t* uart1_rx_string(void) {
	int cntr = 0;
	static uint8_t buf[100];
	while (1) {
		uint8_t a;
		a = uart1_rx_char();
		
		if (a == 0) {
			continue;
		}
		else if (a == 10 || a == '\r' || a == 13) {
			break;
		}
		else {
			// printf("%d\r\n", a);
			buf[cntr++] = a;
		}
	}
	
	return buf;
}
