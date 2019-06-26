#include "stm32f4xx.h"
#include "my_rcc_config.h"
#include "delay.h"
#include "led_pc3.h"
#include "my_usart.h"
#include "tm1_ovf.h"
#include "MPU6000.h"
#include "HMC5983.h"
#include "AHRS.h"
#include "MS5611.h"
#include "GPS_6MV2.h"
#include "Processing.h"
#include "pid.h"
#include "rx.h"
#include "motor.h"
//#include "futaba_sbus.h"

uint16_t stand_by_loop;//=12000;//wait 1 miniute	
int main(void)
{	
	SystemInit();
	RCC_xtal_configuration();
	Delay_Init();
	TM1_OVF_Configuration();
	led_init();			
	USART1_Config(256000);	
	USART3_Config(9600);	
	USART6_Config(115200);
	
	RX_Configuration();
	Motor_Configuration();
	SPI1_Init();							//okie
	MPU6000_Configuration();	//okie
	HMC5883_Configuration();	//okie
	MS5611_Configuration(); 	//okie
	PID_Init();
	led_on();
	delay_ms(1000);
	led_off();

  while(1)
  {		
		GPIOB->ODR ^= GPIO_Pin_3;//mesure the loop time by using this pin			
		//---- the highest priority -------	 
		MPU6000_get_value();
		HMC5983_get_value();				
		MPU6000_Calculation();
		MadgwickAHRSupdate(gyro_value[1]*M_PI/180.0f,gyro_value[0]*M_PI/180.0f,gyro_value[2]*M_PI/180.0f,acc_value[1],acc_value[0],acc_value[2],(float)mag_x_raw,(float)mag_y_raw,(float)mag_z_raw);
		getRollPitchYaw();
		MS5611_Update(CMD_ADC_4096,CMD_ADC_4096);
		BaroFilterUpdate();
		GPS_Get_data();
		Processing_data_decode();
		Processing_send_data();
		
		RX_Calculation();
		PID_Update();
		MOTOR_OUT();
		//---------------------------------	
		
		if(stand_by_loop<10000)//wait till the AHRS for yaw angle becomes stable
		{		
		stand_by_loop++;
		}
		else//move to controlling arrea
		{
			led_on();
			CHECK_START_STT();	
		}
		//---------------------------------
		fix_loop_time();		
  } 
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to rep ort the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif
