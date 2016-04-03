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

  show(88, 88, true, true); // Anzeigetafeltest: Alle Segmente mit Dezimalpunkten fuer 750 ms einschalten.
  delay(750);
  
  show(points_L, points_R, !prevPoint_L, prevPoint_L); // Anzeigetafeln fuer den Spielstart initialisieren
}


void loop() // Hauptprogramm
{
  currentMillis = millis();

  if (currentMillis - prevMillis > buttonSampling) //nur alle 10ms ausfuehren
  {
          switch(readButton_l()) // Knopf von Spieler Links
          {
            case 1: //Einfachklick: Punkt fuer den Spieler links
            
              tone(pinspeaker, 1600, 100); // Soundeffekt
              
              prevPoint_L = true;
              points_L = points_L + 1
              
              show(points_L, points_R, !prevPoint_L, prevPoint_L);
              break;
              
            case 2: // Doppelklick: ein Punkt abzug fuer den Spieler links
            
              tone(pinspeaker, 1000, 100); // Soundeffekt
              
              if(points_L != 0) show(--points_L, points_R, !prevPoint_L, prevPoint_L);
              else 
              {
                prevPoint_L = !prevPoint_L;
                show(points_L, points_R, !prevPoint_L, prevPoint_L);
              }
              break;
          }
      
          switch(readButton_r()) // Knopf von Spieler Rechts
          {
            case 1: //Klick
              tone(pinspeaker,1600,100);
              prevPoint_L = false;
              points_R = points_R + 1
              
              show(points_L, points_R, !prevPoint_L, prevPoint_L);
              break;
              
            case 2: // Doppelklick
            tone(pinspeaker,1000,100);
              if(points_R != 0) show(points_L, --points_R, !prevPoint_L, prevPoint_L);
              else 
              {
                prevPoint_L = !prevPoint_L;
                show(points_L, points_R, !prevPoint_L, prevPoint_L);
              }
              break;
          }



          if((punkte_l >= 11 or punkte_r >= 11) and abs(punkte_l - punkte_r) >= 2) // Sieg
          {
            tone(pinspeaker,500,250);
            delay(250);
            tone(pinspeaker,800,250);
            delay(250);
            tone(pinspeaker,1000,1000);
            delay(500);
            tone(pinspeaker,1200,1000);
            delay(450);
            noTone(pinspeaker);
            delay(50);
            tone(pinspeaker,1200,1000);
            delay(500);
            noTone(pinspeaker);
            delay(100);
            tone(pinspeaker,1600,1000);
            delay(500);
            noTone(pinspeaker);
            delay(100);   
            delay(3000);
            
            punkte_l = 0;
            punkte_r = 0;
            show(punkte_l, punkte_r, !letzter_pkt_l, letzter_pkt_l);
          }
          
          prevMillis = millis();
  }
}
