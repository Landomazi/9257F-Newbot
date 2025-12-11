#include "vex.h"
using namespace vex;

// A global instance of competition
competition Competition;

// Brain, controllers, sensors, and pistons
brain BigBrain;

//controllers
controller controller1 = controller(primary);
controller controller2 = controller(partner);

//sensors
inertial inertialsensor1 = inertial(PORT14);
inertial inertialsensor2 = inertial(PORT19);
inertial InertialSensor3 = inertial(PORT9);
inertial InertialSensor4 = inertial(PORT12);

// Intake motor
motor TopIntake = motor(PORT3 ,ratio18_1, true);
motor BottomIntake = motor(PORT1, ratio18_1, false);
motor_group intake = motor_group(TopIntake, BottomIntake);

//lift motor
motor liftmotor1 = motor(PORT9, ratio6_1, true);
motor liftmotor2 = motor(PORT12, ratio6_1, false);
motor_group liftmotor = motor_group(liftmotor1, liftmotor2);

// Right motors
motor motor_right_front = motor(PORT20, ratio6_1, false);
motor motor_right_mid = motor(PORT18, ratio6_1, false);
motor motor_right_back = motor(PORT17, ratio6_1, false);
motor_group rightMotors = motor_group(motor_right_front, motor_right_mid, motor_right_back);

// Left motors
motor motor_left_front = motor(PORT2, ratio6_1, true);
motor motor_left_mid = motor(PORT11, ratio6_1, true);
motor motor_left_back = motor(PORT8, ratio6_1, true);
motor_group leftMotors = motor_group(motor_left_front, motor_left_mid, motor_left_back);

// Drivetrain setup for autonomous code
drivetrain drivetrain1 = drivetrain(leftMotors, rightMotors, 304.8, 257.175, 259.338473, distanceUnits::mm);