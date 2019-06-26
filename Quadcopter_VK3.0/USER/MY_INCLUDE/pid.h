#ifndef PID_H_
#define PID_H_

#include "stm32f4xx.h"
#include "math.h"
#include "mpu6000.h"
#include "hmc5983.h"
#include "ms5611.h"
#include "ahrs.h"
#include "tm1_ovf.h"
#include "motor.h"
#include "rx.h"

#define MIN(a, b)			(((a) < (b)) ? (a) : (b))
#define MAX(a, b)			(((a) > (b)) ? (a) : (b))
#define MINMAX(x, min, max)	(MIN(MAX((x), (min)), (max)))
#define CONSTRAIN(x, a) (MINMAX(x, -(a), (a)))

#define MAX_TARGET_ANGLE 	40
#define MAX_PID_P_OUT 	 	500	
#define MAX_PID_P_OUT_Z 	450	
#define MAX_PID_D_OUT 		2500  
#define MAX_PID_D_OUT_Z 	1500 
#define MAX_PID_I_OUT		 	500  
#define MAX_PID_OUT				3500  
#define MAX_PID_OUT_Z			1800 

#define X_MODE
//#define PLUS_MODE

extern float target_angle[3];
extern float throttle;
extern float KP[5],KD[5],KI[5];
extern float PID_P_TEMP[3];
extern float PID_D_TEMP[3];
extern float PID_I_TEMP[3];
volatile extern float error_temp;
extern int16_t PID_OUT[3];

void PID_Init(void);
void PID_Update(void);
void MOTOR_OUT(void);
#endif
