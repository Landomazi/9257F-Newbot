#include "configure.h"

// Competition and brain
competition Competition;
brain BigBrain;

// Controllers
controller Controller1 = controller(primary);
controller Controller2 = controller(partner);

// Inertial sensors
inertial InertialSensor1 = inertial(PORT4);
inertial InertialSensor2 = inertial(PORT7);

// Pneumatics
pneumatics Descore = pneumatics(BigBrain.ThreeWirePort.A);
pneumatics lilWill = pneumatics(BigBrain.ThreeWirePort.B);
pneumatics Double1 = pneumatics(BigBrain.ThreeWirePort.C);
pneumatics Double2 = pneumatics(BigBrain.ThreeWirePort.D);

// Intake motors
motor TopIntake = motor(PORT6, ratio18_1, false);
motor BottomIntake = motor(PORT5, ratio18_1, true);
motor_group Intake = motor_group(TopIntake, BottomIntake);

// Right motors
motor RightFront = motor(PORT10, ratio6_1, false);
motor RightMid = motor(PORT9, ratio6_1, false);
motor RightBack = motor(PORT8, ratio6_1, false);
motor_group RightMotors = motor_group(RightFront, RightMid, RightBack);

// Left motors
motor LeftFront = motor(PORT1, ratio6_1, true);
motor LeftMid = motor(PORT2, ratio6_1, true);
motor LeftBack = motor(PORT11, ratio6_1, true);
motor_group LeftMotors = motor_group(LeftFront, LeftMid, LeftBack);

// Drivetrain setup
drivetrain Drivetrain1 = drivetrain(LeftMotors, RightMotors, 304.8, 257.175, 259.338473, distanceUnits::mm);