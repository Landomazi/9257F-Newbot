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
/*
 Intake.setVelocity(100, vex::percent);
    DriveStraight(-5,30);
    lilWill.set(true);
    Intake.spin(vex::reverse);
    wait(500, vex::msec);
    DriveStraight(44,80);
    lilWill.set(false);

    DriveStraight(43.5,80);
    lilWill.set(true);
    Turn(-90,70);
    Intake.spin(vex::reverse);
    DriveStraight(19,30);
    wait(300, vex::msec);
    DriveStraight(2.8,70);
    DriveStraight(-10, 80);
    Intake.stop();
    lilWill.set(false);
    Turn(0,70);
    DriveStraight(27,40);

    //First matchloader completed with a wall reset

    wait(100, vex::msec);
    DriveStraight(-3,100);
    Turn(86,100);
    DriveStraight(60, 80);
    Turn(88,100);
    DriveStraight(70, 80);
    Turn(0,100);
    DriveStraight(-15.5,80);
    Turn(90,100);
    DriveStraight(-16,70);
    Intake.spin(vex::forward);
    lilWill.set(true);
    Double2.set(true);
    Intake.spin(vex::reverse);
    wait(1800, vex::msec);
    Double2.set(false);
    lilWill.set(true);
    wait(100, vex::msec);
    DriveStraight(16,70);
    Turn(90,90);
    DriveStraight(21,30);
    wait(300, vex::msec);
    DriveStraight(3,70);
    DriveStraight(-20,90);
    Intake.stop();
    Turn(90,100);
    DriveStraight(-20,80);
    Intake.spin(vex::forward);
    Double2.set(true);
    Intake.spin(vex::reverse);
    wait(1200, vex::msec);
    Double2.set(false);
    lilWill.set(false);
    DriveStraight(20, 70); 
    Turn(178,90);
    Intake.stop();
    DriveStraight(100, 80);
    DriveStraight(30, 50);
    lilWill.set(true);
    Turn(90,70);
    Intake.spin(vex::reverse);
    DriveStraight(19,30);
    wait(300, vex::msec);
    DriveStraight(2.8,70);
    DriveStraight(-10, 80);
    Intake.stop();
    lilWill.set(false);
    Turn(180,70);
    DriveStraight(29,40);
    wait(100, vex::msec);
    DriveStraight(-2.5,100);
    Turn(-86,100);
    Double2.set(true);
    Intake.spin(vex::reverse);
    DriveStraight(60, 80);
    Turn(-86,100);
    DriveStraight(70, 80);
    Turn(180,100);
    DriveStraight(-15,80);
    Turn(-90,100);
    lilWill.set(true);
    DriveStraight(17,70);
    wait(400, vex::msec);
    DriveStraight(2,70);
    DriveStraight(-10,80);
    lilWill.set(false);
    Turn(-140,100);
    DriveStraight(20,80);
    Turn(180,100);
    DriveStraight(20,80);
    lilWill.set(true);
    DriveStraight(40,80);
*/