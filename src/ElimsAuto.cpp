#include "vex.h"
#include "Configure.h"
#include "AutoInclude.h"

void ElimsRight(void){
    Intake.spin(vex::reverse);
    MoveToPoint(11,26,100,2000);
    Turn(135,100);
    MoveToPoint(34,0, 100, 2000);
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

void ElimsLeft(void){
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