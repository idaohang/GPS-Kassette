
#include "state.h"
#include "output.h"
#include "gps.h"

// Flag wird von Taster-Interrupt gesetzt
static boolean taster = false;

// ISR fuer taster schreiben, worin das Flag taster gesetzt wird

void init()
{
}

void loop()
{
  static char oldState = OPEN;
  boolean deckeltaster = ;
  int abstand = getDistance();
  char state = getState(oldState, deckeltaster, taster, amBestimmungsort(abstand));
  taster = false; // reset interrupt flag
  
  output(state, abstand, taster);
  
  
  oldState = state;
}

