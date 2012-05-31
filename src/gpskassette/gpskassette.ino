#include <TinyGPS.h>
#include <Servo.h>
#include <LiquidCrystal.h>


// externer Interrupt: PIN 2
#define PIN_TASTER       9 // 2 (INTR) ist schon belegt durch Display

#define PIN_DECKELTASTER 8
 
#define MAX_ULONG 4294967295

// Flag wird von Taster-Interrupt gesetzt
static boolean taster = false;

static float long_Ziel = 48.154155;
static float lat_Ziel  = 11.555362;

Servo servo;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);    // initialize the LiquidCrystal library with the numbers of the interface pins



#include "state.h"
#include "gps.h"
#include "output.h"
#include "menu.h"


void lcdSetup(void){
  lcd.begin(20, 2);
  lcd.clear();
  delay(100);
}

void ISR_Taster(void)
{
  taster = true;
}

void setup()
{
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);

  pinMode(PIN_DECKELTASTER, INPUT);
  pinMode(PIN_TASTER, INPUT);

  lcdSetup();	//LCD-Display Setup 
  servo.attach(14);
  Serial.begin(9600);
  //attachInterrupt(PIN_TASTER, &ISR_Taster, RISING);
}

void loop()
{
  static char oldState = OPEN;
 
  boolean unlock = false;
  if (Serial.read() == ANFANG)
    menu(&unlock, &long_Ziel, &lat_Ziel);

  boolean deckeltaster = digitalRead(PIN_DECKELTASTER);
  taster = digitalRead(PIN_TASTER);
  int abstand = int(getDistance(long_Ziel, lat_Ziel));
  
  char state = getState(oldState, unlock, deckeltaster, taster, amBestimmungsort(abstand));
    
  outputs(state, oldState, abstand, taster);

  taster = false; // reset our flag  
  
  oldState = state;

}


