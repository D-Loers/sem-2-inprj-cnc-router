#include <Arduino.h>
#include <Stepper.h>
#include "gcode.h"
#include "example.h"
#include "calculate_base.h"
//#include "logic.h"

// change this to the number of steps on your motor
#define STEPS 100

enum MovementType {
  DRAW,
  MOVE,
  CLOCKWISE,
  COUNTERWISE
};
enum MovementType typeMovement = MOVE;

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepperX(STEPS, 2, 3, 4, 5);
Stepper stepperY(STEPS, 6, 7, 8, 9);
Stepper stepperZ(STEPS, 10, 11, 12, 13);

void resetLinearLoop();


float currentX, currentY, currentZ = 0;
float nextX, nextY, nextZ;
int stepX, stepY, stepZ;
double smallStepX, smallStepY, smallStepZ;
double baseSmallX, baseSmallY, baseSmallZ;
int stepsTakenX, stepsTakenY, stepsTakenZ;
bool ongoing;


void setup() {
  Serial.begin(9600);
  // set the speed of the motor to 200 RPMs
  stepperX.setSpeed(200);
  stepperY.setSpeed(200);
  stepperZ.setSpeed(200);
}

void loop() {
  for (int i = 0; i < 29; i++) {
    String line = ("$" + exampleCode(i) + ";");
    //Serial.println(line);
    line.trim();
    String MState;
    int pause = 1;

    if ((line.indexOf("$") != -1) && (line.indexOf(";") != -1))
    {
      line.remove(line.indexOf("$"), 1); //removes the $
      while (line.indexOf("G") != -1){ //checks whether there is a G in the received line and, since there can be multiple G settings, keeps repeating until there are no more G's
        int GState = split(&line, "G");

        if (GState == 0)
        {
          typeMovement = MOVE;
          Serial.println("Movement type: MOVE");
        }
        else if (GState == 1)
        {
          typeMovement = DRAW;
          Serial.println("Movement type: DRAW");
        }
        // else if (GState == 2)
        // {
        //   typeMovement = CLOCKWISE;
        //   Serial.println("Movement type: CLOCKWISE");
        // }
        // else if (GState == 3)
        // {
        //   typeMovement = COUNTERWISE;
        //   Serial.println("Movement type: COUNTERWISE");
        // }
        else{
        setGState(GState);
        }
      }
      pause = (split(&line, "P") * 1000);
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
      Serial.println("The message did not seem to be sent properly.");
    }
    Serial.println("");
    
    if (nextX != 0) {
      stepX = ((nextX - currentX) / 0.0785398);
      currentX = nextX;
    }
    else {
      stepX = 0;
    }

    if (nextY != 0) {
      stepY = ((nextY - currentY) / 0.0785398);
      currentY = nextY;
    }
    else {
      stepY = 0;
    }

    if (nextZ != 0) {
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
        // case CLOCKWISE:
        // {
          
        //   break;
        // }
        // case COUNTERWISE:
        // {
          
        //   break;
        // }
      }
    }
    // Serial.println("All steps have been taken. Next line:");
    // Serial.println("----------------------------------------");
    delay(pause);
  }
  // Serial.println("Done");
  delay((1000*10));
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
