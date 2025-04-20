#ifndef GCODE_H
#define GCODE_H
#include <Arduino.h>

void setGState(int);
void setMState(String);
float split(String*, String);

#endif