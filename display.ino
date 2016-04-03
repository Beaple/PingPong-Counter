void show(byte links, byte rechts, bool dplinks, bool dprechts) {
  
  postNumber(rechts % 10, dprechts); // 1ner rechts

  if (rechts / 10 == 0) postNumber(' ', dprechts); // 10ner rechts
  else postNumber(rechts / 10, dprechts);

  
  postNumber(links % 10, dplinks); // 1ner links
  
  if (links / 10 == 0) postNumber(' ', dplinks); // 10ner links
  else postNumber(links / 10, dplinks);


  //Register aufs Display schreiben
  digitalWrite(segmentLatch, LOW);
  digitalWrite(segmentLatch, HIGH);
}

//    -  A
//   / / F/B
//    -  G
//   / / E/C
//    -. D/DP

//DP B C D E G F A
// 8 7 6 5 4 3 2 1
void postNumber(byte number, boolean dp) {
  
  byte segments;

  switch (number)
  {
    case 1: segments = B01100000; break;
    case 2: segments = B01011101; break;
    case 3: segments = B01110101; break;
    case 4: segments = B01100110; break;
    case 5: segments = B00110111; break;
    case 6: segments = B00111111; break;
    case 7: segments = B01100001; break;
    case 8: segments = B01111111; break;
    case 9: segments = B01110111; break;
    case 0: segments = B01111011; break;
    case ' ': segments = B00000000; break;
  }

  if (dp) segments += B10000000;

  for (byte x = 0 ; x < 8 ; x++)
  {
    digitalWrite(segmentClock, LOW);
    digitalWrite(segmentData, segments & 1 << (7 - x));
    digitalWrite(segmentClock, HIGH);
  }
}
