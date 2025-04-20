#include <Arduino.h>
#include <Wire.h>




void setup() 
{
  Serial.begin(9600);
  Wire.begin();

}

void loop() 
{
  byte error, address;
  int nrDevices = 0;
  Serial.println("Scanning...");
  for(address = 1; address < 127; address++)
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if(address < 16)
      {
        Serial.print("0");
      }
      Serial.println(address, HEX);
      nrDevices++;
    }
    else if(error == 4)
    {
      Serial.print("Unexpected error at address 0x");
      if(address < 16)
      {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
  if(nrDevices == 0)
  {
    Serial.println("No devices found\n");
  }
  else
  {
    Serial.println("devices found\n");
  }
  delay(5000);
}
