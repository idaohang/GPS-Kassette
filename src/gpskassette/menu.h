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
  
  // Von GPS auf PC/Seriell umschalten
  Serial.end();
  Serial.begin(9600);
  
  Serial.println("Willkommen bei der GPS-Kassette!");
  boolean finished;
  while (!finished)
  {
    Serial.println("Bitte waehlen Sie:");
    Serial.println("");
    Serial.println(" * Koordinateneingabe (k)");
    Serial.println(" * Entsperren (u)");
    Serial.println(" * Beenden (q)");
    Serial.println("");                
    
    char c = blockSerialRead(TIMEOUT);
    //Serial.println("%c", c); // echo off -- terminal should do this job.

    boolean abort = false;    
    char s[2][DIGITS];
    int i, k;

    switch (c)
    {
      case 'k':
      case 'K':
        // Koordinateneingabe
        Serial.print("\n> ");
        
        i = 0;
        k = 0;
        
        // 2 Koordinaten, mit Trennzeichen getrennt
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
              // Eingabe in Buffer
              s[k][i++] = c;
              break;
          }
        }
        
        if(!abort)
        {
          float d1 = atof(s[0]);
          float d2 = atof(s[1]);
          if (d1 && d2)
          {
            *long_Ziel = d1;
            *lat_Ziel = d2;
            
            Serial.println("Ihre Koordinaten:");
            // Evtl. d1 und d2, statt original Eingaben
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
  
  // Wieder umschalten auf GPS
  Serial.end();
  Serial.begin(4800);
}

#endif

