#ifndef HMC5983_H
#define HMC5983_H

#include "stm32f4xx.h"
#include "mySPI.h"

//---- HMC5983 Register address --------
#define CF_REG_A_ADR					0x00//Configuration Register A 
#define CF_REG_B_ADR					0x01//Configuration Register B
#define MODE_REG_ADR					0x02//Mode Register 
#define DO_X_MSB_REG_ADR 			0x03//Data Output X MSB Register 
#define DO_X_LSB_REG_ADR 			0x04//Data Output X LSB Register 
#define DO_Z_MSB_REG_ADR 			0x05//Data Output Z MSB Register 
#define DO_Z_LSB_REG_ADR 			0x06//Data Output Z LSB Register 
#define DO_Y_MSB_REG_ADR 			0x07//Data Output Y MSB Register
#define DO_Y_LSB_REG_ADR 			0x08//Data Output Y LSB Register
#define ST_REG_ADR						0x09//Status Register 
#define TEMP_MSB_REG_ADR			0x31//Temperature Output MSB Register 
#define TEMP_LSB_REG_ADR			0x32//Temperature Output LSB Register 
//--------------------------------------

//----- HMC5983 Setup register values ----
#define CF_REG_A_ST_ON			0xF9//8-average, 75 Hz, positive self test measurement, enable temperature sensor
#define CF_REG_A_ST_OFF			0xF8//8-average, 75 Hz, disable self test measurement, enable temperature sensor
#define CF_REG_B						0xA0//(Gain=5) 
#define MODE_REG						0x00//(Continuous-measurement mode) 
//----------------------------------------

#define GAIN_VALUE 390//LSB/GAUSS, recommended sensor field range ± 4.7 Gauss

//------- necessary variables ---------
extern int16_t mag_x_raw,mag_y_raw,mag_z_raw;//range: 0xF800 to 0x07FF, 2's complement form
extern int16_t hmc5983_temp_raw;
extern float max_x,mag_y,mag_z;//GAUSS
extern float hmc5983_temp;//Temperature = hmc5983_temp_raw / (2^4 * 8) + 25 in  C 
extern int16_t mag_x_offset,mag_y_offset,mag_z_offset;
extern float mag_x_scale,mag_y_scale,mag_z_scale;

//-------------------------------------


//------- list of commands ------------
void HMC5883_Configuration(void);
uint8_t HMC5883_read_byte(uint8_t res_adr);
void HMC5883_test_config(void);
void HMC5983_send_byte(uint8_t reg_adr,uint8_t reg_value);
void HMC5983_get_value(void);
void HMC5893_test_config(void);
//void HMC5983_update_rotation_angles(void);
//-------------------------------------
/*
SPI OPERATIONAL EXAMPLES 
 
To read Configuration B register 
Lower CS line 
Write 0x81 to the SPI bus 
Read 1 byte from SPI bus  
Raise CS line 
 
To write Configuration B register 
Lower CS line 
Write 0x01 to the SPI bus 
Write 0xVV to the SPI bus  (VV is the value to be written to register B) 
Raise CS line 

To read Status 
Lower CS line 
Write 0x89 to the SPI bus 
Read 1 byte from SPI bus  
Raise CS line 
 
To read output 
Lower CS line 
Write 0xC3 to the SPI bus 
Read 6 byte from SPI bus  
Raise CS line 
*/
#endif
