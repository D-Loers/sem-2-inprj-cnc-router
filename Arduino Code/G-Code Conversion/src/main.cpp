#include <Arduino.h>
#include "gcode.h"

enum MovementType
{
  RAPID,
  LINEAR,
  CLOCKWISE,
  COUNTERWISE
};
enum MovementType typeMovement = RAPID;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // String line = ("$G01 X247.951560 Y11.817060;");
  // String line = "$G02 X10 Y-10 I0 J-10;";
  // String line = ("$G17 G64 P0.001 M3 S3000;");
  // String line = ("$G17 G64 G01;");
  String line = ("$F127.0;");
  line.trim();
  String MState;

  if ((line.indexOf("$") != -1) && (line.indexOf(";") != -1))
  {
    line.remove(line.indexOf("$"), 1); //removes the $
    while (line.indexOf("G") != -1){ //checks whether there is a G in the received line and, since there can be multiple G settings, keeps repeating until there are no more G's
      int GState = split(&line, "G");

      if (GState == 0)
      {
        typeMovement = RAPID;
      }
      else if (GState == 1)
      {
        typeMovement = LINEAR;
      }
      else if (GState == 2)
      {
        typeMovement = CLOCKWISE;
      }
      else if (GState == 3)
      {
        typeMovement = COUNTERWISE;
      }
      else{
      setGState(GState);
      }
    }
    split(&line, "P");
    split(&line, "M");
    split(&line, "S");
    split(&line, "X");
    split(&line, "Y");
    split(&line, "Z");
    split(&line, "F");
    split(&line, "I");
    split(&line, "J");

    switch (typeMovement)
    {
    case RAPID:
    {
      Serial.println("Movement type: RAPID");
      break;
    }
    case LINEAR:
    {
      Serial.println("Movement type: LINEAR");
      break;
    }
    case CLOCKWISE:
    {
      Serial.println("Movement type: CLOCKWISE");
      break;
    }
    case COUNTERWISE:
    {
      Serial.println("Movement type: COUNTERWISE");
      break;
    }
    }
  }
  else
  {
    Serial.println("The message did not seem to be sent properly.");
   }

  delay(100000);
}