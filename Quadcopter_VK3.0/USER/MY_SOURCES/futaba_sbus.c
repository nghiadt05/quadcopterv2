#include "futaba_sbus.h"

unsigned char start_byte=0Xf0;
unsigned char stop_byte=0x00;
unsigned char data_byte_array[25];
unsigned char FUTABA_rx_done;
unsigned int  FUTABA_CHANNEL[16];//values for channel 0-15
unsigned char FUTABA_CHANNEL_17;
unsigned char FUTABA_CHANNEL_18;
unsigned char futaba_byte_pt;



void SBUS_DATA_SETUP(void)
{
	uint8_t i=0;
	for(i=0;i<22;i++)
	{
		data_byte_array[i]=0x55+i;	
	}
	data_byte_array[22]=0xc0;
}

void SBUS_DECODE(void)
{
	//FUTABA_rx_done=1;
	if(FUTABA_rx_done==1)
	{
		unsigned char sbus_temp_array[25];
		unsigned char sbus_bit_array[180];//2*8=176 bit
		unsigned char i=0;
		unsigned char j=0;
		unsigned char temp_pt=futaba_byte_pt;
		usart_port=1;
		//printf("SBUS data decoding\r");
		if(temp_pt==22)
		{
			//-------- store usart data to a buffer array ----------
			for(i=0;i<22;i++)
			{
			 sbus_temp_array[i]=data_byte_array[i];
			 //printf("%c",sbus_temp_array[i]);		 
			}
			//printf("\r");
			//------------------------------------------------------
			
			//--- store all of 176-bit data to a buffer array ------
			for(i=0;i<22;i++)
			{
				for(j=0;j<8;j++)
				{
					sbus_bit_array[i*8+j]=(sbus_temp_array[i]&(1<<(7-j)))>>(7-j);
					//printf("%c",sbus_bit_array[i*8+j]+48);
					//if(j==3)printf(" ");
				}
				//printf("---");			
			}
			//printf("\r");
			//------------------------------------------------------
			/*
			//----- show the received data ------------
			printf("Show sbus_data");
			for(i=0;i<176;i++)
			{
					if((i%11)==0)
				{				
					printf("\r");
					printf("%d:",i/11);
				}
				printf("%c",sbus_bit_array[i]+48);
			
			}
			printf("\r");
			//-----------------------------------------
			*/
			//----- get every 11 bits in those 176-bit data array for each RX channel ------
			
			for(i=0;i<16;i++)
			{
				FUTABA_CHANNEL[i]=0;
				for(j=0;j<11;j++)
				{
					FUTABA_CHANNEL[i]|=sbus_bit_array[i*11+j]<<(10-j);
				}
			}
			printf("%d\r",FUTABA_CHANNEL[0]);	
			/*
			printf("\rCalculated data:\r");
			for(j=0;j<16;j++)
			{
				printf("Ch %d ",j);
				for(i=0;i<11;i++)
				{
				printf("%c",((FUTABA_CHANNEL[j]&(1<<(10-i)))>>(10-i))+48);					
				}
				printf(" Value: %d",FUTABA_CHANNEL[j]);	
				printf("\r");
			}		
			*/
			//------------------------------------------------------------------------------	
			
			FUTABA_rx_done=0;
		}
	}
}

void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2,USART_IT_RXNE))//receive complete
	{
		char rx = USART2->DR;
//		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
//		usart_putchar(USART1,rx);
		
		if(rx==start_byte)
		{
			futaba_byte_pt=0;
			FUTABA_rx_done=0;
		}
		else if(rx==stop_byte)
		{
			FUTABA_rx_done=1;
		}
		else
		{
		data_byte_array[futaba_byte_pt]=rx;
		futaba_byte_pt++;	
		}
	}
}

