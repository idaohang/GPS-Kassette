#ifndef MENUE_H
#define MENUE_H

#define DIGITS 15
#define TIMEOUT 10000

// Konstanten fuer Uebertragung
#define ANFANG 'A'

void waitForInput()
{
  unsigned mils = millis();
  while (!Serial.available() && (millis() - mils) < TIMEOUT);
}

void menu(boolean* unlock, float* long_Ziel, float* lat_Ziel)
{
  char c;
  int i, k, flag=0;
  char s[2][DIGITS];
        float d1, d2;
  boolean finished = false;
  while (!finished)
  {
    Serial.println("Willkommen bei der GPS-Kassette!");
    Serial.println("");
    Serial.println(" * Koordinateneingabe (k)");
    Serial.println(" * Entsperren (u)");
    Serial.println(" * Beenden (q)");
    Serial.println("");
                waitForInput();
                c = Serial.read();
                //Serial.println("%c", c);
    switch (c)
    {
      case 'k':
      case 'K':
        Serial.println("\n> ");
        i = 0;
        k = 0;
        while (k < 2)
        {
          waitForInput();
          c = Serial.read();
          switch (c)
          {
            case -1: 
              flag=1;
              break;
            case ',': 
            case '\n':
            case '\r':
            case ';':
              s[k][i] = 0;
              i = 0;
              k++;
              break;
            default:
              s[k][i++] = c;
              break;
          }
        }
        
        if(!flag)
        {
          Serial.println("Koordinaten:");
          Serial.println(s[0]);
          Serial.println(s[1]);
        
          d1 = atof(s[0]);
          d2 = atof(s[1]);
          if (d1 && d2)
          {
            *long_Ziel = d1;
            *lat_Ziel = d2;
          }
          else
          {
            Serial.println("Ungueltige Koordinaten!");
          }
        }
        break;
      case 'u':
      case 'U':
        Serial.println("Unlocking...");
        *unlock = 1;
        break;
      case 'q':
      case 'Q':
      case 27:
      case -1:
        Serial.println("Uebertragung beenden...");
        finished = true;
        break;
    }
  }
}

#endif

