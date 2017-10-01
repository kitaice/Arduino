/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>
#include "Adafruit_VL53L0X.h"
Adafruit_VL53L0X lox = Adafruit_VL53L0X();
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int stt =0;
void setup() {
  pinMode(12, OUTPUT);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  //Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power 
  //Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
}
void ceju(){
  VL53L0X_RangingMeasurementData_t measure;
  Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    if(measure.RangeMilliMeter<=1200) { 
      if(stt==0){
        Serial.print("Height (mm): "); 
        Serial.println(measure.RangeMilliMeter);
      } else {
          int distance =measure.RangeMilliMeter;
          if(distance>=750){
            digitalWrite(12, HIGH);
            delay(1000);
            digitalWrite(12, LOW);
            delay(1000);
          } else if (distance<750 || distance>=400){
            digitalWrite(12, HIGH);
            delay(500);
            digitalWrite(12, LOW);
            delay(500);
          } else if (distance<400 || distance>=200){
            digitalWrite(12, HIGH);
            delay(250);
            digitalWrite(12, LOW);
            delay(250);
          } else {
            digitalWrite(12, HIGH);
            delay(150);
            digitalWrite(12, LOW);
            delay(150);
          }
          Serial.print("Distance (mm): "); 
          Serial.println(measure.RangeMilliMeter);
      }
    } else{
      Serial.println(" safe ");
    }   
  } else {
    Serial.println(" out of range ");
  }
  //delay(1000);  
}
void loop() {
  /*for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }*/ 
  if(stt==0){
    Serial.println("start running and detect height");
    ceju();
    for (pos = 0; pos <=45 ; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    delay(1000);
    for (pos = 45; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    Serial.println("height detection finished");
    stt = 1;
  } else {
    ceju();  
  }
 // myservo.write(45);
}

