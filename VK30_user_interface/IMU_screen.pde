//----- variables ---------
int op_rotate_roll=1, op_rotate_pitch=1, op_rotate_yaw=1;
//-------------------------

public void Draw_imu_screen()
{
  clear();
  image(myImages[20], 0, 0);  
  Draw_imu_options();
  Draw_roll_axis();
  Draw_pitch_axis();
  Draw_yaw_axis();
  Draw_temp();
  Draw_baro();
  Draw_imu_block();
}

void Draw_imu_block()
{
  translate(WIDTH/2, 340);
  /*
  rpy[0]+=1.0;
   rpy[1]+=1.0;
   rpy[2]+=1.0;
   for(int i=0;i<3;i++)
   {
   rpy[i]%=360;
   }
   */
  if (op_rotate_roll==1)rotateZ(radians(rpy[0]));
  if (op_rotate_pitch==1)rotateX(radians(rpy[1]));
  if (op_rotate_yaw==1)rotateY(-radians(rpy[2]));
  scale(3.2);
  noStroke();
  beginShape(QUADS);
  // z+ (to the drawing area)
  fill(#00ff00);
  vertex(-5, -5, 40);
  vertex(5, -5, 40);
  vertex(5, 5, 40);
  vertex(-5, 5, 40);

  vertex(-40, -5, 5);
  vertex(40, -5, 5);
  vertex(40, 5, 5);
  vertex(-40, 5, 5);

  vertex(-10, -5, 10);
  vertex(10, -5, 10);
  vertex(10, 5, 10);
  vertex(-10, 5, 10);

  // z- 
  fill(#0000ff);
  vertex(-5, -5, -40);
  vertex(5, -5, -40);
  vertex(5, 5, -40);
  vertex(-5, 5, -40);

  vertex(-40, -5, -5);
  vertex(40, -5, -5);
  vertex(40, 5, -5);
  vertex(-40, 5, -5); 

  vertex(-10, -5, -10);
  vertex(10, -5, -10);
  vertex(10, 5, -10);
  vertex(-10, 5, -10);
  // x-
  fill(#ff0000);
  vertex(-5, -5, -40);
  vertex(-5, -5, 40);
  vertex(-5, 5, 40);
  vertex(-5, 5, -40);

  vertex(-40, -5, -5);
  vertex(-40, -5, 5);
  vertex(-40, 5, 5);
  vertex(-40, 5, -5);

  vertex(-10, -5, -10);
  vertex(-10, -5, 10);
  vertex(-10, 5, 10);
  vertex(-10, 5, -10);
  // x+
  fill(#ffff00);
  vertex(5, -5, -40);
  vertex(5, -5, 40);
  vertex(5, 5, 40);
  vertex(5, 5, -40);

  vertex(40, -5, -5);
  vertex(40, -5, 5);
  vertex(40, 5, 5);
  vertex(40, 5, -5);

  vertex(10, -5, -10);
  vertex(10, -5, 10);
  vertex(10, 5, 10);
  vertex(10, 5, -10);
  // y-
  fill(#ff00ff);
  vertex(-5, -5, -40);
  vertex(5, -5, -40);
  vertex(5, -5, 40);
  vertex(-5, -5, 40);

  vertex(-40, -5, -5);
  vertex(40, -5, -5);
  vertex(40, -5, 5);
  vertex(-40, -5, 5);

  vertex(-10, -5, -10);
  vertex(10, -5, -10);
  vertex(10, -5, 10);
  vertex(-10, -5, 10);


  // y+
  fill(#00ffff);
  vertex(-5, 5, -40);
  vertex(5, 5, -40);
  vertex(5, 5, 40);
  vertex(-5, 5, 40);

  vertex(-40, 5, -5);
  vertex(40, 5, -5);
  vertex(40, 5, 5);
  vertex(-40, 5, 5);

  vertex(-10, 5, -10);
  vertex(10, 5, -10);
  vertex(10, 5, 10);
  vertex(-10, 5, 10);

  //--- forward_symbol
  fill(#17F70C);
  vertex(-5, -10, -40);
  vertex(5, -10, -40);
  vertex(5, -10, -45);
  vertex(-5, -10, -45);

  vertex(-5, -5, -40);
  vertex(5, -5, -40);
  vertex(5, -5, -45);
  vertex(-5, -5, -45);

  fill(#0CF7E6);
  vertex(-5, -10, -40);
  vertex(-5, -10, -45);
  vertex(-5, -5, -45);
  vertex(-5, -5, -40);

  vertex(5, -10, -40);
  vertex(5, -10, -45);
  vertex(5, -5, -45);
  vertex(5, -5, -40);


  fill(#0C5CF7);
  vertex(-5, -5, -45);
  vertex(-5, -10, -45); 
  vertex(5, -10, -45);
  vertex(5, -5, -45); 

  vertex(-5, -5, -40);
  vertex(-5, -10, -40); 
  vertex(5, -10, -40);
  vertex(5, -5, -40); 

  endShape();  
  scale(1/3.2);
  //-----------------------------------------------
  if (op_rotate_yaw==1)rotateY(radians(rpy[2]));
  if (op_rotate_pitch==1)rotateX(-radians(rpy[1]));
  if (op_rotate_roll==1)rotateZ(-radians(rpy[0]));  

  translate(-WIDTH/2, -340);
}

void Draw_imu_options()
{
  textSize(24);
  fill(#00ff00);
  text("OPTIONS:", 680, 140); 
  textSize(15); 
  text("Rotate Roll", 680, 170);
  text("Rotate Pitch", 680, 200);
  text("Rotate Yaw", 680, 230);

  strokeWeight(3);
  stroke(#0000FF);
  if (op_rotate_roll==1)fill(#00ff00);
  else noFill();
  rect(775, 155, 15, 15);

  if (op_rotate_pitch==1)fill(#00ff00);
  else noFill();
  rect(775, 185, 15, 15);

  if (op_rotate_yaw==1)fill(#00ff00);
  else noFill();
  rect(775, 215, 15, 15);
}

void Draw_roll_axis()
{  
  translate(700, 325);
  //--- print number of degree ----
  fill(#00ff00);
  textSize(24);
  text(0, -5, -70);  
  textSize(20);
  text("Roll axis= "+rpy[0], -60, 90);
  //--------------------------------

  //---- print roll degree ruler ---
  stroke(#ffffff);
  strokeWeight(2);
  for (int i=0; i<361; i+=30)
  {
    rotateZ((float)radians(i));
    line(0, 45, 0, 60);
    rotateZ(-(float)radians(i));
  }

  for (int i=0; i<361; i+=15)
  {
    rotateZ((float)radians(i));
    line(0, 55, 0, 60);
    rotateZ(-(float)radians(i));
  }

  strokeWeight(2);
  stroke(#ffffff);
  noFill();
  ellipse(0, 0, 120, 120);

  fill(0);
  ellipse(0, 0, 90, 90);
  //----------------------------------

  //----- draw roll pointer ----------
  rotateZ(radians(rpy[0]));
  stroke(#ff0000);
  strokeWeight(4);
  line(-40, 0, 40, 0);
  line(0, 0, 0, -20);
  rotateZ(-radians(rpy[0]));
  noStroke();
  //----------------------------------
  translate(-700, -325);
}

void Draw_pitch_axis()
{
  translate(700, 500);
  //--- print number of degree ----
  fill(#00ff00);
  textSize(20);
  text(0, 70, 5);
  text("Pitch axis= "+rpy[1], -60, 80);
  //--------------------------------

  //---- print pitch degree ruler ---
  stroke(#ffffff);
  strokeWeight(2);
  for (int i=0; i<361; i+=30)
  {
    rotateZ((float)radians(i));
    line(0, 45, 0, 60);
    rotateZ(-(float)radians(i));
  }

  for (int i=0; i<361; i+=15)
  {
    rotateZ((float)radians(i));
    line(0, 55, 0, 60);
    rotateZ(-(float)radians(i));
  }

  strokeWeight(2);
  stroke(#ffffff);
  noFill();
  ellipse(0, 0, 120, 120);

  strokeWeight(2);
  stroke(#ffffff);
  noFill();
  ellipse(0, 0, 120, 120);

  fill(0);
  ellipse(0, 0, 90, 90);
  //----------------------------------

  //----- draw pitch pointer ----------
  rotateZ(radians(rpy[1]));
  noStroke();
  fill(#ff0000);
  beginShape(QUADS);
  vertex(-30, 5);
  vertex(-30, -5);
  vertex(15, -5);
  vertex(15, 5);
  endShape();

  beginShape();
  vertex(15, -5);
  vertex(15, -10);
  vertex(30, 0);
  vertex(15, 10);
  vertex(15, 5);
  endShape();
  rotateZ(-radians(rpy[1]));
  //----------------------------------
  translate(-700, -500);
}

void Draw_yaw_axis()
{
  translate(100, 500);
  //------------------------------
  noStroke();
  fill(#2F22C6);
  ellipse(0, 0, 120, 120);
  fill(#90A08E);
  ellipse(0, 0, 80, 80);
  //-----------------------------
  fill(#C4C04D);
  textSize(25);
  text("N", -8, -41);
  text("W", -60, 8);
  text("E", 42, 8);
  text("S", -7, 58);
  fill(#0AF713);
  textSize(20);
  text("E-Compass", -45, -80);
  text("Yaw angles= "+rpy[2], -60, 80);
  //-------------------------------

  rotateZ(radians(rpy[2]));
  beginShape(QUADS);
  fill(#FF0000);
  vertex(-5, 0);
  vertex(5, 0);
  vertex(5, -25);
  vertex(-5, -25);  
  endShape();

  noStroke();
  beginShape();
  vertex(-10, -25);
  vertex(0, -35);
  vertex(10, -25);
  endShape();
  rotateZ(-radians(rpy[2]));
  translate(-100, -500);
}

void Draw_temp()
{
  //--------------------------------------------------  
  translate(250, 570);
  strokeWeight(2);
  stroke(#ffffff);
  fill(#060383);
  rect(0, 0, 300, 15);
  noStroke();
  fill(#ff0000);
  rect(0, 0, T*6, 15);
  strokeWeight(2);
  stroke(#ffffff);
  for (char i=0; i<6; i++)
  {
    line(60*i, 0, 60*i, 10);
    fill(#0AFF0C);
    text(i*10, 60*i-10, -10);
  }
  for (char i=0; i<11; i++)
  {
    line(30*i, 0, 30*i, 6);
  }

  for (char i=0; i<51; i++)
  {
    line(6*i, 0, 6*i, 3);
  }

  fill(#0AFF0C);
  text("oC", 310, -10);
  text("Temperature= "+T, 0, -35);
  translate(-250, -570);
  //--------------------------------------------------
}

void Draw_baro()
{
  //----------- draw barometter -----------------
  translate(110, 350);  
  //-------------- barometer ruler --------

  for (char i=0; i<3; i++)
  {
    stroke(#FFFFFF);
    strokeWeight(2);
    line(-20, -80*i, -60, -80*i);
    textSize(20);
    fill(#0AF713);
    text(i*50, -100, -80*i);
  }

  for (char i=0; i<5; i++)
  {
    stroke(#FFFFFF);
    strokeWeight(2);
    line(-20, -40*i, -40, -40*i);
    textSize(20);
    if ((i%2)!=0)
    {
      fill(#0AF713);
      text(i*25, -80, -40*i);
    }
  }

  for (char i=0; i<9; i++)
  {
    stroke(#FFFFFF);
    strokeWeight(2);
    line(-20, -20*i, -30, -20*i);
  }
  //---------------------------------------

  beginShape(QUADS);
  fill(#838683);
  vertex(-20, 0);
  vertex(20, 0);
  vertex(20, -160);
  vertex(-20, -160);

  fill(#0778ED);
  vertex(-20, 0);
  vertex(20, 0);
  vertex( 20, -160*(int)(P%100)/100);
  vertex(-20, -160*(int)(P%100)/100);
  endShape();

  fill(#0AF713);
  textSize(20);
  text("Barometer (kPa)", -50, -170);
  textSize(20);
  text("P= "+(int)P, -40, 20);
  translate(-110, -350);
  //----------- end of barometer ---------------
}

