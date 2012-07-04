#ifndef MENUE_H
#define MENUE_H

#define DIGITS 15
#define TIMEOUT 10000

// Konstanten fuer Uebertragung
//#define ANFANG '<'

/*
 * A blocking version of Serial.read()
 * Returns -1, when timed out
 */
int blockSerialRead(unsigned timeout)
{
  unsigned long mils = millis();
  while (!Serial.available() && (millis() - mils) < timeout);
  return Serial.read();
}

void menu(boolean* unlock, float* long_Ziel, float* lat_Ziel)
{
  char c;
  int i, k;
  char s[2][DIGITS];
  float d1, d2;
  boolean finished = false;
  boolean abort = false;
  
  Serial.end();
  Serial.begin(9600);
  
  Serial.println("Willkommen bei der GPS-Kassette!");
  while (!finished)
  {
    Serial.println("Bitte waehlen Sie:");
    Serial.println("");
    Serial.println(" * Koordinateneingabe (k)");
    Serial.println(" * Entsperren (u)");
    Serial.println(" * Beenden (q)");
    Serial.println("");                
    c = blockSerialRead(TIMEOUT);
    //Serial.println("%c", c);
    switch (c)
    {
      case 'k':
      case 'K':
        Serial.println("\n> ");
        i = 0;
        k = 0;
        while (k < 2 && !abort)
        {          
          c = blockSerialRead(TIMEOUT);
          switch (c)
          {
            case -1: // timeout
            case 27: // escape
              abort = true;
              break;
            case ',': 
            case '\n':
            case '\r':
            case ';':
              s[k][i] = 0; // string abschliessen
              i = 0;
              k++;
              break;
            default:
              s[k][i++] = c;
              break;
          }
        }
        
        if(!abort)
        {
          d1 = atof(s[0]);
          d2 = atof(s[1]);
          if (d1 && d2)
          {
            *long_Ziel = d1;
            *lat_Ziel = d2;
            
            Serial.println("Koordinaten:");
            Serial.println(s[0]);
            Serial.println(s[1]);
          }
          else
          {
            Serial.println("Ungueltige Koordinaten!");
          }
        }
        break;
      case 'u':
      case 'U':
        *unlock = 1;
        Serial.println("Aufgesperrt");
        break;
      case 'q':
      case 'Q':
      case 27: // escape
      case -1: // timeout
        finished = true;
        Serial.println("Uebertragung beendendet");
        break;
    }
  }
  
  Serial.end();
  Serial.begin(4800);
}

#endif

