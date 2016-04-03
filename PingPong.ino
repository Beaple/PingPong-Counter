
//Ein- und Ausgang Pins definieren
const byte segmentClock = 5;
const byte segmentLatch = 4;
const byte segmentData = 6;
const byte button_l = 2;
const byte button_r = 3;
const byte pinspeaker = 11;

//Globale Variabeln
byte punkte_l = 0;
byte punkte_r = 0;
bool letzter_pkt_l = true;

unsigned long currentMillis = 0;
unsigned long prevMillis = 0;

unsigned long sampling_rate = 20;
unsigned long click_pause = 200;

void setup() { // Initialisieren
  Serial.begin(9600);

  pinMode(segmentClock, OUTPUT); // Pins als Ausgaenge definieren
  pinMode(segmentData, OUTPUT);
  pinMode(segmentLatch, OUTPUT);
  pinMode(button_l, INPUT_PULLUP);
  pinMode(button_r, INPUT_PULLUP);

  digitalWrite(segmentClock, LOW);
  digitalWrite(segmentData, LOW);
  digitalWrite(segmentLatch, LOW);

  show(88, 88, true, true); //Displaytest
  delay(750);
  show(0, 0, !letzter_pkt_l, letzter_pkt_l);
}


void loop() {
  currentMillis = millis();

  if (currentMillis - prevMillis > sampling_rate) //nur alle 10ms ausfuehren
  {
          switch(readButton_l()) // Button_l
          {
            case 1: //Klick
             tone(pinspeaker,1600,100);
              letzter_pkt_l = true;
              show(++punkte_l, punkte_r, !letzter_pkt_l, letzter_pkt_l);
              break;
              
            case 2: // Doppelklick
              tone(pinspeaker,1000,100);
              if(punkte_l != 0) show(--punkte_l, punkte_r, !letzter_pkt_l, letzter_pkt_l);
              else 
              {
                letzter_pkt_l = !letzter_pkt_l;
                show(punkte_l, punkte_r, !letzter_pkt_l, letzter_pkt_l);
              }
          }
      
          switch(readButton_r()) // Button_r
          {
            case 1: //Klick
              tone(pinspeaker,1600,100);
              letzter_pkt_l = false;
              show(punkte_l, ++punkte_r, !letzter_pkt_l, letzter_pkt_l);
              break;
              
            case 2: // Doppelklick
            tone(pinspeaker,1000,100);
              if(punkte_r != 0) show(punkte_l, --punkte_r, !letzter_pkt_l, letzter_pkt_l);
              else 
              {
                letzter_pkt_l = !letzter_pkt_l;
                show(punkte_l, punkte_r, !letzter_pkt_l, letzter_pkt_l);
              }
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
