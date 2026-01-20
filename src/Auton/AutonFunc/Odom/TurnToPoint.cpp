#include "vex.h"
#include "Configure.h"
#include "OdomTracking.h"
#include "InertialHeading.h"
#include "AngWrap.h"
#include <cmath>

// helper functions
double degToRad(double deg) {
  return deg * M_PI / 180.0;
}

double radToDeg(double rad) {
  return rad * 180.0 / M_PI;
}

void TurnToPointOdom(double targetX, double targetY, double maxSpeed, int timeout) {
  // PID values (you will tune these)
  double kP = 2.0;
  double kI = 0.0;
  double kD = 0.2;

  double error = 0;
  double prevError = 0;
  double integral = 0;
  double derivative = 0;

  vex::timer t;
  t.reset();

  while (t.time(msec) < timeout) {
    // make sure odom stays updated
    UpdateOdom();

    // calculate target angle
    double deltaX = targetX - globalX;
    double deltaY = targetY - globalY;
    double targetTheta = radToDeg(atan2(deltaY, deltaX));

    // calculate error
    error = angleWrap(targetTheta - globalTheta);

    // exit condition
    if (fabs(error) < 1.0) break;

    // PID math
    integral += error;
    derivative = error - prevError;
    prevError = error;

    double motorPower = (kP * error) + (kI * integral) + (kD * derivative);

    // clamp speed
    if (motorPower > maxSpeed) motorPower = maxSpeed;
    if (motorPower < -maxSpeed) motorPower = -maxSpeed;

    // apply turn
    LeftMotors.spin(forward, motorPower, pct);
    RightMotors.spin(forward, -motorPower, pct);

    vex::task::sleep(10);
  }

  // stop drivetrain
  LeftMotors.stop(brake);
  RightMotors.stop(brake);
}