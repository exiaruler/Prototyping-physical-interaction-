#include <HCSR04.h>

//int measure;

UltraSonicDistanceSensor distanceSensor(6, 7);  // Initialize sensor that uses digital pins 13 and 12.

void setup () {
    Serial.begin(9600);  // We initialize serial connection so that we could print values from sensor.
}

void loop () {
    // Every 500 miliseconds, do a measurement using the sensor and print the distance in centimeters.
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

void measure () {
  double distance = distanceSensor.measureDistanceCm();
  return distance;
}
