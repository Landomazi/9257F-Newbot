#include "configure.h"

// Competition and brain
competition Competition;
brain BigBrain;

// Controllers
controller Controller1 = controller(primary);
controller Controller2 = controller(partner);

// Inertial sensors
inertial InertialSensor1 = inertial(PORT1);
inertial InertialSensor2 = inertial(PORT6);
inertial InertialSensor3 = inertial(PORT8);
inertial InertialSensor4 = inertial(PORT20);

// Pneumatics
pneumatics goalPiston = pneumatics(BigBrain.ThreeWirePort.A);
pneumatics lilWill = pneumatics(BigBrain.ThreeWirePort.B);

// Intake motors
motor TopIntake = motor(PORT10, ratio18_1, false);
motor BottomIntake = motor(PORT19, ratio18_1, true);
motor_group Intake = motor_group(TopIntake, BottomIntake);

// Right motors
motor RightFront = motor(PORT3, ratio6_1, false);
motor RightMid = motor(PORT5, ratio6_1, false);
motor RightBack = motor(PORT4, ratio6_1, false);
motor_group RightMotors = motor_group(RightFront, RightMid, RightBack);

// Left motors
motor LeftFront = motor(PORT2, ratio6_1, true);
motor LeftMid = motor(PORT7, ratio6_1, true);
motor LeftBack = motor(PORT9, ratio6_1, true);
motor_group LeftMotors = motor_group(LeftFront, LeftMid, LeftBack);

// Drivetrain setup
drivetrain Drivetrain1 = drivetrain(LeftMotors, RightMotors, 304.8, 257.175, 259.338473, distanceUnits::mm);