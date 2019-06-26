int home_position;
float yaw_home_angle;
int test_angle_pt_max;
public void keyPressed()
{
  if (screen==IMU_DISPLAY_SCREEN)
  {
    if (key=='h')
    {
      home_position=1;
      yaw_home_angle=rpy[2];
    } else if (key=='n')
    {
      home_position=0;
      yaw_home_angle=0;
    }
  } else if (screen==CALIBRATE_MAG_SCREEN)
  {
    if (key=='h')
    {
      yaw_home_angle=yaw_angle;
    } else if (key=='n')
    {
      yaw_home_angle=0;
    }
    else if (key==39)//Press: '
    {
      test_mag_str_array_pt--;
      if (test_mag_str_array_pt<0)test_mag_str_array_pt=0;
    } else if (key==92)//press: \
    {
      test_mag_str_array_pt++;
      if (test_mag_str_array_pt>test_angle_pt_max)test_mag_str_array_pt=test_angle_pt_max;
    } else if (key==10)//enter
    {
      test_mag_str_array[test_mag_str_array_pt]=String.valueOf((float)test_mag_str_array_pt)+','+
        String.valueOf(yaw_angle_temp)+','+
        String.valueOf(mag_x_raw)+','+
        String.valueOf(mag_y_raw)+','+
        String.valueOf(mag_z_raw);
      yaw_calculated[test_mag_str_array_pt]=yaw_angle_temp;
      test_mag_str_array_pt++;      
      test_mag_str_array_pt%=360;
      test_angle_pt_max=test_mag_str_array_pt;
    }
  }
}

