#include <Arduino.h>
#include <Stepper.h>
#include "gcode.h"
#include "example.h"
#include "calculate_base.h"
#include "logic.h"
#include "serial_comm.h"

// change this to the number of steps on your motor
#define STEPS 100
#define MAGNET_X1 9 //PWM
#define BUTTON_Y 18
#define BUTTON_Z 19

enum MovementType {
  MOVE,
  DRAW,
  CLOCKWISE,
  COUNTERWISE,
  HOME
};
enum MovementType typeMovement = HOME;

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepperX(STEPS, 17, 4, 16, 5);
Stepper stepperY(STEPS, 15, 6, 14, 7);
Stepper stepperZ(STEPS, 10, 11, 12, 13);

void resetLinearLoop();


float currentX, currentY, currentZ = 0;
float nextX, nextY, nextZ;
int stepX, stepY, stepZ;
double smallStepX, smallStepY, smallStepZ;
double baseSmallX, baseSmallY, baseSmallZ;
int stepsTakenX, stepsTakenY, stepsTakenZ;
bool homeX, homeY, homeZ, ongoing, continueNextLine;

int pauseDelay = 1;
unsigned long prevMillis;


void setup() {
  Serial.begin(9600);
  // set the speed of the motor to 200 RPMs
  stepperX.setSpeed(200);
  stepperY.setSpeed(200);
  stepperZ.setSpeed(200);
  prevMillis = millis();

  pinMode(MAGNET_X1, INPUT_PULLUP);
  pinMode(BUTTON_Y, INPUT_PULLUP);
  pinMode(BUTTON_Z, INPUT_PULLUP);
}

void loop() {
  String line;
  if (Serial.available()){
    line = Serial.readStringUntil('\n');
    line.trim();
    Serial.println("ACK");

  // for (int i = 0; i < 92; i++) {
  //   String line = ("$" + exampleCode(i) + ";");
  //   //Serial.println(line);
  //   line.trim();
    String MState;
    

    if ((line.indexOf("$") != -1) && (line.indexOf(";") != -1))
    {
      line.remove(line.indexOf("$"), 1); //removes the $
      while (line.indexOf("G") != -1){ //checks whether there is a G in the received line and, since there can be multiple G settings, keeps repeating until there are no more G's
        int GState = split(&line, "G");

        if (GState == 0)
        {
          typeMovement = MOVE;
        }
        else if (GState == 1)
        {
          typeMovement = DRAW;
        }
        else if (GState == 2)
        {
          typeMovement = CLOCKWISE;
        }
        else if (GState == 3)
        {
          typeMovement = COUNTERWISE;
        }
        else if (GState == 90) 
        {
          typeMovement = HOME;
        }
        else{
        setGState(GState);
        }
      }
      pauseDelay = (split(&line, "P"));
      // split(&line, "M");
      // split(&line, "S");
      nextX = split(&line, "X");
      nextY = split(&line, "Y");
      nextZ = split(&line, "Z");
      // split(&line, "F");
      // split(&line, "I");
      // split(&line, "J");
    }
    else
    {
      //Serial.println("The message did not seem to be sent properly.");
    }
    //Serial.println("");
    
    if (nextX != 404) {
      stepX = ((nextX - currentX) / 0.0785398);
      currentX = nextX;
    }
    else {
      stepX = 0;
    }

    if (nextY != 404) {
      stepY = ((nextY - currentY) / 0.0785398);
      currentY = nextY;
    }
    else {
      stepY = 0;
    }

    if (nextZ != 404) {
      stepZ = ((nextZ - currentZ) / 0.0785398);
      currentZ = nextZ;
    }
    else {
      stepZ = 0;
    }

    //showSteps(stepX, stepY, stepZ);
    resetLinearLoop();

    int modeX = calculateX(stepX);
    int modeY = calculateY(stepY);

    calculateXY(modeX, modeY, stepX, stepY, &baseSmallX, &baseSmallY);
    calculateZ(stepZ, &baseSmallZ);

    while (ongoing) {
      switch (typeMovement)
      {
        case MOVE:
        {
          stepperX.step(stepX);
          stepperY.step(stepY);
          stepperZ.step(stepZ);
          ongoing = false;
          break;
        }
        case DRAW:
        {
          smallStepX += baseSmallX;
          smallStepY += baseSmallY;
          smallStepZ += baseSmallZ;
          //showSteps(smallStepx, smallStepY, smallStepZ);

          if (smallStepX > 1.00) {
            smallStepX--;
            stepperX.step(1);
            stepsTakenX++;
            //stepsTaken('X', stepsTakenX);
          }
          else if (smallStepX < -1.00) {
            smallStepX++;
            stepperX.step(-1);
            stepsTakenX--;
            //stepsTaken('X', stepsTakenX);
          }

          if (smallStepY > 1.00) {
            smallStepY--;
            stepperY.step(1);
            stepsTakenY++;
            //stepsTaken('Y', stepsTakenY);
          }
          else if (smallStepY < -1.00) {
            smallStepY++;
            stepperY.step(-1);
            stepsTakenY--;
            //stepsTaken('Y', stepsTakenY);
          }

          if (smallStepZ > 1.00) {
            smallStepZ--;
            stepperZ.step(1);
            stepsTakenZ++;
            //stepsTaken('Z', stepsTakenZ);
          }
          else if (smallStepZ < -1.00) {
            smallStepZ++;
            stepperZ.step(-1);
            stepsTakenZ--;
            //stepsTaken('Z', stepsTakenZ);
          }
          
          if ((stepsTakenX == stepX) && (stepsTakenY == stepY) && (stepsTakenZ == stepZ)) {
            ongoing = false;
          }

          break;
        }
        case CLOCKWISE:
        {
          
          break;
        }
        case COUNTERWISE:
        {
          
          break;
        }
        case HOME:
        {
          bool homeResetX = false;
          homeX = false;
          while (!homeX)
          {
            int magnetStateX1 = digitalRead(MAGNET_X1);
            if (magnetStateX1 == HIGH) {
              stepperX.step(1);
              homeResetX = true;
            }
            else if (homeResetX && magnetStateX1 == LOW) {
              homeX = true;
            }
            else {
              stepperX.step(-1);
            }
          }

          bool homeResetY = false;
          homeY = false;
          while (!homeY)
          {
            int buttonState = digitalRead(BUTTON_Y);
            if (buttonState == LOW) {
              stepperY.step(1);
              homeResetY = true;
            }
            else if (homeResetY && buttonState == HIGH) {
              homeY = true;
            }
            else {
              stepperY.step(-1);
            }
          }
          
          bool homeResetZ = false;
          homeZ = false;
          while (!homeZ)
          {
            int buttonState = digitalRead(BUTTON_Z);
            if (buttonState == LOW) {
              stepperZ.step(-1);
              homeResetZ = true;
            }
            else if (homeResetZ && buttonState == HIGH) {
              homeZ = true;
            }
            else {
              stepperZ.step(1);
            }
          }

          ongoing = false;
          typeMovement = MOVE;
          break;
        }
      }
    }
    //Serial.println("All steps have been taken. Next line:");
    //Serial.println("----------------------------------------");

    continueNextLine = false;
    while (!continueNextLine) {
      if (millis() - prevMillis >= (unsigned long)pauseDelay) {
        continueNextLine = true;
      }
    }
  }
  //Serial.println("Done");
}

void resetLinearLoop() {
  ongoing = true;
  stepsTakenX = 0;
  stepsTakenY = 0;
  stepsTakenZ = 0;
  baseSmallX = 0;
  baseSmallY = 0;
  baseSmallZ = 0;
  smallStepX = 0;
  smallStepY = 0;
  smallStepZ = 0;
}
