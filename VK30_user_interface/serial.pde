//-------- variables -----------
import processing.serial.*;
public Serial myPort;
public int no_com_ports, com_chosen;
public String serial_list[]=new String[20];
public float gyro_x_raw, gyro_y_raw, gyro_z_raw;
public float acc_x_raw, acc_y_raw, acc_z_raw;
public float mag_x_raw, mag_y_raw, mag_z_raw;
public float rpy[]=new float[3];
public float T=25;
public float P=10000;
public int serial_free=1;
public int first_start=0;
//------------------------------

public void Com_check_available()
{
  // List all the available serial ports:
  no_com_ports=Serial.list().length;
  println("Number of com ports= "+no_com_ports);
  for (int j=0; j<no_com_ports; j++)
  {
    serial_list[j]=Serial.list()[j];
    println(serial_list[j]);
  }
}

public void Com_start()
{
  //------ com start up ------------
  if (first_start==0)
  {  
    myPort = new Serial(this, serial_list[com_chosen], 115200);
    myPort.bufferUntil('\r');
    first_start=1;
  }
  //--------------------------------
  if (receiving_mode==1)
  {
    for (int i=0; i<1; i++)
    {
      myPort.write("%1");//start_send calib mode
    }
  } else if (receiving_mode==2)
  {
    for (int i=0; i<1; i++)
    {
      myPort.write("%2");//start_send calib mode
    }
  } else if (receiving_mode==3)
  {
    for (int i=0; i<1; i++)
    {
      myPort.write("%3");//start_send calib mode
    }
  }
  println("Start command is sent");  
  //---------------------------------
}

public void COM_Stop()
{
  myPort.write("%0");//stop sending data mode
}
public void Draw_com_ports()
{
  //----- draw Start button -------
  //image(myImages[5], 10, 80);
  //-------------------------------

  //------------ draw com ports and check a chosen port ----------------
  strokeWeight(3);
  stroke(0);
  textFont(font);
  textSize(18);
  for (int i=0; i<no_com_ports; i++)
  {
    if (mouseX>35 && mouseX<95 && mouseY>(i*40+225) && mouseY<(i*40+255))
    {
      fill(#00ffff);
    } else
    {  
      noFill();
    }

    //------- fill color to chosen box and draw boxes --------
    if (com_chosen==i)
    {
      fill(#00ffff);
    }
    rect(35, i*40+225, 70, 30);    

    fill(0);
    text(serial_list[i], 40, i*40+250);
    //--------------------------------------------------------
  }
  //-----------------------------------------------------------------------
}

public void serialEvent(Serial port)
{  
  serial_free=0;
  String inputString = port.readStringUntil((int) '\r');
  if (inputString != null) 
  {
    String [] inputStringArr = split(inputString, ",");

    if (receiving_mode==1)
    {
      int i=inputStringArr.length;
      if (i==10)
      {
        gyro_x_raw = float(inputStringArr[0]);
        gyro_y_raw = float(inputStringArr[1]);
        gyro_z_raw = float(inputStringArr[2]);

        acc_x_raw = float(inputStringArr[3]);
        acc_y_raw = float(inputStringArr[4]);
        acc_z_raw = float(inputStringArr[5]);

        mag_x_raw = float(inputStringArr[6]);
        mag_y_raw = float(inputStringArr[7]);
        mag_z_raw = float(inputStringArr[8]);
        yaw_angle = float(inputStringArr[9])/100.0f+180.0;
        yaw_angle_temp=yaw_angle-yaw_home_angle;      
         if(yaw_angle_temp<0)yaw_angle_temp+=360;
         else if(yaw_angle_temp>360)yaw_angle_temp-=360;
        gyro_x_raw_array[gyro_pt]=gyro_x_raw;
        gyro_y_raw_array[gyro_pt]=gyro_y_raw;
        gyro_z_raw_array[gyro_pt]=gyro_z_raw;
        gyro_pt++;
        gyro_pt%=65535;

        acc_x_raw_array[acc_pt]=acc_x_raw;
        acc_y_raw_array[acc_pt]=acc_y_raw;
        acc_z_raw_array[acc_pt]=acc_z_raw;
        acc_pt++;
        acc_pt%=65535;

        if (start_mag==1)// && (int)mag_x_raw!=0 && (int)mag_y_raw!=0 && (int)mag_z_raw!=0)
        {
          mag_x_raw_array[mag_pt]=mag_x_raw;
          mag_y_raw_array[mag_pt]=mag_y_raw;
          mag_z_raw_array[mag_pt]=mag_z_raw;
          mag_pt++;
          mag_pt%=65535;
          if (abs((float)abs(acc_z_raw)/acc_1G_LSB-1)<0.05)
          {
            mag_xy_z1g_array[0][mag_xy_z1g_pt]=mag_x_raw;
            mag_xy_z1g_array[1][mag_xy_z1g_pt]=mag_y_raw;
            mag_xy_z1g_pt++;
            mag_xy_z1g_pt%=65535;
          }
          if (abs(acc_y_raw)>8150 && abs(acc_z_raw)<8000)
          {
            mag_xz_y1g_array[0][mag_xz_y1g_pt]=mag_x_raw;
            mag_xz_y1g_array[1][mag_xz_y1g_pt]=mag_z_raw;
            mag_xz_y1g_pt++;
            mag_xz_y1g_pt%=65535;
          }
        }
      }
    } else if (receiving_mode==2)
    {
      int i=inputStringArr.length;
      if (i==10)
      {
        rpy[0] = -float(inputStringArr[0])/100.0f;
        rpy[1] = float(inputStringArr[1])/100.0f;
        rpy[2] = float(inputStringArr[2])/100.0f;
        rpy[2]-=yaw_home_angle;
        if (rpy[2]>180)rpy[2]-=360;
        else if (rpy[2]<-180)rpy[2]+=360;
        P = float(inputStringArr[3]);
        T = float(inputStringArr[4])/100;      
        Valid=(int)float(inputStringArr[5]);     

        lat_h=(long)float(inputStringArr[6]);
        lat_l=(long)float(inputStringArr[7]);

        long_h=(long)float(inputStringArr[8]);
        long_l=(long)float(inputStringArr[9]);
      }
    } else if (receiving_mode==3)
    {
      int i=inputStringArr.length;
      if (i==15)
      {
        PID[0] = float(inputStringArr[0]);
        PID[1] = float(inputStringArr[1]);
        PID[2] = float(inputStringArr[2]);

        rpy[0] = float(inputStringArr[3])/100.0f;
        rpy[1] = float(inputStringArr[4])/100.0f;
        rpy[2] = float(inputStringArr[5])/100.0f;

        KP[0]=float(inputStringArr[6])/1000.0f;
        KD[0]=float(inputStringArr[7])/1000.0f;
        KI[0]=float(inputStringArr[8])/1000.0f;

        KP[1]=float(inputStringArr[9])/1000.0f;
        KD[1]=float(inputStringArr[10])/1000.0f;
        KI[1]=float(inputStringArr[11])/1000.0f;

        KP[2]=float(inputStringArr[12])/1000.0f;
        KD[2]=float(inputStringArr[13])/1000.0f;
        KI[2]=float(inputStringArr[14])/1000.0f;

        PID_array[0][PID_pt]=(int) PID[0];
        PID_array[1][PID_pt]=(int) PID[1];
        PID_array[2][PID_pt]=(int) PID[2];
        PID_pt++;
        PID_pt%=65535;

        rpy_array[0][rpy_pt]=(int) rpy[0];
        rpy_array[1][rpy_pt]=(int) rpy[1];
        rpy_array[2][rpy_pt]=(int) rpy[2];
        rpy_pt++;
        rpy_pt%=65535;
      }
    }  

    serial_free=1;
  }
} 

