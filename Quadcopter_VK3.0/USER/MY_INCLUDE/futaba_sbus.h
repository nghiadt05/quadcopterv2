#ifndef _FUTABA_SBUS_H_
#define _FUTABA_SBUS_H_

#include "stm32f4xx.h"
#include "my_usart.h"
#include <stdio.h>

extern unsigned char start_byte;
extern unsigned char stop_byte;
extern unsigned char data_byte_array[25];
extern unsigned char FUTABA_rx_done;
extern unsigned int  FUTABA_CHANNEL[16];//values for channel 0-15
extern unsigned char FUTABA_CHANNEL_17;
extern unsigned char FUTABA_CHANNEL_18;
extern unsigned char futaba_byte_pt;

void SBUS_DECODE(void);
void SBUS_DATA_SETUP(void);
void USART2_IRQHandler(void);

#endif
