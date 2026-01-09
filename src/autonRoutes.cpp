#include "vex.h"
#include "configure.h"
#include "autonFunctions.h"


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
  TopIntake.spin(fwd);
  wait(2, seconds);
  TopIntake.stop();
}

 

void AWPoint()
{

}

 

void AutonomousRight(void)
{
  DriveStraight(23, 50);
  wait(.1, seconds);
  Turn(30, 50);
  BottomIntake.spin(reverse);
  DriveStraight(20, 8);
  wait(.4, seconds);
  DriveStraight(20, 8);
  Turn(135, 50);
  DriveStraight(67, 50);
  Intake.stop();
  Turn(0, 50);
  DriveStraight(21, 50);
  IntakeSpin(100, reverse);
}

 

void AutonomousLeft(void)
{
  DriveStraight(23, 50);
  wait(.1, seconds);
  Turn(-30, 50);
  BottomIntake.spin(reverse);
  DriveStraight(20, 8);
  wait(.4, seconds);
  DriveStraight(20, 8);
  Turn(-135, 50);
  DriveStraight(68, 50);
  Intake.stop();
  Turn(0, 50);
  DriveStraight(21, 50);
  IntakeSpin(100, reverse);
}
