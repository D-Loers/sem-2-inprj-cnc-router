#include <Arduino.h>
#include <Wire.h>

const int slaveAddress = 0x10;
const int ledPin = LED_BUILTIN;
void recieveEvent();

void setup() 
{
  Wire.begin(slaveAddress);
  Wire.onReceive(recieveEvent);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  delay(100);
}

void recieveEvent()
{
  while(Wire.available())
  {
    char command = Wire.read();
    if(command == '1')
    {
      Serial.println("turning led on");
      digitalWrite(ledPin, HIGH);
    }
    else if(command == '0')
    {
      Serial.println("turning led off");
      digitalWrite(ledPin, LOW);
    }
  }
}