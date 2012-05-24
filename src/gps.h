#ifndef GPS_H
#define GPS_H

TinyGPS gps;

static float getDistance(float lat_Ziel, float long_Ziel)
{  
  float lat_Position=0,long_Position=0;
  unsigned long age;
  gps.f_get_position(&lat_Position, &long_Position, &age);
	// TODO sonderfall: kein signal abfangen
  float dx = 71.5 * (long_Ziel - long_Position);
  float dy = 111.3 * (lat_Ziel - lat_Position);
  float dist = sqrt(dx * dx + dy * dy);  
  return dist;

}

boolean amBestimmungsort(int abstand)
{
  return (abstand <= 10);
}

#endif


