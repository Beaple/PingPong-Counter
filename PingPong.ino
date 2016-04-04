//Ein- und Ausgang Pins definieren

const byte pinSegmentClock = 5; // Drei Ausgang-Pins fuer die Anzeigetafeln
const byte pinSegmentLatch = 4;
const byte pinSegmentData = 6;

const byte pinButton_L = 2; // Je ein Eingangs Pin fuer die Knoepfe
const byte pinButton_R = 3;

const byte pinSpeaker = 11; // ein Ausgangspin fuer den Piezo Lautsprecher


//Globale Variabeln

byte points_L = 0; // Punkte fuer beide Spieler
byte points_R = 0;
bool prevPoint_L = true; // Um zu bestimmen welcher Spieler das Anspiel hat

unsigned long currentMillis = 0; //zwei Zeit Variabeln
unsigned long prevMillis = 0;

unsigned long buttonSampling = 20; // Wartezeit bis zum erneuten Auslesen der Knoepfe in ms
unsigned long maxDoubleclickPause = 200; // maximale Zeit eines Doppelklick intervalls in ms



void setup()  // Initialisieren
{
  pinMode(pinSegmentClock, OUTPUT); // Drei Ausgangs Pins fuer die Anzeigetafeln (als Output)
  pinMode(pinSegmentData, OUTPUT);
  pinMode(pinSegmentLatch, OUTPUT);
  pinMode(pinButton_L, INPUT_PULLUP); // Je ein Eingangs Pin fuer die Knoepfe (als Input mit Pullup Widerstand)
  pinMode(pinButton_R, INPUT_PULLUP);

  digitalWrite(pinSegmentClock, LOW); // Die Ausgaenge fuer das Anzeigetafeln auf Low setzten
  digitalWrite(pinSegmentData, LOW);
  digitalWrite(pinSegmentLatch, LOW);

  display(88, 88, true, true); // Anzeigetafeltest: Alle Segmente mit Dezimalpunkten fuer 750 ms einschalten.
  delay(750);
  
  display(points_L, points_R, !prevPoint_L, prevPoint_L); // Anzeigetafeln fuer den Spielstart initialisieren
}


void loop() // Hauptprogramm
{
  currentMillis = millis();

  if (currentMillis - prevMillis > buttonSampling) //nur alle 20ms (buttonSampling) ausfuehren
  {
          switch(readButton_L()) // Knopf von Spieler Links
          {
            case 1: //Einfachklick: Punkt fuer den Spieler links
            
              tone(pinSpeaker, 1600, 100); // Soundeffekt
              
              points_L = points_L + 1; // Punkte fuer Spieler Links um 1 erhoehen
              prevPoint_L = true; // Spieler Links hat den letzten Punkt gemacht
              
            break;
              
              
            case 2: // Doppelklick: ein Punkt abzug fuer den Spieler links
            
              tone(pinSpeaker, 1000, 100); // Soundeffekt
              
              if(points_L > 0) points_L = points_L - 1; // Punkte fuer Spieler Links um 1 verringern (falls der Spieler ueberhaupt punkte hat)

              else prevPoint_L = !prevPoint_L; // Ansonsten Anspielwechsel

            break;
          }
          
          
      
          switch(readButton_R()) // Knopf von Spieler Rechts
          {
            case 1: //Einfachklick: Punkt fuer den Spieler rechts
            
              tone(pinSpeaker, 1600, 100); // Soundeffekt
              
              points_R = points_R + 1; // Punkte fuer Spieler Rechts um 1 erhoehen
              prevPoint_L = false; // Spieler Rechts hat den letzten Punkt gemacht
              
            break;
              
              
            case 2: // Doppelklick: ein Punkt abzug fuer den Spieler rechts
            
              tone(pinSpeaker, 1000, 100); // Soundeffekt
              
              if(points_R > 0) points_R = points_R - 1; // Punkte fuer Spieler Rechts um 1 verringern (falls der Spieler ueberhaupt punkte hat)
              
              else prevPoint_L = !prevPoint_L; // Ansonsten Anspielwechsel

            break;
          }
          
          display(points_L, points_R, !prevPoint_L, prevPoint_L); // Anzeige auf der Tafel


          if((points_L >= 11 or points_R >= 11) and abs(points_L - points_R) >= 2) // Sieg wenn ein Spieler mehr als 11 Punkte hat UND die Punktdifferenz midestens 2 ist
          {
            tone(pinSpeaker, 500, 250); // Soundeffekt
            delay(250);
            tone(pinSpeaker, 800, 250);
            delay(250);
            tone(pinSpeaker, 1000, 1000);
            delay(500);
            tone(pinSpeaker, 1200, 1000);
            delay(450);
            noTone(pinSpeaker);
            delay(50);
            tone(pinSpeaker, 1200, 1000);
            delay(500);
            noTone(pinSpeaker);
            delay(100);
            tone(pinSpeaker, 1600, 1000);
            delay(500);
            noTone(pinSpeaker);
            delay(100);
            
            delay(2000);
            
            points_L = 0; // Punkte fuer beide Spieler zurueck setzen
            points_R = 0;
            
            display(points_L, points_R, !prevPoint_L, prevPoint_L); // Anzeige auf der Tafel
          }
          
          prevMillis = millis(); // Zeit der letzten Ausfuehrung speichern
  }
}
