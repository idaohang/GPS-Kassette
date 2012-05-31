#ifndef OUTPUT_H
#define OUTPUT_H

#define MAX_ULONG 4294967295

#define PIN_GREEN 6
#define PIN_RED   7

#define BLINK_DELAY 500

void lcdClearIfFlag(boolean *flag)
{
  if (*flag)
  {
    lcd.clear();
    *flag = false;
    delay(100);
  }
}

void outputs(char state, char oldState, int abstand, boolean taster)
{

  static boolean blinky = false;
  static unsigned long oldMils = 0;
  unsigned long mils = millis();
  if (oldMils > mils)
    mils = oldMils + MAX_ULONG;
  if ((mils - oldMils) >= BLINK_DELAY)
  {
    blinky = !blinky;
    oldMils = mils;
  }
  

  // Ausgaenge setzen
    
  //lcdClearIfFlag(lcdClear);   //Abstand auf LCD anzeigen
  
  lcd.print("Abstand:             ");
  lcd.setCursor(9, 0);  
  lcd.print(abstand);
  delay(200);
  
  switch (state)
  {
    case LOCKED:
      if (oldState == UNLOCKED)
        ;//servo. TODO verriegeln
      digitalWrite(PIN_RED,HIGH);      //Rote LED an
      if (amBestimmungsort(abstand))
        digitalWrite(PIN_GREEN, blinky ? HIGH : LOW);     // set the LED on
      else
        digitalWrite(PIN_GREEN,LOW);      //gruene LED aus

      break;
      
    case UNLOCKED:
      if (oldState == LOCKED)
        ;//servo. TODO entriegeln
      digitalWrite(PIN_GREEN, HIGH);      // gruene LED an
    
      if (!amBestimmungsort(abstand))
      {
        digitalWrite(PIN_RED, blinky ? HIGH : LOW);       // set the LED on
      }
      else
        digitalWrite(PIN_RED,LOW);        // rote LED aus

      break;
      
    case OPEN:
      digitalWrite(PIN_GREEN,HIGH);      // gruene LED an
      digitalWrite(PIN_RED,LOW);        // rote LED aus
      lcd.clear();                // Display aus
      delay(100);
      break;
        
    default:
      //blinky = true;
      digitalWrite(PIN_RED, blinky ? HIGH : LOW);       //Beide LEDs Blinken      
      digitalWrite(PIN_GREEN, blinky ? HIGH : LOW);
    
      //lcd.clear();
      delay(100);
      lcd.print("Fehler!!!!");        // Ungueltiger Zustand: Fehlermeldung auf Bildschirm, Reset...
      lcd.setCursor(0, 1);
      lcd.print("Reset druecken");

      break;
  }
}

#endif


