//----------- variables --------------
PFont font, fontb, fontbi, fonti;
PImage myImages[]=new PImage[50];
//------------------------------------

void Graphic_configuration()
{
  //------- graphic init -----------
  size(800, 600, P3D);
  frameRate(30);
  smooth();
  background(0);
  colorMode(RGB, 8); 
  //--------------------------------
}

void Font_Image_Configuration()
{
  //--------- load font ------------
  font= loadFont("Andalus-48.vlw");
  fontb=loadFont("TimesNewRomanPS-BoldMT-48.vlw");
  fontbi=loadFont("TimesNewRomanPS-BoldItalicMT-48.vlw");
  fonti=loadFont("TimesNewRomanPS-ItalicMT-48.vlw");
  textFont(font);
  //--------------------------------

  //---------- load images ---------
  myImages[0]=loadImage("Welcome.jpg");
  myImages[1]=loadImage("Gyroscope.jpg");
  myImages[2]=loadImage("gyro_calib.jpg");
  myImages[3]=loadImage("calib_button.jpg");
  myImages[4]=loadImage("send2uC_button.jpg");
  myImages[5]=loadImage("COM_START_BUTTON.jpg");
  myImages[6]=loadImage("acc_screen.jpg");
  myImages[7]=loadImage("acc_x_negative.jpg");
  myImages[8]=loadImage("acc_x_positive.jpg");
  myImages[9]=loadImage("acc_y_negative.jpg");
  myImages[10]=loadImage("acc_y_positive.jpg");
  myImages[11]=loadImage("acc_z_negative.jpg");
  myImages[12]=loadImage("acc_z_positive.jpg");
  myImages[13]=loadImage("next_button.jpg");
  myImages[14]=loadImage("back_button.jpg");
  myImages[15]=loadImage("reset_button.jpg");
  myImages[16]=loadImage("calculate_button.jpg");  
  myImages[17]=loadImage("mag_banner.jpg");
  myImages[18]=loadImage("start_mag.jpg");
  myImages[19]=loadImage("stop_mag.jpg");
  myImages[20]=loadImage("imu_banner.jpg");
  myImages[21]=loadImage("google_pointer.jpg");
  myImages[22]=loadImage("next_button_raw.jpg");
  myImages[23]=loadImage("back_button_raw.jpg");
  myImages[24]=loadImage("main_menu.jpg");
  myImages[25]=loadImage("PID_banner.jpg");
  myImages[26]=loadImage("pid_read_button.jpg");
  myImages[27]=loadImage("pid_write_button.jpg");
  myImages[28]=loadImage("pid_back_button.jpg");
  myImages[29]=loadImage("pid_next_button.jpg");
  myImages[30]=loadImage("read_file.jpg");
  myImages[31]=loadImage("save_file.jpg");
  myImages[32]=loadImage("calib_button_2.jpg");
  myImages[33]=loadImage("test.jpg");
  myImages[34]=loadImage("return_mag.jpg");
  myImages[35]=loadImage("calib_button_1.jpg");
  //--------------------------------
}

