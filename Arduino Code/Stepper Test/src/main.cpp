#include <Arduino.h>
#include <Stepper.h>

#define STEPS 100
#define CHECK_INTERVAL 100
#define X_FORW_BUTTON 8
#define X_BACW_BUTTON 9
#define Y_FORW_BUTTON 10
#define Y_BACW_BUTTON 11
#define Z_FORW_BUTTON 12
#define Z_BACW_BUTTON 13

Stepper stepperX(STEPS, 2, 3, 4, 5);
Stepper stepperY(STEPS, 6, 7, 8, 9);
Stepper stepperZ(STEPS, 10, 11, 12, 13);

int tmrCheck;
int forwX, bacX, forwY, bacY, forwZ, bacZ;

void setup() {
  // put your setup code here, to run once:
  stepperX.setSpeed(200);
  stepperY.setSpeed(200);
  stepperZ.setSpeed(200);

  pinMode(X_FORW_BUTTON, INPUT_PULLUP);
  pinMode(X_BACW_BUTTON, INPUT_PULLUP);
  pinMode(Y_FORW_BUTTON, INPUT_PULLUP);
  pinMode(Y_BACW_BUTTON, INPUT_PULLUP);
  pinMode(Z_FORW_BUTTON, INPUT_PULLUP);
  pinMode(Z_BACW_BUTTON, INPUT_PULLUP);
}

void loop() {
  forwX = digitalRead(X_FORW_BUTTON);
  bacX = digitalRead(X_BACW_BUTTON);
  forwY = digitalRead(Y_FORW_BUTTON);
  bacY = digitalRead(Y_BACW_BUTTON);
  forwZ = digitalRead(Z_FORW_BUTTON);
  bacZ = digitalRead(Z_BACW_BUTTON);

  if (forwX > 0 && bacX == 0){
    stepperX.step(1);
  }

  if (bacX > 0 && forwX == 0){
    stepperX.step(-1);
  }
  
  if (forwY > 0 && bacY == 0){
    stepperX.step(1);
  }
  
  if (bacY > 0 && forwY == 0){
    stepperX.step(-1);
  }
  
  if (forwZ > 0 && bacZ == 0){
    stepperX.step(1);
  }
  
  if (bacZ > 0 && forwZ == 0){
    stepperX.step(-1);
  }
}