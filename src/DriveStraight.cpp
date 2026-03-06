#include "vex.h"
#include "Configure.h"
#include "AutoInclude.h"
#include "InertialHeading.h"

void DriveStraight(double TargetMovement, double maxSpeed) {
  double kP = 2.59;
  double kI = 0.001;
  double kD = 3.78;

  double kP_heading = 0.583;

  double error = 0;
  double prevError = 0;
  double integral = 0;
  double derivative = 0;

  double wheelDiameter = 3.25;
  double wheelCircumference = wheelDiameter * M_PI;

  double TargetHeading = BotFacing();

  LeftMotors.resetPosition();
  RightMotors.resetPosition();

  vex::timer t;
  t.reset();

  while (true) {
    UpdateOdom();
    double avgDegrees =
      (LeftMotors.position(vex::degrees) + RightMotors.position(vex::degrees)) / 2.0;

    double CurrentPosition =
      (avgDegrees / 360.0) * wheelCircumference;

    error = TargetMovement - CurrentPosition;

    double headingError = TargetHeading - BotFacing();
    // wrap to -180 to 180
    if (headingError > 180) headingError -= 360;
    if (headingError < -180) headingError += 360;

    double turnCorrection = headingError * kP_heading;

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

    if (fabs(error) < 10) {
    moveSpeed = clamp(moveSpeed, -25.0, 20.5);
    }

    double leftSpeed = moveSpeed + turnCorrection;
    double rightSpeed = moveSpeed - turnCorrection;

    leftSpeed = clamp(leftSpeed, -maxSpeed, maxSpeed);
    rightSpeed = clamp(rightSpeed, -maxSpeed, maxSpeed);

    LeftMotors.spin(vex::forward, leftSpeed, vex::percent);
    RightMotors.spin(vex::forward, rightSpeed, vex::percent);

    prevError = error;

    if (fabs(error) < 0.3 || t.time(vex::sec) > 3) {
      break;
    }

    vex::wait(20, vex::msec);
  }

  LeftMotors.stop(vex::coast);
  RightMotors.stop(vex::coast);
}