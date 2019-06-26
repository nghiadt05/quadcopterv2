#include "Processing.h"
#include "led_pc3.h"

uint8_t mode,sending_mode;
uint8_t receiving_mode;
uint8_t rx_done;
uint8_t rx_pt;
uint8_t temp_string[100];
//uint8_t temp_string[100]="1,123,456,789@";
//uint8_t temp_string[100]="2,123,456,789,23,45,67@";
//uint8_t temp_string[100]="3,123,456,789,-23,-45,-67@";

void Processing_data_decode(void)//work fine
{
	if(rx_done)
	{
	//"1,123,456,789@"//gyro data
	
	//"2,acc_x_offset,acc_y_offset,acc_z_offset,acc_x_scale,acc_y_scale,acc_z_scale@"
	
	//"3,mag_x_offset,mag_y_offset,mag_z_offset,mag_x_scale,mag_y_scale,mag_z_scale@"
	uint8_t data_segment;
	uint8_t i,calib_data_pt;
	uint8_t calib_data[10][20];	
	uint8_t data_kind;
	uint8_t len;
	
	len=strlen((char*)temp_string);
	data_kind=temp_string[0]-48;
	data_segment=0;
	calib_data_pt=0;
	
	for(i=1;i<len;i++)
		{
			if(temp_string[i]==',')//split character
			{
					calib_data_pt=0;
					data_segment++;									
			}
			else if(temp_string[i]=='@')//stop character
			{
					switch (data_kind)
				{
					case 1://gyro calib
						gyro_x_offset=(int16_t)atof((char*)calib_data[1]);
						gyro_y_offset=(int16_t)atof((char*)calib_data[2]);
						gyro_z_offset=(int16_t)atof((char*)calib_data[3]);
//						usart_port=1;
//						printf("1: %d, %d, %d\r",(int)gyro_x_offset,(int)gyro_y_offset,(int)gyro_z_offset);		
						break;
					case 2://acc calib
						acc_x_offset=(int16_t)atof((char*)calib_data[1]);
						acc_y_offset=(int16_t)atof((char*)calib_data[2]);
						acc_z_offset=(int16_t)atof((char*)calib_data[3]);
						AccX_sensitivity=(int16_t)atof((char*)calib_data[4]);
					  AccY_sensitivity=(int16_t)atof((char*)calib_data[5]);
					  AccZ_sensitivity=(int16_t)atof((char*)calib_data[6]);
//						usart_port=1;
//					  printf("2: %d, %d, %d, %d, %d, %d\r",(int)acc_x_offset,(int)acc_y_offset,(int)acc_z_offset,(int)AccX_sensitivity,(int)AccY_sensitivity,(int)AccZ_sensitivity);
						break;	
					case 3://mag calib
						mag_x_offset+=(int16_t)atof((char*)calib_data[1]);
						mag_y_offset+=(int16_t)atof((char*)calib_data[2]);
						mag_z_offset+=(int16_t)atof((char*)calib_data[3]);
						mag_x_scale=atof((char*)calib_data[4]);
					  mag_y_scale=atof((char*)calib_data[5]);
					  mag_z_scale=atof((char*)calib_data[6]);								
//						usart_port=1;
//					  printf("3: %d, %d, %d, %d, %d, %d, %f, %f, %f\r",(int)mag_x_offset,(int)mag_y_offset,(int)mag_z_offset,(int)mag_x_scale,(int)mag_y_scale,(int)mag_z_scale,alpha,beta,theta);

						break;
					case 4:
						KP[0]=atof((char*)calib_data[1]);
						KD[0]=atof((char*)calib_data[2]);
						KI[0]=atof((char*)calib_data[3]);
//						usart_port=1;
//						printf("4: %d,%d,%d\r",(uint32_t)(KP[0]*10000.0f),(uint32_t)(KD[0]*10000.0f),(uint32_t)(KI[0]*10000.0f));
						break;
					case 5:
						KP[1]=atof((char*)calib_data[1]);
						KD[1]=atof((char*)calib_data[2]);
						KI[1]=atof((char*)calib_data[3]);
//						usart_port=1;
//						printf("5: %d,%d,%d\r",(uint32_t)(KP[1]*10000.0f),(uint32_t)(KD[1]*10000.0f),(uint32_t)(KI[1]*10000.0f));
						break;
					case 6:
						KP[2]=atof((char*)calib_data[1]);
						KD[2]=atof((char*)calib_data[2]);
						KI[2]=atof((char*)calib_data[3]);
//						usart_port=1;
//						printf("6: %d,%d,%d\r",(uint32_t)(KP[2]*10000.0f),(uint32_t)(KD[2]*10000.0f),(uint32_t)(KI[2]*10000.0f));
						break;
				}		
			}
			else
				{
					calib_data[data_segment][calib_data_pt]=temp_string[i];
					calib_data_pt++;
				}
			}
			
			for(i=0;i<100;i++)
			{
				temp_string[i]=0;
			}		
	}
	rx_done=0;	
}

void Processing_send_data(void)
{	
	if(sending_mode==1)//calibration mode
	{
		static uint8_t i=0;	
		#ifdef P_port_usart1
		usart_port=1;
		#endif
		
		#ifdef P_port_usart6
		usart_port=6;
		#endif
		
		//----- prepare and send data -----
		switch(i)
		{
			//send gyro data
			case 0:
				printf("%d,%d,%d,",gyro_x_raw,gyro_y_raw,gyro_z_raw);
				break;
			//-------------------------------
			//send accelerometer data
			case 1:			
				printf("%d,%d,%d,",acc_x_raw,acc_y_raw,acc_z_raw);
				break;
			//--------------------------------
			//send magnetic data
			case 2:	
				printf("%d,%d,%d,%d\r",mag_x_raw,mag_y_raw,mag_z_raw,(int)(rpy[2]*100.0f));
				break;
			//--------------------------------			
		}
		i++;
		i%=3;
		//---------------------------------
	}
	else if(sending_mode==2)
	{
		static uint8_t i;
		#ifdef P_port_usart1
		usart_port=1;
		#endif
		
		#ifdef P_port_usart6
		usart_port=6;
		#endif
		
		switch(i)
		{
			case 0:
				printf("%d,",(int)(rpy[0]*100));
				break;
			case 1:
				printf("%d,",(int)(rpy[1]*100));
				break;
			case 2:
				printf("%d,",(int)(rpy[2]*100));
				break;
			case 3:
				printf("%d,",(int32_t)P);
				break;
			case 4:
				printf("%d,",(int)T);
				break;
			case 5:
				printf("%d,",VALID);
				break;
			case 6:
				printf("%d,",latitude/100000);
				break;
			case 7:
				printf("%d,",latitude%100000);
				break;			  
			case 8:
				printf("%d,",longitude/100000);
				break;
			case 9:
				printf("%d\r",longitude%100000);
				break;
		}
		i++;
		i%=10;
	}
	else if(sending_mode==3)
	{
		static uint8_t i;
		#ifdef P_port_usart1
		usart_port=1;
		#endif
		
		#ifdef P_port_usart6
		usart_port=6;
		#endif		
		switch(i)
		{
			case 0:
				printf("%d,%d,%d,",(int32_t)PID_OUT[0],(int32_t)PID_OUT[1],(int32_t)PID_OUT[2]);
				break;	
			case 1:
				//printf("%d,%d,%d,",(int)rpy[0],(int)rpy[1],(int)rpy[2]);
				printf("%d,%d,%d,",(int)(rpy[0]*100),(int)(rpy[1]*100),(int)(rpy[2]*100));
				break;	
			case 2:
				printf("%d,%d,%d,",(uint32_t)(KP[0]*1000.0f),(uint32_t)(KD[0]*1000.0f),(uint32_t)(KI[0]*1000.0f));
				break;
			case 3:
				printf("%d,%d,%d,",(uint32_t)(KP[1]*1000.0f),(uint32_t)(KD[1]*1000.0f),(uint32_t)(KI[1]*1000.0f));
				break;
			case 4:
				printf("%d,%d,%d\r",(uint32_t)(KP[2]*1000.0f),(uint32_t)(KD[2]*1000.0f),(uint32_t)(KI[2]*1000.0f));
				break;
		}
		i++;
		i%=5;
	}
}


		
#ifdef P_port_usart1
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE))//receive complete
	{
		uint8_t ch=USART1->DR;
		if(ch=='%')//sending data mode
		{
			mode=1;
		}
		else if(ch=='&')//receiving data mode
		{
			mode=2;			
			rx_pt=0;
			rx_done=0;
		}
		else
		{
			switch(mode)
			{
				case 1:
					sending_mode=ch-48;		
					break;
				case 2:
					temp_string[rx_pt]=ch;								
					rx_pt++;
					if(ch=='@')//end signal			
					{								
						rx_done=1;												
					}
					break;
			}
		}		
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
}
#endif


#ifdef P_port_usart6
void USART6_IRQHandler(void)
{
	if(USART_GetITStatus(USART6,USART_IT_RXNE))//receive complete
	{
		uint8_t ch=USART6->DR;
		if(ch=='%')//sending data mode
		{
			mode=1;
		}
		else if(ch=='&')//receiving data mode
		{
			mode=2;			
			rx_pt=0;
			rx_done=0;
		}
		else
		{
			switch(mode)
			{
				case 1:
					sending_mode=ch-48;		
					break;
				case 2:
					temp_string[rx_pt]=ch;								
					rx_pt++;
					if(ch=='@')//end signal			
					{								
						rx_done=1;												
					}
					break;
			}
		}		
		USART_ClearITPendingBit(USART6,USART_IT_RXNE);
	}
}
#endif
