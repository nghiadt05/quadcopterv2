#include "GPS_6MV2.h"
#include "led_pc3.h"

uint8_t data_pt;
uint8_t	ms_pt;
uint8_t ms_name[5];
uint8_t data_type;
uint8_t GPGLL[6]="GPGLL";
uint8_t GLL_DETAILS[50]=",2057.63074,N,10548.15068,E,055154.00,A,A*6D\n\r";
uint8_t GLL;
uint8_t VALID;
uint8_t Valid[1];
uint8_t NorthSouth;
uint8_t EastWest; 
uint32_t longitude,latitude;
float real_time;

uint8_t gll_receive_done=1;
uint8_t gll_start_receiving=0;
uint8_t calculate_stt=0;


void GPS_Get_data(void)//okie
{
	//,2057.63074,N,10548.15068,E,055154.00,A,A*6D\n\r
	if(gll_receive_done==1)
	{
		uint8_t GLL_TEMP_DETAILS[50];//need to be used
		uint8_t block_pt=0;
		uint8_t data_pt=0;
		uint8_t i;
		uint8_t GPS_TEMP_DATA[5][15];
		uint8_t len=strlen((char*)GLL_DETAILS);		

		for(i=0;i<len;i++)
		{
//			usart_putchar(USART1,GLL_DETAILS[i]);	
			GLL_TEMP_DETAILS[i]=GLL_DETAILS[i];
		}
		
		len=len-8;//move to valid/invalid charater
		Valid[0]=GLL_TEMP_DETAILS[len];
		
		if(Valid[0]=='V')//data is invalid
		{
			VALID=0;
		}
		else if(Valid[0]=='A')//data is valid
		{			
				VALID=1;			
				data_pt=0;
				block_pt=0;			
				for(i=0;i<len;i++)
				{ 
				if(GLL_TEMP_DETAILS[i]==',')
				{
					block_pt++;
					data_pt=0;
				}
				else
				{
					GPS_TEMP_DATA[block_pt][data_pt]=GLL_TEMP_DETAILS[i];
					data_pt++;
				}
				}				

			latitude=(uint32_t)(atof((char*)GPS_TEMP_DATA[1])*1e5);
			longitude=(uint32_t)(atof((char*)GPS_TEMP_DATA[3])*1e5);
			//NorthSouth=GPS_TEMP_DATA[2][0];//charater 'N' or 'S'			
			//EastWest=GPS_TEMP_DATA[4][0];//charater 'E' or 'W'
			//real_time=atof((char*)GPS_TEMP_DATA[5]);
			gll_receive_done=0;//clear this flag for the next detection
							
//			usart_port=1;
//			printf("Cal:%d,%d,%d\r",latitude,longitude,VALID);
//			printf("%d,%d,",latitude/100000,latitude%100000);
				
		}
	}
}

void USART3_IRQHandler(void)//work fine
{
	if(USART_GetITStatus(USART3,USART_IT_RXNE))//receive complete
	{
		//$GPGLL,Latitude,N,Longitude,E,hhmmss.ss,Valid,Mode*cs<CR><LF>
		//$GPGLL,4717.11364,N,00833.91565,E,092321.00,A,A*60
		uint8_t ch=USART_ReceiveData(USART3);
		if(ch=='$')
		{
			if(gll_start_receiving)gll_receive_done=1;
			gll_start_receiving=0;
			data_type=0;//message label
			ms_pt=0;//reset message pointer
			GLL=1;			
		}
		else
		{
			switch(data_type)
			{
				case 0://message label
						ms_name[ms_pt]=ch;			
						if(ms_name[ms_pt]!=GPGLL[ms_pt])
						{
							GLL=0;
						}						
						if(ms_pt==4)
						{
							if(GLL==1)
							{
								uint8_t i;
								for(i=0;i<50;i++)
								{
									GLL_DETAILS[i]=0;
								}		
								data_type=1;
								data_pt=0;															
								gll_start_receiving=1;
							}
						}						
						ms_pt++;			
						ms_pt%=5;
						break;
				case 1:
						GLL_DETAILS[data_pt]=ch;
						data_pt++;
						break;
			}
		}
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);
	}	
}

