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
    MoveToPoint(-23.5, 24.5, 100, 2000, true);
    Turn(-135,100);
    Intake.stop();
    MoveToPoint(-46, 0, 100, 2000, true);
    Turn(180,100);
    MoveToPoint(-46, 20, 100, 2000, false);
    IMPdouble.set(true);
    Intake.spin(vex::reverse);
    wait(1500, vex::msec);
    IMPdouble.set(false);
    MoveToPoint(-46, 10, 100, 3000, true);
    Turn(180,100);
    lilWill.set(true);
    MoveToPoint(-46,-14, 100, 2000, true);
    wait(800, vex::msec);
    DriveStraight(3,30);
    wait(1000, vex::msec);
    Intake.stop();
    MoveToPoint(-52, 0,100 ,2000, false );
    MoveToPoint(-57, 80, 100, 3000, false);
    MoveToPoint(-46, 90,100, 2000, false);
    Turn(0,100);
    MoveToPoint(-46,70,100,2000, false);
    IMPdouble.set(true);
    wait(100, vex::msec);
    Intake.spin(vex::reverse);
    wait(1500, vex::msec);
    IMPdouble.set(false);
    MoveToPoint(-46, 100, 100, 3000, true);
    Turn(180,100);
    lilWill.set(true);
    MoveToPoint(-46, 114, 100, 2000, true);
    wait(800, vex::msec);
    DriveStraight(3,30);
    wait(1000, vex::msec);
    Intake.stop();
    MoveToPoint(-46,70,100,2000, false);
    IMPdouble.set(true);
    wait(100, vex::msec);
    Intake.spin(vex::reverse);
    wait(1500, vex::msec);
    IMPdouble.set(false);
    Intake.stop();
    DriveStraight(10,100);
    //Start Mirror
    MoveToPoint(23.5, 90, 100, 2000, true);
    Turn(-135,100);
    Intake.stop();
    MoveToPoint(47, 100, 100, 2000, true);
    Turn(180,100);
    MoveToPoint(47, 95, 100, 2000, false);
    IMPdouble.set(true);
    Intake.spin(vex::reverse);
    wait(1500, vex::msec);
    IMPdouble.set(false);
    MoveToPoint(47, 107, 100, 3000, true);
    Turn(180,100);
    lilWill.set(true);
    MoveToPoint(47,114, 100, 2000, true);
    wait(800, vex::msec);
    DriveStraight(3,30);
    wait(1000, vex::msec);
    Intake.stop();
    MoveToPoint(52, 90,100 ,2000, false );
    MoveToPoint(57, 80, 100, 3000, false);
    MoveToPoint(46, 0,100, 2000, false);
    Turn(0,100);
    MoveToPoint(46,20 ,100,2000, false);
    IMPdouble.set(true);
    wait(100, vex::msec);
    Intake.spin(vex::reverse);
    wait(1500, vex::msec);
    IMPdouble.set(false);
    MoveToPoint(46, 0, 100, 3000, true);
    Turn(180,100);
    lilWill.set(true);
    MoveToPoint(46, -14, 100, 2000, true);
    wait(800, vex::msec);
    DriveStraight(3,30);
    wait(1000, vex::msec);
    Intake.stop();
    MoveToPoint(46,20,100,2000, false);
    IMPdouble.set(true);
    wait(100, vex::msec);
    Intake.spin(vex::reverse);
    wait(1500, vex::msec);
    IMPdouble.set(false);
    MoveToPoint(47,0, 100, 1000, true);
    Turn(-130, 100);
    MoveToPoint(20, -5,100,2000, true);
    Turn(90,100);
    MoveToPoint(10,-10, 100, 1000, true);
    lilWill.set(true);
    Intake.spin(vex::reverse);
    DriveStraight(40, 80);
    lilWill.set(false);
}

void AWP()
{

}


void AutonomousRight()
{
    Intake.spin(vex::reverse);
    MoveToPoint(11,26,90,3000, true);
    Intake.stop();
    Intake.setVelocity(85, vex::percent);
    lilWill.set(true);
    MoveToPoint(35.05,0,100,3000, true);
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
    MoveToPoint(-11,26,100,2000, true);
    Turn(-135,100);
    MoveToPoint(-34,0, 100, 2000, true);
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
