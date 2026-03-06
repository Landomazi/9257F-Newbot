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
    Intake.setVelocity(100, vex::percent);
    Intake.spin(vex::reverse);
    DriveStraight(44, 70);
    lilWill.set(true);
    Turn(-90, 80);
    lilWill.set(true);
    DriveStraight(20, 30);
    wait(300, vex::msec);
    DriveStraight( 3, 70);
    DriveStraight(-20, 70);
    Turn(-90, 80);
    DriveStraight(-22, 70);
    Intake.spin(vex::forward);
    Double2.set(true);
    Intake.spin(vex::reverse);
    wait(2000, vex::msec);
    Double2.set(false);
    lilWill.set(false);
    DriveStraight(18, 70);
    Turn(180, 80);
    DriveStraight(35, 45);
    Turn(90, 80);
    DriveStraight(25, 25);
    lilWill.set(true);
    DriveStraight(10, 25);
    wait(300, vex::msec);
    DriveStraight(-35, 70);
    lilWill.set(false);
    Turn(0, 80);
    DriveStraight(33, 45);
    Turn(-90, 80);
    DriveStraight(-20, 70);
    Intake.spin(vex::forward);
    Double2.set(true);
    Intake.spin(vex::reverse);
    wait(1200, vex::msec);
    Double2.set(false);
    DriveStraight(10, 70);
    Turn(180, 80);
}

void AWP()
{

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
    Double2.set(true);
    Intake.spin(vex::reverse);
    wait(1000, vex::msec);
    Intake.setVelocity(100, vex::percent);
    Double2.set(false);
    DriveStraight(22,90);
    Turn(180,90);
    DriveStraight(20,30);
    wait(100, vex::msec);
    DriveStraight(-20,90);
    Intake.stop();
    Turn(180,90);
    DriveStraight(-20,90);
    Double2.set(true);
    Intake.spin(vex::reverse);
}

void AutonomousLeft()
{
    Intake.spin(vex::reverse);
    MoveToPoint(-11,26,100,2000);
    Turn(-135,100);
    MoveToPoint(-34,0, 100, 2000);
    Intake.stop();
    Turn(180,100);
    DriveStraight(-27,100);
    IMPdouble.set(true);
    Intake.spin(vex::reverse);
    wait(1300, vex::msec);
    IMPdouble.set(false);
    DriveStraight(15,100);
    lilWill.set(true);
    DriveStraight(25.5, 30);
    wait(165, vex::msec);
    Intake.stop();
    DriveStraight(-40,100);
    IMPdouble.set(true);
}



