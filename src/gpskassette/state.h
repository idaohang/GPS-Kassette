#ifndef STATE_H
#define STATE_H

#define OPEN 0
#define LOCKED 1
#define UNLOCKED 2

char getState(char oldState, boolean unlock, boolean deckeltaster, boolean taster, boolean bestimmungsort)
{
  char state= UNLOCKED;

  if (!deckeltaster)
    state = OPEN;
    
  else if (unlock)
    state = UNLOCKED;

  // Deckel ist zu
  else if (bestimmungsort)
  {
    if (oldState == OPEN)
      state = UNLOCKED;

    else if (taster)
    {
      if (oldState == LOCKED)
        state = UNLOCKED;

      else if (oldState == UNLOCKED)
        state = LOCKED;

    }
    else
      state = oldState;

  }
  else // Nicht am Bestimmungsort
  {
    if (oldState == LOCKED)    
      state = LOCKED;

    else if (taster) // && deckeltaster
      state = LOCKED;
  }

  return state;
}

#endif


