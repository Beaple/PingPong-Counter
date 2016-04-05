//Erfordert:  - points_L, points_R byte variabeln < 100, bool dp_LL, dp_LR, dp_RL, dp_RR
//Effekt:     - Zeigt die Zahl "points_L" auf der linken Seite der Anzeige an.
//            - Zeigt die Zahl "points_R" auf der rechten Seite der Anzeige an.
//            - Wenn "dp_LL" true ist wird der Dezimalpunkte auf der  ganz linken Seite der Anzeigetafel angezeigt.
//            - Wenn "dp_LR" true ist wird der Dezimalpunkte auf der mitte linken Seite der Anzeigetafel angezeigt.
//            - Wenn "dp_RL" true ist wird der Dezimalpunkte auf der mitte rechten Seite der Anzeigetafel angezeigt.
//            - Wenn "dp_RR" true ist wird der Dezimalpunkte auf der ganz rechten Seite der Anzeigetafel angezeigt.
void display(byte points_L, byte points_R, bool dp_LL, bool dp_LR, bool dp_RL, bool dp_RR)
{
  postNumber(points_R % 10, dp_RR); // 1ner rechts und Dezimalpunkt rechts
  postNumber(points_R / 10, dp_RL); // 10ner rechts und Dezimalpunkt rechts

  postNumber(points_L % 10, dp_LR); // 1ner links und Dezimalpunkt links
  postNumber(points_L / 10, dp_LL); // 10ner links und Dezimalpunkt links


  digitalWrite(pinSegmentLatch, LOW); // Register aufs Display schreiben
  digitalWrite(pinSegmentLatch, HIGH);
}


//Erfordert:  - byte number < 10, bool dp
//Effekt:     - schiebt die Zahl "number" auf den display treiber
//
//Segmentnamen:
//    -  A
//   / / F/B
//    -  G
//   / / E/C
//    -. D/DP
//
//Position im Register:
//DP B C D E G F A
// 8 7 6 5 4 3 2 1
void postNumber(byte number, boolean dp)
{
  byte segments;

  switch (number)
  {
    case 1: segments = B01100000; break; // Zahl "1" hat aktive segmente A und B, etc.
    case 2: segments = B01011101; break;
    case 3: segments = B01110101; break;
    case 4: segments = B01100110; break;
    case 5: segments = B00110111; break;
    case 6: segments = B00111111; break;
    case 7: segments = B01100001; break;
    case 8: segments = B01111111; break;
    case 9: segments = B01110111; break;
    case 0: segments = B01111011; break;
//    case ' ': segments = B00000000; break;
  }

  if (dp) segments = segments + B10000000; // Fuegt gegebenen falls den Dezimalpunkt hinzu

  for (byte x = 0 ; x < 8 ; x++) //Aufs register schieben
  {
    digitalWrite(pinSegmentClock, LOW);
    digitalWrite(pinSegmentData, segments & 1 << (7 - x));
    digitalWrite(pinSegmentClock, HIGH);
  }
}
