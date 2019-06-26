#ifndef LED_PC3
#define LED_PC3


#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

void led_init(void);
void led_on(void);
void led_off(void);
void led_toogle(void);

#endif
