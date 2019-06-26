#ifndef my_rcc_config
#define my_rcc_config
#endif
/*
	This setup is only precise for the 8Mhz xtal
	other values are needed to be adjusted
*/

#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"

void RCC_default_configuration(void);
void RCC_xtal_configuration(void);
void RCC_information(void);
