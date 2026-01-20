#include "vex.h"
#include "Configure.h"
#include "InertialHeading.h"

// ================================
// FULL 2D ODOMETRY
// IMEs = forward
// X Pod = sideways
// Inertial = heading
// ================================

// Global position
double globalX = 0.0;
double globalY = 0.0;
double globalHeading = 0.0;

// Last sensor values
double lastDriveDeg = 0.0;
double lastXPodDeg = 0.0;
double lastHeading = 0.0;

// ================================
// ROBOT CONSTANTS (TUNE THESE)
// ================================
const double DriveWheelDiameter = 3.25;
const double DriveWheelCircumference = DriveWheelDiameter * M_PI;

const double TrackingWheelDiameter = 2.0;
const double TrackingWheelCircumference = TrackingWheelDiameter * M_PI;

// Distance between left and right drive wheels (inches)
double trackWidth = 12.0;

// Front to back robot length (inches)
double robotLength = 14.0;

// X pod offset from robot center (inches)
// left is positive, right is negative
double xPodOffset = 5.5;

// ================================
// Reset odom
// ================================
void ResetOdom(double startX = 0, double startY = 0, double startHeading = 0) {
  globalX = startX;
  globalY = startY;
  globalHeading = startHeading;

  LeftMotors.resetPosition();
  RightMotors.resetPosition();
  Xpod.resetPosition();

  lastDriveDeg = 0.0;
  lastXPodDeg = 0.0;
  lastHeading = startHeading;
}

// ================================
// Update odom
// Call every 10 to 20 ms
// ================================
void UpdateOdom() {
  // ----- FORWARD TRACKING (IMEs) -----
  double leftDeg = LeftMotors.position(vex::rotationUnits::deg);
  double rightDeg = RightMotors.position(vex::rotationUnits::deg);
  double avgDeg = (leftDeg + rightDeg) / 2.0;

  double driveDeltaDeg = avgDeg - lastDriveDeg;
  lastDriveDeg = avgDeg;

  double forwardInches =
    (driveDeltaDeg / 360.0) * DriveWheelCircumference;

  // ----- SIDEWAYS TRACKING (X POD) -----
  double xPodDeg = Xpod.position(vex::rotationUnits::deg);
  double xDeltaDeg = xPodDeg - lastXPodDeg;
  lastXPodDeg = xPodDeg;

  double sidewaysInches =
    (xDeltaDeg / 360.0) * TrackingWheelCircumference;

  // ----- HEADING -----
  double newHeading = BotFacing();
  double deltaHeadingDeg = newHeading - lastHeading;
  double deltaHeadingRad = deltaHeadingDeg * M_PI / 180.0;

  // ----- ROTATION COMPENSATION -----
  // X pod moves during turns because it is offset
  double xRotationComp = deltaHeadingRad * xPodOffset;
  sidewaysInches -= xRotationComp;

  // ----- AVERAGE HEADING -----
  double avgHeadingRad =
    (newHeading + lastHeading) / 2.0 * M_PI / 180.0;

  // ----- GLOBAL POSITION UPDATE -----
  globalX += forwardInches * sin(avgHeadingRad)
           + sidewaysInches * cos(avgHeadingRad);

  globalY += forwardInches * cos(avgHeadingRad)
           - sidewaysInches * sin(avgHeadingRad);

  lastHeading = newHeading;
  globalHeading = newHeading;
}

// Accessors
double GetX() { return globalX; }
double GetY() { return globalY; }
double GetHeading() { return globalHeading; }

// Debug
void PrintOdom() {
  BigBrain.Screen.clearScreen();
  BigBrain.Screen.setCursor(1, 1);
  BigBrain.Screen.print("X: %.2f", globalX);
  BigBrain.Screen.newLine();
  BigBrain.Screen.print("Y: %.2f", globalY);
  BigBrain.Screen.newLine();
  BigBrain.Screen.print("H: %.2f", globalHeading);
}