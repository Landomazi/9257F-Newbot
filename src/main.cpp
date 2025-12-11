/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Landon.kiely                                              */
/*    Created:      11/19/2025, 7:35:43 AM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "configure.h"
#include "autoselector.h"
#include "autonRoutes.h"
#include "autonFunctions.h"

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  leftMotors.resetPosition();
  rightMotors.resetPosition();
  TopIntake.resetPosition();
  BottomIntake.resetPosition();
  TopIntake.setVelocity(100, vex::percent);
  BottomIntake.setVelocity(100, vex::percent);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous() {
  if (selectedAutonMode == SKILLS) {
    autonomousSkills();
  } else if (selectedWinPoint == WINPOINT) {
    winpoint();
  } else if (selectedSide == right_SIDE) {
    autonomousRight();
  } else if (selectedSide == left_SIDE) {
    autonomousLeft();
  }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol() {
  TopIntake.setVelocity(100, vex::percent);
  BottomIntake.setVelocity(100, vex::percent);

  while (1) {
   double left_power = controller1.Axis3.position(vex::percent);
   double right_power = controller1.Axis2.position(vex::percent);
   leftMotors.spin(vex::fwd, left_power, vex::percent);
   rightMotors.spin(vex::fwd, right_power, vex::percent);
  
    if (controller1.ButtonR1.pressing()){
      TopIntake.spin(vex::fwd);
      BottomIntake.spin(vex::fwd);
    } else if (controller1.ButtonR2.pressing()){
      TopIntake.spin(vex::reverse);
      BottomIntake.spin(vex::reverse);
    } else {
      TopIntake.stop(vex::brake);
      BottomIntake.stop(vex::brake);
    }

    wait(20, vex::msec);
  }
}

int main() {
  pre_auton();
  autonSelectionFlow();
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Prevent main from exiting with an infinite loop.
  while (true) {
    vex::wait(100, vex::msec);
  }
}
