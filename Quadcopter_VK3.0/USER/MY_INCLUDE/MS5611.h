#ifndef MS5611_H
#define MS5611_H
/*
! @Pleasa read the samples code published hereby:
! @http://www.amsys.de/sheets/amsys.de.an520_e.pdf
*/
#include "stm32f4xx.h"
#include "my_usart.h"
#include "mpu6000.h"
#include "tm1_ovf.h"
#include "mySPI.h"
#include "math.h"

#define UKF_P0        1013250//standard static pressure at sea level []=bar
//------- MS5611 command define ---------
#define CMD_RESET 		0x1E // ADC reset command 
#define CMD_ADC_READ 	0x00 // ADC read command 
#define CMD_ADC_CONV 	0x40 // ADC conversion command 
#define CMD_ADC_D1		0x00 // ADC D1 conversion 
#define CMD_ADC_D2 		0x10 // ADC D2 conversion 
#define CMD_ADC_256 	0x00 // ADC OSR=256 
#define CMD_ADC_512 	0x02 // ADC OSR=512 
#define CMD_ADC_1024 	0x04 // ADC OSR=1024 
#define CMD_ADC_2048 	0x06 // ADC OSR=2056 
#define CMD_ADC_4096 	0x08 // ADC OSR=4096 
#define CMD_PROM_RD 	0xA0 // Prom read command
//---------------------------------------

//---------- list of variables -----------
extern uint32_t D1;    // ADC value of the pressure conversion 
extern uint32_t D2;    // ADC value of the temperature conversion  
extern uint16_t C[8];  // calibration coefficients 
extern double P;   		// compensated pressure value 
extern double T;   		// compensated temperature value 
extern double dT;   		// difference between actual and measured temperature 
extern double OFF;   	// offset at actual temperature 
extern double SENS;   	// sensitivity at actual temperature 
//----------------------------------------

//---------- list of commands ------------
void MS5611_Reset(void); 
void MS5611_read_Prom(void);
void MS5611_Configuration(void);
void MS5611_Calculation(void);
void MS5611_Update(uint8_t D1_CM,uint8_t D2_CM);
void BaroFilterUpdate(void);

uint32_t cmd_adc(uint8_t cmd); 
uint16_t cmd_prom(uint8_t coef_num); 
uint8_t crc4(uint16_t n_prom[]); 
//----------------------------------------

#endif
