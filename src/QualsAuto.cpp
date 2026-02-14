/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       autonRoutes.cpp                                           */
/*    Author:       Landon.kiely                                              */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "Configure.h"
#include "AutoInclude.h"
void AutonomousSkills()
{
DriveStraight(-10,50);
Intake.spin(vex::reverse);
DriveStraight(30,90);
DriveStraight(-40,80);
Turn(180,90);
ResetOdom();
MoveToPose(-10,20,-30,90,3000);
}

void AWP()
{
ResetOdom();
Intake.spin(vex::reverse);
MoveToPoint(-10,25,20,3000);
lilWill.set(true);
MoveToPoint(-32,5,20,3000);
Turn(180,90);
MoveToPoint(-32,17,20,3000);
IMPdouble.set(true);
Double2.set(false);
wait(1250, vex::msec);
IMPdouble.set(false);
Double2.set(false);
MoveToPoint(-32,-13,20,3000);
wait(0.3, vex::seconds);
MoveToPoint(-32,17,20,3000);
IMPdouble.set(true);
Double2.set(false);

}

void AutonomousRight()
{
  
}

void AutonomousLeft()
{
Intake.spin(vex::reverse);
MoveToPoint(-11,25,90,3000);
lilWill.set(true);
MoveToPoint(-9,25,90,3000);
Turn(-135,90);
DriveStraight(-17,30);
IMPdouble.set(false);
Double2.set(true);
wait(4000, vex::msec);
IMPdouble.set(true);
Double2.set(false);
wait(500, vex::msec);
MoveToPoint(-34,0,90,3000);
Turn(180,90);
IMPdouble.set(false);
MoveToPoint(-34,-12,20,3000);
wait(1000, vex::msec);
MoveToPoint(-34,-26,80,3000);
Double2.set(false);
wait(2000, vex::msec);
Intake.stop();
}
