#ifndef MOTOR_H_
#define MOTOR_H_

#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "rx.h"

//extern uint32_t tm5_ovf_count;
#define PWM_STOP 				2100
#define PWM_WARNING			2210
#define PWM_MIN	 				2300
#define PWM_MAX	 				3800
#define PWM_RANGE 			1590

void Motor_Configuration(void);
void MOTOR_ON_OFF(void);
void TIM5_IRQHandler(void);
void MOTOR_ARMING(void);
void MOTOR_WARNING(void);

#endif
