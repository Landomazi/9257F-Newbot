#include "vex.h"
using namespace vex;

// Competition and brain
extern competition Competition;
extern brain BigBrain;

// Controllers
extern controller Controller1;
extern controller Controller2;

// Inertial sensors
extern inertial InertialSensor1;
extern inertial InertialSensor2;

// Pneumatics
extern pneumatics goalPiston;
extern pneumatics lilWill;
extern pneumatics IMPdouble;
extern pneumatics Double2;

// Intake motors
extern motor TopIntake;
extern motor BottomIntake;
extern motor_group Intake;

// Right motors
extern motor RightFront;
extern motor RightMid;
extern motor RightBack;
extern motor_group RightMotors;

// Left motors
extern motor LeftFront;
extern motor LeftMid;
extern motor LeftBack;
extern motor_group LeftMotors;

// Drivetrain for auton
extern drivetrain Drivetrain1;