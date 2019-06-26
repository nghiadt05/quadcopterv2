#ifndef MY_RCC_CONFIG_H
#define MY_RCC_CONFIG_H

#include "my_rcc_config.h"
#include "my_usart.h"
#include <stdio.h>

void RCC_default_configuration(void)
{
	RCC_DeInit();//reset to the default state 	
}

void RCC_xtal_configuration(void)
{
	RCC_DeInit();//reset to the default state 
	RCC_PLLCmd(DISABLE);//disable main PLL for setting up 
		
	//--we should not disable HSI clock source for safety reason
	//RCC_HSICmd(DISABLE);//disable the internal clock source HSI
	//--wait untill HSIRDY=0 (afer 6 HSI clock cycles)
	//while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY)){RCC_GetFlagStatus(RCC_FLAG_HSIRDY);}
			
	//enable HSE clock source
	RCC_HSEConfig(RCC_HSE_ON);
	//wait untill HSE is ready
	while(!RCC_WaitForHSEStartUp()){}//wait until hse ready
	
	//config PLL
	//we need a small explaination in this function:
	//RCC_PLLSource= RCC_PLLSource_HSE: use external xtal
	//PLLM=8->VCO input frequency= xtal/PLLM=8/8=1Mhz
	//PLLN=336 -> VCO output  frequency= VCO input frequency*PLLN=1*336=336 MHz
	//PLLP=2 -> SYSCLK=VCO output frequency/PLLP=336/2=168 Mhz (maximum value)
	//PLLQ= 7 -> OTG FS, SDIO and RNG clocks= VCO output frequency/PLLQ=48 Mhz
		
	RCC_PLLConfig(RCC_PLLSource_HSE,8,336,2,7);
	
		
	//config PLL
	//we need a small explaination in this function:
	//RCC_PLLSource= RCC_PLLSource_HSE: use external xtal
	//PLLM=8->VCO input frequency= xtal/PLLM=8/8=1Mhz
	//PLLN=256 -> VCO output  frequency= VCO input frequency*PLLN=1*256=256 MHz
	//PLLP=2 -> SYSCLK=VCO output frequency/PLLP=256/2=128 Mhz 
	//PLLQ=8 -> OTG FS, SDIO and RNG clocks= VCO output frequency/PLLQ=32 Mhz
	//RCC_PLLConfig(RCC_PLLSource_HSE,8,256,2,8);
	
	RCC_PLLCmd(ENABLE);//enable PLL clk source	
	while(!RCC_GetFlagStatus(RCC_FLAG_PLLRDY)){}// wait untill PLL is ready
	
	RCC_HCLKConfig(RCC_SYSCLK_Div4);
	//RCC_HCLKConfig(RCC_SYSCLK_Div2);
  RCC_PCLK1Config(RCC_HCLK_Div1);
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);//use PLL clock source as system clock source		
}

/*
	this fuction will print out the specific values of the system clocks
	using usart1 as default port out
*/
void RCC_information(void)
{
	RCC_ClocksTypeDef RCC_ClocksInitStrucure;
	char t;	
	RCC_GetClocksFreq(&RCC_ClocksInitStrucure);		
	t=RCC_GetSYSCLKSource();
	
	usart_port=1;
	if(t==0x00){printf("HSI used as system clock\r");}
	else if(t==0x04){printf("HSE used as system clock\r");}
	else if(t==0x08){printf("PLL used as system clock\r");}
	printf("HCLK_Frequency= %d\r",RCC_ClocksInitStrucure.HCLK_Frequency);
	printf("PCLK1_Frequency= %d\r",RCC_ClocksInitStrucure.PCLK1_Frequency);
	printf("PCLK2_Frequency= %d\r",RCC_ClocksInitStrucure.PCLK2_Frequency);
	printf("SYSCLK_Frequency= %d\r",RCC_ClocksInitStrucure.SYSCLK_Frequency);
	printf("\r");
}

#endif
