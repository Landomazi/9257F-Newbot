/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       autonRoutes.cpp                                           */
/*    Author:       Landon.kiely                                              */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "Configure.h"
#include "DriveStraight.h"
#include "TurnPid.h"
#include "OdomFunctions.h"

using namespace vex;

void AutonomousSkills(void)
{
  /*TopIntake.setVelocity(100, percent);
  BottomIntake.setVelocity(100, percent);
  //step 1:
  DriveStraight(63, 50);
  wait(.1, seconds);
  Turn(-90, 100);
  //step 2:
  IntakeSpin(100, forward);
  DriveStraight(14, 20);
  DriveStraight(15, 10);
  wait(1, seconds);
  DriveStraight(-6.7, 40);
  DriveStraight(8, 10);
  wait( 1, seconds);
  DriveStraight(-7, 40);
  DriveStraight(7, 10);
  wait( 1, seconds);
  //step 3:
  DriveStraight(-20, 15);
  Turn(88, 50);
  DriveStraight(25, 30);
  //step 4:
  wait(1.5, seconds);
  DriveStraight(20, 15);
  IntakeSpin(100, reverse);
  wait(1.5, seconds);
  //step 5:
  DriveStraight(-15, 15);
  wait(0.5, seconds);
  wait(1, seconds);
  //step 6:
  Turn(177, 100);
  DriveStraight(187, 50);
  wait(.1, seconds);
  //step 7:
  Turn(-90, 100);
  IntakeSpin(100, forward);
  DriveStraight(48, 30);
  //step 8:
  wait(.5, seconds);
  DriveStraight(-5, 30);
  DriveStraight(4.7, 30);
  wait( 1, seconds);
  DriveStraight(-5, 30);
  DriveStraight(4.7, 30);
  wait( 1, seconds);
  //step 9:
  DriveStraight(-20, 15);
  Turn(89, 50);
  DriveStraight(25, 30);
  //step 10:
  wait(1.5, seconds);
  DriveStraight(20, 15);
  IntakeSpin(100, reverse);
  //step 11:
  wait(1.5, seconds);
  DriveStraight(-25, 15);
  wait(0.5, seconds);
  //step 12:
  wait(1, seconds);
  Turn(0, 50);
  DriveStraight(90, 50);
  Turn(-90, 50);
  //step 13:
  wait(1, seconds);
  DriveStraight(65, 80);*/
  Intake.spin(fwd);
  wait(2, seconds);
  Intake.stop();
}

 

void AWPoint()
{
  //drive to the tube and grab blocks
  DriveStraight(39, 100);
  Intake.spin(reverse);
  lilWill.set(true);
  Turn(-89.5, 70);
  DriveStraight(22, 30);
  wait(.5, seconds);
  DriveStraight(1,40);
  DriveStraight(-40, 50);
  Double2.set(true);
  wait(2,seconds);
  //go to mid blocks
  Double2.set(false);
  DriveStraight(31, 100);
  lilWill.set(false);
  Turn(131, 70);
  DriveStraight(40, 50);
  lilWill.set(true);
  DriveStraight(18,30);
  Turn(-45, 70);
  DriveStraight(-17,70);
  Double2.set(false);
  IMPdouble.set(true);
}

 

void AutonomousRight(void)
{
  Intake.setVelocity(75, percent);
  DriveStraight(18, 20);
  Turn(32, 50);
  Intake.spin(forward);
  wait(0.5, seconds);
  DriveStraight(20, 20);
  Turn(135, 30);
  DriveStraight(60, 20);
  Turn(-180, 30);
  Intake.stop(hold);
  DriveStraight(-38, 20);
  IMPdouble.set(true);
  wait(1, seconds);
  Intake.setVelocity(100, percent);
  Intake.spin(forward);
}

void AutonomousLeft(void)
{
  Intake.setVelocity(75, percent);
  DriveStraight(18, 20);
  Turn(-32, 50);
  Intake.spin(forward);
  wait(0.5, seconds);
  DriveStraight(20, 20);
  Turn(-135, 30);
  DriveStraight(60, 20);
  Turn(180, 30);
  Intake.stop(hold);
  DriveStraight(-35, 20);
  IMPdouble.set(true);
  wait(1, seconds);
  Intake.setVelocity(100, percent);
  Intake.spin(forward);
}

void ChatGPTAuton(void){

}

void GeminiAuton(void){

}

void AIAuton(void){
  DriveStraight(12,70);
}

//Prompt: Create me a autonoumous route using the Drivestraight function, turn function, Intake.spin and 
//each piston with there respective names: LilWill for match loader, IMPDouble for blocker and high goal scoring, 
//and IMPDOuble and DOuble 2 at the same time for middle goal. Everything works in inches or degrees or true and false. 
//Also specify the starting location as when it starts it needs to be touching the park zone.