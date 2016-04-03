bool prev_high_l = false;
bool first_click_l = false;
bool second_click_l = false;
unsigned long prevclickMillis_l = 0;

bool prev_high_r = false;
bool first_click_r = false;
bool second_click_r = false;
unsigned long prevclickMillis_r = 0;

byte readButton_l()
{
  if(digitalRead(button_l) == HIGH) //gedrueckt
  {
    first_click_l = true; // Einfachklick
    if(millis() - prevclickMillis_l < click_pause) second_click_l = true; //Doppelklick
    prev_high_l = true;
  }
  
  else //nicht gedrueckt
  {
    if(prev_high_l == true) //Drop
    {         
      prevclickMillis_l = millis();
      prev_high_l = false;
    }
    
    else if(first_click_l == true and (millis() - prevclickMillis_l >= click_pause)) //Warten bis klick sequenz abgeschlossen
      {
        if(second_click_l == true) //Doppelklick
        {
          first_click_l = false;
          second_click_l = false;
          return 2;
        }
        else //Einfachklick
        {
          first_click_l = false;
          return 1;
        }
      }
  }
  return 0;
}



byte readButton_r()
{
  if(digitalRead(button_r) == HIGH) //gedrueckt
  {
    first_click_r = true; // Einfachklick
    if(millis() - prevclickMillis_r < click_pause) second_click_r = true; //Doppelklick
    prev_high_r = true;
  }
  
  else //nicht gedrueckt
  {
    if(prev_high_r == true) //Drop
    {         
      prevclickMillis_r = millis();
      prev_high_r = false;
    }
    
    else if(first_click_r == true and (millis() - prevclickMillis_r >= click_pause)) //Warten bis klick sequenz abgeschlossen
      {
        if(second_click_r == true) //Doppelklick
        {
          first_click_r = false;
          second_click_r = false;
          return 2;
        }
        else //Einfachklick
        {
          first_click_r = false;
          return 1;
        }
      }
  }
  return 0;
}
