/*
 * functions.h
 *
 *  Created on: Jul 17, 2013
 *      Author: Grzegorz
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

volatile uint32_t a;
volatile uint32_t b;

void SysTick_Handler(void);
void GPIO_initialization(void);
void USART1_initialization(void);
void USART_puts(USART_TypeDef* USARTx, volatile char *s);



#endif /* FUNCTIONS_H_ */
