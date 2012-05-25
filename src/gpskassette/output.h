#ifndef OUTPUT_H
#define OUTPUT_H

#define MAX_ULONG 4294967295

// TODO pin werte rausfinden
#define RED_PIN 7
#define GREEN_PIN 6

#define BLINK_DELAY 500

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);    // initialize the LiquidCrystal library with the numbers of the interface pins

void lcdSetup(void){
  lcd.begin(20, 2);
  lcd.clear();
  delay(100);
}

void outputs(char state, int abstand, boolean taster)
{

  static boolean blinky = 0;
  static unsigned long oldMils = 0;
  unsigned long mils = millis();
  if (oldMils > mils)
    mils = oldMils + MAX_ULONG;
  if ((mils - oldMils) >= BLINK_DELAY)
    blinky = !blinky;
  oldMils = mils;

  // Ausgaenge setzen
    
  lcd.clear();   //Abstand auf LCD anzeigen
  delay(100);
  lcd.print("Abstand: ");
  lcd.print(abstand);  
  
  switch (state)
  {
    case LOCKED:
      digitalWrite(RED_PIN,HIGH);      //Rote LED   an    
      if (amBestimmungsort(abstand))
        digitalWrite(GREEN_PIN, blinky);     // set the LED on
    else
      digitalWrite(GREEN_PIN,LOW);      //gruene LED aus
      break;
      
    case UNLOCKED:
      digitalWrite(GREEN_PIN,HIGH);      // gruene LED an
    
      if (!amBestimmungsort(abstand))
    {
        digitalWrite(RED_PIN, blinky);       // set the LED on
    }
    else
      digitalWrite(RED_PIN,LOW);        // rote LED aus                
      break;
      
    case OPEN:
      digitalWrite(GREEN_PIN,HIGH);      // gruene LED an
    digitalWrite(RED_PIN,LOW);        // rote LED aus
      lcd.clear();                // Display aus
    delay(100);            
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


