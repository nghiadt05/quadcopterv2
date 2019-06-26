#include "my_usart.h"
#include "mpu6000.h"
#include "HMC5983.h"
#include "AHRS.h"
#include "MS5611.h"
#include "GPS_6MV2.h"
#include "pid.h"
#include <stdlib.h>
#include <string.h>
 
#define P_port_usart6
//#define P_port_usart1

extern uint8_t mode,sending_mode;
extern uint8_t receiving_mode;
extern uint8_t rx_done;
extern uint8_t rx_pt;
extern uint8_t temp_string[100];

void Processing_send_data(void);
void Processing_data_decode(void);

#ifdef P_port_usart1
		void USART1_IRQHandler(void);
#endif
		
#ifdef P_port_usart6
		void USART6_IRQHandler(void);
#endif


