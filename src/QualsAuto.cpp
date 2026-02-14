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
DriveStraight(-5,30);
lilWill.set(true);
Intake.spin(vex::reverse);
wait(500, vex::msec);
DriveStraight(44,80);
lilWill.set(false);
}

void AWP()
{
    DriveStraight(10,50);
}


void AutonomousRight()
{
    Intake.spin(vex::reverse);
    MoveToPoint(11,26,90,3000);
    Intake.stop();
    Intake.setVelocity(85, vex::percent);
    lilWill.set(true);
    MoveToPoint(35.05,0,100,3000);
    Turn(180,90);
    DriveStraight(-25,100);
    IMPdouble.set(true);
    Intake.spin(vex::reverse);
    wait(1000, vex::msec);
    Intake.setVelocity(100, vex::percent);
    IMPdouble.set(false);
    DriveStraight(22,90);
    Turn(180,90);
    DriveStraight(20,30);
    wait(100, vex::msec);
    DriveStraight(-20,90);
    Intake.stop();
    Turn(180,90);
    DriveStraight(-20,90);
    IMPdouble.set(true);
    Intake.spin(vex::reverse);
}

void AutonomousLeft()
{
Intake.spin(vex::reverse);
MoveToPoint(-10,25.2,90,3000);
Intake.stop();
Turn(-135,85);
DriveStraight(-23.9,30);
IMPdouble.set(false);
Double2.set(true);
Intake.setVelocity(80, vex::percent);
Intake.spin(vex::reverse);
wait(1450, vex::msec);
DriveStraight(69, 90);
Double2.set(false);
lilWill.set(true);
Turn(180,90);
DriveStraight(30,30);
wait(175, vex::msec);
DriveStraight(-20,90);
Intake.stop();
Turn(180,90);
DriveStraight(-20,90);
Intake.spin(vex::forward);
IMPdouble.set(true);
Intake.setVelocity(90, vex::percent);
Intake.spin(vex::reverse);
}
