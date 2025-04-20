#include "logic.h"

void showSteps(int x, int y, int z) {
  Serial.print("X: ");
  Serial.println(x);
  Serial.print("Y: ");
  Serial.println(y);
  Serial.print("Z: ");
  Serial.println(z);
  Serial.println("");
}

void stepsTaken(char c, int i) {
  Serial.print("Steps taken by ");
  Serial.print(c);
  Serial.print(" : ");
  Serial.println(i);
}