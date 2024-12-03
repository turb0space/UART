/*
 * main.c
 *
 * Created: 29/11/2024 4:40:35 pm
 *  Author: Yu Heng
 */ 

#include "include/uart.h"
#include "include/uart1.h"
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/io.h>

int main() {
	
	uart_init(); // 57600
	uart1_init(); // Initialize UART, Baud Rate 9600
	sei(); // Enable Interrupts

	char *received_str = uart1_rx_string(); // receive by calling rx function
	printf("%s\r\n", received_str);
	uart1_tx_string(received_str); // send the received string
	
	return 0;
}