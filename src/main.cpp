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

void PreAuton(void) {
  LeftMotors.resetPosition();
  RightMotors.resetPosition();
  InertialSensor1.calibrate();
  InertialSensor2.calibrate();
  InertialSensor3.calibrate();
  InertialSensor4.calibrate();
  InertialSensor1.resetHeading();
  InertialSensor2.resetHeading();
  InertialSensor3.resetHeading();
  InertialSensor4.resetHeading();
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

void Autonomous() {
  if (SelectedAutonMode == Skills) {
    AutonomousSkills();
  } else if (SelectedWinPoint == WinPoint) {
    AWPoint();
  } else if (SelectedSide == RightSide) {
    AutonomousRight();
  } else if (SelectedSide == LeftSide) {
    AutonomousLeft();
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

/*void UserControl() {
  TopIntake.setVelocity(100, vex::percent);
  BottomIntake.setVelocity(100, vex::percent);
  bool mogoMechEngaged = false;
  bool mogoMechPosition = false;

  while (1) {
   double LeftPower = Controller1.Axis3.position(vex::percent);
   double RightPower = Controller1.Axis2.position(vex::percent);
   LeftMotors.spin(vex::fwd, LeftPower, vex::percent);
   RightMotors.spin(vex::fwd, RightPower, vex::percent);
  
    if (Controller1.ButtonR2.pressing()){
      TopIntake.spin(vex::fwd);
      BottomIntake.spin(vex::fwd);
    } else if (Controller1.ButtonR1.pressing()){
      TopIntake.spin(vex::reverse);
      BottomIntake.spin(vex::reverse);
    } else if (Controller1.ButtonL1.pressing()){
      BottomIntake.spin(vex::reverse);
    } else {
      TopIntake.stop();
      BottomIntake.stop();
    }

      if (Controller1.ButtonL2.pressing()&&(mogoMechEngaged==false)){
        mogoMechPosition = !mogoMechPosition;
        goalPiston.set(mogoMechPosition);
      }
      mogoMechEngaged = Controller1.ButtonL2.pressing();

    wait(20, vex::msec);
  }
}*/
void UserControlDebug() {
    TopIntake.setVelocity(100, vex::percent);
    BottomIntake.setVelocity(100, vex::percent);

    bool mogoMechEngaged = false;
    bool mogoMechPosition = false;
    bool LilWillEngaged = false;
    bool LilWillPosition = false;

    while(true) {
        // --- Controller Axes ---
        double L3 = Controller1.Axis3.position(); // left stick vertical
        double R3 = Controller1.Axis2.position(); // right stick vertical
        double L4 = Controller1.Axis4.position(); // left stick horizontal
        double R4 = Controller1.Axis1.position(); // right stick horizontal

        // --- Buttons ---
        bool R1 = Controller1.ButtonR1.pressing();
        bool R2 = Controller1.ButtonR2.pressing();
        bool L1 = Controller1.ButtonL1.pressing();
        bool L2 = Controller1.ButtonL2.pressing();
        bool Up = Controller1.ButtonUp.pressing();
        bool Down = Controller1.ButtonDown.pressing();
        bool Left = Controller1.ButtonLeft.pressing();
        bool Right = Controller1.ButtonRight.pressing();

        // --- Motor commands ---
        double leftPower = L3;
        double rightPower = R3;

        // Drive motors
        LeftMotors.spin(forward, leftPower, percent);
        RightMotors.spin(forward, rightPower, percent);

        // Intake motors
        if(R2) {
            TopIntake.spin(forward);
            BottomIntake.spin(forward);
        } else if(R1) {
            TopIntake.spin(reverse);
            BottomIntake.spin(reverse);
        } else if(L1) {
            BottomIntake.spin(reverse);
        } else {
            TopIntake.stop();
            BottomIntake.stop();
        }

        // Mogo mechanism
        if( Right && !mogoMechEngaged) {
            mogoMechPosition = !mogoMechPosition;
            goalPiston.set(mogoMechPosition);
        }
        mogoMechEngaged = Right;

        if( Down && !LilWillEngaged) {
          LilWillPosition = !LilWillPosition;
          lilWill.set(LilWillPosition);
        }
        LilWillEngaged = Down;



        // --- Print debug info to Brain ---
        BigBrain.Screen.clearScreen();
        BigBrain.Screen.setCursor(1,1);
        BigBrain.Screen.print("Drive L: %.1f  R: %.1f", leftPower, rightPower);
        BigBrain.Screen.newLine();
        BigBrain.Screen.print("Intake R1:%d R2:%d L1:%d", R1, R2, L1);
        BigBrain.Screen.newLine();
        BigBrain.Screen.print(" L3:bumbers%.1f R3:%.1f L4:%.1f R4:%.1f", L3, R3, L4, R4);
        BigBrain.Screen.newLine();
        BigBrain.Screen.print("Mogo engaged:%d  position:%d", mogoMechEngaged, mogoMechPosition);
        BigBrain.Screen.newLine();
        BigBrain.Screen.print("LilWIll engaged:%d  position:%d", LilWillEngaged, LilWillPosition);
        BigBrain.Screen.newLine();
        BigBrain.Screen.print("headings position1:%d  position2:%d", InertialSensor1.heading(), InertialSensor2.heading());
        BigBrain.Screen.newLine();
        BigBrain.Screen.print("headings position3:%d  position4:%d", InertialSensor3.heading(), InertialSensor4.heading());
        BigBrain.Screen.newLine();
        BigBrain.Screen.print("absoloute heading:%d ", BotFacing());
        wait(50, msec); // update every 50ms
    }
}



int main() {
  AutonSelectionFlow();
  PreAuton();
  Competition.autonomous(Autonomous);
  Competition.drivercontrol(UserControlDebug);

  // Prevent main from exiting with an infinite loop.
  while (true) {
    vex::wait(100, vex::msec);
  }
}