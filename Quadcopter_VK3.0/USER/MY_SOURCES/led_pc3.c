#include "led_pc3.h"

void led_init(void)// in this board, we only have led in pin pc3
{
	GPIO_InitTypeDef LED_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//enable clock for portC_PinC3
	
	LED_InitStructure.GPIO_Mode= GPIO_Mode_OUT;
	LED_InitStructure.GPIO_OType=GPIO_OType_PP;
	LED_InitStructure.GPIO_Pin=GPIO_Pin_3;
	LED_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
	LED_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOC,&LED_InitStructure);
}

void led_on(void)
{
	GPIOC->BSRRL = GPIO_Pin_3;//set bit PC3
}

void led_off(void)
{
	GPIOC->BSRRH = GPIO_Pin_3;//reset bit PC3
}

void led_toogle(void)
{
	GPIOC->ODR ^= GPIO_Pin_3;//toogle pinc3 
}
