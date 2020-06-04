#include "paj7620.h" //gesture controller 
#include <IRSendRev.h>      //IR emitter 
#define BIT_LEN         0
#define BIT_START_H     1
#define BIT_START_L     2
#define BIT_DATA_H      3
#define BIT_DATA_L      4
#define BIT_DATA_LEN    5
#define BIT_DATA        6
#include <Wire.h>
#include "rgb_lcd.h"
 #include <HCSR04.h> //ultrasonic distance sensor 
rgb_lcd lcd;
UltraSonicDistanceSensor distanceSensor(6, 7);
const int colorR = 255;
const int colorG = 0;
const int colorB = 0;
//send IR protocol
const int ir_freq = 38;                 // 38k
unsigned char dtaSend[20];

const int pinRecv = 2;       // ir receiver connect to D2
int MoPin = 5; //vibrator

//game system
int health=1; 
int ammo=1;
long randNumber;
double check = 300; 
    
//transmitted data
void dtaInit() {
    dtaSend[BIT_LEN]        = 11;      // all data that needs to be sent
    dtaSend[BIT_START_H]    = 179;      // the logic high duration of "Start"
    dtaSend[BIT_START_L]    = 90;     // the logic low duration of "Start"
    dtaSend[BIT_DATA_H]     = 11;     // the logic "long" duration in the communication
    dtaSend[BIT_DATA_L]     = 33;     // the logic "short" duration in the communication

    dtaSend[BIT_DATA_LEN]   =
        6;      // Number of data which will sent. If the number is other, you should increase or reduce dtaSend[BIT_DATA+x].

    dtaSend[BIT_DATA + 0]     = 128;      // data that will sent
    dtaSend[BIT_DATA + 1]     = 127;
    dtaSend[BIT_DATA + 2]     = 192;
    dtaSend[BIT_DATA + 3]     = 63;
    dtaSend[BIT_DATA + 4]     = 192;
    dtaSend[BIT_DATA + 5]     = 63;
}
void setup() {
    Serial.begin(115200);
    IR.Init(pinRecv);
    Serial.println("init over");
     dtaInit();
   pinMode( MoPin, OUTPUT );//vibrator
     paj7620Init(); //Gesture controller 
uint8_t error = 0;
//LCD
lcd.begin(16, 2);
 lcd.setRGB(colorR, colorG, colorB);
 

}
unsigned char dta[20];//dta array

void loop() {
uint8_t data = 0, data1 = 0, error;
    error = paj7620ReadReg(0x43, 1, &data);  
  //starting session declare button 
  
    //Game session
    while(health!=0){
       lcd.setCursor(1,0);
       lcd.print("Alive");
        lcd.setCursor(0,1);
       lcd.print("ready to fire");
       //gesture controller
      if (!error) {
        switch (data) {             
            case GES_UP_FLAG:
                delay(800);
                paj7620ReadReg(0x43, 1, &data);
                if (data == GES_FORWARD_FLAG&&ammo!=0) {
                } else {
                      //double distance = distanceSensor.measureDistanceCm();
                      
                      IR.Send(dtaSend, 38);
                      ammo--; 
                    Serial.println("send");
                      
                }
                break;
               
           
        }
    }
    delay(100);

     if(ammo==0){
     reload(); 
                }
  //Gettting hit
    if (IR.IsDta()) {
    // get IR data
    lcd.clear();
        IR.Recv(dta); // receive data to dta
        health--;
        alert(); 
  lcd.print("game over");
  break;
    }
    }
    //if button is pressed resets the game 
    while(health==0){
     
    }
}

void start(){
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

void reload(){
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

      ammo++; 
      
}
}
void alert(){
    digitalWrite(MoPin, HIGH);
    delay(1000);
 
    digitalWrite(MoPin, LOW);
    delay(1000);
}

void distance(){
  Serial.println(distanceSensor.measureDistanceCm());
    delay(500);
    
    double check = 300; 
    double distance = distanceSensor.measureDistanceCm();
    if (distance < check)
    {
      Serial.println("True"); 
    }
    else
    {
      Serial.println("False");
    }
}




 
