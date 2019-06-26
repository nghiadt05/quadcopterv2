#ifndef TM1_OVF_H
#define TM1_OVF_H

#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "delay.h"
#include "my_usart.h"

#define fix_ovf_tm1_count 5//ms

//------ list of variables --------
extern uint32_t ovf_tm1_count,loop_time,last_ovf_tm1_count;
//---------------------------------

//------ list of functions --------
void TM1_OVF_Configuration(void);
void TIM1_UP_TIM10_IRQHandler(void);
void fix_loop_time(void);
//---------------------------------

#endif
