#include <LiquidCrystal_I2C.h>
#include <Wire.h>

long randNumber;
LiquidCrystal_I2C lcd (0x27, 16, 2);
const int startButton = 4;
const int reloadButton = 3;
int health = 1;
int ammo =1;

void setup() {

  lcd.begin();
  lcd.backlight();
  randomSeed(analogRead(0));
  pinMode(startButton, INPUT);
  pinMode(reloadButton, INPUT);
  lcd.print("Press to Start");
}

void loop() {
    
  if(health = 1) {
  int buttonState1 = digitalRead(startButton);
  if (buttonState1 == HIGH) {
    lcd.clear();
    lcd.print("5");
    delay(1000);
    lcd.clear();
    lcd.print("4");
    delay(1000);
    lcd.clear();
    lcd.print("3");
    delay(1000);
    lcd.clear();
    lcd.print("2");
    delay(1000);
    lcd.clear();
    lcd.print("1");
    delay(1000);
    lcd.clear();
    lcd.print("Start");
    delay(1000);
    lcd.clear();
}
  
  int buttonState2 = digitalRead(reloadButton); // As we are using only 1 button, this is used as a trigger to test if the following codes work. Delete it and put the following code after where the player fires. something like:
                                                // if (ammo = 0){
                                                 // ...
                                                //}
  if(buttonState2 == HIGH){
    
    lcd.print("Reload time:");
    int randNumber = random(1,6);
    lcd.setCursor(13,0);
    lcd.print(randNumber);
    lcd.setCursor(0,1); 
    switch(randNumber){
      
      case 5:
      lcd.print(randNumber);
      delay(1000);
      randNumber--;
      lcd.clear();

      case 4:
      lcd.print(randNumber);
      delay(1000);
      randNumber--;
      lcd.clear();

      case 3:
      lcd.print(randNumber);
      delay(1000);
      randNumber--;
      lcd.clear();

      case 2:
      lcd.print(randNumber);
      delay(1000);
      randNumber--;
      lcd.clear();

      case 1:
      lcd.print(randNumber);
      delay(1000);
      lcd.clear();
      break;
      
      }
  }   

  
      
   
      
}

else{
  lcd.print("Game Over");
  delay(2000);
  lcd.clear();
  health = 1;
  ammo = 1;
  }
  
  
}
