#include "vex.h"
#include <cmath>

namespace {
double wrap180(double angleDeg) {
  while (angleDeg > 180.0) angleDeg -= 360.0;
  while (angleDeg < -180.0) angleDeg += 360.0;
  return angleDeg;
}
}

double BotFacing() {
  const bool has1 = InertialSensor1.installed();
  const bool has2 = InertialSensor2.installed();

  if (!has1 && !has2) return 0.0;
  if (has1 && !has2) return InertialSensor1.heading(vex::degrees);
  if (!has1 && has2) return InertialSensor2.heading(vex::degrees);

  double h1 = InertialSensor1.heading(vex::degrees);
  double h2 = InertialSensor2.heading(vex::degrees);

  // If IMUs disagree strongly (mounting mismatch or bad reading), prefer sensor 1.
  if (fabs(wrap180(h1 - h2)) > 25.0) {
    return h1;
  }

  // Circular mean for normal case across the 0/360 seam.
  double h1Rad = h1 * M_PI / 180.0;
  double h2Rad = h2 * M_PI / 180.0;
  double sumSin = sin(h1Rad) + sin(h2Rad);
  double sumCos = cos(h1Rad) + cos(h2Rad);
  double averageHeadingDeg = atan2(sumSin, sumCos) * 180.0 / M_PI;
  if (averageHeadingDeg < 0.0) averageHeadingDeg += 360.0;
  return averageHeadingDeg;
}
