/*
 * uart1.h
 *
 * Created: 29/11/2024 3:05:39 pm
 *  Author: Yu Heng
 */ 


#ifndef UART1_H_
#define UART1_H_

void uart1_init(void);
void uart1_tx_char(char c);
char uart1_rx_char(void);
void uart1_tx_string(char str[]);
const uint8_t* uart1_rx_string(void);

#define RX1_BUFFER_SIZE 128

#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))


#endif /* UART1_H_ */