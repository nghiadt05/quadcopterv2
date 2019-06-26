
void mousePressed()
{
  if (mouseButton==LEFT)
  {    
    if (mouseX>730 && mouseX<780 && mouseY>40 && mouseY<70)//next button
    {
      screen++;
      if (screen>PID_GAINING_SCREEN)screen=PID_GAINING_SCREEN;
    } else  if (mouseX>18 && mouseX<48 && mouseY>40 && mouseY<70)//back button
    {
      screen--;
      if (screen<WELCOME_SCREEN)screen=WELCOME_SCREEN;
    } else if (mouseX>675 && mouseX<800 && mouseY>0 && mouseY<25)//main menu button
    {
      last_screen=screen;
      screen=WELCOME_SCREEN;
    }
    //----- funtions that are appropriate to the specific screen number -------------
    switch(screen)
    {
    case WELCOME_SCREEN:
      if (mouseX>10 && mouseX<130 && mouseY>85 && mouseY<120)//calibration mode
      {
        println("Choose calib mode");
        receiving_mode=1;       
        Com_start();
        screen=CALIBRATE_GYRO_SCREEN;
      } else if (mouseX>10 && mouseX<130 && mouseY>132 && mouseY<166)//flying mode
      {
        println("Choose flying mode");
        receiving_mode=2;
        Com_start();
        screen=IMU_DISPLAY_SCREEN;
      } else if (mouseX>10 && mouseX<130 && mouseY>177 && mouseY<208)//pid tunning
      {
        println("Choose PID_tunning mode");
        receiving_mode=3;
        Com_start();
        screen=PID_GAINING_SCREEN;
      } else if (mouseX>0 && mouseX<125 && mouseY>495 && mouseY<520)//return screen
      {
        screen=last_screen;
      } else if (mouseX>134 && mouseX<256 && mouseY>495 && mouseY<520)//stop button
      {
        COM_Stop();
        println("Stop sending data");
      } else 
      {
        for (int i=0; i<no_com_ports; i++)
        {
          if (mouseX>35 && mouseX<95 && mouseY>(i*40+225) && mouseY<(i*40+255))
          {
            com_chosen=i;
            println("Chose com port: "+serial_list[com_chosen]);
            //Com_check_available();
          }
        }
      }
      break;
    case CALIBRATE_GYRO_SCREEN:
      if (mouseX>130 && mouseX<250 && mouseY>180 && mouseY<215)
      {
        println("gyroscope is being calibrated, please wait for a moment ...");
        calib_gyro=1;           
        gyro_pt=0;//reset pointer to get new data
      } else if (mouseX>310 && mouseX<430 && mouseY>180 && mouseY<215)
      {
        Gyro_send_to_uc();             
        textSize(24);
        fill(#00ff00);
        text("Calibrated data is sent", 313, 245);
      }
      break;    
    case CALIBRATE_ACC_SCREEN:

      if (mouseX>10 && mouseX<110 && mouseY>220 && mouseY<255)//back button
      {
        acc_step--;
        if (acc_step<1)acc_step=1;
        println("Move to step: "+acc_step+"/6");
      }

      if (mouseX>150 && mouseX<250 && mouseY>220 && mouseY<255)
      {
        println("Accelerometer clibration step: "+acc_step+"/6");
        switch(acc_step)
        {
        case 1://calib acc x negative
          /*
                  Store acc_z vs acc_y off set
           Store LSB value for acc_x (equvalant as -1g)
           */
          acc_gain_temp[0]=0;//acc x temp gain negative
          acc_offset_temp[0]=0;//acc y offet 0
          acc_offset_temp[1]=0;//acc z offset 0
          acc_pt=0;//reset data pointer to get new data
          step_done[1]=0;
          acc_calib_stt[1]=1;
          println("Please wait for a moment ...");
          break;
        case 2://calib acc x positive
          /*
                  Store acc_z vs acc_y off set
           Store LSB value for acc_x (equvalant as +1g)
           */
          acc_gain_temp[1]=0;//acc_x temp positive
          acc_offset_temp[2]=0;// acc y offset 1
          acc_offset_temp[3]=0;//acc z offset 1
          acc_pt=0;//reset data pointer to get new data
          step_done[2]=0;
          acc_calib_stt[2]=1;
          println("Please wait for a moment ...");
          break;
        case 3://calib acc y negative
          /*
                  Store acc_x vs acc_z off set
           Store LSB value for acc_y (equvalant as -1g)
           */
          acc_gain_temp[2]=0;//acc_y temp negative
          acc_offset_temp[4]=0;// acc x offset 0
          acc_offset_temp[5]=0;//acc z offset 2
          acc_pt=0;//reset data pointer to get new data
          step_done[3]=0;
          acc_calib_stt[3]=1;
          println("Please wait for a moment ...");
          break;
        case 4://calib acc y positive
          /*
                  Store acc_x vs acc_z off set
           Store LSB value for acc_y (equvalant as 1g)
           */
          acc_gain_temp[3]=0;//acc_y temp positive
          acc_offset_temp[6]=0;// acc x offset 1
          acc_offset_temp[7]=0;//acc z offset 3
          acc_pt=0;//reset data pointer to get new data
          step_done[4]=0;
          acc_calib_stt[4]=1;
          println("Please wait for a moment ...");
          break;
        case 5://calib acc z negative
          /*
                  Store acc_x vs acc_y off set
           Store LSB value for acc_z (equvalant as -1g)
           */
          acc_gain_temp[4]=0;//acc_z temp negative
          acc_offset_temp[8]=0;// acc x offset 2
          acc_offset_temp[9]=0;// acc y offset 2
          acc_pt=0;//reset data pointer to get new data
          step_done[5]=0;
          acc_calib_stt[5]=1;
          println("Please wait for a moment ...");
          break;
        case 6://calib acc z positive
          /*
                  Store acc_x vs acc_y off set
           Store LSB value for acc_z (equvalant as 1g)
           */
          acc_gain_temp[5]=0;//acc_z temp positive
          acc_offset_temp[10]=0;// acc x offset 3
          acc_offset_temp[11]=0;// acc y offset 3
          acc_pt=0;//reset data pointer to get new data
          step_done[6]=0;
          acc_calib_stt[6]=1;
          println("Please wait for a moment ...");
        }
      }       

      if (mouseX>290 && mouseX<390 && mouseY>220 && mouseY<255)//next button
      {
        acc_step++;
        if (acc_step>6)acc_step=6;
        println("Move to step: "+acc_step+"/6");
      }   

      if (mouseX>430 && mouseX<530 && mouseY>220 && mouseY<255)//reset button
      {
        acc_step=1;
        acc_calculate=0;
        for (int i=1; i<7; i++)//reset all the calibrate status values
        {
          acc_calib_stt[i]=0;
          step_done[i]=0;
          step_done_flag[i]=0;
        }
        textSize(24);
        fill(#00ff00);
        text("All data is reset", 142, 330);
        println("all data is reset");
      }   

      if (mouseX>290 && mouseX<390 && mouseY>268 && mouseY<303)//calculate button
      {
        acc_gain[0]=(int)((abs(acc_gain_temp[0])+abs(acc_gain_temp[1]))/4000);//acc x gain;
        acc_gain[1]=(int)((abs(acc_gain_temp[2])+abs(acc_gain_temp[3]))/4000);//acc y gain
        acc_gain[2]=(int)((abs(acc_gain_temp[4])+abs(acc_gain_temp[5]))/4000);//acc x gain

        acc_offset[0]=(int)((acc_offset_temp[4]+acc_offset_temp[6]+acc_offset_temp[8]+acc_offset_temp[10])/8000);//acc x offset
        acc_offset[1]=(int)((acc_offset_temp[0]+acc_offset_temp[2]+acc_offset_temp[9]+acc_offset_temp[11])/8000);//acc y offset
        acc_offset[2]=(int)((acc_offset_temp[1]+acc_offset_temp[3]+acc_offset_temp[5]+acc_offset_temp[7])/8000);//acc z offset

        acc_calculate=1;
        for (int i=0; i<3; i++)
        {
          println("acc_gain_temp["+i+"]= "+acc_gain[i]);
        }
        for (int i=0; i<3; i++)
        {
          println("acc_offset_temp["+i+"]="+acc_offset[i]);
        }
      }   

      if (mouseX>430 && mouseX<530 && mouseY>268 && mouseY<303)//send2uc button button
      {
        Send_acc_calibrated_data();
      }           
      break;
    case CALIBRATE_MAG_SCREEN:
      if (test==0)
      {
        if (mouseX>8 && mouseX<108 && mouseY>125 && mouseY<160)
        {
          data_enough=0;
          start_mag=1;
          mag_calibrated=0;
          println("Start drawing mag points");
        } else if (mouseX>8 && mouseX<108 && mouseY>160 && mouseY<195)
        {
          start_mag=0;
          println("Stop drawing mag points");
        } else if (mouseX>675 && mouseX<782 && mouseY>334 && mouseY<361)
        {
          data_enough=0;
          start_mag=0;
          mag_pt=0;
          mag_pt_temp=0;
          mag_calibrated=0;
          mag_scale[0]=1;
          mag_scale[1]=1;
          mag_scale[2]=1;
          for (int i=0; i<65535; i++)
          {
            mag_x_raw_array_temp[i]=0;
            mag_y_raw_array_temp[i]=0;
            mag_z_raw_array_temp[i]=0;
            mag_x_raw_array[i]=0;
            mag_y_raw_array[i]=0;
            mag_z_raw_array[i]=0;

            mag_xy_z1g_array[0][i]=0;
            mag_xy_z1g_array[1][i]=0;

            mag_xz_y1g_array[0][i]=0;
            mag_xz_y1g_array[1][i]=0;
          }
          println("Reset magnetic values");
        } else if (mouseX>676 && mouseX<782 && mouseY>365 && mouseY<395)//move to test screen
        {
          test=1;
          println("move to test screen");
        } else if (mouseX>676 && mouseX<782 && mouseY>264 && mouseY<292)//read from file
        {
          //---reset current magnetic data
          data_enough=0;
          start_mag=0;
          mag_xy_z1g_pt=0;
          mag_xz_y1g_pt=0;
          mag_pt=0;
          mag_pt_temp=0;
          mag_calibrated=0;       
          for (int i=0; i<65535; i++)
          {
            mag_x_raw_array_temp[i]=0;
            mag_y_raw_array_temp[i]=0;
            mag_z_raw_array_temp[i]=0;
            mag_x_raw_array[i]=0;
            mag_y_raw_array[i]=0;
            mag_z_raw_array[i]=0;

            mag_xy_z1g_array[0][i]=0;
            mag_xy_z1g_array[1][i]=0;

            mag_xz_y1g_array[0][i]=0;
            mag_xz_y1g_array[1][i]=0;
          }
          println("Reset magnetic values");
          //-------------------------------

          // Load text file as a string
          float[] mag_data;
          String[] mag_temp_string = loadStrings("mag_data.txt");
          // Convert string into an array of integers using ',' as a delimiter
          mag_data = float(split(mag_temp_string[0], ','));
          mag_pt=mag_data.length/3;
          for (int i=0; i<mag_data.length; i++)
          {
            int j=i%3;
            switch (j)
            {
            case 0:
              mag_x_raw_array[i/3]=mag_data[i];
              break;
            case 1:
              mag_y_raw_array[i/3]=mag_data[i];
              break;
            case 2:
              mag_z_raw_array[i/3]=mag_data[i];
              break;
            }
          }
          println("mag_pt="+mag_pt);
          println("Read mag data from text file");
        } else if (mouseX>676 && mouseX<782 && mouseY>300 && mouseY<328)//save to file
        {
          int temp_start_mag=start_mag;
          start_mag=0;//stop getting new mag data
          output = createWriter("mag_data.txt");//creat new file for each saving time
          for (int i=0; i<mag_pt; i++)
          {
            output.print(mag_x_raw_array[i]+","+mag_y_raw_array[i]+","+mag_z_raw_array[i]+",");      
            //output.print(i*3+","+(i*3+1)+","+(i*3+2)+",");
          }
          output.flush();  // Writes the remaining data to the file
          output.close();  // Finishes the file
          start_mag=temp_start_mag;
          println("Save mag data to text file");
        } else if (mouseX>775 && mouseX<790 && mouseY>155 && mouseY<170)//op_offset
        {
          op_offset++;
          op_offset%=2;
        } else if (mouseX>775 && mouseX<790 && mouseY>185 && mouseY<200)//op_rotation
        {
          op_rotation++;
          op_rotation%=2;
        } else if (mouseX>775 && mouseX<790 && mouseY>215 && mouseY<230)//op_rotation_back
        {
          op_rotation_back++;
          op_rotation_back%=2;
        } else if (mouseX>775 && mouseX<790 && mouseY>245 && mouseY<260)//op_rotation_back
        {
          op_scale++;
          op_scale%=2;
        } else if (mouseX>8 && mouseX<108 && mouseY>230 && mouseY<265)//calibrate button I is pressed
        {
          start_mag=0;//stop getting new values            
          mag_pt_temp=mag_pt;
          for (int i=0; i<mag_pt_temp; i++)
          {
            //store exist data to a temp array
            mag_x_raw_array_temp[i]=mag_x_raw_array[i];
            mag_y_raw_array_temp[i]=mag_y_raw_array[i];
            mag_z_raw_array_temp[i]=mag_z_raw_array[i];
          }

          if (op_offset==1)
          {
            float mag_x_max, mag_y_max, mag_z_max;
            float mag_x_min, mag_y_min, mag_z_min;
            //------------ find the offset points --------------------------------------
            mag_x_min=mag_x_raw_array_temp[0];
            mag_x_max=mag_x_min;
            mag_y_min=mag_y_raw_array_temp[0];
            mag_y_max=mag_y_min;
            mag_z_min=mag_z_raw_array_temp[0];
            mag_z_max=mag_z_min;            
            for (int i=1; i<mag_pt_temp; i++)
            {
              if (mag_x_min>mag_x_raw_array_temp[i]) mag_x_min=mag_x_raw_array_temp[i];
              if (mag_y_min>mag_y_raw_array_temp[i]) mag_y_min=mag_y_raw_array_temp[i];
              if (mag_z_min>mag_z_raw_array_temp[i]) mag_z_min=mag_z_raw_array_temp[i];
              if (mag_x_max<mag_x_raw_array_temp[i]) mag_x_max=mag_x_raw_array_temp[i];
              if (mag_y_max<mag_y_raw_array_temp[i]) mag_y_max=mag_y_raw_array_temp[i];
              if (mag_z_max<mag_z_raw_array_temp[i]) mag_z_max=mag_z_raw_array_temp[i];
            }

            mag_offset[0]=(mag_x_max+mag_x_min)/2;//mag_x_raw_offset
            mag_offset[1]=(mag_y_min+mag_y_max)/2;//mag_y_raw_offset
            mag_offset[2]=(mag_z_min+mag_z_max)/2;//mag_z_raw_offset
            println("mag_offset[0]="+mag_offset[0]);
            println("mag_offset[1]="+mag_offset[1]);
            println("mag_offset[2]="+mag_offset[2]);
            //--------------------- -----------------------------------------------------

            //------------- delete the offset values -----------------
            for (int i=0; i<mag_pt_temp; i++)
            {
              mag_x_raw_array_temp[i]-=mag_offset[0];
              mag_y_raw_array_temp[i]-=mag_offset[1];
              mag_z_raw_array_temp[i]-=mag_offset[2];
            }          
            //--------------------------------------------------------

            //------ find the strongest magnetic direction --------       
            max_x=0;
            max_y=0;
            max_z=0;  
            for (int i=0; i<mag_pt_temp; i++)
            {
              /*
                if(max_x<abs(mag_x_raw_array_temp[i]))max_x=abs(mag_x_raw_array_temp[i]);
               if(max_y<abs(mag_y_raw_array_temp[i]))max_y=abs(mag_y_raw_array_temp[i]);
               if(max_z<abs(mag_z_raw_array_temp[i]))max_z=abs(mag_z_raw_array_temp[i]);
               */
              max_x+=abs(mag_x_raw_array_temp[i])/1000.0f;
              max_y+=abs(mag_y_raw_array_temp[i])/1000.0f;
              max_z+=abs(mag_z_raw_array_temp[i])/1000.0f;
            }  
            println("Dir max argP: "+max_x+" "+max_y+" "+max_z);
            //-----------------------------------------------------
          }

          //------------- find the EA line segment------------------
          float EA=sqrt(mag_x_raw_array_temp[0]*mag_x_raw_array_temp[0]+mag_y_raw_array_temp[0]*mag_y_raw_array_temp[0]+mag_z_raw_array_temp[0]*mag_z_raw_array_temp[0]);
          for (int i=1; i<mag_pt_temp; i++)
          {
            float temp;
            temp= sqrt(mag_x_raw_array_temp[i]*mag_x_raw_array_temp[i]+mag_y_raw_array_temp[i]*mag_y_raw_array_temp[i]+mag_z_raw_array_temp[i]*mag_z_raw_array_temp[i]);

            if (EA<temp)
            {
              EA=temp;
              EA_pt=i;
            }
          }
          println("EA= "+EA+ "  EA_pt= "+EA_pt);
          println("EA_vector= "+mag_x_raw_array_temp[EA_pt]+" "+mag_y_raw_array_temp[EA_pt]+" "+mag_z_raw_array_temp[EA_pt]);           
          //--------------------------------------------------------

          //--------- find the EB line segment ---------------------
          //find the alpha plane which is perpendicular to the line EA
          //then find a point that is in the alpha, which have the smalest distance to the alpha plane
          //vector_EA=(a,b,c)=(mag_x_raw_array_temp[EA_pt],mag_y_raw_array_temp[EA_pt],mag_z_raw_array_temp[EA_pt]);
          float a=mag_x_raw_array_temp[EA_pt];
          float b=mag_y_raw_array_temp[EA_pt];
          float c=mag_z_raw_array_temp[EA_pt];
          //the alpha plane contains E(0,0,0) so its equation is: (alpha) ax+by+cz=0
          //we find all the points in the Elip that have the distances to the alpha plane less than d_M_to_alpha_min
          //then we content that those points are in the alpha plane.
          float d_M_to_alpha_min=0.005;
          int M_pointer[]=new int[200];
          int M_count=0;
          int step_1=0;
          for (int i=0; i<mag_pt_temp; i++)
          {
            float d_M_to_alpha_temp=abs(a*mag_x_raw_array_temp[i]+b*mag_y_raw_array_temp[i]+c*mag_z_raw_array_temp[i])/EA;
            if (d_M_to_alpha_temp<d_M_to_alpha_min)
            {
              M_pointer[M_count]=i;//store the pointer of all the points that fit those mentioned conditions
              M_count++; 
              println("d_M_to_alpha_temp= "+d_M_to_alpha_temp+" i= "+i+"  mag_raw_data[]= "+mag_x_raw_array_temp[i]+" "+mag_y_raw_array_temp[i]+" "+mag_z_raw_array_temp[i]);
              step_1=1;//check step done
            }
          }

          if (step_1==1)
          {
            //find the smalest EM, so we get EM_min=EB
            float EB=sqrt(mag_x_raw_array_temp[M_pointer[0]]*mag_x_raw_array_temp[M_pointer[0]]+mag_y_raw_array_temp[M_pointer[0]]*mag_y_raw_array_temp[M_pointer[0]]+mag_z_raw_array_temp[M_pointer[0]]*mag_z_raw_array_temp[M_pointer[0]]);
            for (int i=0; i<M_count; i++)
            {
              float EB_temp=sqrt(mag_x_raw_array_temp[M_pointer[i]]*mag_x_raw_array_temp[M_pointer[i]]+mag_y_raw_array_temp[M_pointer[i]]*mag_y_raw_array_temp[M_pointer[i]]+mag_z_raw_array_temp[M_pointer[i]]*mag_z_raw_array_temp[M_pointer[i]]);
              if (EB_temp<EB || EB_temp==EB)
              {
                EB=EB_temp;
                EB_pt=M_pointer[i];
              }
            }            
            println("EB= "+EB+"  EB_pt= "+EB_pt);   
            //--------- find the EC line segment ---------------------
            //draw the line EC line (not the segment)
            //vecto_EC=[vector_EA,vector_EB]
            //vector_EA=(mag_x_raw_array_temp[EA_pt],mag_y_raw_array_temp[EA_pt],mag_z_raw_array_temp[EA_pt]);
            //vector_EB=(mag_x_raw_array_temp[EB_pt],mag_y_raw_array_temp[EB_pt],mag_z_raw_array_temp[EB_pt]);
            EC_vector[0]=mag_y_raw_array_temp[EA_pt]*mag_z_raw_array_temp[EB_pt]-mag_y_raw_array_temp[EB_pt]*mag_z_raw_array_temp[EA_pt];
            EC_vector[1]=mag_z_raw_array_temp[EA_pt]*mag_x_raw_array_temp[EB_pt]-mag_z_raw_array_temp[EB_pt]*mag_x_raw_array_temp[EA_pt];
            EC_vector[2]=mag_x_raw_array_temp[EA_pt]*mag_y_raw_array_temp[EB_pt]-mag_x_raw_array_temp[EB_pt]*mag_y_raw_array_temp[EA_pt];//correct to the equation

            //find the C' point in the group of points of the elip, which has the smalest distance to the EC line
            //then we assume that C is C'           
            a=EC_vector[0];
            b=EC_vector[1];
            c=EC_vector[2];         
            float module_EC_vector=sqrt(a*a+b*b+c*c);
            float d=sqrt(pow(mag_y_raw_array_temp[0]*c-mag_z_raw_array_temp[0]*b, 2)+pow(mag_z_raw_array_temp[0]*a-mag_x_raw_array_temp[0]*c, 2)+pow(mag_x_raw_array_temp[0]*b-mag_y_raw_array_temp[0]*a, 2))/module_EC_vector;
            for (int i=1; i<mag_pt_temp; i++)
            {
              float d_temp=sqrt(pow(mag_y_raw_array_temp[i]*c-mag_z_raw_array_temp[i]*b, 2)+pow(mag_z_raw_array_temp[i]*a-mag_x_raw_array_temp[i]*c, 2)+pow(mag_x_raw_array_temp[i]*b-mag_y_raw_array_temp[i]*a, 2))/module_EC_vector;
              if (d>d_temp)
              {
                d=d_temp;
                EC_pt=i;
              }
            }
            float EC=sqrt(mag_x_raw_array_temp[EC_pt]*mag_x_raw_array_temp[EC_pt]+mag_y_raw_array_temp[EC_pt]*mag_y_raw_array_temp[EC_pt]+mag_z_raw_array_temp[EC_pt]*mag_z_raw_array_temp[EC_pt]);
            println("EC= "+EC+"  EC_pt= "+EC_pt);
            println("d_min= "+d);
            //--------------------------------------------------------

            //----test the angle bettwen EA,EB,EC -------------------            
            /*
               float cos_angle_EAEC=(mag_x_raw_array_temp[EA_pt]*a+mag_y_raw_array_temp[EA_pt]*b+mag_z_raw_array_temp[EA_pt]*c)/(EA*module_EC_vector);
             float cos_angle_EBEC=(mag_x_raw_array_temp[EB_pt]*a+mag_y_raw_array_temp[EB_pt]*b+mag_z_raw_array_temp[EB_pt]*c)/(EB*module_EC_vector);
             println("angle_EAEC= "+acos(cos_angle_EAEC)*rad2degree);//90 degrees
             println("angle_EBEC= "+acos(cos_angle_EBEC)*rad2degree);//90 degrees
             */
            int step_2=0;
            float cos_89=cos(radians(89));
            float cos_angle_EA_EB=(mag_x_raw_array_temp[EA_pt]*mag_x_raw_array_temp[EB_pt]+mag_y_raw_array_temp[EA_pt]*mag_y_raw_array_temp[EB_pt]+mag_z_raw_array_temp[EA_pt]*mag_z_raw_array_temp[EB_pt])/(EA*EB);
            float cos_angle_EA_EC=(mag_x_raw_array_temp[EA_pt]*mag_x_raw_array_temp[EC_pt]+mag_y_raw_array_temp[EA_pt]*mag_y_raw_array_temp[EC_pt]+mag_z_raw_array_temp[EA_pt]*mag_z_raw_array_temp[EC_pt])/(EA*EC);
            float cos_angle_EB_EC=(mag_x_raw_array_temp[EB_pt]*mag_x_raw_array_temp[EC_pt]+mag_y_raw_array_temp[EB_pt]*mag_y_raw_array_temp[EC_pt]+mag_z_raw_array_temp[EB_pt]*mag_z_raw_array_temp[EC_pt])/(EB*EC);
            if (abs(cos_angle_EA_EB)<cos_89 && abs(cos_angle_EA_EC)<cos_89 && abs(cos_angle_EB_EC)<cos_89)step_2=1;//check step done
            println("cos_angle_EA_EB= "+cos_angle_EA_EB+ "  angle_EA_EB= "+acos(cos_angle_EA_EB)*rad2degree);     
            println("cos_angle_EA_EC= "+cos_angle_EA_EC+ "  angle_EA_EC= "+acos(cos_angle_EA_EC)*rad2degree);   
            println("cos_angle_EB_EC= "+cos_angle_EB_EC+ "  angle_EB_EC= "+acos(cos_angle_EB_EC)*rad2degree);      
            //-------------------------------------------------------            

            if (op_rotation==1)
            {
              //---------- rotate the whole magnetic feild ------------            
              a=mag_x_raw_array_temp[EA_pt];
              b=mag_y_raw_array_temp[EA_pt];
              c=mag_z_raw_array_temp[EA_pt];  

              cos_alpha=a/sqrt(a*a+b*b);          
              cos_beta=(sqrt(a*a+b*b))/(sqrt(a*a+b*b+c*c));

              if (b<0)sin_alpha=-sqrt(1-cos_alpha*cos_alpha);
              else sin_alpha=sqrt(1-cos_alpha*cos_alpha);
              alpha=asin(sin_alpha);

              if (c<0)sin_beta=-sqrt(1-cos_beta*cos_beta);
              else sin_beta=sqrt(1-cos_beta*cos_beta);
              beta=asin(sin_beta);

              for (int i=0; i<mag_pt_temp; i++)// Q(OZ,alpha) rotation: 
              {
                float x_temp=mag_x_raw_array_temp[i];
                float y_temp=mag_y_raw_array_temp[i];

                mag_x_raw_array_temp[i]=x_temp*cos_alpha    +sin_alpha*y_temp;
                mag_y_raw_array_temp[i]=(-sin_alpha)*x_temp +y_temp*cos_alpha;
              }

              for (int i=0; i<mag_pt_temp; i++)// Q(Oy,beta) rotation
              {
                float x_temp=mag_x_raw_array_temp[i];
                float z_temp=mag_z_raw_array_temp[i];

                mag_x_raw_array_temp[i]=x_temp*cos_beta+z_temp*sin_beta;
                mag_z_raw_array_temp[i]=(-sin_beta)*x_temp+z_temp*cos_beta;
              }             

              //---- Q(Ox,theta) rotation: to make the EB line become Oy line
              a=mag_x_raw_array_temp[EB_pt];
              b=mag_y_raw_array_temp[EB_pt];
              c=mag_z_raw_array_temp[EB_pt];  
              println("vector_EB= "+a+" "+b+" "+c);
              float arg=sqrt(a*a+b*b+c*c);
              cos_theta=b/arg;
              if (c>0)sin_theta=sqrt(1-cos_theta*cos_theta);
              else sin_theta=-sqrt(1-cos_theta*cos_theta);            
              theta=asin(sin_theta);

              for (int i=0; i<mag_pt_temp; i++)
              {
                float y_temp=mag_y_raw_array_temp[i];
                float z_temp=mag_z_raw_array_temp[i];

                mag_y_raw_array_temp[i]=y_temp*cos_theta+z_temp*sin_theta;
                mag_z_raw_array_temp[i]=y_temp*(-sin_theta)+z_temp*cos_theta;
              }
              //-------------------------------------------------------
            }

            //default value
            mag_scale[0]=1;//scale_x
            mag_scale[1]=1;//scale_y
            mag_scale[2]=1;//scale_z
            if (op_scale==1)
            {          
              /*   
               //EA>EC>EB
               //---------- get the mag scale --------------------------
               if(max_x>=max_y && max_y>=max_z)//max_x>max_y>max_z
               {
               mag_scale[0]=1;//=EA/EA
               mag_scale[1]=EC/EA;//scale_y
               mag_scale[2]=EB/EA;//scale_z
               }
               else if(max_x>=max_z && max_z>=max_y)//max_x>max_z>max_y
               {
               mag_scale[0]=1;//=EA/EA
               mag_scale[1]=EB/EA;//scale_y
               mag_scale[2]=EC/EA;//scale_z
               }
               else if(max_y>=max_x && max_x>=max_z)//max_y>max_x>max_z
               {
               mag_scale[0]=EC/EA;
               mag_scale[1]=1;
               mag_scale[2]=EB/EA;
               }
               else if(max_y>=max_z && max_z>=max_x)//max_y>max_z>max_x
               {
               mag_scale[0]=EB/EA;
               mag_scale[1]=1;
               mag_scale[2]=EC/EA;
               }
               else if(max_z>=max_x && max_x>=max_y)//max_z>max_x>max_y
               {
               mag_scale[0]=EC/EA;
               mag_scale[1]=EB/EA;
               mag_scale[2]=1;
               }
               else if(max_z>=max_y && max_y>=max_x)//max_z>max_y>max_x
               {
               mag_scale[0]=EB/EA;
               mag_scale[1]=EC/EA;
               mag_scale[2]=1; 
               }
               println("mag_scale[0]= "+mag_scale[0]);
               println("mag_scale[1]= "+mag_scale[1]);
               println("mag_scale[2]= "+mag_scale[2]);
               //-------------------------------------------------------        
               */

              mag_scale[0]=1;//=EA/EA
              mag_scale[1]=(2*EA+EB)/(3*EA);//scale_y
              mag_scale[2]=(2*EA+EC)/(3*EA);//scale_z

              //--------- scale all mag values ------------------------
              for (int i=0; i<mag_pt_temp; i++)
              {
                mag_x_raw_array_temp[i]/=mag_scale[0];
                mag_y_raw_array_temp[i]/=mag_scale[1];
                mag_z_raw_array_temp[i]/=mag_scale[2];
              }
              //-------------------------------------------------------
            }      


            if (op_rotation_back==1)//rotation back the whole magnetic field
            {
              //---- Q(Ox,-theta) rotation:
              cos_neg_theta=cos_theta;
              sin_neg_theta=-sin_theta;  
              for (int i=0; i<mag_pt_temp; i++)
              {
                float y_temp=mag_y_raw_array_temp[i];
                float z_temp=mag_z_raw_array_temp[i];

                mag_y_raw_array_temp[i]=y_temp*cos_theta+z_temp*sin_neg_theta;
                mag_z_raw_array_temp[i]=y_temp*(-sin_neg_theta)+z_temp*cos_theta;
              }
              //-------------------------------------------------------

              //------ Q(Oy,-beta) rotation-----------------------------
              cos_neg_beta=cos_beta;
              sin_neg_beta=-sin_beta;
              for (int i=0; i<mag_pt_temp; i++)
              {
                float x_temp=mag_x_raw_array_temp[i];
                float z_temp=mag_z_raw_array_temp[i];

                mag_x_raw_array_temp[i]=x_temp*cos_neg_beta+z_temp*sin_neg_beta;
                mag_z_raw_array_temp[i]=(-sin_neg_beta)*x_temp+z_temp*cos_neg_beta;
              }       
              //-------------------------------------------------------

              //-------------- Q(OZ,-alpha) rotation: ------------------
              cos_neg_alpha=cos_alpha;       
              sin_neg_alpha=-sin_alpha;           
              for (int i=0; i<mag_pt_temp; i++)
              {
                float x_temp=mag_x_raw_array_temp[i];
                float y_temp=mag_y_raw_array_temp[i];

                mag_x_raw_array_temp[i]=x_temp*cos_neg_alpha    +sin_neg_alpha*y_temp;
                mag_y_raw_array_temp[i]=(-sin_neg_alpha)*x_temp +y_temp*cos_neg_alpha;
              }   
              //--------------------------------------------------------
            }

            data_enough=step_1*step_2;
          } else
          {
            println("Can not have EB yet !");
          }  
          //--------------------------------------------------------                 
          mag_calibrated=1;       
          println("Magnetic data is being calibrated");
        } else if (mouseX>8 && mouseX<108 && mouseY>202 && mouseY<226)//calibrate button 2 is pressed
        {
          start_mag=0;//stop getting new values            
          mag_scale[2]=1;
          mag_scale[1]=1;
          mag_scale[0]=1;
          if (op_offset==1)
          {
            float mag_x_max=0, mag_y_max=0, mag_z_max=0;
            float mag_x_min=0, mag_y_min=0, mag_z_min=0;
            //------------ find the offset points --------------------------------------
            mag_x_min=mag_x_raw_array[0];
            mag_x_max=mag_x_min;
            mag_y_min=mag_y_raw_array[0];
            mag_y_max=mag_y_min;
            mag_z_min=mag_z_raw_array[0];
            mag_z_max=mag_z_min;            
            for (int i=0; i<mag_pt; i++)
            {
              if (mag_x_min>mag_x_raw_array[i]) mag_x_min=mag_x_raw_array[i];
              if (mag_y_min>mag_y_raw_array[i]) mag_y_min=mag_y_raw_array[i];
              if (mag_z_min>mag_z_raw_array[i]) mag_z_min=mag_z_raw_array[i];
              if (mag_x_max<mag_x_raw_array[i]) mag_x_max=mag_x_raw_array[i];
              if (mag_y_max<mag_y_raw_array[i]) mag_y_max=mag_y_raw_array[i];
              if (mag_z_max<mag_z_raw_array[i]) mag_z_max=mag_z_raw_array[i];
            }

            mag_offset[0]=(mag_x_max+mag_x_min)/2;//mag_x_raw_offset
            mag_offset[1]=(mag_y_min+mag_y_max)/2;//mag_y_raw_offset
            mag_offset[2]=(mag_z_min+mag_z_max)/2;//mag_z_raw_offset
            println("mag_offset[0]="+mag_offset[0]);
            println("mag_offset[1]="+mag_offset[1]);
            println("mag_offset[2]="+mag_offset[2]);
            //--------------------- -----------------------------------------------------

            //------ in the plane when acc_z_raw=1g--------------
            mag_x_max=mag_xy_z1g_array[0][0];
            mag_x_min=mag_xy_z1g_array[0][0];
            mag_y_max=mag_xy_z1g_array[1][0];
            mag_y_min=mag_xy_z1g_array[1][0];
            for (int i=0; i<mag_xy_z1g_pt; i++)
            {
              float mag_x_temp=mag_xy_z1g_array[0][i];
              float mag_y_temp=mag_xy_z1g_array[1][i];

              if (mag_x_max<mag_x_temp)mag_x_max=mag_x_temp;
              if (mag_x_min>mag_x_temp)mag_x_min=mag_x_temp;

              if (mag_y_max<mag_y_temp)mag_y_max=mag_y_temp;
              if (mag_y_min>mag_y_temp)mag_y_min=mag_y_temp;
            }
            float E1_x=(mag_x_max+mag_x_min)/2;
            float E1_y=(mag_y_max+mag_y_min)/2;
            println("E1_x= "+E1_x+" E1_y="+E1_y);
            float E1A1=sqrt(pow((E1_x-mag_xy_z1g_array[0][0]), 2)+pow((E1_y-mag_xy_z1g_array[1][0]), 2));
            int A1_pt=0;          
            for (int i=0; i<mag_xy_z1g_pt; i++)
            {
              float temp=sqrt(pow((E1_x-mag_xy_z1g_array[0][i]), 2)+pow((E1_y-mag_xy_z1g_array[1][i]), 2));
              if (E1A1<temp)
              {
                E1A1=temp;
                A1_pt=i;
              }
            }
            println("A1_x= "+mag_xy_z1g_array[0][A1_pt]+" A1_y= "+mag_xy_z1g_array[1][A1_pt]+" E1A1= "+E1A1+" A1_pt= "+A1_pt);          
            float a_E1A1=mag_xy_z1g_array[0][A1_pt]-E1_x;
            float b_E1A1=mag_xy_z1g_array[1][A1_pt]-E1_y;
            float arg_E1A1=sqrt(a_E1A1*a_E1A1+b_E1A1*b_E1A1);
            float d_min=abs(a_E1A1*(mag_xy_z1g_array[0][0]-E1_x)+b_E1A1*(mag_xy_z1g_array[1][0]-E1_y))/arg_E1A1;
            int B1_pt=0;
            for (int i=0; i<mag_xy_z1g_pt; i++)
            {
              float d_temp=abs(a_E1A1*(mag_xy_z1g_array[0][i]-E1_x)+b_E1A1*(mag_xy_z1g_array[1][i]-E1_y))/arg_E1A1;
              if (d_min>d_temp)
              {
                d_min=d_temp;
                B1_pt=i;
              }
            }          
            float E1B1=sqrt(pow((E1_x-mag_xy_z1g_array[0][B1_pt]), 2)+pow((E1_y-mag_xy_z1g_array[1][B1_pt]), 2));   
            //mag_scale[1]=(E1B1+2*E1A1)/(3*E1A1);
            mag_scale[1]=(E1B1/E1A1+1)/2;
            println("d_min= "+d_min);
            println("B1_x= "+mag_xy_z1g_array[0][B1_pt]+" B1_y= "+mag_xy_z1g_array[1][B1_pt]+" E1B1= "+E1B1+" B1_pt= "+B1_pt);
            println("mag_scale[1]= "+mag_scale[1]);                                   
            //---------------------------------------------------

            //------ in the plane when acc_y_raw=1g------------
            mag_x_max=mag_xz_y1g_array[0][0];
            mag_x_min=mag_xz_y1g_array[0][0];
            mag_z_max=mag_xz_y1g_array[1][0];
            mag_z_min=mag_xz_y1g_array[1][0];
            for (int i=0; i<mag_xz_y1g_pt; i++)
            {
              float mag_x_temp=mag_xz_y1g_array[0][i];
              float mag_z_temp=mag_xz_y1g_array[1][i];

              if (mag_x_max<mag_x_temp)mag_x_max=mag_x_temp;
              if (mag_x_min>mag_x_temp)mag_x_min=mag_x_temp;

              if (mag_z_max<mag_z_temp)mag_z_max=mag_z_temp;
              if (mag_z_min>mag_z_temp)mag_z_min=mag_z_temp;
            }
            float E2_x=(mag_x_max+mag_x_min)/2;
            float E2_z=(mag_z_max+mag_z_min)/2;
            println("E2_x= "+E2_x+" E2_z="+E2_z);
            float E2A2=sqrt(pow((E2_x-mag_xz_y1g_array[0][0]), 2)+pow((E2_z-mag_xz_y1g_array[1][0]), 2));    
            int A2_pt=0;       
            for (int i=0; i<mag_xz_y1g_pt; i++)
            {
              float temp=sqrt(pow((E2_x-mag_xz_y1g_array[0][i]), 2)+pow((E2_z-mag_xz_y1g_array[1][i]), 2));
              if (E2A2<temp)
              {
                E2A2=temp;   
                A2_pt=i;
              }
            }          
            println("A2_x= "+mag_xz_y1g_array[0][A2_pt]+" A2_y= "+mag_xz_y1g_array[1][A2_pt]+" E2A2= "+E2A2+" A2_pt= "+A2_pt);          

            float a_E2A2=mag_xz_y1g_array[0][A2_pt]-E2_x;
            float b_E2A2=mag_xz_y1g_array[1][A2_pt]-E2_z;          
            float arg_E2A2=sqrt(a_E2A2*a_E2A2+b_E2A2*b_E2A2);          
            d_min=abs(a_E2A2*(mag_xz_y1g_array[0][0]-E2_x)+b_E2A2*(mag_xz_y1g_array[1][0]-E2_z))/arg_E2A2;
            int B2_pt=0;          
            for (int i=0; i<mag_xz_y1g_pt; i++)
            {
              float d_temp=abs(a_E2A2*(mag_xz_y1g_array[0][i]-E2_x)+b_E2A2*(mag_xz_y1g_array[1][i]-E2_z))/arg_E2A2;
              if (d_min>d_temp)
              {
                d_min=d_temp;
                B2_pt=i;
              }
            }          
            float E2B2=sqrt(pow((E2_x-mag_xz_y1g_array[0][B2_pt]), 2)+pow((E2_z-mag_xz_y1g_array[1][B2_pt]), 2));   
            //mag_scale[2]=(E2B2+2*E2A2)/(3*E2A2);
            mag_scale[2]=(1+E2B2/E2A2)/2;
            println("d_min= "+d_min);
            println("B2_x= "+mag_xz_y1g_array[0][B2_pt]+" B2_y= "+mag_xz_y1g_array[1][B2_pt]+" E2B2= "+E2B2+" B2_pt= "+B2_pt);
            println("mag_scale[2]= "+mag_scale[2]);         
            //---------------------------------------------------

            //--- load calibrated values to a buffer array-------
            mag_pt_temp=mag_pt;
            for (int i=0; i<mag_pt_temp; i++)
            {
              mag_x_raw_array_temp[i]=(mag_x_raw_array[i]-mag_offset[0])/mag_scale[0];
              mag_y_raw_array_temp[i]=(mag_y_raw_array[i]-mag_offset[1])/mag_scale[1];
              mag_z_raw_array_temp[i]=(mag_z_raw_array[i]-mag_offset[2])/mag_scale[2];
            }
            //---------------------------------------------------

            println("Calibrate button 2 is pressed");
            mag_calibrated=2;
            data_enough=1;
          }
        } else if (mouseX>8 && mouseX<108 && mouseY>265 && mouseY<300)//send button is pressed
        {
          Send_mag_calibrated_data();
        }

        if (_1st_time_press==0)//first time press
        {
          mouse_first_pos[0]=mouseY;
          mouse_first_pos[1]=mouseX;
          _1st_time_press=1;
        }
      } else if (test==1)
      {
        if (mouseX>8 && mouseX<108 && mouseY>130 && mouseY<155)
        {
          test=0;
        } else if (mouseX>8 && mouseX<108 && mouseY>165 && mouseY<190)
        {
          start_test=1;
          println("Start testing");
        } else if (mouseX>8 && mouseX<108 && mouseY>202 && mouseY<225)
        {
          start_test=0;
          println("Stop testing");
        } else if (mouseX>8 && mouseX<108 && mouseY>235 && mouseY<260)
        {
          yaw_home_angle=yaw_angle;
          test_mag_str_array_pt=0;
          for (int i=0; i<360; i++)
          {
            test_mag_str_array[i]="";
            yaw_calculated[i]=999;//default value, uncalculated value
          }
          println("Reset all values");
        } else if (mouseX>8 && mouseX<108 && mouseY>270 && mouseY<295)
        {
          get_time();//convert the current time to a string
          output=createWriter("TM_"+time_string);
          for (int i=0; i<test_mag_str_array_pt; i++)
          {            
            output.println(test_mag_str_array[i]);
          }
          //output.flush(); // Writes the remaining data to the file
          output.close(); // Finishes the file
          println("Save to file");
        }
      }      
      break;
    case IMU_DISPLAY_SCREEN:
      if (mouseX>775 && mouseX<790 && mouseY>155 && mouseY<170)//op_offset
      {
        op_rotate_roll++;
        op_rotate_roll%=2;
      } else if (mouseX>775 && mouseX<790 && mouseY>185 && mouseY<200)//op_rotation
      {
        op_rotate_pitch++;
        op_rotate_pitch%=2;
      } else if (mouseX>775 && mouseX<790 && mouseY>215 && mouseY<230)//op_scale
      {
        op_rotate_yaw++;
        op_rotate_yaw%=2;
      }
      break;
    case GPS_MAP_SCREEN:      
      if (mouseX>735 && mouseX<795 && mouseY>515 && mouseY<555)
      {
        int zoom_level_temp=myMapGetsZoom();
        map_kind++;
        map_kind%=2;
        if (map_kind==1)
        {
          map=map_standard;
        } else if (map_kind==0)
        {
          map=map_satellite;
        }
        MapUtils.createDefaultEventDispatcher(this, map);//enable drag, zoom by using mouse
        myZoomAndPanTo((float)latitude, (float)longitude, zoom_level_temp); 
        //compass = new CompassUI(this,map);
      }
      break;
    case PID_GAINING_SCREEN:
      if (mouseX>35 && mouseX<185 && mouseY>378 &&mouseY<410)//write button is pressed
      {
        PID_write=1;
        println("Write gain values to uC");
      } else if (mouseX>35 && mouseX<185 && mouseY>477 &&mouseY<511)//read button is pressed 
      {
        PID_read=1;
        println("Read gain values from uC");
      } else if (mouseX>550 && mouseX<700 && mouseY>375 &&mouseY<410)//back button is pressed 
      {
        PID_screen--;
        if (PID_screen<0)PID_screen=0;
        println("Move to pid_screen "+PID_screen);
      } else if (mouseX>550 && mouseX<700 && mouseY>478 &&mouseY<511)//next button is pressed 
      {
        PID_screen++;
        if (PID_screen>2)PID_screen=2;
        println("Move to pid_screen "+PID_screen);
      } else if (mouseX>250 && mouseX<280 && mouseY>377 &&mouseY<508)//box chossing
      {
        for (int i=0; i<3; i++)
        {
          if (mouseX>255 && mouseX<280 && mouseY>(380+i*50) && mouseY<(405+i*50))
          {
            box_number=i;
          }
        }
      } else
      {
        if (_1st_time_press==0)
        {
          last_mouse_X=mouseX;
          _1st_time_press=1;
        }
      }
    }
    //----------------------------------------------------------------------------------
  } else if (mouseButton==RIGHT)
  {
    switch(screen)
    {
    case GPS_MAP_SCREEN:       
      myLocation++;
      myLocation%=2;
      break;
    case PID_GAINING_SCREEN:       
      if (_1st_time_press==0)
      {
        last_mouse_X=mouseX;
        current_mouse_X=mouseX;
      } 
      break;
    }
  }
}

void Draw_mouse_pos()
{
  textFont(font);
  fill(255, 0, 0);
  textSize(20);
  text(mouseX+" "+mouseY, 5, 15);
}

void mouseDragged()
{
  switch(screen)
  {
  case WELCOME_SCREEN://check new com port(s) if they are available
    Com_check_available();
    break;
  }
}

void mouseReleased()
{
  switch(screen)
  {
  case CALIBRATE_MAG_SCREEN:
    _1st_time_press=0;//forget the previous press
    break;
  case PID_GAINING_SCREEN:
    _1st_time_press=0;//forget the previous press
    delta_gain=0;
    break;
  }
}

