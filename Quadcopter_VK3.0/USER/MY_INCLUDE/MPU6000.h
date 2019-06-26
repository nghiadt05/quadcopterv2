#ifndef MPU_6000_H
#define MPU_6000_H

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "mySPI.h"
#include "my_usart.h"
#include "delay.h"
#include "math.h"

/******************************************
**** List of needed register addresses*****
*******************************************/
#define SMPRT_DIV_Adr 		0x19	// 25
#define CONFIG_Adr				0x1a  // 26
#define GYRO_CONFIG_Adr		0x1b	// 27
#define ACCEL_CONFIG_Adr	0x1c	// 28

#define ACCEL_XOUT_H_Adr	0x3b	// 59
#define ACCEL_XOUT_L_Adr	0x3c	// 60
#define ACCEL_YOUT_H_Adr	0x3d	// 61
#define ACCEL_YOUT_L_Adr	0x3e	// 62
#define ACCEL_ZOUT_H_Adr	0x3f	// 63
#define ACCEL_ZOUT_L_Adr	0x40	// 64

//Temperature in degrees C = (TEMP_OUT Register Value as a signed quantity)/340 + 36.53
#define TEMP_OUT_H_Adr		0x41	// 65
#define TEMP_OUT_L_Adr		0x42	// 66 

#define GYRO_XOUT_H_Adr		0x43	// 67
#define GYRO_XOUT_L_Adr		0x44	// 68
#define GYRO_YOUT_H_Adr		0x45	// 69
#define GYRO_YOUT_L_Adr		0x46	// 70
#define GYRO_ZOUT_H_Adr		0x47	// 71
#define GYRO_ZOUT_L_Adr		0x48	// 72

#define SIGNAL_PATH_RESET_Adr	0x68	// 104
#define USER_CTRL_Adr			0x6a	//106
#define PWR_MGMT_1_Adr		0x6b	//107
#define WHO_AM_I_Adr			0x75	//117

/**************************************************
***Configuration value for those above registers***
***************************************************/

#define SMPRT_DIV					0x00	//Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV)=1kHz/(1+0)=1kHz	
#define CONFIG						0x01	//Disable FSYNC; enable DLPF with mode 1, delay roughly 2ms for gyro and acclero each reading time
#define GYRO_CONFIG				0x10	//FS_SEL=0x10 <-> Full Scale Range=± 1000 °/s (gyro)
#define ACCEL_CONFIG			0x08	//AFS_SEL=0x08 <-> Full Scale Range=± 4g (accelerometer) 
#define SIGNAL_PATH_RESET	0x07	//Reset only the signal paths of gyro, acc and temp sensors not the registers
#define USER_CTRL					0x11	//Disable I2C line, reset the signal path as well as the resisters of all sensors(reset to 0 after done)
#define PWR_MGMT_1				0x01	//Use PLL with X axis gyroscope reference, dont configure this resgister to reset the device !

#define Gyro_sensitivity 	32.8f 		//LSB/degree


/***************************************
**********	LIST OF VARIABLES **********
***************************************/
//---- list of variables -------
extern uint8_t receive_data,spi_tx_data[10],spi_rx_data[20];
extern int16_t acc_x_raw,acc_y_raw,acc_z_raw;
extern int16_t temp_raw;
extern int16_t gyro_x_raw,gyro_y_raw,gyro_z_raw;
extern int16_t gyro_x_offset;
extern int16_t gyro_y_offset;
extern int16_t gyro_z_offset;
extern int16_t acc_x_offset;
extern int16_t acc_y_offset;
extern int16_t acc_z_offset;
extern int16_t AccX_sensitivity;
extern int16_t AccY_sensitivity;
extern int16_t AccZ_sensitivity;
extern float acc_value[3];//g
extern float gyro_value[3];//rad/s
extern float temperature;
//------------------------------
//------------------------------

/***************************************
**********	LIST OF FUNCTIONS **********
***************************************/
void MPU6000_send_byte(uint8_t res_adr, uint8_t data);
uint8_t MPU6000_read_byte(uint8_t res_adr);
void MPU6000_Configuration(void);
void MPU6000_get_value(void);
void MPU6000_test_Config(void);
void MPU6000_Calculation(void);
void MPU6000_getAccAngles(void);
void MPU6000_Calib(void);

#endif
