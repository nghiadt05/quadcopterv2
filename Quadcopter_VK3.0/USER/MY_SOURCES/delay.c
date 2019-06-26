#include "delay.h"

static __IO uint32_t sysTickCounter;

/*
	Set the step time to occur each interrupt for system timer
	Do not need to set up NVIC for systick
*/
void Delay_Init(void) 
	{
    /*
     *RCC_ClocksInitStrucure.HCLK_Frequency/1000   = counts to reach 1ms         *
     *RCC_ClocksInitStrucure.HCLK_Frequency/100000 = counts to reach 10us        *
     *RCC_ClocksInitStrucure.HCLK_Frequency/1000000= counts to reach 1us         *
		*/
		RCC_ClocksTypeDef RCC_ClocksInitStrucure;
		SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);//AHB clock selected as SysTick clock source.
		RCC_GetClocksFreq(&RCC_ClocksInitStrucure);
		//each interrupt occurs every 1us
		SysTick_Config(RCC_ClocksInitStrucure.HCLK_Frequency / 1000000);
}
	
void delay(__IO uint32_t nCount)
{
  while(nCount--)
  {
  }
}
 
void delay_us(u32 n) 
{
    sysTickCounter = n;
    while (sysTickCounter != 0){}
}

 
void delay_ms(uint32_t n) 
{
    while (n--)
		{
     sysTickCounter = 1000;
     while (sysTickCounter != 0) {}
    }
}

/*
	If any interrupt occur, decrease the delay_set value to 1 unit (1us/per cout)
*/
void SysTick_Handler(void) 
{
    if (sysTickCounter != 0x00) 
		{
        sysTickCounter--;
    }
}
