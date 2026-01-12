#include "vex.h"
#include "configure.h"
#include "odomTracking.h"
#include "InertialHeading.h"

// ======================================
// ODOM MOVEMENT FUNCTIONS
// Uses odomTracking.cpp values
// ======================================

struct Waypoint {
  double x;
  double y;
};

// Simple clamp

double Clamp(double value, double maxVal) {
  if (value > maxVal) return maxVal;
  if (value < -maxVal) return -maxVal;
  return value;
}

// ======================================
// Curved drive to a single point (forward)
// No stop to turn
// ======================================

void DriveToPointCurved(double targetX, double targetY, double maxSpeed = 70) {
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

// ======================================
// Curved drive to a single point (backward)
// ======================================

void DriveToPointCurvedBackwards(double targetX, double targetY, double maxSpeed = 70) {
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
// Drive through multiple waypoints
// ======================================

void DrivePath(Waypoint path[], int count, double maxSpeed = 70) {
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
// DrivePath(path, 3);