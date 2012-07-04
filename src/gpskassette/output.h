#ifndef OUTPUT_H
#define OUTPUT_H

#define GREEN_PIN 6
#define RED_PIN 7

#define ENTRIEGELUNG 0
#define VERRIEGELUNG 180

#define BLINK_DELAY 500

Servo servo;

void lcdSetup(void){
  lcd.begin(20, 2);
  lcd.clear();
  delay(100);
}

void outputs(char oldState, char state, int abstand, boolean taster)
{    
  static boolean blinky = 0;
  static unsigned long oldMils = 0;
  unsigned long mils = millis();  
  if ((mils - oldMils) >= BLINK_DELAY)
  {
    blinky = !blinky;
    oldMils = mils; // Bugfixed, but not tested
  }

  // Ausgaenge setzen
    
  //lcd.clear();   //Abstand auf LCD anzeigen
  //delay(100);
  static int oldAbstand = 0;
  if(abstand != oldAbstand)
  {
    lcd.setCursor(0,0);
    lcd.print("Abstand: ");
    lcd.print(abstand);
    lcd.print(" m            ");
    oldAbstand = abstand;
  }
  
  if (amBestimmungsort(abstand))      
    digitalWrite(GREEN_PIN, HIGH);       // set the LED on
  else    
    digitalWrite(GREEN_PIN, LOW);       // set the LED on
  
  switch (state)
  {
    case LOCKED:
      //servo. verriegeln
      if (oldState != LOCKED)
      {
        servo.write(VERRIEGELUNG);
        delay(800);
      }
      
      
      digitalWrite(RED_PIN, HIGH);      //Rote LED an

      break;
      
    case UNLOCKED:
      //servo. entriegeln
      if (oldState != OPEN && oldState != UNLOCKED)
      {
        servo.write(ENTRIEGELUNG);
        delay(800);
      }
      digitalWrite(RED_PIN, LOW);      //Rote LED an

      break;
      
    case OPEN:
      //servo. entriegeln
      if (oldState != OPEN && oldState != UNLOCKED)
      {
        servo.write(ENTRIEGELUNG);
        delay(800);
      }

      break;
        
    default:
      lcd.clear();
      delay(100);
      lcd.print("Fehler!!!!");        // Ungueltiger Zustand: Fehlermeldung auf Bildschirm, Reset...
      lcd.setCursor(0, 1);
      lcd.print("Reset druecken");

      digitalWrite(RED_PIN, blinky);       //Beide LEDs Blinken      
      digitalWrite(GREEN_PIN, blinky);
                
      break;
  }
}

#endif


