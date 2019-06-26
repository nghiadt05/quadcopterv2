#ifndef my_SPI_H
#define my_SPI_H

#include "stm32f4xx.h"
#include "stm32f4xx_spi.h"
#include "delay.h"

#define READ_CM 	0x80
#define WRITE_CM	0x00

void SPI1_Init(void);
uint8_t SPI1_transfer_byte(uint8_t data);
uint16_t SPI_read_reg(void);

void MPU6000_ChipEnable(void);
void MPU6000_ChipDisable(void);
void HMC5983_ChipEnable(void);
void HMC5983_ChipDisable(void);
void MS5611_ChipEnable(void);
void MS5611_ChipDisable(void);


#endif
