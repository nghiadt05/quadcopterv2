import de.fhpotsdam.unfolding.*;
import de.fhpotsdam.unfolding.geo.*;
import de.fhpotsdam.unfolding.utils.*;
import de.fhpotsdam.unfolding.providers.*;


//---------variables -------------
UnfoldingMap map, map_standard, map_satellite;  
//CompassUI compass;
final float Default_lat=20.9603143;
final float Default_long=105.802443;
int myLocation=1;
int NorthSouth;
int EastWest; 
double longitude, latitude;
long long_h, long_l;
long lat_h, lat_l;
long real_time, real_time_last;
int Valid;
int map_kind;
//--------------------------------

public void Draw_GPS_screen()
{
  clear();
  GPS_getsValue();
  DrawMap();
  DrawMouseLocation();
  Draw_map_change();  
  Draw_lat_long();
  Draw_back_next_button(); 
  Draw_Compass();
}

void DrawMap()
{
  map.draw();
  if (myLocation==1)myZoomAndPanTo((float)latitude, (float)longitude, myMapGetsZoom());
  myDrawMarker((float)latitude, (float)longitude);
  //compass.draw();
}

void GPS_getsValue()
{
  // Valid=1;
  if (Valid==1)//data is valid
  {
    /*
  lat_h=2057;
     lat_l=62242;
     long_h=10548;
     long_l=14981;
     */
    latitude=(lat_h/100)+((double)(lat_h%100)+(double)lat_l/1e5)/60.0f; 
    longitude=(long_h/100)+((double)(long_h%100)+(double)long_l/1e5)/60.0f;
  }
}

public void myMapInit()
{
  map_satellite = new UnfoldingMap(this, new Microsoft.AerialProvider());  
  map_standard = new UnfoldingMap(this, new Google.GoogleMapProvider());
  map=map_satellite;
  //compass = new CompassUI(this,map);
  myZoomAndPanTo(Default_lat, Default_long, 5);//default location 
  MapUtils.createDefaultEventDispatcher(this, map);//enable drag, zoom by using mouse
  latitude=Default_lat;
  longitude=Default_long;
}

void myZoomAndPanTo(float latitude, float longitude, int zoom_level)
{
  map.zoomToLevel(zoom_level);
  map.panTo(new Location(latitude, longitude));
}

int myMapGetsZoom()
{
  int zoom_level=(int)(log(map.getZoom())/log(2));
  //println("zoom_level="+zoom_level);
  return zoom_level;
}

void myDrawMarker(float latitude, float longtitude)
{
  Location myLocation=new Location(latitude, longtitude);//define a new Location variable
  ScreenPosition myPosition = map.getScreenPosition(myLocation);//get the screen pointer of this specific location

    translate(myPosition.x, myPosition.y-10);
  fill(#ff0000);
  noStroke();
  ellipse(0, 0, 10, 10);//draw the location of this point on the screen
  beginShape();
  vertex(-5, 0);
  vertex(5, 0);
  vertex(0, 10);
  endShape();
  translate(-myPosition.x, -myPosition.y+10);
  //image(myImages[21],myPosition.x, myPosition.y);
}

void DrawMouseLocation()
{
  Location location = map.getLocation(mouseX, mouseY);//define a new location object then get the location at the mouse positons
  noStroke();
  fill(0);
  rect(585, 570, 300, 30);
  textSize(20);
  fill(#00ff00);
  text(location.getLat() + ", " + location.getLon(), 588, 590);
}

void Draw_map_change()
{
  strokeWeight(4);
  stroke(#0000ff);
  fill(0);
  rect(735, 515, 60, 40);
  if (map_kind==0)//satellite
  {
    textSize(24);
    fill(#00ff00);
    text("SAT", 746, 545);
  }
  else//standard, basic
  {
    textSize(24);
    fill(#00ff00);
    text("BAS", 746, 545);
  }
}

void Draw_lat_long()
{
  if (Valid==1)//data is valid
  { 
    noStroke();
    fill(0);
    rect(5, 550, 320, 50);
    textSize(22);
    fill(#00ff00);
    text("latitude[degree]= "+(double)((long)(latitude*1e7))/1e7, 10, 570);   
    text("longitude[degree]= "+(double)((long)(longitude*1e7))/1e7, 10, 595);
  } else
  {
    noStroke();
    fill(0);
    rect(5, 570, 180, 30);
    textSize(22);
    fill(#00ff00);
    text("GPS data is invalid", 10, 590);
  }
}

void Draw_back_next_button()
{
  image(myImages[23], 15, 35);
  image(myImages[22], 735, 35);
  image(myImages[24], 675, 0);
}

void Draw_Compass()
{
  translate(762, 477);
  beginShape();
  fill(#ff0000);
  vertex(-8, 0);
  vertex(8, 0);
  vertex(0, -20);
  endShape();  

  beginShape();
  fill(#0000ff);
  vertex(-8, 0);
  vertex(8, 0);
  vertex(0, 20);
  endShape();  
  translate(-762, -477);
}

