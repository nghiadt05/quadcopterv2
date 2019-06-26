//-------- variables -----------
public int calib_gyro=0;
public float gyro_x_raw_array[]=new float[65535];
public float gyro_y_raw_array[]=new float[65535];
public float gyro_z_raw_array[]=new float[65535];
public int gyro_pt=580;
public int gyro_cl_data[]=new int[3];
//------------------------------

public void Draw_gyro_screen()
{
  clear();
  background(0);
  image(myImages[1], 0, 0);//banner
  Gyro_calibration();
  Draw_gyro_graphic();
  Draw_gyro_color();
  Draw_gyro_raw();
}

public void  Gyro_calibration()
{
  image(myImages[2], 570, 140);//guide image
  image(myImages[3], 130, 180);//gyro_calibrate_bt= 120x35
  image(myImages[4], 310, 180);//gyro_send_to_uC=120x35
  textFont(font);
  textSize(24);
  fill(0, 255, 0);
  text("Please place the board on a static surface and avoid any ", 5, 145);
  text("vibration sources nereby, then press CALIBRATE button.", 5, 170);
  //println(gyro_x_raw+"  "+gyro_y_raw+"  "+gyro_z_raw);

  if (calib_gyro==1)
  {
    if (gyro_pt>2000)//get 2000 new gyro data
    {
      for (int i=0; i<2000; i++)
      {           
        gyro_cl_data[0]+=(int)gyro_x_raw_array[i];
        gyro_cl_data[1]+=(int)gyro_y_raw_array[i];
        gyro_cl_data[2]+=(int)gyro_z_raw_array[i];
      }
      gyro_cl_data[0]/=2000;
      gyro_cl_data[1]/=2000;
      gyro_cl_data[2]/=2000;

      println("gyroscope is calibrated");
      println("gyro_x_offset_LSB= "+gyro_cl_data[0]);
      println("gyro_y_offset_LSB= "+gyro_cl_data[1]);
      println("gyro_z_offset_LSB= "+gyro_cl_data[2]);

      calib_gyro=0;
    } else
    {
      textSize(24);
      text("Please wait for a moment ...!", 100, 248);
    }
  }
  else//calibrate done
  {
    textSize(24);
    fill(#00FF00);
    text("gyro_x_offset_LSB= "+gyro_cl_data[0], 20, 255);
    text("gyro_y_offset_LSB= "+gyro_cl_data[1], 20, 285);
    text("gyro_z_offset_LSB= "+gyro_cl_data[2], 20, 315);
  }
}

public void Draw_gyro_graphic()
{
  translate(220, 590);
  //------- draw background ----------------
  for (int i=0; i<13; i++)
  {
    if (i==6)
    {
      strokeWeight(2);
      stroke(109, 0, 255);
    } else
    {
      strokeWeight(1);
      stroke(#78737E);
    }
    line(0, -i*20, 580, -i*20);
  }
  //----------------------------------------
  //------- draw Ot vs Ox line -------------
  strokeWeight(5);
  stroke(0, 0, 255);
  line(0, 0, 0, -250);
  line(0, 0, 580, 0);
  //----------------------------------------

  //------- draw 580 latest values of the gyroscope --------
  if (gyro_pt>580)
  {
    strokeWeight(3);
    for (int i=0; i<579; i++)
    {
      stroke(#03FFE8);
      line(i, -(gyro_x_raw_array[gyro_pt-580+i]/200)-120, i+1, -(gyro_x_raw_array[gyro_pt-579+i]/200)-120);
      stroke(#03FF11);
      line(i, -(gyro_y_raw_array[gyro_pt-580+i]/200)-120, i+1, -(gyro_y_raw_array[gyro_pt-579+i]/200)-120);
      stroke(#FFF703);
      line(i, -(gyro_z_raw_array[gyro_pt-580+i]/200)-120, i+1, -(gyro_z_raw_array[gyro_pt-579+i]/200)-120);
    }
  }
  //--------------------------------------------------------
  translate(-220, -590);
}

public void Draw_gyro_color()
{  
  String str_temp[]=new String[3];
  color color_temp[]=new color[3];  
  color_temp[0]=#03FFE8;
  color_temp[1]=#03FF11;
  color_temp[2]=#FFF703;
  str_temp[0]="Gyro X";
  str_temp[1]="Gyro Y";
  str_temp[2]="Gyro Z";
  for (int i=0; i<3; i++)
  {
    textSize(20);
    fill(color_temp[i]);
    text(str_temp[i], 18, 370+i*25);
    noStroke();
    rect(95, i*30+350, 30, 20);
  }
}

public void Draw_gyro_raw()
{
  textSize(24);
  fill(#00FF00);
  text("Gx_raw= "+gyro_x_raw, 18, 490);
  text("Gy_raw= "+gyro_y_raw, 18, 520);
  text("Gz_raw= "+gyro_z_raw, 18, 550);
}

public void Gyro_send_to_uc()
{
  /*
  gyro_cl_data[0]=1;
   gyro_cl_data[1]=2;
   gyro_cl_data[2]=3;
   */
  String gyro_send_string;
  String gyro_offset_string[]=new String[3];
  gyro_offset_string[0]=String.valueOf(gyro_cl_data[0]);
  gyro_offset_string[1]=String.valueOf(gyro_cl_data[1]);
  gyro_offset_string[2]=String.valueOf(gyro_cl_data[2]);
  gyro_send_string="&1,"+gyro_offset_string[0]+','+gyro_offset_string[1]+','+gyro_offset_string[2]+'@';
  println(gyro_send_string); 
  while (serial_free==0) {
  }
  myPort.write(gyro_send_string);
  println("gyroscope data is sent");
}

