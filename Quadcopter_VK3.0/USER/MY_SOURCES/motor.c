#include "motor.h"

//uint32_t tm5_ovf_count;

void Motor_Configuration(void)
{
	GPIO_InitTypeDef PWM_PINS_GPIO_InitTypeDef;
	TIM_TimeBaseInitTypeDef PWM_TIM_TimeBaseInitTypeDef;
	NVIC_InitTypeDef	PWM_NVIC_InitTypeDef;
	TIM_OCInitTypeDef PWM_TIM_OCInitTypeDef;
	
	//---enable clock for gpioA, timer 5----------
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	//--------------------------------------------
	
	//--configure pin A[0-3] as output pin -------
	PWM_PINS_GPIO_InitTypeDef.GPIO_Mode=GPIO_Mode_AF;
	PWM_PINS_GPIO_InitTypeDef.GPIO_OType=GPIO_OType_PP;
	PWM_PINS_GPIO_InitTypeDef.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	PWM_PINS_GPIO_InitTypeDef.GPIO_PuPd=GPIO_PuPd_NOPULL;
	PWM_PINS_GPIO_InitTypeDef.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&PWM_PINS_GPIO_InitTypeDef);
	//--------------------------------------------
	
	//-- config alternative fuction for PWM Pins -----
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_TIM5);
	//------------------------------------------------
	
	//-- config timer5: general purpose part ---------
	//f_apb1=sysclock/4=168/4=42Mhz
	//f_sys_tim5=f_apb1/TIM_ClockDivision=f_apb1=42Mhz
	//f_step_tim5=f_sys_tim5/(TIM_Prescaler+1)= 2 Mhz
	//t_step_tim5=1/f_step_tim5= 0.5 us
	//T_period=t_step_tim5*TIM_Period=2.041 ms
	PWM_TIM_TimeBaseInitTypeDef.TIM_ClockDivision=TIM_CKD_DIV1;
	PWM_TIM_TimeBaseInitTypeDef.TIM_CounterMode=TIM_CounterMode_Up;
	PWM_TIM_TimeBaseInitTypeDef.TIM_Period=4082;
	PWM_TIM_TimeBaseInitTypeDef.TIM_Prescaler=21;
	PWM_TIM_TimeBaseInitTypeDef.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM5,&PWM_TIM_TimeBaseInitTypeDef);
	
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);	
	//------------------------------------------------
	
	//---config oc mode for timer5 -------------------
	PWM_TIM_OCInitTypeDef.TIM_OCMode=TIM_OCMode_PWM1;
	PWM_TIM_OCInitTypeDef.TIM_OutputState=TIM_OutputState_Enable;
	PWM_TIM_OCInitTypeDef.TIM_Pulse=0;
	PWM_TIM_OCInitTypeDef.TIM_OCPolarity=TIM_OCPolarity_High;
	
	TIM_OC1Init(TIM5,&PWM_TIM_OCInitTypeDef);
	TIM_OC2Init(TIM5,&PWM_TIM_OCInitTypeDef);
	TIM_OC3Init(TIM5,&PWM_TIM_OCInitTypeDef);
	TIM_OC4Init(TIM5,&PWM_TIM_OCInitTypeDef);

	TIM_OC1PreloadConfig(TIM5,TIM_OCPreload_Enable);//enable to change T_on	
	TIM_OC2PreloadConfig(TIM5,TIM_OCPreload_Enable);//enable to change T_on	
	TIM_OC3PreloadConfig(TIM5,TIM_OCPreload_Enable);//enable to change T_on	
	TIM_OC4PreloadConfig(TIM5,TIM_OCPreload_Enable);//enable to change T_on	
	TIM_ARRPreloadConfig(TIM5,ENABLE);//enable to change T		
	//------------------------------------------------
	
	TIM_Cmd(TIM5,ENABLE);
		
	//-- configure NVIC ------------------------------
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	PWM_NVIC_InitTypeDef.NVIC_IRQChannel=TIM5_IRQn;
	PWM_NVIC_InitTypeDef.NVIC_IRQChannelCmd=ENABLE;
	PWM_NVIC_InitTypeDef.NVIC_IRQChannelPreemptionPriority=0;
	PWM_NVIC_InitTypeDef.NVIC_IRQChannelSubPriority=5;
	NVIC_Init(&PWM_NVIC_InitTypeDef);
	//------------------------------------------------
}

void MOTOR_WARNING(void)
{
	TIM5->CCR1=PWM_WARNING;
	TIM5->CCR2=PWM_WARNING;
	TIM5->CCR3=PWM_WARNING;
	TIM5->CCR4=PWM_WARNING;
}

void MOTOR_ARMING(void)
{
	TIM5->CCR1=PWM_STOP;
	TIM5->CCR2=PWM_STOP;
	TIM5->CCR3=PWM_STOP;
	TIM5->CCR4=PWM_STOP;
}

void TIM5_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update))
	{
		//tm5_ovf_count++;
		//GPIOC->ODR ^= GPIO_Pin_3;
		TIM_ClearITPendingBit(TIM5,TIM_IT_Update);
	}
}


