#include "vex.h"
#include "Configure.h"

void DriveStraight(double TargetMovement, double maxSpeed) {
  double kP = 3.0;
  double kI = 0.0;
  double kD = 1.93;

  double error = 0;
  double prevError = 0;
  double integral = 0;
  double derivative = 0;

  double wheelDiameter = 3.25;
  double wheelCircumference = wheelDiameter * M_PI;

  LeftMotors.resetPosition();
  RightMotors.resetPosition();

  vex::timer t;
  t.reset();

  while (true) {
    double avgDegrees =
      (LeftMotors.position(degrees) + RightMotors.position(degrees)) / 2.0;

    double CurrentPosition =
      (avgDegrees / 360.0) * wheelCircumference;

    error = TargetMovement - CurrentPosition;

    if (fabs(error) < 8)
      integral += error;
    else
      integral = 0;

    derivative = error - prevError;

    double moveSpeed = (kP * error) + (kI * integral) + (kD * derivative);

    if (moveSpeed > maxSpeed) moveSpeed = maxSpeed;
    if (moveSpeed < -maxSpeed) moveSpeed = -maxSpeed;

    // minimum power to overcome friction
    if (fabs(moveSpeed) < 8 && fabs(error) > 1.5) {
      moveSpeed = (moveSpeed > 0) ? 8 : -8;
    }

    LeftMotors.spin(vex::forward, moveSpeed, vex::percent);
    RightMotors.spin(vex::forward, moveSpeed, vex::percent);

    prevError = error;

    if (fabs(error) < 1.5 || t.time(vex::sec) > 3) {
      break;
    }

    vex::wait(20, vex::msec);
  }

  LeftMotors.stop(vex::brake);
  RightMotors.stop(vex::brake);
}