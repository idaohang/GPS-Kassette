#IFNDEF STATE_H
#DEFINE STATE_H

#define OPEN 0
#define LOCKED 1
#define UNLOCKED 2

char getState(char oldState, boolean deckeltaster, boolean taster, boolean bestimmungsort)
{
	char state;
	
	if (!deckeltaster)
		state = OPEN;

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

		else if (deckeltaster && taster)
			state = LOCKED;
	}

	return state;
}

#ENDIF