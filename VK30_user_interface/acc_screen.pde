//------- variables ------------
public float acc_x_raw_array[]=new float[65535];
public float acc_y_raw_array[]=new float[65535];
public float acc_z_raw_array[]=new float[65535];
public int acc_pt=580;
public int acc_calculate=0;
public int acc_step=1;
public int step_done[]=new int[7];
public int acc_calib_stt[]=new int[7];
public int step_done_flag[]=new int[7];
public int acc_offset[]=new int[3];
public int acc_gain[]=new int[3];
public float acc_gain_temp[]=new float[6];
public float acc_offset_temp[]=new float[12];
public final int acc_1G_LSB=8200;
//------------------------------

public void Draw_acc_screen()
{
  Draw_acc_banner();  
  Draw_acc_buttons();
  Acc_sample_values();
  Acc_calculate_values();
  Draw_acc_graphic();
  Draw_acc_color();
}

public void Draw_acc_banner()
{
  clear();
  image(myImages[6], 0, 0);
  textSize(24);
  fill(#00ff00);
  text("Please place the board at the same position as the", 5, 150);
  text("picture beside then press the Calibrate button.", 5, 180);
  text("Please press Reset button to reset all values !", 5, 210);
  text("Step: "+acc_step+"/6", 15, 288);
}

public void Draw_acc_buttons()
{
  image(myImages[14], 10, 220);
  image(myImages[3], 150, 220);
  image(myImages[13], 290, 220); 
  image(myImages[15], 430, 220);
}

public void Acc_sample_values()
{
  switch(acc_step)
  {
  case 1://calib acc x negative
    image(myImages[7], 570, 130);
    if ( acc_calib_stt[1]==1)//pressed calibrate button at step 1
    {
      if (acc_pt>2000)
      {
        for (int i=0; i<2000; i++)
        {
          acc_gain_temp[0]+=(acc_x_raw_array[i]);//store acc x raw value (LSB) equivalant to 1g
          acc_offset_temp[0]+=acc_y_raw_array[i];//store acc y offset values
          acc_offset_temp[1]+=acc_z_raw_array[i];//store acc z offset values
        }           
        println("acc_x_gain_temp_negative="+(acc_gain_temp[0]/2000));
        println("acc_y_offset_temp_0="+(acc_offset_temp[0]/2000));
        println("acc_z_offset_temp_0="+(acc_offset_temp[1]/2000));           
        acc_calib_stt[1]=0;
        step_done[1]=1;//to notice that: step 1 is done
        step_done_flag[1]=1;
        acc_step++;
        println("Move to step: "+acc_step+"/6");
      } else
      {
        textSize(24);
        fill(#00ff00);
        text("Please wait for a moment ...", 15, 315);
      }
    }

    if (step_done[1]==1)//this step is done 
    {
      textSize(24);
      fill(#00ff00);
      text("This step is done", 40, 315);
    }
    break;
  case 2://calib acc x positive
    image(myImages[8], 570, 130);
    if ( acc_calib_stt[2]==1)//pressed calibrate button at step 2
    {
      if (acc_pt>2000)
      {
        for (int i=0; i<2000; i++)
        {
          acc_gain_temp[1]+=(acc_x_raw_array[i]);//store acc x raw value (LSB) equivalant to 1g
          acc_offset_temp[2]+=acc_y_raw_array[i];//store acc y offset values
          acc_offset_temp[3]+=acc_z_raw_array[i];//store acc z offset values
        }           
        println("acc_x_gain_temp_positive="+(acc_gain_temp[1]/2000));
        println("acc_y_offset_temp_1="+(acc_offset_temp[2]/2000));
        println("acc_z_offset_temp_1="+(acc_offset_temp[3]/2000));
        acc_calib_stt[2]=0;
        step_done[2]=1;//to notice that: step 1 is done
        step_done_flag[2]=1;
        acc_step++;
        println("Move to step: "+acc_step+"/6");
      } else
      {
        textSize(24);
        fill(#00ff00);
        text("Please wait for a moment ...", 15, 315);
      }
    }

    if (step_done[2]==1)//this step is done 
    {
      textSize(24);
      fill(#00ff00);
      text("This step is done", 40, 315);
    }
    break;
  case 3://calib acc y negative
    image(myImages[9], 570, 130);
    if ( acc_calib_stt[3]==1)//pressed calibrate button at step 3
    {
      if (acc_pt>2000)
      {
        for (int i=0; i<2000; i++)
        {   
          acc_gain_temp[2]+=(acc_y_raw_array[i]);//acc_y temp negative
          acc_offset_temp[4]+=acc_x_raw_array[i];// acc x offset 0
          acc_offset_temp[5]+=acc_z_raw_array[i];//acc z offset 2
        }           
        println("acc_y_gain_temp_negative="+(acc_gain_temp[2]/2000));
        println("acc_x_offset_temp_0="+(acc_offset_temp[4]/2000));
        println("acc_z_offset_temp_2="+(acc_offset_temp[5]/2000));
        acc_calib_stt[3]=0;
        step_done[3]=1;//to notice that: step 1 is done
        step_done_flag[3]=1;
        acc_step++;
        println("Move to step: "+acc_step+"/6");
      } else
      {
        textSize(24);
        fill(#00ff00);
        text("Please wait for a moment ...", 15, 315);
      }
    }

    if (step_done[3]==1)//this step is done 
    {
      textSize(24);
      fill(#00ff00);
      text("This step is done", 40, 315);
    }
    break;
  case 4://calib acc y positive
    image(myImages[10], 570, 130);
    if ( acc_calib_stt[4]==1)//pressed calibrate button at step 4
    {
      if (acc_pt>2000)
      {
        for (int i=0; i<2000; i++)
        {   
          acc_gain_temp[3]+=acc_y_raw_array[i];//acc_y temp positive
          acc_offset_temp[6]+=acc_x_raw_array[i];// acc x offset 1
          acc_offset_temp[7]+=acc_z_raw_array[i];//acc z offset 3
        }           
        println("acc_y_gain_temp_positive="+(acc_gain_temp[3]/2000));
        println("acc_x_offset_temp_1="+(acc_offset_temp[6]/2000));
        println("acc_z_offset_temp_3="+(acc_offset_temp[7]/2000));
        acc_calib_stt[4]=0;
        step_done[4]=1;//to notice that: step 1 is done
        step_done_flag[4]=1;
        acc_step++;
        println("Move to step: "+acc_step+"/6");
      } else
      {
        textSize(24);
        fill(#00ff00);
        text("Please wait for a moment ...", 15, 315);
      }
    }

    if (step_done[4]==1)//this step is done 
    {
      textSize(24);
      fill(#00ff00);
      text("This step is done", 40, 315);
    }
    break;
  case 5://calib acc z negative
    image(myImages[11], 570, 130);
    if ( acc_calib_stt[5]==1)//pressed calibrate button at step 5
    {
      if (acc_pt>2000)
      {
        for (int i=0; i<2000; i++)
        {   
          acc_gain_temp[4]+=acc_z_raw_array[i];//acc_z temp negative
          acc_offset_temp[8]+=acc_x_raw_array[i];// acc x offset 2
          acc_offset_temp[9]+=acc_y_raw_array[i];// acc y offset 2
        }           
        println("acc_z_gain_temp_negative="+(acc_gain_temp[4]/2000));
        println("acc_x_offset_temp_2="+(acc_offset_temp[8]/2000));
        println("acc_y_offset_temp_2="+(acc_offset_temp[9]/2000));
        acc_calib_stt[5]=0;
        step_done[5]=1;//to notice that: step 1 is done
        step_done_flag[5]=1;
        acc_step++;
        println("Move to step: "+acc_step+"/6");
      } else
      {
        textSize(24);
        fill(#00ff00);
        text("Please wait for a moment ...", 15, 315);
      }
    }

    if (step_done[5]==1)//this step is done 
    {
      textSize(24);
      fill(#00ff00);
      text("This step is done", 40, 315);
    }
    break;
  case 6://calib acc z positive
    image(myImages[12], 570, 130);
    if ( acc_calib_stt[6]==1)//pressed calibrate button at step 5
    {
      if (acc_pt>2000)
      {
        for (int i=0; i<2000; i++)
        {   
          acc_gain_temp[5]+=acc_z_raw_array[i];//acc_z temp positive
          acc_offset_temp[10]+=acc_x_raw_array[i];// acc x offset 3
          acc_offset_temp[11]+=acc_y_raw_array[i];// acc y offset 3
        }           
        println("acc_z_gain_temp_positive="+(acc_gain_temp[5]/2000));
        println("acc_x_offset_temp_3="+(acc_offset_temp[10]/2000));
        println("acc_y_offset_temp_3="+(acc_offset_temp[11]/2000));
        acc_calib_stt[6]=0;
        step_done_flag[6]=1;
        step_done[6]=1;//to notice that: step 1 is done
      } else
      {
        textSize(24);
        fill(#00ff00);
        text("Please wait for a moment ...", 15, 315);
      }
    }

    if (step_done[6]==1)//this step is done 
    {
      textSize(24);
      fill(#00ff00);
      text("This step is done", 40, 315);
    }
    break;
  }
}

public void Acc_calculate_values()
{
  int done_status=1;
  /*
  for(int i=1;i<7;i++)
   {
   step_done_flag[i]=1;
   }
   */
  for (int i=1; i<7; i++)
  {
    done_status=done_status*step_done_flag[i];
  }

  if (done_status==1)//all steps are gone through
  {
    image(myImages[16], 290, 268);//calculate button
    image(myImages[4], 430, 268);//send 2 mycrocontroller button
  }

  if (acc_calculate==1)
  {
    textSize(20);
    fill(#00ff00);
    text("Acc_x_gain= "+acc_gain[0], 5, 350);
    text("Acc_y_gain= "+acc_gain[1], 5, 380);
    text("Acc_z_gain= "+acc_gain[2], 5, 410);
    text("Acc_x_offset= "+acc_offset[0], 5, 435);
    text("Acc_y_offset= "+acc_offset[1], 5, 460);
    text("Acc_z_offset= "+acc_offset[2], 5, 485);
  }
}

public void Draw_acc_graphic()
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

  //------- draw 580 latest values of the acclerometer --------
  if (acc_pt>580)
  {
    strokeWeight(3);
    for (int i=0; i<579; i++)
    {
      stroke(#03FFE8);
      line(i, -(acc_x_raw_array[acc_pt-580+i]/200)-120, i+1, -(acc_x_raw_array[acc_pt-579+i]/200)-120);
      stroke(#03FF11);
      line(i, -(acc_y_raw_array[acc_pt-580+i]/200)-120, i+1, -(acc_y_raw_array[acc_pt-579+i]/200)-120);
      stroke(#FFF703);
      line(i, -(acc_z_raw_array[acc_pt-580+i]/200)-120, i+1, -(acc_z_raw_array[acc_pt-579+i]/200)-120);
    }
  }
  //--------------------------------------------------------
  translate(-220, -590);
}

public void Draw_acc_color()
{  
  String str_temp[]=new String[3];
  color color_temp[]=new color[3];  
  color_temp[0]=#03FFE8;
  color_temp[1]=#03FF11;
  color_temp[2]=#FFF703;
  str_temp[0]="Acc X";
  str_temp[1]="Acc Y";
  str_temp[2]="Acc Z";
  for (int i=0; i<3; i++)
  {
    textSize(20);
    fill(color_temp[i]);
    text(str_temp[i], 8, 520+i*25);
    noStroke();
    rect(85, i*30+500, 30, 20);
  }
}

public void Send_acc_calibrated_data()//okie
{
  /*
  acc_offset[0]=4;
   acc_offset[1]=5;
   acc_offset[2]=6;
   acc_gain[0]=7;
   acc_gain[1]=8;
   acc_gain[2]=9;
   */
  String acc_send_string;
  String acc_temp_string[]=new String[6];
  acc_temp_string[0]=String.valueOf(acc_offset[0]);
  acc_temp_string[1]=String.valueOf(acc_offset[1]);
  acc_temp_string[2]=String.valueOf(acc_offset[2]);
  acc_temp_string[3]=String.valueOf(acc_gain[0]);
  acc_temp_string[4]=String.valueOf(acc_gain[1]);
  acc_temp_string[5]=String.valueOf(acc_gain[2]);
  acc_send_string="&2,"+acc_temp_string[0]+','+acc_temp_string[1]+','+acc_temp_string[2]+','+acc_temp_string[3]+','+acc_temp_string[4]+','+acc_temp_string[5]+'@';
  println(acc_send_string);
  while (serial_free==0) {
  }
  myPort.write(acc_send_string);
  println("Calibrated acc-data is sent");
}

