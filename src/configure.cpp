#include "Configure.h"

// Competition and brain
competition Competition;
brain BigBrain;

// Controllers
controller Controller1 = controller(primary);
controller Controller2 = controller(partner);

// Inertial sensors
inertial InertialSensor1 = inertial(PORT15);
inertial InertialSensor2 = inertial(PORT16);

//Odometray tracking wheels
rotation Xpod = rotation(PORT1);
rotation Ypod = rotation(PORT21);

// Pneumatics
pneumatics goalPiston = pneumatics(BigBrain.ThreeWirePort.C);
pneumatics lilWill = pneumatics(BigBrain.ThreeWirePort.E);
pneumatics IMPdouble = pneumatics(BigBrain.ThreeWirePort.A);
pneumatics Double2 = pneumatics(BigBrain.ThreeWirePort.G);

// Intake motors
motor TopIntake = motor(PORT17, ratio18_1, false);
motor BottomIntake = motor(PORT14, ratio18_1, true);
motor_group Intake = motor_group(TopIntake, BottomIntake);

// Right motors
motor RightFront = motor(PORT20, ratio6_1, false);
motor RightMid = motor(PORT19, ratio6_1, false);
motor RightBack = motor(PORT18, ratio6_1, false);
motor_group RightMotors = motor_group(RightFront, RightMid, RightBack);

// Left motors
motor LeftFront = motor(PORT11, ratio6_1, true);
motor LeftMid = motor(PORT12, ratio6_1, true);
motor LeftBack = motor(PORT13, ratio6_1, true);
motor_group LeftMotors = motor_group(LeftFront, LeftMid, LeftBack);

// Drivetrain setup
drivetrain Drivetrain1 = drivetrain(LeftMotors, RightMotors, 304.8, 257.175, 259.338473, distanceUnits::mm);