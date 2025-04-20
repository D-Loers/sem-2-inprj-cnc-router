#include <Arduino.h>
#include <Wire.h>
#include <DHT20.h>

#define MAIN_ADDR 0x10
#define REMOVE_DECIMALS(DECIMAL_VALUE) ((DECIMAL_VALUE) * 100)

DHT20 DHT;

void request_event();
uint16_t get_temp();

void setup()
{
  Wire.onRequest(request_event);
  Wire.begin(MAIN_ADDR);
  DHT.begin();
}

void loop()
{
}

void request_event()
{
  Wire.write(get_temp());
}

uint16_t get_temp()
{
  static uint16_t readingToUint16 = 0;

  if (!DHT.read())
  {
    float reading = DHT.getTemperature();
    readingToUint16 = REMOVE_DECIMALS(reading);
  }

  Serial.println(readingToUint16);

  return readingToUint16;
}