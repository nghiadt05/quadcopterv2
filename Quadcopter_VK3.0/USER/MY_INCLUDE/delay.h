#ifndef __DELAY_H
#define __DELAY_H
#include "stm32f4xx.h"
#include "misc.h"
 
void Delay_Init(void);
void delay_us(u32 n);
void delay_ms(u32 n);
void delay(__IO uint32_t nCount);
void SysTick_Handler(void); 
#endif
