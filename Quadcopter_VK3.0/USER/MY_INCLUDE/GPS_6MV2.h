#ifndef GPS_6MV2_H
#define GPS_6MV2_H

#include "stm32f4xx.h"
#include "my_usart.h"
#include <stdlib.h>
#include <string.h>

#define Hanoi_BangKok_Jakata

extern uint8_t data_pt;
extern uint8_t ms_pt;
extern uint8_t ms_name[5];
extern uint8_t data_type;
extern uint8_t GPGLL[6];
extern uint8_t GLL_DETAILS[50];
extern uint8_t GLL;
extern uint8_t VALID;
extern uint8_t Valid[1];
extern uint8_t NorthSouth;
extern uint8_t EastWest; 
extern uint32_t longitude,latitude;
extern float real_time;

void GPS_Get_data(void);
void USART3_IRQHandler(void);

#endif

