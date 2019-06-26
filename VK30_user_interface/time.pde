int day, month, year;
int h, m, s;
String time_string;

public void get_time()
{
  day=day();
  month=month();
  year=year();
  h=hour();
  m=minute();
  s=second();
  time_string=String.valueOf(day)+"_"+String.valueOf(month)+"_"+String.valueOf(year)+"_"+String.valueOf(h)+"h_"+String.valueOf(m)+"p_"+String.valueOf(s)+"s.txt";
  println(time_string);
}

