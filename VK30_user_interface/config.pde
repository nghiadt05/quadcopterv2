/*
  SCREEN NUMBER
 */
public final float pi                  =3.14159265359;
public final float rad2degree          =180/pi;
public final float degree2rad          =pi/180;
public final int HEIGHT                =600;
public final int WIDTH                 =800;
public final int WELCOME_SCREEN        =0;
public final int CALIBRATE_GYRO_SCREEN =1;
public final int CALIBRATE_ACC_SCREEN  =2;
public final int CALIBRATE_MAG_SCREEN  =3;
public final int IMU_DISPLAY_SCREEN    =4;
public final int GPS_MAP_SCREEN        =5;
public final int PID_GAINING_SCREEN    =6;

//---------- LIST OF SYSTEM VARIABLES --------------
int screen=WELCOME_SCREEN;
int last_screen;
//--------------------------------------------------

