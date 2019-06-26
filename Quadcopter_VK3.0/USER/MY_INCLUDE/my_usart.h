#ifndef MY_USART_H
#define MY_USART_H

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"
#include <stdio.h>
#include "misc.h"

#define usart_1
#define usart_2
#define usart_3
#define usart_6

//-------- list of variables ----------
extern uint8_t usart_port;
//-------------------------------------

//-------- list of functions ----------
void usart_putchar(USART_TypeDef* USARTx, uint16_t Data);

#ifdef usart_1
void USART1_Config(uint32_t baudrate);
//void USART1_IRQHandler(void);//move to processing.h
#endif

#ifdef usart_2
void USART2_Config(uint32_t baudrate);
//void USART2_IRQHandler(void);
#endif

#ifdef usart_3
void USART3_Config(uint32_t baudrate);
//void USART3_IRQHandler(void);
#endif

#ifdef usart_6
void USART6_Config(uint32_t baudrate);
//void USART6_IRQHandler(void);//move to processing.h
#endif

//-------------------------------------

#endif

