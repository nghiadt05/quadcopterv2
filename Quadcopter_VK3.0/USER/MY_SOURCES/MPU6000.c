#include "mpu6000.h"

#ifndef M_PI
#define M_PI	3.14159265359f
#endif

//---- list of variables -------
uint8_t receive_data,spi_tx_data[10],spi_rx_data[20];
int16_t acc_x_raw,acc_y_raw,acc_z_raw;
int16_t temp_raw;
int16_t gyro_x_raw,gyro_y_raw,gyro_z_raw;
int16_t gyro_x_offset=-25;
int16_t gyro_y_offset=57;
int16_t gyro_z_offset=-115;
int16_t AccX_sensitivity=8200;	//LSB/g
int16_t AccY_sensitivity=8165;	//LSB/g
int16_t AccZ_sensitivity=8206;	//LSB/g
int16_t acc_x_offset=-4;
int16_t acc_y_offset=99;
int16_t acc_z_offset=522;
float acc_value[3];//g
float gyro_value[3];//rad/s
float temperature;
//------------------------------



//----- send a 8-bit data ------------------
void MPU6000_send_byte(uint8_t res_adr, uint8_t data)
{
	HMC5983_ChipDisable();
	MS5611_ChipDisable();
	MPU6000_ChipEnable();
	SPI1_transfer_byte(res_adr);
	SPI1_transfer_byte(data);
	MPU6000_ChipDisable();
}
//---------------------------------------------

//----- read a 8-bit data ------------------
uint8_t MPU6000_read_byte(uint8_t res_adr)
{
	uint8_t data;
	HMC5983_ChipDisable();
	MS5611_ChipDisable();
	MPU6000_ChipEnable();
	SPI1_transfer_byte(res_adr|READ_CM);
	data=SPI1_transfer_byte(0);
	MPU6000_ChipDisable();
	return data;
}
//---------------------------------------------

//-------MPU6000 configuration ----------------
void MPU6000_Configuration(void)
{	
	MPU6000_send_byte(PWR_MGMT_1_Adr,PWR_MGMT_1);
	delay_ms(10);
	
	MPU6000_send_byte(SMPRT_DIV_Adr,SMPRT_DIV);
	delay_ms(10);
	
	MPU6000_send_byte(USER_CTRL_Adr,USER_CTRL);
	delay_ms(10);
	
	MPU6000_send_byte(CONFIG_Adr,CONFIG);
	delay_ms(10);
		
	MPU6000_send_byte(GYRO_CONFIG_Adr,GYRO_CONFIG);
	delay_ms(10);
	
	MPU6000_send_byte(ACCEL_CONFIG_Adr,ACCEL_CONFIG);
	delay_ms(10);				
}
//---------------------------------------------

void MPU6000_test_Config(void)
{
	usart_port=1;
	printf("\r");
	printf("SMPRT_DIV=%d\r",MPU6000_read_byte(SMPRT_DIV_Adr));
	printf("CF=%d\r",MPU6000_read_byte(CONFIG_Adr));
	printf("GYRO_CONFIG=%d\r",MPU6000_read_byte(GYRO_CONFIG_Adr));
	printf("ACCEL_CONFIG=%d\r",MPU6000_read_byte(ACCEL_CONFIG_Adr));
	printf("USER_CTRL=%d\r",MPU6000_read_byte(USER_CTRL_Adr));
	printf("PWR_MGMT_1=%d\r",MPU6000_read_byte(PWR_MGMT_1_Adr));
}
void MPU6000_get_value(void)
{
	HMC5983_ChipDisable();
	MS5611_ChipDisable();
	MPU6000_ChipEnable();
	SPI1_transfer_byte(ACCEL_XOUT_H_Adr|READ_CM);//send the first data register adr
	acc_x_raw=	-(int16_t)SPI_read_reg();
	acc_y_raw=	-(int16_t)SPI_read_reg();
	acc_z_raw=	-(int16_t)SPI_read_reg();
	temp_raw=		(int16_t)SPI_read_reg();
	gyro_x_raw=	(int16_t)SPI_read_reg();
	gyro_y_raw=	(int16_t)SPI_read_reg();
	gyro_z_raw=	(int16_t)SPI_read_reg();
	MPU6000_ChipDisable();	
	//printf("%d\r",acc_x_raw);
	//printf("%d\r",temp_raw);
	//printf("%d\r",gyro_z_raw);
}

void MPU6000_Calculation(void)
{
	acc_value[0]=(float)(acc_y_raw-acc_y_offset)/AccY_sensitivity;//acc_y
	acc_value[1]=(float)(acc_x_raw-acc_x_offset)/AccX_sensitivity;//acc_x	
	acc_value[2]=(float)(acc_z_raw-acc_z_offset)/AccZ_sensitivity;//acc_z	
	gyro_value[0]=((float)gyro_y_raw-gyro_y_offset)/Gyro_sensitivity;//gyro_y[degrees/s]
	gyro_value[1]=((float)gyro_x_raw-gyro_x_offset)/Gyro_sensitivity;//gyro_x 
	gyro_value[2]=((float)gyro_z_raw-gyro_z_offset)/Gyro_sensitivity;//gyro_z
	//temperature=(float)temp_raw/340.0f+36.53f;
}

