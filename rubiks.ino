/*
  Rubiks Cube Timer
  Built with the LiquidCrystal Library
  Author Conny Dahlgren conny@shoogle.se
*/

#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int switchPinA = 8;
const int switchPinB = 9;

int switchStateA = 0;
int switchStateB = 0;
int running = 0;
unsigned long oldTime = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.print("RubiksCube Timer");
}

void loop() {

  lcd.setCursor(0, 1);
  unsigned long currentTime = millis();
  
  switchStateA = digitalRead(switchPinA); 
  switchStateB = digitalRead(switchPinB);    
  
  unsigned long now = (currentTime - oldTime)/100;
  unsigned long minutes = (now/10)/60;
  unsigned long seconds = (now/10) - (minutes*60);
  unsigned long milliseconds = now - (((minutes*60)*10) + seconds*10 );

  if (running) {
    print_time(minutes, seconds, milliseconds);
  }
  // reset
  if (switchStateA && switchStateB)
  {
    if (running)
    {
      reset(now);
      running = 0;
    }
    else 
    {
      while(switchStateA && switchStateB)
      {
          switchStateA = digitalRead(switchPinA); 
          switchStateB = digitalRead(switchPinB); 
          lcd.setCursor(0,1);
          lcd.print("Release when ready");
      }
      running = 1;
      unsigned long currentTime = millis();
      lcd.setCursor(0,1);
      lcd.print("                  ");

      oldTime = currentTime;

    }
  }
}

void reset(unsigned long now) {
    clear_lcd(now);
    delay(1000);
    unsigned long currentTime = millis();
    oldTime = currentTime;
}

void clear_lcd(unsigned long now) {
  unsigned long minutes = (now/10)/60;
  unsigned long seconds = (now/10) - (minutes*60);
  unsigned long milliseconds = now - (((minutes*60)*10) + seconds*10 );
  lcd.setCursor(0,0);
  lcd.print("                 ");
  lcd.setCursor(0,0);
  print_time(minutes, seconds, milliseconds);
  delay(1000);  
  lcd.setCursor(0,1);
  lcd.print("Start when ready");
}

void print_time(unsigned long minutes, unsigned long seconds, unsigned long milliseconds) {
    if (minutes < 1) {
      lcd.print("0:");
    } else {
      lcd.print(minutes);
      lcd.print(":");
    }
    if (seconds < 10) {
      lcd.print("0");
    }
    lcd.print( seconds);
    lcd.print(":");
    lcd.print(milliseconds);
}
