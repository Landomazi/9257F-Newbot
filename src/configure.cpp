#include "vex.h"

// Competition and brain
vex::competition Competition;
vex::brain BigBrain;

// Controllers
vex::controller Controller1 = vex::controller(vex::primary);
vex::controller Controller2 = vex::controller(vex::partner);

// Inertial sensors
vex::inertial InertialSensor1 = vex::inertial(vex::PORT15);
vex::inertial InertialSensor2 = vex::inertial(vex::PORT16);

//Odometray tracking wheel
vex::rotation Ypod = vex::rotation(vex::PORT1, false);

// Pneumatics
vex::pneumatics DescorePiston = vex::pneumatics(BigBrain.ThreeWirePort.G);
vex::pneumatics lilWill = vex::pneumatics(BigBrain.ThreeWirePort.C);
vex::pneumatics IMPdouble = vex::pneumatics(BigBrain.ThreeWirePort.A);
vex::pneumatics Double2 = vex::pneumatics(BigBrain.ThreeWirePort.E);

// Intake motors
vex::motor TopIntake = vex::motor(vex::PORT17, vex::ratio18_1, false);
vex::motor BottomIntake = vex::motor(vex::PORT14, vex::ratio18_1, true);
vex::motor_group Intake = vex::motor_group(TopIntake, BottomIntake);

// Right motors
vex::motor RightFront = vex::motor(vex::PORT20, vex::ratio6_1, false);
vex::motor RightMid = vex::motor(vex::PORT19, vex::ratio6_1, false);
vex::motor RightBack = vex::motor(vex::PORT18, vex::ratio6_1, false);
vex::motor_group RightMotors = vex::motor_group(RightFront, RightMid, RightBack);

// Left motors
vex::motor LeftFront = vex::motor(vex::PORT11, vex::ratio6_1, true);
vex::motor LeftMid = vex::motor(vex::PORT12, vex::ratio6_1, true);
vex::motor LeftBack = vex::motor(vex::PORT13, vex::ratio6_1, true);
vex::motor_group LeftMotors = vex::motor_group(LeftFront, LeftMid, LeftBack);

// Drivetrain setup
vex::drivetrain Drivetrain1 = vex::drivetrain(LeftMotors, RightMotors, 304.8, 257.175, 259.338473, vex::distanceUnits::mm);