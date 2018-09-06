#include <IRremote.h> //include the library

//Ein- und Ausgang Pins definieren

const byte pinSegmentClock = 5; // Drei Ausgang-Pins fuer die Anzeigetafeln
const byte pinSegmentLatch = 4;
const byte pinSegmentData = 6;

const byte pinButton_L = 2; // Je ein Eingangs Pin fuer die Knoepfe
const byte pinButton_R = 3;

const byte pinSpeaker = 11; // ein Ausgangspin fuer den Piezo Lautsprecher

const byte pinIR = 12; // pin for receiving IR signals

//Globale Variabeln

byte points_L = 0; // Punkte fuer beide Spieler
byte points_R = 0;
bool prevPoint_L = true; // Um zu bestimmen welcher Spieler das Anspiel hat
bool win21 = false; // Siegesbedingung 21 Punkte
bool seitenwechsel_happend = false; // Damit der Seitenwechsel nur einmal passieren kann

unsigned long currentMillis = 0; //zwei Zeit Variabeln
unsigned long prevMillis = 0;

unsigned long buttonSampling = 20; // Wartezeit bis zum erneuten Auslesen der Knoepfe in ms
unsigned long maxDoubleclickPause = 300; // maximale Zeit eines Doppelklick intervalls in ms

IRrecv irrecv(pinIR); //create a new instance of receiver
decode_results results;


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

  display(88, 88, true, true, true, true); // Anzeigetafeltest: Alle Segmente mit Dezimalpunkten fuer 750 ms einschalten.
  delay(750);
  
  display(points_L, points_R, !prevPoint_L, !prevPoint_L and win21, prevPoint_L and win21, prevPoint_L); // Anzeigetafeln fuer den Spielstart initialisieren

  irrecv.enableIRIn(); //start the receiver

 randomSeed(analogRead(0));

}


void loop() // Hauptprogramm
{
          currentMillis = millis();

          switch(readIR()) // Knopf von Spieler Links
          {
            case 1: //Einfachklick: Punkt fuer den Spieler links
            
              tone(pinSpeaker, 1600, 100); // Soundeffekt
              
              points_L = points_L + 1; // Punkte fuer Spieler Links um 1 erhoehen
              prevPoint_L = true; // Spieler Links hat den letzten Punkt gemacht
              
            break;
              
              
            case 2: // Doppelklick: ein Punkt abzug fuer den Spieler links
            
              tone(pinSpeaker, 1000, 100); // Soundeffekt
              
              if(points_L > 0) points_L = points_L - 1; // Punkte fuer Spieler Links um 1 verringern (falls der Spieler ueberhaupt punkte hat)

              else if(points_R == 0) {// Ansonsten wenn beide Spieler 0 Punkte haben:
                if (prevPoint_L) prevPoint_L = !prevPoint_L; // Anpielwechsel
                else {
                  prevPoint_L = !prevPoint_L; //Anspielwechsel
                  win21 = !win21; // Auf 21 spielen
                }
              }
            break;

            case 3: //Einfachklick: Punkt fuer den Spieler rechts
            
              tone(pinSpeaker, 1600, 100); // Soundeffekt
              
              points_R = points_R + 1; // Punkte fuer Spieler Rechts um 1 erhoehen
              prevPoint_L = false; // Spieler Rechts hat den letzten Punkt gemacht
              
            break;
              
              
            case 4: // Doppelklick: ein Punkt abzug fuer den Spieler rechts
            
              tone(pinSpeaker, 1000, 100); // Soundeffekt
              
              if(points_R > 0) points_R = points_R - 1; // Punkte fuer Spieler Rechts um 1 verringern (falls der Spieler ueberhaupt punkte hat)
              
              else if(points_L == 0) { // Ansonsten wenn beide Spieler 0 Punkte haben:
                if (prevPoint_L) prevPoint_L = !prevPoint_L; // Anpielwechsel
                else {
                  prevPoint_L = !prevPoint_L; //Anspielwechsel
                  win21 = !win21; // Auf 21 spielen
                }
              }
            break;
          }
          
          display(points_L, points_R, !prevPoint_L, !prevPoint_L and win21, prevPoint_L and win21, prevPoint_L); // Anzeige auf der Tafel

          if(win21 and (points_L == 10 or points_R == 10) and !seitenwechsel_happend) //Seitenwechsel
          {
            delay(200); // Soundeffekt
            tone(pinSpeaker, 1600, 100);
            delay(750);
            
            byte points_temp = points_L; //Punkte und Anspiel Tauschen
            points_L = points_R;
            points_R = points_temp;
            prevPoint_L = !prevPoint_L;
			seitenwechsel_happend = true;
          }

          if((points_L >= (11 + win21 * 10 ) or points_R >= (11 + win21 * 10 )) and abs(points_L - points_R) >= 2) // Sieg wenn ein Spieler mehr als 11/21 Punkte hat UND die Punktdifferenz midestens 2 ist
          {
            if (random(100) < 10) {
              pirates(); // Soundeffekt
            }
            else {
              victorySound();
            }
            delay(2000);
            
            points_L = 0; // Punkte fuer beide Spieler zurueck setzen
            points_R = 0;
            
            display(points_L, points_R, !prevPoint_L, !prevPoint_L and win21, prevPoint_L and win21, prevPoint_L); // Anzeige auf der Tafel
          }
          
          prevMillis = millis(); // Zeit der letzten Ausfuehrung speichern

}
