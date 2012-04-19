#IFNDEF OUTPUT_H
#DEFINE OUTPUT_H

void output(char state, int abstand, boolean taster)
{
	// Ausgaenge setzen
		
	switch (state)
	{
		case LOCKED:
			// rote LED
			if (amBestimmungsort(abstand))
				; // gruene LED (blinken)
			break;
			
		case UNLOCKED:
			// gruene LED
			if (!amBestimmungsort(abstand))
				; // rote LED (blinken)
			break;
			
		case OPEN:
			// gruene LED
			// Display aus
			break;
		
		default:
			// Ungueltiger Zustand: Fehlermeldung auf Bildschirm, Reset...
			// beide LED blinken...
			break;
	}
}

#ENDIF
