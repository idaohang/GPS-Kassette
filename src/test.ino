#include <TinyGPS.h>
#include <Servo.h>
#include <LiquidCrystal.h>

#include "gps.h"
#include "state.h"
#include "output.h"
#include "menue.h"

// externer Interrupt: PIN 2
#define PIN2_NUMBER 0

// TODO pin nr des taster
#define PIN_DECKELTASTER 0
 
#define MAX_ULONG 4294967295

// Flag wird von Taster-Interrupt gesetzt
static boolean taster = false;

static float long_Ziel, lat_Ziel;

Servo servo;

void ISR_Taster(void)
{
	taster = true;
}

void setup()
{
	lcdSetup();					//LCD-Display Setup 
	servo.attach(14);
	Serial.begin(9600);
	attachInterrupt(PIN2_NUMBER, &ISR_Taster, RISING);
}

void loop()
{
  static char oldState = OPEN;
  char state;
  int abstand;
  boolean unlock = false;
  boolean deckeltaster = false;

  deckeltaster = digitalRead(PIN_DECKELTASTER);
  abstand = int (getDistance(long_Ziel, lat_Ziel));
  state = getState(unlock, oldState, deckeltaster, taster, amBestimmungsort(abstand));
  
  ausgabe(state , abstand , taster);
  
  if (Serial.read() == ANFANG)
    menue(&unlock, &long_Ziel, &lat_Ziel);

  taster = false; // reset our interrupt flag  
  oldState = state;

}


