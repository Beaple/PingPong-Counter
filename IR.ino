// weitere globale Variabeln

bool firstClick_L = false; // Einfachklick
bool firstClick_R = false; // Einfachklick
unsigned long prevClickMillis_L = 0; // Zeit nachdem loslassen des Knopfes
unsigned long prevClickMillis_R = 0; // Zeit nachdem loslassen des Knopfes

byte readIR()
{
   if (irrecv.decode(&results)) { //we have received an IR
      irrecv.resume(); //next value

      switch(results.value)
      {
        case 0x53A5A857: // Links
            firstClick_L = true; // mindestens Einfachklick
            if(millis() - prevClickMillis_L < maxDoubleclickPause) {
                firstClick_L = false;
                prevClickMillis_L = millis(); // Zeit merken
                return 2; // Doppelklick falls der klick unter der Wartezeit eines Doppelklickes erfolgt
            }
            prevClickMillis_L = millis(); // Zeit merken
            break;

        case 0x53A58877: // Rechts
            firstClick_R = true; // mindestens Einfachklick
            if(millis() - prevClickMillis_R < maxDoubleclickPause) {
                firstClick_R = false;
                prevClickMillis_R = millis(); // Zeit merken
                return 4; // Doppelklick falls der klick unter der Wartezeit eines Doppelklickes erfolgt
            }
            prevClickMillis_R = millis(); // Zeit merken
            break;
      }
  }

  if (firstClick_L == true and (millis() - prevClickMillis_L >= maxDoubleclickPause)) 
  {
      firstClick_L = false;

      return 1;
  }

  if (firstClick_R == true and (millis() - prevClickMillis_R >= maxDoubleclickPause)) 
  {
      firstClick_R = false;
      return 3;
  }
  return 0;
}
