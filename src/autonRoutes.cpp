#include "vex.h"
#include "configure.h"
#include "autonFunctions.h"


using namespace vex;

void autonomousSkills(void)
{
  TopIntake.setVelocity(100, percent);
  BottomIntake.setVelocity(100, percent);
  //step 1:
  drivestraight(63, 50);
  wait(.1, seconds);
  Turn(-90, 100);
  //step 2:
  intakeSpin(100, forward);
  drivestraight(14, 20);
  drivestraight(15, 10);
  wait(1, seconds);
  drivestraight(-6.7, 40);
  drivestraight(8, 10);
  wait( 1, seconds);
  drivestraight(-7, 40);
  drivestraight(7, 10);
  wait( 1, seconds);
  //step 3:
  drivestraight(-20, 15);
  Turn(88, 50);
  drivestraight(25, 30);
  //step 4:
  wait(1.5, seconds);
  drivestraight(20, 15);
  intakeSpin(100, reverse);
  wait(1.5, seconds);
  //step 5:
  drivestraight(-15, 15);
  wait(0.5, seconds);
  wait(1, seconds);
  //step 6:
  Turn(177, 100);
  drivestraight(187, 50);
  wait(.1, seconds);
  //step 7:
  Turn(-90, 100);
  intakeSpin(100, forward);
  drivestraight(48, 30);
  //step 8:
  wait(.5, seconds);
  drivestraight(-5, 30);
  drivestraight(4.7, 30);
  wait( 1, seconds);
  drivestraight(-5, 30);
  drivestraight(4.7, 30);
  wait( 1, seconds);
  //step 9:
  drivestraight(-20, 15);
  Turn(89, 50);
  drivestraight(25, 30);
  //step 10:
  wait(1.5, seconds);
  drivestraight(20, 15);
  intakeSpin(100, reverse);
  //step 11:
  wait(1.5, seconds);
  drivestraight(-25, 15);
  wait(0.5, seconds);
  //step 12:
  wait(1, seconds);
  Turn(0, 50);
  drivestraight(90, 50);
  Turn(-90, 50);
  //step 13:
  wait(1, seconds);
  drivestraight(65, 80);
}

 

void winpoint()

{

}

 

void autonomousRight(void)
{

  //step 1:
  drivestraight(60, 50);
  wait(.1, seconds);
  Turn(90, 100);

  //step 2:
  intakeSpin(100, forward);
  drivestraight(27, 30);
  drivestraight(-5, 30);
  drivestraight(4.7, 30);
  drivestraight(-5, 30);
  drivestraight(4.7, 30);
  
  //step 3:
  drivestraight(-20, 15);
  Turn(-87, 50);
  drivestraight(25, 30);
  
  //step 4:

  wait(1, seconds);
  drivestraight(20, 15);
  intakeSpin(100, reverse);
  wait(1.5, seconds);
  
  //step 5:
  drivestraight(-15, 15);
  wait(0.5, seconds);
  wait(1, seconds);
}

 

void autonomousLeft(void)
{
  //step 1:
  drivestraight(64, 50);
  wait(.1, seconds);
  Turn(-90, 100);
  //step 2:
  intakeSpin(100, forward);
  drivestraight(27, 30);
  drivestraight(-5, 30);
  drivestraight(4.7, 30);
  wait( .5, seconds);
  //step 3:
  drivestraight(-20, 15);
  Turn(89, 50);
  drivestraight(25, 30);
  //step 4:
  wait(1.5, seconds);
  drivestraight(20, 15);
  intakeSpin(100, reverse);
  wait(1.5, seconds);
  //step 5:
  drivestraight(-15, 15);
  wait(0.5, seconds);
  wait(1, seconds);
}