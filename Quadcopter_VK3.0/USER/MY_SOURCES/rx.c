#include "rx.h"
#include "my_usart.h"
#include "led_pc3.h"

uint32_t TCNT_LAST[6];
uint32_t TCNT_NOW[6];
uint32_t TM_OVF_COUNT_LAST[6];
uint32_t TM_OVF_COUNT_NOW[6];
uint32_t PULSE_VALUES[6];
uint8_t RX_RECEIVE_DONE[6];
uint8_t RX_CACULATED[6];
uint32_t TM2_OVF_COUNT;
uint8_t start,_1st_run,run;
uint8_t yaw_stick_pos;

void RX_Configuration(void)
{
	GPIO_InitTypeDef RX_PINS_GPIO_InitTypeDef;
	EXTI_InitTypeDef RX_PINS_EXTI_InitTypeDef;
	NVIC_InitTypeDef RX_PINS_NVIC_InitTypeDef;
	TIM_TimeBaseInitTypeDef RX_TIM_TimeBaseInitTypeDef;
	
	//--- enable clock for GPIOB -------
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); 
	//----------------------------------
	
	//--- enable clock for SYSCFG ------
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	//----------------------------------
	
	//--- enable clock for TIM2 --------
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	//----------------------------------
	
	//---set GPIO0-1-6-7-8-9 as input pull-up pins-----
	RX_PINS_GPIO_InitTypeDef.GPIO_Mode=GPIO_Mode_IN;
	RX_PINS_GPIO_InitTypeDef.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	RX_PINS_GPIO_InitTypeDef.GPIO_PuPd=GPIO_PuPd_UP;
	RX_PINS_GPIO_InitTypeDef.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&RX_PINS_GPIO_InitTypeDef);
	//-------------------------------------------------
	
	//---set GPIO10 as output pull-up pins-----
	RX_PINS_GPIO_InitTypeDef.GPIO_Mode=GPIO_Mode_OUT;
	RX_PINS_GPIO_InitTypeDef.GPIO_Pin=GPIO_Pin_3;
	RX_PINS_GPIO_InitTypeDef.GPIO_PuPd=GPIO_PuPd_UP;
	RX_PINS_GPIO_InitTypeDef.GPIO_OType=GPIO_OType_PP;
	RX_PINS_GPIO_InitTypeDef.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOB,&RX_PINS_GPIO_InitTypeDef);
	//-------------------------------------------------

	//--------- chose interrupt pin sources ------------
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource0);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource1);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource6);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource7);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource8);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource9);
	//------------------------------------------------- 
	
	//--- configure external interrupt ----------------
	RX_PINS_EXTI_InitTypeDef.EXTI_Line=EXTI_Line0|EXTI_Line1|EXTI_Line6|EXTI_Line7|EXTI_Line8|EXTI_Line9;
	RX_PINS_EXTI_InitTypeDef.EXTI_LineCmd=ENABLE;
	RX_PINS_EXTI_InitTypeDef.EXTI_Mode=EXTI_Mode_Interrupt;
	RX_PINS_EXTI_InitTypeDef.EXTI_Trigger=EXTI_Trigger_Rising_Falling;
	EXTI_Init(&RX_PINS_EXTI_InitTypeDef);	

	EXTI_ClearITPendingBit(EXTI_Line0);
	EXTI_ClearITPendingBit(EXTI_Line1);
	EXTI_ClearITPendingBit(EXTI_Line6);
	EXTI_ClearITPendingBit(EXTI_Line7);
	EXTI_ClearITPendingBit(EXTI_Line8);
	EXTI_ClearITPendingBit(EXTI_Line9);
	//-------------------------------------------------
	
	//---- configure timer2 at time-base mode ---------
	//f_apb1=sysclock/4=168/4=42Mhz
	//f_sys_tim2=f_apb1/TIM_ClockDivision=f_apb1=42Mhz
	//f_step_tim2=f_sys_tim5/(TIM_Prescaler+1)= 2 Mhz
	//t_step_tim2=1/f_step_tim5= 0.5 us
	//T_period=t_step_tim5*TIM_Period
	RX_TIM_TimeBaseInitTypeDef.TIM_ClockDivision=TIM_CKD_DIV1;
	RX_TIM_TimeBaseInitTypeDef.TIM_CounterMode=TIM_CounterMode_Up;
	RX_TIM_TimeBaseInitTypeDef.TIM_Period=TIM2_MAX_COUNT;
	RX_TIM_TimeBaseInitTypeDef.TIM_Prescaler=21;
	RX_TIM_TimeBaseInitTypeDef.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&RX_TIM_TimeBaseInitTypeDef);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	TIM_Cmd(TIM2,ENABLE);
	//-------------------------------------------------
	
	//---- config nvic vector -------------------------
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	RX_PINS_NVIC_InitTypeDef.NVIC_IRQChannel=EXTI0_IRQn;
	RX_PINS_NVIC_InitTypeDef.NVIC_IRQChannelCmd=ENABLE;
	RX_PINS_NVIC_InitTypeDef.NVIC_IRQChannelPreemptionPriority=0;
	RX_PINS_NVIC_InitTypeDef.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&RX_PINS_NVIC_InitTypeDef);	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	RX_PINS_NVIC_InitTypeDef.NVIC_IRQChannel=EXTI1_IRQn;
	RX_PINS_NVIC_InitTypeDef.NVIC_IRQChannelCmd=ENABLE;
	RX_PINS_NVIC_InitTypeDef.NVIC_IRQChannelPreemptionPriority=0;
	RX_PINS_NVIC_InitTypeDef.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&RX_PINS_NVIC_InitTypeDef);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	RX_PINS_NVIC_InitTypeDef.NVIC_IRQChannel=EXTI9_5_IRQn;
	RX_PINS_NVIC_InitTypeDef.NVIC_IRQChannelCmd=ENABLE;
	RX_PINS_NVIC_InitTypeDef.NVIC_IRQChannelPreemptionPriority=0;
	RX_PINS_NVIC_InitTypeDef.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&RX_PINS_NVIC_InitTypeDef);	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);//configure NVIC for tim2
	RX_PINS_NVIC_InitTypeDef.NVIC_IRQChannel=TIM2_IRQn;
	RX_PINS_NVIC_InitTypeDef.NVIC_IRQChannelCmd=ENABLE;
	RX_PINS_NVIC_InitTypeDef.NVIC_IRQChannelPreemptionPriority=0;
	RX_PINS_NVIC_InitTypeDef.NVIC_IRQChannelSubPriority=4;
	NVIC_Init(&RX_PINS_NVIC_InitTypeDef);	
	//-------------------------------------------------
}

void RX_Calculation(void)
{
	uint8_t i=0;
	int32_t rx_sub_temp;
	for(i=0;i<6;i++)
	{
		if(RX_RECEIVE_DONE[i])
		{
		int32_t rx_temp=(TM_OVF_COUNT_NOW[i]-TM_OVF_COUNT_LAST[i])*TIM2_MAX_COUNT+TCNT_NOW[i]-TCNT_LAST[i];		
		RX_CACULATED[i]=0;	
		if(rx_temp>1700 && rx_temp<4100)
		{
			PULSE_VALUES[i]=rx_temp;	
		}			
		RX_CACULATED[i]=1;
		}
	}		
	
	//get target angle: roll angle
	rx_sub_temp=PULSE_VALUES[0]-MID_CH0;
	if(rx_sub_temp<-RX_NOISE||rx_sub_temp>RX_NOISE)
	{
		target_angle[0]=-2*MAX_TARGET_ANGLE*rx_sub_temp/CH0_RANGE;
	}
	else target_angle[0]=0.0f;
	
	//get target angle: pitch angle
	rx_sub_temp=PULSE_VALUES[1]-MID_CH1;
	if(rx_sub_temp<-RX_NOISE||rx_sub_temp>RX_NOISE)
	{
		target_angle[1]=2*MAX_TARGET_ANGLE*rx_sub_temp/CH1_RANGE;
	}
	else target_angle[1]=0.0f;
	
	//get throttle
	rx_sub_temp=PULSE_VALUES[2]-MIN_CH2;
	throttle=(float)rx_sub_temp*0.8f/(float)CH2_RANGE;
	
	//get target angle: yaw angle
	if(run==0)//no moving at all
	{
		target_angle[2]=0;
		yaw_angle_offset=rpy[2];//get the current actual yaw angle
	}
	else
	{		
		rx_sub_temp=PULSE_VALUES[3]-MID_CH3;		
			if(rx_sub_temp<-RX_NOISE)
		{
			yaw_stick_pos=1;//yaw stick is being moved
			target_angle[2]-=0.2f;
		}		
		else if(rx_sub_temp>RX_NOISE)
		{
			yaw_stick_pos=1;//yaw stick is being moved
			target_angle[2]+=0.2f;
		}
		else
		{
			yaw_stick_pos=0;
		}
		if(target_angle[2]>180.0f)target_angle[2]-=360.0f;
		else if(target_angle[2]<-180.0f)target_angle[2]+=360.0f;
	}
			
//	usart_port=1;
//	printf("%d\r",(int16_t)(throttle*100));
//	printf("%d,%d,%d,%d,%d,%d\r",PULSE_VALUES[0],PULSE_VALUES[1],PULSE_VALUES[2],PULSE_VALUES[3],PULSE_VALUES[4],PULSE_VALUES[5]);
//	printf("%d\r",PULSE_VALUES[5]);
//	printf("%d %d %d %d\r",(int32_t)(target_angle[0]*100),(int32_t)(target_angle[1]*100),(int32_t)(target_angle[2]*100),(int32_t)(throttle*100));
}

void CHECK_START_STT(void)
{
	if(PULSE_VALUES[3]>3600 && PULSE_VALUES[2]<2400 && PULSE_VALUES[1]<2400 && PULSE_VALUES[0]<2650)//motor on
	{
		start=1;	
		_1st_run=1;
		led_on();
		MOTOR_ARMING();
	}
	else if(PULSE_VALUES[3]<2200&& PULSE_VALUES[2]<2400 && PULSE_VALUES[0]>3050 && PULSE_VALUES[1]<2400)//motor off
	{		
		start=0;		
		led_off();
		MOTOR_ARMING();
	}
	
	if(start==1 && ((int)(throttle*100)>=10))
	{
		_1st_run=0;
		run=1;
	}
	else
	{
		run=0;
	}
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update))
	{
		TM2_OVF_COUNT++;
		//GPIOC->ODR ^= GPIO_Pin_3;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}

void EXTI0_IRQHandler(void)
{	
	EXTI_ClearITPendingBit(EXTI_Line0);//we should clear the flag right after entering the int program
	if((GPIOB->IDR & GPIO_Pin_0)&& RX_CACULATED[0])//rising edge and data is calculated
	{
		RX_RECEIVE_DONE[0]=0;
		TCNT_LAST[0]=TIM2->CNT;
		TM_OVF_COUNT_LAST[0]=TM2_OVF_COUNT;
	}
	else
	{		
		TCNT_NOW[0]=TIM2->CNT;
		TM_OVF_COUNT_NOW[0]=TM2_OVF_COUNT;
		RX_RECEIVE_DONE[0]=1;
	}
}

void EXTI1_IRQHandler(void)
{	
	EXTI_ClearITPendingBit(EXTI_Line1);//we should clear the flag right after entering the int program
	if((GPIOB->IDR & GPIO_Pin_1)&& RX_CACULATED[1])//rising edge and data is calculated
	{
		RX_RECEIVE_DONE[1]=0;
		TCNT_LAST[1]=TIM2->CNT;
		TM_OVF_COUNT_LAST[1]=TM2_OVF_COUNT;
	}
	else
	{		
		TCNT_NOW[1]=TIM2->CNT;
		TM_OVF_COUNT_NOW[1]=TM2_OVF_COUNT;
		RX_RECEIVE_DONE[1]=1;
	}
}

void EXTI9_5_IRQHandler(void)
{
	uint8_t i=0;
	for(i=0;i<4;i++)
	{
		if(EXTI_GetITStatus(1<<(i+6)))//interrupt for pin PB[6:9]
		{
			EXTI_ClearITPendingBit(1<<(i+6));
			if(GPIOB->IDR&(1<<(i+6))&& RX_CACULATED[i+2])//rising edge
			{
				RX_RECEIVE_DONE[i+2]=0;
				TCNT_LAST[i+2]=TIM2->CNT;
				TM_OVF_COUNT_LAST[i+2]=TM2_OVF_COUNT;
			}
			else
			{
				TCNT_NOW[i+2]=TIM2->CNT;
				TM_OVF_COUNT_NOW[i+2]=TM2_OVF_COUNT;
				RX_RECEIVE_DONE[i+2]=1;				
			}
		}
	}
}
