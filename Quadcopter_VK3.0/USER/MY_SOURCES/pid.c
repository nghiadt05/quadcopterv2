#include "pid.h"

#define sqrt_2_devide_2 0.7071
float target_angle[3];
float throttle;
float KP[5],KD[5],KI[5];
float PID_P_TEMP[3];
float PID_D_TEMP[3];
float PID_I_TEMP[3];
volatile float error_temp;
int16_t PID_OUT[3];

void PID_Init(void)
{
	//----- PID roll axis -------
	KP[0]=8.0f;
	KD[0]=4.8f;
	KI[0]=0.0f;
	//---------------------------
	
	//----- PID pitch axis -------
	KP[1]=8.0f;
	KD[1]=4.8f;
	KI[0]=0.0f;
	//---------------------------
	
	//----- PID pitch axis -------
	KP[2]=25.5f;
	KD[2]=5.2f;
	KI[0]=0.0f;
	//---------------------------
}

void PID_Update(void)
{
	if(run==1)
	{
		int i=0; 
		for(i=0;i<3;i++)
		{				
			error_temp=target_angle[i]-rpy[i];
			if(i==2)//pid for yaw angle
			{				
				static int16_t PID_OUT_Z_TEMP_STATIC=MAX_PID_OUT_Z;
				//get the smalest diferrences between two angles
				if(error_temp>180)error_temp-=360;
				else if(error_temp<-180)error_temp+=360;						
				PID_P_TEMP[i]=CONSTRAIN(KP[i]*error_temp,MAX_PID_P_OUT_Z);
				PID_D_TEMP[i]=CONSTRAIN(KD[i]*gyro_value[i],MAX_PID_D_OUT_Z);
				PID_I_TEMP[i]+=KI[i]*error_temp*(loop_time/1000.0f);
				PID_I_TEMP[i]=CONSTRAIN(PID_I_TEMP[i],MAX_PID_I_OUT);		
				PID_OUT[i]=PID_P_TEMP[i]+PID_D_TEMP[i]+PID_I_TEMP[i];
				PID_OUT[i]=(int16_t)CONSTRAIN(PID_OUT[i],PID_OUT_Z_TEMP_STATIC);				
				/*
				if(yaw_stick_pos==0)//no movements of it just comes back to the center position
				{		
					PID_OUT_Z_TEMP_STATIC+=2;
					if(PID_OUT_Z_TEMP_STATIC>MAX_PID_OUT_Z)PID_OUT_Z_TEMP_STATIC=MAX_PID_OUT_Z;
					PID_OUT[i]=(int16_t)CONSTRAIN(PID_OUT[i],PID_OUT_Z_TEMP_STATIC);
				}
				else//yaw stick is moving
				{
					PID_OUT_Z_TEMP_STATIC=0;				
					PID_OUT[i]=(int16_t)CONSTRAIN(PID_OUT[i],MAX_PID_OUT_Z);
				}
				*/
			}
			else//pid roll and pitch
			{	
				error_temp=CONSTRAIN(error_temp,MAX_TARGET_ANGLE);			
				PID_P_TEMP[i]=CONSTRAIN(KP[i]*error_temp,MAX_PID_P_OUT);
				PID_D_TEMP[i]=CONSTRAIN(KD[i]*gyro_value[i],MAX_PID_D_OUT);
				PID_I_TEMP[i]+=KI[i]*error_temp*(loop_time/1000.0f);
				PID_I_TEMP[i]=CONSTRAIN(PID_I_TEMP[i],MAX_PID_I_OUT);			
				PID_OUT[i]=(int16_t)CONSTRAIN((PID_P_TEMP[i]+PID_D_TEMP[i]+PID_I_TEMP[i]),MAX_PID_OUT);			
			}	
//				if(i==2)
//				{
//					usart_port=1;
//					printf("%d %d %d\r",(int)target_angle[2],(int)rpy[2],PID_OUT[2]);
//				}		
		}
	}
	else
	{
		int i=0; 
		for(i=0;i<3;i++)
		{	
			PID_OUT[i]=0;
		}
	}
}
            
void MOTOR_OUT(void)
{
	//////Quad X configuration
//////MT4 (CCW)			MT3(CW)	
//////	\			+x		 /
//////	 \		|			/
//////		\		|		 /	
//////		 \------/ 
////// +y---******---
//////		 /------\
//////		/		|		 \
//////	 /		|			\
//////	/						 \
//////MT1(CW)	   MT2(CCW)
	
	//Quad + configuration	
//		       mt1(CCW)
//		     ***(y)***
//						 ^
//						 |
//						 |
//						 |
//						 |
//mt2(x)<------0---------mt4
//(CW)				 |				(CW)	
//			       |
//			       |
//			       |
//	         mt3(CCW)

	if(start==1)
	{
		if((int)(throttle*100)>=10)//throtle>=0.1
		{ 
			uint8_t i;
			uint16_t PWM_MT[5];
			float throttle_temp=throttle-0.1f;
			uint16_t MOTOR_BASE=PWM_RANGE*throttle_temp+PWM_MIN;	
						
//			usart_port=1;
//			printf("%d\r",MOTOR_BASE);
			
			#ifdef PLUS_MODE
			PWM_MT[1]=MOTOR_BASE-(int16_t)PID_OUT[1]-(int16_t)PID_OUT[2];
			PWM_MT[2]=MOTOR_BASE-(int16_t)PID_OUT[0]+(int16_t)PID_OUT[2];
			PWM_MT[3]=MOTOR_BASE+(int16_t)PID_OUT[1]-(int16_t)PID_OUT[2];
			PWM_MT[4]=MOTOR_BASE+(int16_t)PID_OUT[0]+(int16_t)PID_OUT[2];
			#endif
			
			#ifdef X_MODE
			PWM_MT[1]=MOTOR_BASE+(int16_t)(sqrt_2_devide_2*(-PID_OUT[0]-PID_OUT[1]))-(int16_t)PID_OUT[2];
			PWM_MT[2]=MOTOR_BASE+(int16_t)(sqrt_2_devide_2*(-PID_OUT[0]+PID_OUT[1]))+(int16_t)PID_OUT[2];
			PWM_MT[3]=MOTOR_BASE+(int16_t)(sqrt_2_devide_2*( PID_OUT[0]+PID_OUT[1]))-(int16_t)PID_OUT[2];
			PWM_MT[4]=MOTOR_BASE+(int16_t)(sqrt_2_devide_2*( PID_OUT[0]-PID_OUT[1]))+(int16_t)PID_OUT[2];
			#endif			
	
			for(i=1;i<5;i++)
			{
				if(PWM_MT[i]<PWM_MIN)PWM_MT[i]=PWM_MIN;
				else if(PWM_MT[i]>PWM_MAX)PWM_MT[i]=PWM_MAX;
			}			
			TIM5->CCR1=PWM_MT[1];
			TIM5->CCR2=PWM_MT[2];
			TIM5->CCR3=PWM_MT[3];
			TIM5->CCR4=PWM_MT[4];
		}
		else//throttle is smaler than 0.1
		{
			if(_1st_run==1)
			{
				MOTOR_WARNING();
			}
			else
			{
				MOTOR_ARMING();
			}
		}		
	}
	else
	{
		MOTOR_ARMING();
	}
}

