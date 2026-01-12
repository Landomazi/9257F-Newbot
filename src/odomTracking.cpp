#include "vex.h"
#include "configure.h"
#include "InertialHeading.h"

// ================================
// ODOMETRY TRACKING PAGE (2 POD SETUP)
// X pod = sideways tracking
// Y pod = forward tracking
// ================================

// Global robot position

double globalX = 0.0;
double globalY = 0.0;
double globalHeading = 0.0;

// Last sensor values

double lastXPod = 0.0;
double lastYPod = 0.0;
double lastHeading = 0.0;

// Robot constants

const double wheelDiameter = 2.75;
const double wheelCircumference = wheelDiameter * M_PI;

// Distance from center of robot to pods (in inches)
const double xPodOffset = 5.5;
const double yPodOffset = 5.5;

// ================================
// Reset odom state
// ================================

void ResetOdom(double startX = 0, double startY = 0, double startHeading = 0) {
  globalX = startX;
  globalY = startY;
  globalHeading = startHeading;

  lastXPod = Xpod.position(vex::rotationUnits::deg);
  lastYPod = Ypod.position(vex::rotationUnits::deg);
  lastHeading = BotFacing();
}

// ================================
// Core odom update (2 tracking wheels)
// ================================

void UpdateOdom() {
  double xNow = Xpod.position(vex::rotationUnits::deg);
  double yNow = Ypod.position(vex::rotationUnits::deg);

  double xDeltaDeg = xNow - lastXPod;
  double yDeltaDeg = yNow - lastYPod;

  lastXPod = xNow;
  lastYPod = yNow;

  double xInches = (xDeltaDeg / 360.0) * wheelCircumference;
  double yInches = (yDeltaDeg / 360.0) * wheelCircumference;

  double newHeading = BotFacing();
  double headingRad = newHeading * M_PI / 180.0;

  // Remove rotation component
  double headingDelta = (newHeading - lastHeading) * M_PI / 180.0;
  lastHeading = newHeading;

  if (fabs(headingDelta) > 0.0001) {
    xInches -= headingDelta * xPodOffset;
    yInches -= headingDelta * yPodOffset;
  }

  globalX += xInches * cos(headingRad) - yInches * sin(headingRad);
  globalY += xInches * sin(headingRad) + yInches * cos(headingRad);

  globalHeading = newHeading;
}

double GetX() { return globalX; }
double GetY() { return globalY; }
double GetHeading() { return globalHeading; }

void PrintOdom() {
  BigBrain.Screen.clearScreen();
  BigBrain.Screen.setCursor(1, 1);
  BigBrain.Screen.print("X: %.2f", globalX);
  BigBrain.Screen.newLine();
  BigBrain.Screen.print("Y: %.2f", globalY);
  BigBrain.Screen.newLine();
  BigBrain.Screen.print("H: %.2f", globalHeading);
}