#ifndef GPS_H
#define GPS_H

TinyGPS gps;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

float getDistance(float lat_Ziel, float long_Ziel, float oldDistance)
{
  float dist = oldDistance;  
  while(Serial.available())     // While there is data on the RX pin
  {
    char c = Serial.read();    // load the data into a variable
    if(gps.encode(c))      // if there is a new valid sentence
    {
      float lat_Position = 0;
      float long_Position = 0;
      gps.f_get_position(&lat_Position, &long_Position);
      float dx = 71.5 * (long_Ziel - long_Position);
      float dy = 111.3 * (lat_Ziel - lat_Position);
      dist = sqrt(dx * dx + dy * dy) * 1000;
    }
  }
  return dist;
}

boolean amBestimmungsort(int abstand)
{
  return (abstand <= 10);
}

#endif


