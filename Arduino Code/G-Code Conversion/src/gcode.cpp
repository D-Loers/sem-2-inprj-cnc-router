#include "gcode.h"

void setGState(int GState){
    if(GState == 17){
      //XY plane
    }
    else if(GState == 18){
      //XZ plane
    }
    else if(GState == 19){
      //YZ plane
    }
    else if (GState == 20){
      //inches (MAKE SURE IT DOESN'T)
    }
    else if (GState == 21){
      //millimiters
    }
    else if(GState == 28){
      //Return Home
    }

    else if(GState == 90){
      //absolute mode

      //In absolute mode the positioning of the tool is always
      //from the absolute point or zero. So the command G01 X10 Y5
      //will take the tool to that exact point (10,5), no matter the previous position.
    }
    else if(GState == 91){
      //relative mode

      //In relative mode, the positioning of the tool is relative to the last point.
      //So if the machine is currently at point(10,10), the command G01 X10 Y5
      //will take the tool to point (20,15). This mode is also called “incremental mode”.
    }
}

void setMState(String MState){
    if(MState == "00"){
      //M00 – Program stop
    }
    if(MState == "02"){
      //M02 – End of program
    }
    if(MState == "03"){
      //M03 – Spindle ON – clockwise
    }
    if(MState == "04"){
      //M04 – Spindle ON – counterclockwise
    }
    if(MState == "05"){
      //M05 – Spindle stop
    }
    if(MState == "06"){
      //M06 – Tool change
    }
    if(MState == "08"){
      //M08 – Flood colant ON
    }
    if(MState == "09"){
      //M09 – Flood colant OFF 
    }
    if(MState == "30"){
      //M30 – End of program
    }
}

float split(String *line, String character){
    float newIntValue;
    if ((*line).indexOf(character) != -1) //checks whether there is a [character] in the received line
    {
      Serial.print(character + ": ");
      String newValue = *line;
      newValue.remove(0, (newValue.indexOf(character) + 1)); //removes everything up to (and including) the [character] from the line
      int space = newValue.indexOf(" "); //remembers where the next space in the string is
      newValue.remove(space); //removes everything after the space
      newIntValue = newValue.toFloat(); //converts the string to a float
      Serial.println(newIntValue);
      (*line).remove(0, (space + 2));
    }
    return newIntValue;
}