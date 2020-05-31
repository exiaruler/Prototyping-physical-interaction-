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
 
rgb_lcd lcd;
 
const int colorR = 255;
const int colorG = 0;
const int colorB = 0;
//send IR protocol
const int ir_freq = 38;                 // 38k
unsigned char dtaSend[20];

const int pinRecv = 2;       // ir receiver connect to D2
//game system
int health=1; 
int ammo=1; 
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
                if (data == GES_FORWARD_FLAG) {
                } else {
                      IR.Send(dtaSend, 38);
                    Serial.println("send");
                }
                break;
           
        }
    }
    delay(100);

    
  //Gettting hit
    if (IR.IsDta()) {
    // get IR data
    lcd.clear();
        IR.Recv(dta); // receive data to dta
        health--;
  lcd.print("game over");
  break;
    }
    }
}

 
