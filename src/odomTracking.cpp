#include "vex.h"
#include "Configure.h"
#include "InertialHeading.h"

// ================================
// SINGLE POD ODOMETRY TRACKING
// Forward / backward pod only
// ================================

// Global robot position
double globalX = 0.0;
double globalY = 0.0;
double globalHeading = 0.0;

// Last sensor values
double lastYPod = 0.0;
double lastHeading = 0.0;

// Robot constants
const double wheelDiameter = 2.0;
const double wheelCircumference = wheelDiameter * M_PI;

// ================================
// Reset odom state
// ================================
void ResetOdom(double startX = 0, double startY = 0, double startHeading = 0) {
  globalX = startX;
  globalY = startY;
  globalHeading = startHeading;

  lastYPod = Ypod.position(vex::rotationUnits::deg);
  lastHeading = startHeading;
}

// ================================
// Core odom update
// ================================
void UpdateOdom() {
  double yNow = Ypod.position(vex::rotationUnits::deg);
  double yDeltaDeg = yNow - lastYPod;
  lastYPod = yNow;

  double forwardInches = (yDeltaDeg / 360.0) * wheelCircumference;

  double newHeading = BotFacing();

  // Use average heading for better accuracy
  double avgHeadingRad =
    (newHeading + lastHeading) / 2.0 * M_PI / 180.0;

  // Update global position
  globalX += forwardInches * sin(avgHeadingRad);
  globalY += forwardInches * cos(avgHeadingRad);

  lastHeading = newHeading;
  globalHeading = newHeading;
}

// ================================
// Accessors
// ================================
double GetX() { return globalX; }
double GetY() { return globalY; }
double GetHeading() { return globalHeading; }

// ================================
// Debug output
// ================================
void PrintOdom() {
  BigBrain.Screen.clearScreen();
  BigBrain.Screen.setCursor(1, 1);
  BigBrain.Screen.print("X: %.2f", globalX);
  BigBrain.Screen.newLine();
  BigBrain.Screen.print("Y: %.2f", globalY);
  BigBrain.Screen.newLine();
  BigBrain.Screen.print("H: %.2f", globalHeading);
}