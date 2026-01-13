/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       OdomAutonFunc.cpp                                         */
/*    Author:       Landon.kiely                                              */
/*    Created:      11/19/2025, 7:35:43 AM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/


#include "vex.h"
#include "Configure.h"
#include "OdomTracking.h"
#include "InertialHeading.h"

// creates a function to use multiple points in auton
struct Waypoint {
  double x;
  double y;
};

// Simple clamp
// gives a max value to limit speed
double Clamp(double value, double maxVal) {
  if (value > maxVal) return maxVal;
  if (value < -maxVal) return -maxVal;
  return value;
}

//Drive to a point with a curved path to avoid big turns
// this just goes to a point by adjusting motor speeds based on distance and angle to target
// won't end at any specific heading
void DriveToPointCurved(double targetX, double targetY, double maxSpeed) {
  double kP_drive = 2.2;
  double kP_turn = 3.0;

  while (true) {
    double dx = targetX - GetX();
    double dy = targetY - GetY();

    double distanceError = sqrt(dx * dx + dy * dy);
    if (distanceError < 0.75) break;

    double targetHeading = atan2(dy, dx) * 180.0 / M_PI;
    double headingError = targetHeading - GetHeading();

    while (headingError > 180) headingError -= 360;
    while (headingError < -180) headingError += 360;

    double drivePower = Clamp(distanceError * kP_drive, maxSpeed);
    double turnPower = Clamp(headingError * kP_turn, maxSpeed);

    double leftPower = drivePower + turnPower;
    double rightPower = drivePower - turnPower;

    LeftMotors.spin(vex::directionType::fwd, leftPower, vex::percentUnits::pct);
    RightMotors.spin(vex::directionType::fwd, rightPower, vex::percentUnits::pct);

    vex::task::sleep(20);
  }

  LeftMotors.stop(vex::brakeType::brake);
  RightMotors.stop(vex::brakeType::brake);
}   
// samething but moves backwards

void DriveToPointCurvedBackwards(double targetX, double targetY, double maxSpeed) {
  double kP_drive = 2.2;
  double kP_turn = 3.0;

  while (true) {
    double dx = targetX - GetX();
    double dy = targetY - GetY();

    double distanceError = sqrt(dx * dx + dy * dy);
    if (distanceError < 0.75) break;

    // Flip heading 180 for reverse driving
    double targetHeading = atan2(dy, dx) * 180.0 / M_PI + 180.0;
    if (targetHeading > 180) targetHeading -= 360;

    double headingError = targetHeading - GetHeading();

    while (headingError > 180) headingError -= 360;
    while (headingError < -180) headingError += 360;

    double drivePower = Clamp(distanceError * kP_drive, maxSpeed);
    double turnPower = Clamp(headingError * kP_turn, maxSpeed);

    double leftPower = -drivePower + turnPower;
    double rightPower = -drivePower - turnPower;

    LeftMotors.spin(vex::directionType::fwd, leftPower, vex::percentUnits::pct);
    RightMotors.spin(vex::directionType::fwd, rightPower, vex::percentUnits::pct);

    vex::task::sleep(20);
  }

  LeftMotors.stop(vex::brakeType::brake);
  RightMotors.stop(vex::brakeType::brake);
}

// ======================================
// Drive to a point while maintaining a specific heading (forward)
// ======================================

//This function drives to a point while while ending at a point at a specific heading

void DriveToPointAtHeading(double targetX, double targetY, double targetHeading, double maxSpeed) {
  double kP_drive = 2.2;
  double kP_turn = 3.0;

  while (true) {
    double dx = targetX - GetX();
    double dy = targetY - GetY();

    double distanceError = sqrt(dx * dx + dy * dy);
    if (distanceError < 0.75) break;

    double headingError = targetHeading - GetHeading();
    while (headingError > 180) headingError -= 360;
    while (headingError < -180) headingError += 360;

    double drivePower = Clamp(distanceError * kP_drive, maxSpeed);
    double turnPower = Clamp(headingError * kP_turn, maxSpeed);

    double leftPower = drivePower + turnPower;
    double rightPower = drivePower - turnPower;

    leftPower = Clamp(leftPower, maxSpeed);
    rightPower = Clamp(rightPower, maxSpeed);

    LeftMotors.spin(vex::directionType::fwd, leftPower, vex::percentUnits::pct);
    RightMotors.spin(vex::directionType::fwd, rightPower, vex::percentUnits::pct);

    vex::task::sleep(20);
  }

  LeftMotors.stop(vex::brakeType::brake);
  RightMotors.stop(vex::brakeType::brake);
}

// ======================================
// Drive through multiple waypoints
// ======================================

void DrivePath(Waypoint path[], int count, double maxSpeed) {
  for (int i = 0; i < count; i++) {
    DriveToPointCurved(path[i].x, path[i].y, maxSpeed);
  }
}

// ======================================
// Example usage
// ======================================
// Waypoint path[] = {
//   {12, 24},
//   {24, 36},
//   {48, 48}
// };
// DrivePath(path, 3, 70);