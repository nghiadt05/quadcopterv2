#ifndef RX_H_
#define RX_H_

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"
#include "stm32f4xx_syscfg.h"
#include "pid.h"
#include "motor.h"

#define TIM2_MAX_COUNT 		50000
#define RX_NOISE				 	50

#define MIN_CH0			 	 2498//role
#define MID_CH0				 2898
#define MAX_CH0				 3288
#define CH0_RANGE			 790

#define MIN_CH1				 2100//pitch
#define MID_CH1				 2895
#define MAX_CH1				 3680
#define CH1_RANGE			 1580

#define MIN_CH2				 2120//throttle
#define MID_CH2				 2902
#define MAX_CH2				 3697
#define CH2_RANGE			 1577

#define MIN_CH3				 2118//yaw
#define MID_CH3				 2934
#define MAX_CH3				 3702

#define MIN_CH4				 1846//switch
#define MID_CH4				 2905
#define MAX_CH4				 3964

#define MIN_CH5				 1846//VRa
#define MID_CH5				 2889
#define MAX_CH5				 3962


extern uint32_t TCNT_LAST[6];
extern uint32_t TCNT_NOW[6];
extern uint32_t TM_OVF_COUNT_LAST[6];
extern uint32_t TM_OVF_COUNT_NOW[6];
extern uint8_t RX_RECEIVE_DONE[6];
extern uint32_t PULSE_VALUES[6];
extern uint8_t RX_CACULATED[6];
extern uint32_t TM2_OVF_COUNT;
extern float rx_caculated_value[6];
extern uint8_t start,_1st_run,run;
extern uint8_t yaw_stick_pos;

void RX_Configuration(void);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void RX_Calculation(void);
void TIM2_IRQHandler(void);
void CHECK_1ST_RUN(void);
void CHECK_START_STT(void);

#endif
