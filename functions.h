/*
 * functions.h
 *
 *  Created on: Jul 17, 2013
 *      Author: Grzegorz
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

volatile char received_string[100]; // this will hold the recieved string
volatile uint32_t a;
volatile uint32_t b;
volatile int flag; //flag =0 ; flag=1 odebralem;

void SysTick_Handler(void);
void GPIO_initialization(void);
void USART1_initialization(void);
void USART_puts(USART_TypeDef* USARTx, volatile char *s);
void receive_frame(const char *check_word);



#endif /* FUNCTIONS_H_ */
