#include "vex.h"
#include "configure.h"
#include "InertialHeading.h"

// ================================
// ODOMETRY TRACKING PAGE
// X pod = sideways tracking
// Y pod = forward/backward tracking
// ================================

// Global robot position
//These are the starting locations so when the robot is placed on the field it is the orgin point (0,0)
double globalX = 0.0;
double globalY = 0.0;
double globalHeading = 0.0;

// Last sensor values
//The last values will start at zero but will update after any movement
double lastXPod = 0.0;
double lastYPod = 0.0;
double lastHeading = 0.0;

// Robot constants
//these are we adjust the odometry tracking because of physical locatioin of the pods and wheel size
const double wheelDiameter = 2;
const double wheelCircumference = wheelDiameter * M_PI;
const double xPodOffset = 5.5;
const double yPodOffset = 5.5;

// ================================
// Reset odom state
// ================================

//this will reset the orgin to the robots current position
void ResetOdom(double startX = 0, double startY = 0, double startHeading = 0) {
  globalX = startX;
  globalY = startY;
  globalHeading = startHeading;

  lastXPod = Xpod.position(vex::rotationUnits::deg);
  lastYPod = Ypod.position(vex::rotationUnits::deg);
  lastHeading = BotFacing();
}

// ================================
// Core odom update 
// ================================


// This function updates the odometry tracking based on pod movements
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
  // Convert heading to radians for trig functions
  double headingRad = newHeading * M_PI / 180.0;

  // Remove rotation component
  double headingDelta = (newHeading - lastHeading) * M_PI / 180.0;
  lastHeading = newHeading;


  //fabs is absolute value
  if (fabs(headingDelta) > 0.0001) {
    xInches -= headingDelta * xPodOffset;
    yInches -= headingDelta * yPodOffset;
  }
  // Update global position using rotation matrix and trigonometry
  globalX += xInches * cos(headingRad) - yInches * sin(headingRad);
  globalY += xInches * sin(headingRad) + yInches * cos(headingRad);

  globalHeading = newHeading;
}

//this just setups returns for auton functions
double GetX() { return globalX; }
double GetY() { return globalY; }
double GetHeading() { return globalHeading; }

// used for debugging
void PrintOdom() {
  BigBrain.Screen.clearScreen();
  BigBrain.Screen.setCursor(1, 1);
  BigBrain.Screen.print("X: %.2f", globalX);
  BigBrain.Screen.newLine();
  BigBrain.Screen.print("Y: %.2f", globalY);
  BigBrain.Screen.newLine();
  BigBrain.Screen.print("H: %.2f", globalHeading);
}