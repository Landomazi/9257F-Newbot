#include "vex.h"
#include "Configure.h"
#include "AutoInclude.h"
void ElimsRight(void){

}

void ElimsLeft(void){
    Intake.spin(vex::reverse);
    MoveToPoint(-11,26,90,3000);
    Intake.stop();
    lilWill.set(true);
    MoveToPoint(-35.1,0,100,3000);
    Turn(180,90);
    DriveStraight(-25,85);
    Intake.spin(vex::forward);
    IMPdouble.set(true);
    wait(50, vex::msec);
    Intake.spin(vex::reverse);
    wait(1300, vex::msec);
    IMPdouble.set(false);
    DriveStraight(40,80);
    wait(200, vex::msec);
    DriveStraight(-20,90);
    Intake.stop();
    Turn(180,90);
    DriveStraight(-20,90);
    Intake.spin(vex::forward);
    wait(50, vex::msec);
    IMPdouble.set(true);
    Intake.spin(vex::reverse);
}