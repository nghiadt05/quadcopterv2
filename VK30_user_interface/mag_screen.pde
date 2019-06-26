//------------ variables ------------------
public float mag_x_raw_array[]=new float[65535];
public float mag_y_raw_array[]=new float[65535];
public float mag_z_raw_array[]=new float[65535];

public float mag_x_raw_array_temp[]=new float[65535];
public float mag_y_raw_array_temp[]=new float[65535];
public float mag_z_raw_array_temp[]=new float[65535];

public float mag_x_raw_array_temp_cl[]=new float[65535];
public float mag_y_raw_array_temp_cl[]=new float[65535];
public float mag_z_raw_array_temp_cl[]=new float[65535];

public float mag_xy_z1g_array[][]=new float[2][65535];
public float mag_xz_y1g_array[][]=new float[2][65535];
public int   mag_xy_z1g_pt;
public int   mag_xz_y1g_pt;

public float yaw_angle,yaw_angle_temp;
public float yaw_calculated[]=new float[360];

public float cos_theta, sin_theta, cos_neg_theta, sin_neg_theta;
public float cos_beta, sin_beta, cos_neg_beta, sin_neg_beta;
public float cos_alpha, sin_alpha, cos_neg_alpha, sin_neg_alpha;

public float mag_offset[]=new float[3];
public float mag_scale[]=new float[3];
public float alpha, beta, theta;

public float max_x=0, max_y=0, max_z=0;
public String test_mag_str_array[]=new String[360];
public int test_mag_str_array_pt=0;

public int mag_pt, mag_pt_temp;
public int EA_pt, EB_pt, EC_pt;

PrintWriter output;//output file

float EC_vector[]=new float[3];
float rotate_angle[]=new float[2];
int mouse_first_pos[]=new int[2];
int mouse_current_pos[]=new int[2];
int _1st_time_press, mag_press_stt;
int data_enough;
int test=0;
int op_offset=1, op_rotation=1, op_scale=1, op_rotation_back=1;
public int start_mag, mag_calibrated, start_test;
//-----------------------------------------

public void mag_init()
{
  mag_scale[0]=1;
  mag_scale[1]=1;
  mag_scale[2]=1;
  for (int i=0; i<360; i++)
  {
    yaw_calculated[i]=999;//default value, uncalculated value
  }
}
public void Draw_mag_screen()
{
  clear();  
  image(myImages[17], 0, 0);

  if (test==0)
  {
    image(myImages[18], 8, 125);   
    image(myImages[19], 8, 160);
    image(myImages[32], 8, 195);
    image(myImages[35], 8, 230);
    image(myImages[4], 8, 265);
    image(myImages[30], 670, 260);
    image(myImages[31], 670, 295);
    image(myImages[15], 670, 330);
    image(myImages[33], 670, 365);

    Draw_mag_color();
    Draw_calibrated_values();
    Draw_mag_options();
    Draw_mag_raw();//put this function at the last of the line
  } else if (test==1)
  {
    image(myImages[34], 8, 125);
    image(myImages[18], 8, 160);
    image(myImages[19], 8, 195);
    image(myImages[15], 8, 230);
    image(myImages[31], 8, 265);
    textSize(24);
    fill(#00ff00);
    text("Correct angle= "+test_mag_str_array_pt+ "   --------  Calculated angle= "+yaw_calculated[test_mag_str_array_pt], 140, 152);
    text("Recent angle= "+yaw_angle_temp, 140, 180);
    Draw_angle_ruler();    
  }
}

public void Draw_angle_ruler()
{
  translate(450,375);
  stroke(#0000ff);
  noFill();
  strokeWeight(6);  
  ellipse(0,0,350,350);
  
  for(int i=0;i<360;i+=5)
  {
    rotateZ(radians(i));
    stroke(#ffffff);
    strokeWeight(2);
    line(0,165,0,170);
    
    if(i%10==0)
    {
      line(0,160,0,170);
    }
    
    if(i%90==0)
    {
      strokeWeight(3);
      stroke(#ff0000);
      line(0,160,0,170);       
    }
    rotateZ(radians(-i));
    
    rotateZ(radians(yaw_angle_temp-90));
    beginShape(QUADS);
    noStroke();
    fill(#ff0000); 
    vertex(-4,0);
    vertex(4,0);
    vertex(4,-150);
    vertex(-4,-150);        
    endShape();
    
    beginShape();
    vertex(-8,-130);
    vertex(8,-130);
    vertex(0,-160);
    endShape(); 
    
    rotateZ(radians(-yaw_angle_temp+90));  
  }
  fill(#00ff00);
  textSize(24);
  text(yaw_angle_temp,-50,-50);
  translate(-450,-375);  
}

public void Draw_mag_raw()
{
  translate(WIDTH/2, 360);  

  //---------- rotate the axis according to the mouse position --------------------
  if (_1st_time_press==1)//get the mouse gap then calculate to the desire angles
  {
    rotate_angle[0]=-mouseY+mouse_first_pos[0];//rotate x values
    rotate_angle[1]=mouseX-mouse_first_pos[1];//rotate y values
  }
  rotateX(radians(rotate_angle[0]));
  rotateY(radians(rotate_angle[1]));
  //--------------------------------------------------------------------------------

  //------------- draw 3 basic lines ---------------------
  strokeWeight(5);
  stroke(#00ff00);
  line(0, 0, 0, 200, 0, 0);//Ox  
  stroke(#ff0000);
  line(0, 0, 0, 0, 200, 0);//Oy
  stroke(#0000ff);
  line(0, 0, 0, 0, 0, 200);//Oz
  //------------------------------------------------------  

  //------ draw calibrated data ----------
  if (mag_calibrated==1)
  {
    strokeWeight(2);
    stroke(#00FFE8);
    for (int i=0; i<mag_pt_temp; i++)
    {
      point(mag_x_raw_array_temp[i], mag_y_raw_array_temp[i], mag_z_raw_array_temp[i]);
    }

    strokeWeight(5);
    stroke(#FFFF00);//yellow
    line(0, 0, 0, mag_x_raw_array_temp[EA_pt], mag_y_raw_array_temp[EA_pt], mag_z_raw_array_temp[EA_pt]);//EA
    stroke(#DEB574);//color of the sky
    line(0, 0, 0, mag_x_raw_array_temp[EB_pt], mag_y_raw_array_temp[EB_pt], mag_z_raw_array_temp[EB_pt]);//EB
    stroke(#FF00FF);//pink
    line(0, 0, 0, mag_x_raw_array_temp[EC_pt], mag_y_raw_array_temp[EC_pt], mag_z_raw_array_temp[EC_pt]);//EC
    /*
    stroke(#E0D0D0);
     line(0,0,0,EC_vector[0],EC_vector[1],EC_vector[2]);
     */
  } else if (mag_calibrated==2)
  {
    strokeWeight(2);
    stroke(#00FFE8);
    for (int i=0; i<mag_pt_temp; i++)
    {
      point(mag_x_raw_array_temp[i], mag_y_raw_array_temp[i], mag_z_raw_array_temp[i]);
    }
  } else
  {
    //------------- draw mag points ------------------------
    strokeWeight(2);
    stroke(#00FFE8);
    for (int i=0; i<mag_pt; i++)
    {
      point(mag_x_raw_array[i], mag_y_raw_array[i], mag_z_raw_array[i]);
    }
    //------------------------------------------------------
  }
  //--------------------------------------

  rotateY(-radians(rotate_angle[1]));
  rotateX(-radians(rotate_angle[0]));  
  translate(-WIDTH/2, -360);
}

public void Draw_mag_color()
{
  String str[]=new String[10];
  color _color_[]=new color[10];

  str[0]="Ox";
  str[1]="Oy";
  str[2]="Oz";
  str[3]="EA";
  str[4]="EB";
  str[5]="EC";

  _color_[0]=#00ff00;
  _color_[1]=#ff0000;
  _color_[2]=#0000ff;
  _color_[3]=#FFFF00;
  _color_[4]=#DEB574;
  _color_[5]=#FF00FF;

  for (int i=0; i<6; i++)
  {
    fill(_color_[i]);
    textSize(20);
    text(str[i], 690, 460+i*25);

    strokeWeight(5);
    stroke(_color_[i]);
    line(730, 455+i*25, 770, 455+i*25);
  }
}

public void Draw_calibrated_values()
{
  if (mag_calibrated>0)
  {
    if (data_enough==0)
    {
      textSize(25);   
      fill(#ff0000);
      text("Data is not sufficient, please collect more !", 174, 148);//warning if data is not enough
    }
    textSize(20);
    fill(#00ff00);  
    text("Mag_x_offset= "+(int)mag_offset[0], 8, 340); 
    text("Mag_y_offset= "+(int)mag_offset[1], 8, 370);
    text("Mag_z_offset= "+(int)mag_offset[2], 8, 400); 
    text("Mag_x_scale= "+mag_scale[0], 8, 430);
    text("Mag_y_scale= "+mag_scale[1], 8, 460);
    text("Mag_z_scale= "+mag_scale[2], 8, 490);
    if (mag_calibrated==1)
    {
      text("alpha= "+alpha +" rad", 8, 520);
      text("beta= "+beta+ " rad", 8, 550);
      text("theta= "+theta+" rad", 8, 580);
    }
  }
}

void Draw_mag_options()
{
  textSize(24);
  fill(#00ff00);
  text("OPTIONS:", 680, 140); 
  textSize(15); 
  text("OFFSET", 680, 170);
  text("ROTATION I", 680, 200);
  text("ROTATION II", 680, 230);
  text("SCALE", 680, 260);


  strokeWeight(3);
  stroke(#0000FF);
  if (op_offset==1)fill(#00ff00);
  else noFill();
  rect(775, 155, 15, 15);

  if (op_rotation==1)fill(#00ff00);
  else noFill();
  rect(775, 185, 15, 15);//op_rotation_back

  if (op_rotation_back==1)fill(#00ff00);
  else noFill();
  rect(775, 215, 15, 15);  

  if (op_scale==1)fill(#00ff00);
  else noFill();
  rect(775, 245, 15, 15);
}

public void Send_mag_calibrated_data()
{
  String mag_send_string;
  String mag_string_temp[]=new String[9];
  /*
  mag_offset[0]=4;
   mag_offset[1]=5;
   mag_offset[2]=6;
   mag_scale[0]=7;
   mag_scale[1]=8;
   mag_scale[2]=9;
   */
  mag_string_temp[0]=String.valueOf(mag_offset[0]);
  mag_string_temp[1]=String.valueOf(mag_offset[1]);
  mag_string_temp[2]=String.valueOf(mag_offset[2]);

  mag_string_temp[3]=String.valueOf(mag_scale[0]);
  mag_string_temp[4]=String.valueOf(mag_scale[1]);
  mag_string_temp[5]=String.valueOf(mag_scale[2]);

  mag_string_temp[6]=String.valueOf(alpha);
  mag_string_temp[7]=String.valueOf(beta);
  mag_string_temp[8]=String.valueOf(theta);

  mag_send_string="&3,"+mag_string_temp[0]+','+mag_string_temp[1]+','+mag_string_temp[2]+','
    +mag_string_temp[3]+','+mag_string_temp[4]+','+mag_string_temp[5]+'@';
  // +mag_string_temp[6]+','+mag_string_temp[7]+','+mag_string_temp[8]+'@';

  println(mag_send_string);
  while (serial_free==0) {
  }
  myPort.write(mag_send_string);
  println("Mag calibrated data sent");
}

