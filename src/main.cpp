/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Landon.kiely                                              */
/*    Created:      11/19/2025, 7:35:43 AM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "Configure.h"
#include "Autoselector.h"
#include "AutonRoutes.h"
#include "DriveStraight.h"
#include "InertialHeading.h"

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
  InertialSensor1.resetHeading();
  InertialSensor2.resetHeading();
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

void UserControlDebug() {
    TopIntake.setVelocity(100, vex::percent);
    BottomIntake.setVelocity(100, vex::percent);

    bool MogoMechEngaged = false;
    bool MogoMechPosition = false;
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
        bool Y = Controller1.ButtonY.pressing();

        // --- Motor commands ---
        double LeftPower = L3;
        double RightPower = R3;

        // Drive motors
        LeftMotors.spin(forward, LeftPower, percent);
        RightMotors.spin(forward, RightPower, percent);

        // Intake motors
        if(R2) {
          TopIntake.spin(reverse);
          BottomIntake.spin(reverse);
        } else if(R1) {
            TopIntake.spin(forward);
            BottomIntake.spin(forward);
            IMPdouble.set(false);
            Double2.set(false);
        } else if(L1) {
          TopIntake.spin(forward);
          BottomIntake.spin(forward);
          IMPdouble.set(true);
          Double2.set(false);
        } else {
            TopIntake.stop();
            BottomIntake.stop();
        }

        // descore  mechanism
        if( Y && !MogoMechEngaged) {
            MogoMechPosition = !MogoMechPosition;
            goalPiston.set(MogoMechPosition);
        }
        MogoMechEngaged = Y;

        if( Right && !LilWillEngaged) {
          LilWillPosition = !LilWillPosition;
          lilWill.set(LilWillPosition);
        }
        LilWillEngaged = Right;

        // --- Print debug info to Brain ---
        BigBrain.Screen.clearScreen();
        BigBrain.Screen.setCursor(1,1);
        BigBrain.Screen.print("Drive L: %.1f  R: %.1f", LeftPower, RightPower);
        BigBrain.Screen.newLine();
        BigBrain.Screen.print("Intake R1:%d R2:%d L1:%d", R1, R2, L1);
        BigBrain.Screen.newLine();
        BigBrain.Screen.print(" L3:bumbers%.1f R3:%.1f L4:%.1f R4:%.1f", L3, R3, L4, R4);
        BigBrain.Screen.newLine();
        BigBrain.Screen.print("Mogo engaged:%d  position:%d", MogoMechEngaged, MogoMechPosition);
        BigBrain.Screen.newLine();
        BigBrain.Screen.print("LilWIll engaged:%d  position:%d", LilWillEngaged, LilWillPosition);
        BigBrain.Screen.newLine();
        BigBrain.Screen.print("headings position1:%d  position2:%d", InertialSensor1.heading(), InertialSensor2.heading());
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