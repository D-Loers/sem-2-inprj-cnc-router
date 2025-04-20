#include "calculate_base.h"

int calculateX(int stepX) {
  int result = 0;
  if ((stepX < 10) && (stepX > -10)) {
    result = 10;
  }
  else if (((stepX >= 10) && (stepX < 100)) ||  ((stepX <= -10) && (stepX > -100))) {
    result = 100;
  }
  else if ((stepX >= 100) || (stepX <= -100)) {
    result = 1000;
  }
  return result;
}

int calculateY(int stepY) {
  int result = 0;
  if ((stepY < 10) && (stepY > -10)) {
    result = 10;
  }
  else if (((stepY >= 10) && (stepY < 100)) ||  ((stepY <= -10) && (stepY > -100))) {
    result = 100;
  }
  else if ((stepY >= 100) || (stepY <= -100)) {
    result = 1000;
  }
  return result;
}

void calculateXY(int modeX, int modeY, int stepX, int stepY, double *baseX, double *baseY) {
  if (modeX == 1000 || modeY == 1000) {
    *baseX = stepX / 1000.0;
    *baseY = stepY / 1000.0;
  }
  else if (modeX == 100 || modeY == 100) {
    *baseX = stepX / 100.0;
    *baseY = stepY / 100.0;
  }
  else if (modeX == 10 || modeY == 10) {
    *baseX = stepX / 10.0;
    *baseY = stepY / 10.0;
  }
}

void calculateZ(int stepZ, double *baseZ) {
  if ((stepZ < 10) && (stepZ > -10)) {
    *baseZ = stepZ / 10.0;
  }
  else if (((stepZ >= 10) && (stepZ < 100)) ||  ((stepZ <= -10) && (stepZ > -100))) {
    *baseZ = stepZ / 100.0;
  }
  else if ((stepZ >= 100) || (stepZ <= -100)) {
    *baseZ = stepZ / 1000.0;
  }
}