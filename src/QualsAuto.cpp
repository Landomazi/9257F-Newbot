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
    /*DriveStraight(-5,30);
    lilWill.set(true);
    Intake.spin(vex::reverse);
    wait(500, vex::msec);
    DriveStraight(44,80);
    lilWill.set(false);*/
    Intake.spin(vex::reverse);
    MoveToPoint(-23.5, 24.5, 100, 2000);
    Turn(-135,100);
    Intake.stop();
    MoveToPoint(-50, 0, 100, 2000);
    Turn(180,100);
    DriveStraight(-26,80);
    IMPdouble.set(true);
    Intake.spin(vex::reverse);
    wait(1500, vex::msec);
    IMPdouble.set(false);
    MoveToPoint(-49, 10, 100, 3000);
    Turn(180,100);
    lilWill.set(true);
    DriveStraight(27,30);
    wait(800, vex::msec);
    DriveStraight(3,30);
    wait(1000, vex::msec);
    Intake.stop();
    DriveStraight(-40,80);
    Intake.spin(vex::reverse);
    IMPdouble.set(true);
    wait(1500, vex::msec);
    lilWill.set(false);
    DriveStraight(15,90);
    Turn(0,90);
    ResetOdom();
    wait(1000, vex::msec);
    Turn(90,90);
    Intake.stop();
    MoveToPoint(70, 23.2, 100, 5000);
    Turn(135,90);
    Intake.stop();
    MoveToPoint(95.5, 0, 100, 3000);
    Turn(180,90);
    DriveStraight(-24,80);
    IMPdouble.set(true);
    Intake.spin(vex::reverse);
    wait(1500, vex::msec);
    IMPdouble.set(false);
    DriveStraight(15,80);
    lilWill.set(true);
    DriveStraight(27,30);
    wait(800, vex::msec);
    DriveStraight(2,30);
    wait(500, vex::msec);
    Intake.stop();
    DriveStraight(-40,80);
    Intake.spin(vex::reverse);
    IMPdouble.set(true);
    wait(1500, vex::msec);
    lilWill.set(false);
    MoveToPoint(75, -14, 100, 3000);
    Turn(-90,90);
    MoveToPoint(65, -20, 100, 3000);
    wait(750, vex::msec);
    lilWill.set(true);
    DriveStraight(40,70);
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
    Intake.spin(vex::reverse);
}
