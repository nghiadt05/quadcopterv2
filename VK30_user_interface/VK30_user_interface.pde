/*
 VK 3.0 board Processing program
 This program is used for calibrating purposes, as well as display the data
 from the ARM STM32F4 based board.
 
 Ver1.0-26/6/2014
 Released and written by DOAN TRUNG NGHIA
 Email: doantrungnghia05@gmail.com
 Phone: 0084 1649 625 926
 Skype: doantrungnghia05
 
 Project supervisor: Master MAI DUY PHUONG
 Email: phuongmd@yahoo.com 
 */

/*
   MAIN PROGRAM
 */

void setup()
{
  Graphic_configuration();
  Font_Image_Configuration(); 
  Com_check_available() ;

  //system init value
  mag_init();
  myMapInit();
}

void draw()
{
  switch(screen)
  {
  case WELCOME_SCREEN:
    Draw_welcome_screen();
    break;
  case CALIBRATE_GYRO_SCREEN:
    Draw_gyro_screen();    
    break;
  case CALIBRATE_ACC_SCREEN:
    Draw_acc_screen();
    break;
  case CALIBRATE_MAG_SCREEN:
    Draw_mag_screen();
    break;
  case IMU_DISPLAY_SCREEN:
    Draw_imu_screen();
    break;
  case GPS_MAP_SCREEN:
    Draw_GPS_screen();
    break;
  case PID_GAINING_SCREEN:
    Draw_PID_Screen();
    break;
  }  
  Draw_mouse_pos();
}

