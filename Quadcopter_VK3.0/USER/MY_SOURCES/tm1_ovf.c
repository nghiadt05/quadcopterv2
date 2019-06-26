#include "tm1_ovf.h"

//------ list of variables --------
uint32_t ovf_tm1_count,loop_time,last_ovf_tm1_count;
//---------------------------------


void TM1_OVF_Configuration(void)
{		
	//------ type define ------
	TIM_TimeBaseInitTypeDef TIM1_DELAY_Initstructure;
	NVIC_InitTypeDef TIM1_NVIC_Initstructure;
	//-------------------------
	
	//------ enable clock source -----
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	//--------------------------------
			
	//------ nvic setup --------------
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	TIM1_NVIC_Initstructure.NVIC_IRQChannel=TIM1_UP_TIM10_IRQn;
	TIM1_NVIC_Initstructure.NVIC_IRQChannelCmd=ENABLE;
	TIM1_NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority=0;
	TIM1_NVIC_Initstructure.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&TIM1_NVIC_Initstructure);
	//--------------------------------
	
	//------ config time1 ------------
	//f_clock_timer1=f_apb2=168Mhz/4=42Mhz
	//f_step_tm1=f_apb2/(TIM_Prescaler+1)=2 Mhz
	//t_step_timer=1/f_step=0.5 us
	//T_period=t_step_timer*TIM_Period=1ms
	TIM1_DELAY_Initstructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM1_DELAY_Initstructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM1_DELAY_Initstructure.TIM_Period=2000;
	TIM1_DELAY_Initstructure.TIM_Prescaler=20;
	TIM1_DELAY_Initstructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM1,&TIM1_DELAY_Initstructure);
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
	TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
	TIM_Cmd(TIM1,ENABLE);
	//--------------------------------
}

void TIM1_UP_TIM10_IRQHandler(void)
{
	if(TIM_GetFlagStatus(TIM1,TIM_FLAG_Update))
	{	
		ovf_tm1_count++;	
	}
	TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
}

void fix_loop_time(void)
{
//	if(loop_time>fix_ovf_tm1_count)
//	{
//		usart_port=1;
//		printf("T=\r");
//	}			
	loop_time=ovf_tm1_count-last_ovf_tm1_count;	
	while(loop_time<fix_ovf_tm1_count)
	{
		loop_time=ovf_tm1_count-last_ovf_tm1_count;
		delay(1);
	}
	last_ovf_tm1_count=ovf_tm1_count;
	
//	if(loop_time>	fix_ovf_tm1_count)
//	{
//		usart_port=1;
//		printf("\r");
//	}
}
