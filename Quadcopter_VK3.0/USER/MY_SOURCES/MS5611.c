#include "MS5611.h"

//---------- list of variables -----------
uint32_t D1;    // ADC value of the pressure conversion 
uint32_t D2;    // ADC value of the temperature conversion  
uint16_t C[8];  // calibration coefficients 
double P;   		// compensated pressure value 
double T;   		// compensated temperature value 
double dT;   		// difference between actual and measured temperature 
double OFF;   	// offset at actual temperature 
double SENS;   	// sensitivity at actual temperature 
//----------------------------------------

void MS5611_Reset(void)//okie
{
	MPU6000_ChipDisable();
	HMC5983_ChipDisable();
	
	MS5611_ChipEnable();
	SPI1_transfer_byte(CMD_RESET);
	delay_ms(10);
	MS5611_ChipDisable();
	//printf("MS5611 reset done\r");
}

//******************************************************** 
//Please refer to the datasheet, page 2
//! @brief preform adc conversion 
//! 
//! @return 24bit result 
//********************************************************
uint32_t cmd_adc(uint8_t cmd)
{
	uint32_t adc_result;
	
	MPU6000_ChipDisable();
	HMC5983_ChipDisable();
	
	//--- send adc conversion command ----
	MS5611_ChipEnable();
	SPI1_transfer_byte(CMD_ADC_CONV|cmd);//send appropriate command
	MS5611_ChipDisable();
	switch(cmd&0x0f)//get the gain
	{
		case CMD_ADC_256:
			delay_ms(1);
			break;
		case CMD_ADC_512:
			delay_ms(3);
			break;
		case CMD_ADC_1024:
			delay_ms(4);
			break;
		case CMD_ADC_2048:
			delay_ms(6);
			break;
		case CMD_ADC_4096:
			delay_ms(10);
			break;
	}
	//------------------------------------
	
	//---- receive the conversion value ---
	MS5611_ChipEnable();
	SPI1_transfer_byte(CMD_ADC_READ);//send read_command
	adc_result =(SPI1_transfer_byte(0)&0xff)<<16;//send dummy byte to creat clock, first byte
	adc_result|=(SPI1_transfer_byte(0)&0xff)<<8; //send dummy byte to creat clock, 2nd byte
	adc_result|=(SPI1_transfer_byte(0)&0xff);		 //send dummy byte to creat clock, 3rd byte
	MS5611_ChipDisable();
	//-------------------------------------
	
	return adc_result;//32bit unsigned, only has 24 bits meaningfully
}

//******************************************************** 
//! @brief Read calibration coefficients 
//! 
//! @return coefficient 
//! The range of coef_num is between 0 and 7
//******************************************************** 
uint16_t cmd_prom(uint8_t coef_num)
{	
	uint16_t C;
	MPU6000_ChipDisable();
	HMC5983_ChipDisable();
	
	MS5611_ChipEnable();
	SPI1_transfer_byte(CMD_PROM_RD+coef_num*2);//send prom_read_command add the addres  
	C=SPI_read_reg();
	MS5611_ChipDisable();
	return C;
}

//******************************************************** 
//! @brief Read and store all the prom registers 
//! 
//! @return none 
//! C[0]=0: not used
//******************************************************** 
void MS5611_read_Prom(void)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		C[i]=cmd_prom(i);
		//usart_port=1;
		//printf("%d ",C[i]);
	}
	//printf("\r");
}

//******************************************************** 
//! @brief calculate the CRC code for details look into CRC CODE NOTES 
//! 
//! @return crc code 
//******************************************************** 
 
uint8_t crc4(uint16_t n_prom[]) 
{ 
 int cnt;      							// simple counter  
 uint16_t n_rem;     		// crc reminder 
 uint16_t crc_read;    	// original value of the crc 
 uint8_t  n_bit; 
 n_rem = 0x00; 
 crc_read=n_prom[7];    								 //save read CRC 
 n_prom[7]=(0xFF00 & (n_prom[7]));   		 //CRC byte is replaced by 0 
     for (cnt = 0; cnt < 16; cnt++)      // operation is performed on bytes 
     { 
				// choose LSB or MSB 
				if (cnt%2==1) n_rem ^= (unsigned short) ((n_prom[cnt>>1]) & 0x00FF);//LSB 
				else n_rem ^= (unsigned short) (n_prom[cnt>>1]>>8); 								//MSB
			 
         for (n_bit = 8; n_bit > 0; n_bit--) 
         { 
              if (n_rem & (0x8000)) 
              { 
                     n_rem = (n_rem << 1) ^ 0x3000; 
              } 
              else 
              { 
                     n_rem = (n_rem << 1); 
              } 
         } 
     } 
 n_rem=  (0x000F & (n_rem >> 12)); // // final 4-bit reminder is CRC code 
 n_prom[7]=crc_read;   // restore the crc_read to its original place 
 return (n_rem ^ 0x00); 
}

//******************************************************** 
//! @brief MS5611 configuration 
//! 
//! @return none
//******************************************************** 
void MS5611_Configuration(void)
{
	uint8_t CRC_Cal;
	loop:
	MS5611_Reset();					//reset mS5611
	MS5611_read_Prom();			//read all the prom value for CRC
	CRC_Cal=crc4(C);				//CRC check
	if(CRC_Cal!=(C[7]&0x0f))// checking fall-> reset and check a gain
	{
		goto loop;
	}
}

/*
	This function is only used in order to test the performance of the MS5611
*/
void MS5611_Calculation(void)
{	
	D1=cmd_adc(CMD_ADC_D1+CMD_ADC_4096); // read uncompensated pressure 
  D2=cmd_adc(CMD_ADC_D2+CMD_ADC_512); // read uncompensated temperature 
  
  // calcualte 1st order pressure and temperature (MS5607 1st order algorithm) 
  dT=D2-C[5]*pow(2,8); 
	T=(2000.0f+(dT*C[6])/8388608.0f)/100.0f; 
	
  OFF=C[2]*65536.0f+dT*C[4]/128.0f;     
  SENS=C[1]*32768.0f+dT*C[3]/256.0f; 
  P=((D1*SENS)/2097152.0f-OFF)/32768.0f;//[P]=mbar*100=kPa
	usart_port=1;
	printf("P=%d T=%0.2f\r",(int)P,T);
	
}

/*
	! This function is aimed at lessening the calculated time for the main loop
	! Total time per 1-update = (3+3+5)*fixed_loop_time=11*fixed_loop_time=44ms
	! Barometter data is update roughly 22 times per second and it does not affect the main loop time
*/
void MS5611_Update(uint8_t D1_CM,uint8_t D2_CM)
{
	uint8_t static read_cycle,wait_count,done,step;
	
	if(done==0)
	{
	if(read_cycle==0)
	{
		if(wait_count==0)//first time in the loop: send conversion command to get pressure data
		{
		//--- send adc conversion command ----
		MPU6000_ChipDisable();
		HMC5983_ChipDisable();
		MS5611_ChipEnable();
		SPI1_transfer_byte(CMD_ADC_CONV|D1_CM|CMD_ADC_D1);//send appropriate command
		//------------------------------------
		}		
		wait_count++;
		if(wait_count==4)//total delay= (4-1)*fixed_loop_time>=12ms>10ms (okie)
		{
			//---- receive the conversion value ---
			MS5611_ChipDisable();
			MPU6000_ChipDisable();
			HMC5983_ChipDisable();
			MS5611_ChipEnable();
			SPI1_transfer_byte(CMD_ADC_READ);//send read_command
			D1 =(SPI1_transfer_byte(0)&0xff)<<16;//send dummy byte to creat clock, first byte
			D1|=(SPI1_transfer_byte(0)&0xff)<<8; //send dummy byte to creat clock, 2nd byte
			D1|=(SPI1_transfer_byte(0)&0xff);		 //send dummy byte to creat clock, 3rd byte
			MS5611_ChipDisable();
			//-------------------------------------
			read_cycle=1;
			wait_count=0;
		}		
	}
	else//read_cycle=1: get temperature value
	{
		if(wait_count==0)//first time in the loop: send conversion command to get temperature data
		{
		//--- send adc conversion command ----
		MPU6000_ChipDisable();
		HMC5983_ChipDisable();
		MS5611_ChipEnable();
		SPI1_transfer_byte(CMD_ADC_CONV|D2_CM|CMD_ADC_D2);//send appropriate command
		//------------------------------------
		}
		wait_count++;
		if(wait_count==4)//total delay= (4-1)*fixed_loop_time>=12ms>10ms (okie)
		{
			//---- receive the conversion value ---
			MS5611_ChipDisable();
			MPU6000_ChipDisable();
			HMC5983_ChipDisable();
			MS5611_ChipEnable();
			SPI1_transfer_byte(CMD_ADC_READ);//send read_command
			D2 =(SPI1_transfer_byte(0)&0xff)<<16;//send dummy byte to creat clock, first byte
			D2|=(SPI1_transfer_byte(0)&0xff)<<8; //send dummy byte to creat clock, 2nd byte
			D2|=(SPI1_transfer_byte(0)&0xff);		 //send dummy byte to creat clock, 3rd byte
			MS5611_ChipDisable();
			//-------------------------------------
			read_cycle=0;
			wait_count=0;
			done=1;
		}
	}
	}
	else//done=1
	{
		// calcualte 1st order pressure and temperature (MS5607 1st order algorithm) 
		switch(step)
		{
			case 0:
				dT=D2-C[5]*256.0f; 
				step++;
				break;
			case 1://enable case 1 and change step+=2; to step++; if we need temperature
				T=(2000.0f+(dT*C[6])/pow(2,23));///100.0f;
				step++;
				break;
			case 2:
				OFF=C[2]*65536.0f+dT*C[4]/128.0f;
				step++;
				break;
			case 3:
				SENS=C[1]*32768.0f+dT*C[3]/256.0f;
				step++;
				break;
			case 4:
				P=(D1*SENS)/2097152.0f;
			case 5:
				P=(P-OFF)/32768.0f;//[P]=mbar*100=1kPa
				step=0;
				done=0;
				break;			
		}
		//usart_port=1;
		//printf("P=%d T=%0.2f\r",(int)P,T);
	}
}

void BaroFilterUpdate(void)
{
	float static x,k,q=0.0625f,p=0.0f,r=4.0f;
	p=p+q;
	k=p/(p+r);
	
	x=x+k*(P-x);
	p=(1.0f-k)*p;
	//printf("%0.2f %0.2f\r",x,P);
	P=x;
}
