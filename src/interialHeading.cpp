#include "vex.h"

double BotFacing() {
  double sum = 0;
  int count = 0;

  if (InertialSensor1.installed()) {
    sum += InertialSensor1.rotation();
    count++;
  }
  if (InertialSensor2.installed()) {
    sum += InertialSensor2.rotation();
    count++;
  }

  if (count == 0) return 0;
  return sum / count;
}