#include <TinyGPS.h>
#include <Servo.h>
#include <LiquidCrystal.h>

#include "gps.h"
#include "state.h"
#include "output.h"
#include "menu.h"

#define PIN_DECKELTASTER 8
#define PIN_TASTER 9

static float long_Ziel = 11.554054, lat_Ziel = 48.153873;

void setup()
{
  lcdSetup();	//LC-Display Setup 
  
  servo.attach(14);
  
  Serial.begin(4800);
  
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  
  pinMode(PIN_DECKELTASTER, INPUT);
  pinMode(PIN_TASTER, INPUT);
}

void loop()
{
  static char oldState = OPEN;
  static float abstand;
  boolean unlock = false; 
  
  unsigned long milis;
  
  static boolean taster = false;
  boolean tasterRising = false;
  boolean tasterFalling = false;   
    
  boolean deckeltaster = !digitalRead(PIN_DECKELTASTER); // Taster Low-aktiv
  
  // taster-Variablen sind alle einfach lokal, werden also automatisch zurückgesetzt.
  if (!digitalRead(PIN_TASTER)) // Taster Low-aktiv
  {
    if (!taster)
      tasterRising = true;
      
    taster = true;
  }
  else
  {
    if (taster)
      tasterFalling = true;
      
    taster = false;
  }

  // Menue starten, wenn Taster 2 s gedrueckt bleibt.
  if (tasterRising)
  {
    milis = millis();
  }
  else if (taster)
  {
    if(millis() - milis >= 2000)
    {      
      menu(&unlock, &long_Ziel, &lat_Ziel);
      // menu is blocking
    }
  }
 
  abstand = getDistance(lat_Ziel, long_Ziel, abstand);
  abstand = abstand + .00001;  
  char state = getState(oldState, unlock, deckeltaster, tasterFalling, amBestimmungsort(abstand));

  outputs(oldState, state , int(abstand), taster);


  // Ende der Schleife:
  
  oldState = state;

}


