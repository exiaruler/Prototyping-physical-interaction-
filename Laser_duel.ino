void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

void timer(){
   
}

void trigger(){
  //use the sensor 
   if(buttonState==HIGH&&count!=0){
     digitalWrite(LED, HIGH);
      count--;
      delay(500);
    }else
        digitalWrite(LED, LOW);
    lcd.print("Engaged");
      lcd.setCursor(0,1);
      lcd.print("Counts left ");
    lcd.print(count);
  
    //When there no ammmo
         if(buttonState==HIGH&&count==0){
           lcd.clear();
           lcd.print("Out of counts");
     delay(1000);
           lcd.clear();                           
    }
}
