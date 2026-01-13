#include "vex.h"
#include "Configure.h"

void DriveStraight(double TargetMovement, double maxSpeed) {
  double kP = 0.6;
  double kI = 0.002;
  double kD = 0.4;
  double error;
  double prevError = 0;
  double integral = 0;
  double derivative; 
  
  LeftMotors.resetPosition();
  RightMotors.resetPosition();
  
  vex::timer t;
  t.reset();   
  
  while (true) {
    double CurrentPosition = (LeftMotors.position(degrees) + RightMotors.position(degrees))*3.25 / 2;
    error = TargetMovement - CurrentPosition; 
    
    if (fabs(error) < 15)
      integral += error;
    else
      integral = 0;
    derivative = error - prevError;
    
    double MovementSpeed = (kP * error) + (kI * integral) + (kD * derivative);
    
    if (MovementSpeed > maxSpeed) MovementSpeed = maxSpeed;
    if (MovementSpeed < -maxSpeed) MovementSpeed = -maxSpeed;
    
    LeftMotors.spin(vex::forward, MovementSpeed, vex::percent);
    RightMotors.spin(vex::forward, MovementSpeed, vex::percent);
    
    prevError = error;
    
    if ((fabs(error) < 1 && fabs(derivative) < 0.5) || t.time(vex::sec) > 3) {
      break;
    }
  
    vex::wait(20, vex::msec);
  }
  
  LeftMotors.stop(vex::brake);
  RightMotors.stop(vex::brake);
}