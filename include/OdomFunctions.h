#pragma once

struct Waypoint {
  double x;
  double y;
};

// Forward curved movement
void DriveToPointCurved(double targetX, double targetY, double maxSpeed = 70);

// Backward curved movement
void DriveToPointCurvedBackwards(double targetX, double targetY, double maxSpeed = 70);

// Waypoint path movement
void DrivePath(Waypoint path[], int count, double maxSpeed = 70);
