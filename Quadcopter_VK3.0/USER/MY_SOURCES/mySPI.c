#include "mySPI.h"

void SPI1_Init(void)
{
	//--- type define -------
	GPIO_InitTypeDef	GPIO_Init_Structure;
	SPI_InitTypeDef		SPI_InitStructure;
	//-----------------------
	
	//--- enable clock source --
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	//--------------------------
	
	//----- chipselect pins configuration ------
	GPIO_Init_Structure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_Init_Structure.GPIO_OType=GPIO_OType_PP;
	GPIO_Init_Structure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
	GPIO_Init_Structure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init_Structure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOC,&GPIO_Init_Structure);
	//disable all the spi sensors
	MPU6000_ChipDisable();
	HMC5983_ChipDisable();
	MS5611_ChipDisable();
	//------------------------------------------
	
	//-- MOSI, MISO, SCK GPIO configuration ----
	//--MOSI<->PA7, MISO<->PA6, SCK<-> PA5 -----
	GPIO_Init_Structure.GPIO_Mode=GPIO_Mode_AF;
	GPIO_Init_Structure.GPIO_OType=GPIO_OType_PP;
	GPIO_Init_Structure.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_Init_Structure.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_Init_Structure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Init_Structure);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_SPI1);
	//------------------------------------------
	
	//-- MOSI, MISO, SCK GPIO configuration ----
	SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_64;//656.250 Hz
	SPI_InitStructure.SPI_CPHA=SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_CPOL=SPI_CPOL_Low;
	SPI_InitStructure.SPI_CRCPolynomial=7;
	SPI_InitStructure.SPI_DataSize=SPI_DataSize_8b;
	
	SPI_InitStructure.SPI_Direction=SPI_Direction_2Lines_FullDuplex;//SPI_Direction_1Line_Rx|SPI_Direction_1Line_Tx;
	//SPI_InitStructure.SPI_Direction=SPI_Direction_1Line_Rx|SPI_Direction_1Line_Tx;
	
	SPI_InitStructure.SPI_FirstBit=SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_Mode=SPI_Mode_Master;
	SPI_InitStructure.SPI_NSS=SPI_NSS_Soft;
	SPI_Init(SPI1,&SPI_InitStructure);
	//------------------------------------------
	
	SPI_Cmd(SPI1, ENABLE);	
	delay_ms(10);//dont change this command
}


void MPU6000_ChipEnable(void)
{
	GPIOC->BSRRH = GPIO_Pin_2;
}

void MPU6000_ChipDisable(void)
{
	GPIOC->BSRRL = GPIO_Pin_2;
}

void HMC5983_ChipEnable(void)
{
	GPIOC->BSRRH = GPIO_Pin_1;
}

void HMC5983_ChipDisable(void)
{
	GPIOC->BSRRL = GPIO_Pin_1;
}

void MS5611_ChipEnable(void)
{
	GPIOC->BSRRH = GPIO_Pin_0;
}

void MS5611_ChipDisable(void)
{
	GPIOC->BSRRL = GPIO_Pin_0;
}


//----- transfer a 8-bit data by using spi1 ------
uint8_t SPI1_transfer_byte(uint8_t data)
{
	uint16_t spiTimeout;
	spiTimeout = 0x1000;
	while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE))//wait untill transmittion complete
	{
		
		spiTimeout--;
		if(!spiTimeout)break;
		
	}
	SPI_I2S_SendData(SPI1,data);
	
	spiTimeout = 0x1000;
	while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE))//wait untill receive complete
	{
		spiTimeout--;
		if(!spiTimeout)break;
	}
	return SPI_I2S_ReceiveData(SPI1);
}
//---------------------------------------------

//----- read a 16-bit data ------------------
uint16_t SPI_read_reg(void)
{
	uint16_t data;
	data=SPI1_transfer_byte(0)<<8;
	data|=SPI1_transfer_byte(0)&0xff;
	return data;
}
//---------------------------------------------
