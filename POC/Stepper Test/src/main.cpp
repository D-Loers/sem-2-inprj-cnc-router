#include <Arduino.h>
#include <Stepper.h> // Add Stepper from Arduino to Project

#define STEPS 100

#define E1 5
#define M1 4
#define E2 6
#define M2 7

Stepper myStepper(STEPS, M1, M2, E1, E2);

void setup() {
  myStepper.setSpeed(40);
  Serial.begin(9600);
}

void loop() {
  Serial.println("Rotate");
  myStepper.step(STEPS);
  delay(500);
}