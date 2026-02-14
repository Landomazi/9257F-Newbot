#include "vex.h"
#include "Configure.h"
#include "AutoInclude.h"
void ElimsRight(void){

}

void ElimsLeft(void){
Intake.spin(vex::reverse);
MoveToPoint(-11,25,90,3000);
lilWill.set(true);
MoveToPoint(-35,0,90,3000);
Turn(180,90);
IMPdouble.set(false);
MoveToPoint(-35,-14,20,3000);
wait(750, vex::msec);
Intake.spin(vex::forward);
DriveStraight(-40,90);
wait(500, vex::msec);
Intake.stop();
Intake.spin(vex::forward);
IMPdouble.set(true);
Double2.set(false);
Intake.spin(vex::reverse);
wait(1000, vex::msec);
Intake.stop();
}