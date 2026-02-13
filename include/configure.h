#pragma once

// Competition and brain
extern vex::competition Competition;
extern vex::brain BigBrain;

// Controllers
extern vex::controller Controller1;
extern vex::controller Controller2;

// Inertial sensors
extern vex::inertial InertialSensor1;
extern vex::inertial InertialSensor2;

// Odometray tracking wheels
extern vex::rotation Ypod;

// Pneumatics
extern vex::pneumatics DescorePiston;
extern vex::pneumatics lilWill;
extern vex::pneumatics IMPdouble;
extern vex::pneumatics Double2;

// Intake motors
extern vex::motor TopIntake;
extern vex::motor BottomIntake;
extern vex::motor_group Intake;

// Right motors
extern vex::motor RightFront;
extern vex::motor RightMid;
extern vex::motor RightBack;
extern vex::motor_group RightMotors;

// Left motors
extern vex::motor LeftFront;
extern vex::motor LeftMid;
extern vex::motor LeftBack;
extern vex::motor_group LeftMotors;

// Drivetrain for auton
extern vex::drivetrain Drivetrain1;