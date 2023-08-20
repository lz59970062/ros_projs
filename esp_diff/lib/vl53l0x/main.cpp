
#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor1(Wire1);
VL53L0X sensor2(Wire);

void setup()
{
  Serial.begin(115200);
  Wire.begin(41, 42, 400000); 
  Wire1.begin(17,18,  400000);
  Serial.println("Hello!");
  sensor1.init(true );
  sensor2.init(true );
  
  sensor2.setTimeout(500);
  sensor1.setTimeout(500);
  
  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor1.startContinuous();
  sensor2.startContinuous();
}

void loop()
{
  int t1=micros();
  int range1=sensor1.readRangeContinuousMillimeters();
  int range2=sensor2.readRangeContinuousMillimeters();
  Serial.printf("Range1 left: %d, Range2 right: %d\n",range1,range2);
  Serial.printf("Time: %d\n",micros()-t1);
  delay(60);
  
}
