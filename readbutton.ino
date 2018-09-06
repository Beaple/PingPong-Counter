/*
// weitere globale Variabeln
bool prevHigh_L = false; // letzter status des linken Knopfes
bool firstClick_L = false; // Einfachklick
bool secondClick_L = false; // Doppelklick
unsigned long prevClickMillis_L = 0; // Zeit nachdem loslassen des Knopfes

// Returns: liest den pin "pinButton_L" aus und gibt folgende Werte zurueck:
// 0: Kein Klick
// 1: Einfachklick
// 2: Doppelklick
// Die Rueckgabe erfolgt erst wenn der Knopf losgelassen wird UND nachdem die Zeit eines potenziell folgenden Doppelklick abgewartet ist
byte readButton_L()
{
  if(digitalRead(pinButton_L) == HIGH) // gedrueckt
  {
    firstClick_L = true; // mindestens Einfachklick
    if(millis() - prevClickMillis_L < maxDoubleclickPause) secondClick_L = true; // Doppelklick falls der klick unter der Wartezeit eines Doppelklickes erfolgt
    
    prevHigh_L = true; // letzter Knopf status HIGH 
  }
  
  else // nicht gedrueckt
  {
    if(prevHigh_L == true) // Knopf losgelassen 
    {         
      prevClickMillis_L = millis(); // Zeit merken
      prevHigh_L = false;
    }
    
    else if(millis() - prevClickMillis_L >= maxDoubleclickPause) // Warten bis klick sequenz abgeschlossen
      {
        if(secondClick_L == true) // Doppelklick
        {
          firstClick_L = false; // flags zuruecksetzen
          secondClick_L = false;
          return 2;
        }
        
        if(firstClick_L == true)  // Einfachklick
        {
          firstClick_L = false; // flag zuruecksetzen
          return 1;
        }
      }
  }
  return 0;
}



// weitere globale Variabeln
bool prevHigh_R = false; // letzter status des linken Knopfes
bool firstClick_R = false; // Einfachklick
bool secondClick_R = false; // Doppelklick
unsigned long prevClickMillis_R = 0; // Zeit nachdem loslassen des Knopfes

//Returns: liest den pin "pinButton_R" aus und gibt folgende Werte zurueck:
// 0: Kein Klick
// 1: Einfachklick
// 2: Doppelklick
// Die Rueckgabe erfolgt erst wenn der Knopf losgelassen wird UND nachdem die Zeit eines potenziell folgenden Doppelklick abgewartet ist
byte readButton_R()
{
  if(digitalRead(pinButton_R) == HIGH) //gedrueckt
  {
    firstClick_R = true; // mindestens Einfachklick
    if(millis() - prevClickMillis_R < maxDoubleclickPause) secondClick_R = true; // Doppelklick falls der klick unter der Wartezeit eines Doppelklickes erfolgt
    prevHigh_R = true; // letzter Knopf status HIGH
  }
  
  else // nicht gedrueckt
  {
    if(prevHigh_R == true) // Knopf losgelassen 
    {         
      prevClickMillis_R = millis(); // Zeit merken
      prevHigh_R = false;
    }
    
    else if(millis() - prevClickMillis_R >= maxDoubleclickPause) // Warten bis klick sequenz abgeschlossen
      {
        if(secondClick_R == true) //Doppelklick
        {
          firstClick_R = false; // flags zuruecksetzen
          secondClick_R = false;
          return 2;
        }
        
        if(firstClick_R == true) //Einfachklick
        {
          firstClick_R = false; // flag zuruecksetzen
          return 1;
        }
      }
  }
  return 0;
}
*/
