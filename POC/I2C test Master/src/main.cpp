#include <Arduino.h>
#include <Wire.h>

const int slaveAddress = 0x10;

void setup() 
{
  Serial.begin(9600);
  Wire.begin();
}

void loop() 
{
  Wire.beginTransmission(slaveAddress);
  Serial.println("sending 0");
  Wire.write('0');
  Wire.endTransmission();
  delay(1000);

  Wire.beginTransmission(slaveAddress);
  Serial.println("sending 1");
  Wire.write('1');
  Wire.endTransmission();
  delay(1000);
}