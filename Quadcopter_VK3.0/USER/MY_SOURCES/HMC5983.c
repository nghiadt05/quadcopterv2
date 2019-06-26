#include "HMC5983.h"
#include "my_usart.h"
#include "math.h"

//------- necessary variables ---------
int16_t mag_x_raw,mag_y_raw,mag_z_raw;//range: 0xF800 to 0x07FF, 2's complement form
int16_t hmc5983_temp_raw;
float max_x,mag_y,mag_z;//GAUSS
float hmc5983_temp;//Temperature = hmc5983_temp_raw / (2^4 * 8) + 25 in  C 
int16_t mag_x_offset=39;
int16_t mag_y_offset=-78;
int16_t mag_z_offset=-86;
float mag_x_scale=1.0f;
float mag_y_scale=1.0f;
float mag_z_scale=1.0f;

//--------------------------------------

//----- send a 8 bit data ---------------
void HMC5983_send_byte(uint8_t reg_adr,uint8_t reg_value)
{
	MS5611_ChipDisable();
	MPU6000_ChipDisable();
	
	HMC5983_ChipEnable();
	SPI1_transfer_byte(reg_adr);
	SPI1_transfer_byte(reg_value);
	HMC5983_ChipDisable();
}
//---------------------------------------

//----- read a 8-bit data ------------------
uint8_t HMC5883_read_byte(uint8_t res_adr)
{
	uint8_t data;
	MS5611_ChipDisable();
	MPU6000_ChipDisable();
	
	HMC5983_ChipEnable();
	SPI1_transfer_byte(res_adr|READ_CM);
	data=SPI1_transfer_byte(0);//send dummy byte to creat clock
	HMC5983_ChipDisable();
	return data;
}
//---------------------------------------------

//--------- HMC5983 configuraion ------------
void HMC5883_Configuration(void)
{
	HMC5983_send_byte(CF_REG_A_ADR,CF_REG_A_ST_OFF);
	delay_ms(10);
	
	HMC5983_send_byte(CF_REG_B_ADR,CF_REG_B);
	delay_ms(10);
	
	HMC5983_send_byte(MODE_REG_ADR,MODE_REG);
	delay_ms(10);
}
//--------------------------------------------

//-------- HMC5883 getvalue ------------------
void HMC5983_get_value(void)
{
	//only read data registers when RDY_bit=1
	if(HMC5883_read_byte(ST_REG_ADR)&0x01)//data ready
	{
		HMC5983_ChipEnable();
		SPI1_transfer_byte(0xC3);
		mag_x_raw=(int16_t)SPI_read_reg();
		mag_z_raw=(int16_t)SPI_read_reg();
		mag_y_raw=(int16_t)SPI_read_reg();
		HMC5983_ChipDisable();		
		if(mag_x_raw==-4096||mag_y_raw==-4096||mag_z_raw==-4096)//reach the limit range
		{
			//disble magneton sensors for the ahrs computing
			mag_x_raw=0;
			mag_y_raw=0;
			mag_z_raw=0;
		}
		else
		{
			mag_x_raw=(mag_x_raw-mag_x_offset)/mag_x_scale;
			mag_y_raw=(mag_y_raw-mag_y_offset)/mag_y_scale;
			mag_z_raw=(mag_z_raw-mag_z_offset)/mag_z_scale;
		}
	}
	/*
	int16_t MSB,LSB;
	MSB=(int)HMC5883_read_byte(TEMP_MSB_REG_ADR);
	LSB=(int)HMC5883_read_byte(TEMP_LSB_REG_ADR);
	hmc5983_temp=(float)(MSB * 2^8 + LSB) / (2^4 * 8) + 25;
	printf("%0.2f\r",hmc5983_temp);
	*/
}
//--------------------------------------------
//------- test config values -----------------
void HMC5893_test_config(void)
{
	usart_port=1;
	printf("\r");
	printf("CF_REG_A=%d\r",HMC5883_read_byte(CF_REG_A_ADR));
	printf("CF_REG_B=%d\r",HMC5883_read_byte(CF_REG_B_ADR));
	printf("MODE_REG=%d\r",HMC5883_read_byte(MODE_REG_ADR));
}
//--------------------------------------------

