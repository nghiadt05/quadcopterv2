//--------- variables -------------
public float PID[]=new float[5];
public float KP[]=new float[5];
public float KD[]=new float[5];
public float KI[]=new float[5];
public float temp_KP[]=new float[5];
public float temp_KD[]=new float[5];
public float temp_KI[]=new float[5];
public int PID_array[][]=new int[3][65535];
public int PID_pt=801;
public int rpy_array[][]=new int[3][65535];
public int rpy_pt=801;
public int PID_screen=0;
public int PID_read;
public int PID_write;
public int box_number;
public int last_mouse_X, current_mouse_X;
public float delta_gain;
//---------------------------------



public void Draw_PID_Screen()
{
  clear();
  image(myImages[25], 0, 0);
  Draw_pid_button();
  Draw_angle_graphic();
  Draw_chosing_box();
  Read_gain_value();
  Get_gain_value();  
  Draw_gain_values();
  Write_gain_value();
}

void Draw_pid_button()
{
  image(myImages[27], 35, 378);
  image(myImages[26], 35, 478);
  image(myImages[28], 550, 378);
  image(myImages[29], 550, 478);
}

void Draw_angle_graphic()
{
  translate(0, 320);
  //------- draw background ----------------
  for (int i=0; i<11; i++)
  {
    if (i==5)
    {
      strokeWeight(1);
      stroke(255, 0, 255);
    } else
    {
      strokeWeight(1);
      stroke(#78737E);
    }
    line(0, -i*20, 800, -i*20);
  }
  //----------------------------------------
  //------- draw Ot vs Ox line -------------
  strokeWeight(5);
  stroke(0, 0, 255);
  line(0, 0, 0, -200);
  line(0, 0, 800, 0);
  //----------------------------------------

  //------- draw 580 latest values of the acclerometer --------
  if (PID_pt>800)
  {
    strokeWeight(4);
    for (int i=0; i<800; i++)
    {
      stroke(#00ff00);
      line(i, -(PID_array[PID_screen][PID_pt-800+i])/50-100, i+1, -(PID_array[PID_screen][PID_pt-800+i])/50-100);
      stroke(#ff0000);
      line(i, -(rpy_array[PID_screen][rpy_pt-800+i])-100, i+1, -(rpy_array[PID_screen][rpy_pt-800+i])-100);
    }
  }
  //--------------------------------------------------------
  //------ print value ----------------------
  textSize(24);
  fill(#00ff00);
  text("PID["+PID_screen+"]= "+PID[PID_screen], 50, -160);
  text("rpy["+PID_screen+"]= "+rpy[PID_screen], 50, -20);
  //-----------------------------------------
  translate(-0, -320);
}

void Draw_gain_values()
{    
  switch(box_number)
  {
  case 0:
    temp_KP[PID_screen]+=delta_gain;
    break;
  case 1:
    temp_KD[PID_screen]+=delta_gain;
    break;
  case 2:
    temp_KI[PID_screen]+=delta_gain;
    break;
  }
  temp_KP[PID_screen]=(float)((long)(temp_KP[PID_screen]*10000))/10000.0f;
  temp_KD[PID_screen]=(float)((long)(temp_KD[PID_screen]*10000))/10000.0f;
  temp_KI[PID_screen]=(float)((long)(temp_KI[PID_screen]*10000))/10000.0f;
  if (temp_KP[PID_screen]<0)temp_KP[PID_screen]=0;
  if (temp_KD[PID_screen]<0)temp_KD[PID_screen]=0;
  if (temp_KI[PID_screen]<0)temp_KI[PID_screen]=0;
  textSize(28);
  fill(#00ff00);
  text("KP["+PID_screen+"]= "+temp_KP[PID_screen], 300, 400);  
  text("KD["+PID_screen+"]= "+temp_KD[PID_screen], 300, 450);  
  text("KI["+PID_screen+"]= "+temp_KI[PID_screen], 300, 500);
}

void Get_gain_value()
{
  if (mousePressed && mouseButton==RIGHT)
  {
    last_mouse_X=current_mouse_X;
    current_mouse_X=mouseX;
    delta_gain=(mouseX-last_mouse_X)/1000.0f;
  } else if (_1st_time_press==1)
  {
    delta_gain=(mouseX-last_mouse_X)/10000.0f;
  }
}

void Draw_chosing_box()
{
  stroke(3);
  stroke(#0000ff);
  for (int i=0; i<3; i++)
  {
    if (mouseX>255 && mouseX<280 && mouseY>(380+i*50) && mouseY<(405+i*50))
    {
      fill(#00ff00);
    } else
    {
      noFill();
    }

    if (box_number==i)
    {
      fill(#00ff00);
    }
    rect(255, 380+i*50, 25, 25);
  }
}

void Read_gain_value()
{
  if (PID_read==1)
  {
    switch(PID_screen)
    {
    case 0:
      temp_KP[0]=KP[0];
      temp_KD[0]=KD[0];
      temp_KI[0]=KI[0];
      break;
    case 1:
      temp_KP[1]=KP[1];
      temp_KD[1]=KD[1];
      temp_KI[1]=KI[1];
      break;
    case 2:
      temp_KP[2]=KP[2];
      temp_KD[2]=KD[2];
      temp_KI[2]=KI[2];
      break;
    }
    PID_read=0;
  }
}

void Write_gain_value()
{
  if (PID_write==1)
  {
    String PID_send_string;
    String PID_temp_string[]=new String[3];

    PID_temp_string[0]=String.valueOf(temp_KP[PID_screen]);
    PID_temp_string[1]=String.valueOf(temp_KD[PID_screen]);
    PID_temp_string[2]=String.valueOf(temp_KI[PID_screen]);

    PID_send_string="&"+char(PID_screen+52)+','+PID_temp_string[0]+','+PID_temp_string[1]+','+PID_temp_string[2]+'@';
    while (serial_free==0) {
    }
    myPort.write(PID_send_string);
    println(PID_send_string);
    PID_write=0;
  }
}

