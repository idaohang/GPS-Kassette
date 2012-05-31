#ifndef GPS_H
#define GPS_H

TinyGPS gps;

float getDistance(float lat_Ziel, float long_Ziel)
{  
  float lat_Position = 0;
  float long_Position = 0;
  unsigned long fix_age;
  gps.f_get_position(&lat_Position, &long_Position, &fix_age);
  
  // TODO sonderfall: kein signal abfangen
  if (fix_age == TinyGPS::GPS_INVALID_AGE)
    Serial.println("No fix detected");
  else if (fix_age > 5000)
    Serial.println("Warning: possible stale data!");
  else
    Serial.println("Data is current.");
  
  lcd.setCursor(0, 1);
  lcd.print(lat_Position);
  lcd.print(",");
  lcd.print(long_Position);
//  delay(
  
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


