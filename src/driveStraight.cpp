#include "vex.h"
#include "Configure.h"

void DriveStraight(double inches, double maxSpeed) {
    double kP = 2.2;
    double kI = 0.0;
    double kD = 0.35;

    double headingKp = 2.0; // tweak this for straightness

    double error = 0;
    double prevError = 0;
    double integral = 0;
    double derivative = 0;

    const double deadband = 0.5;
    const double integralLimit = 20;

    LeftMotors.resetPosition();
    RightMotors.resetPosition();

    double targetHeading = InertialSensor1.heading(); // store initial heading

    vex::timer t;
    t.reset();

    while (true) {
        double leftPos = LeftMotors.position(vex::degrees);
        double rightPos = RightMotors.position(vex::degrees);
        double avgDeg = (leftPos + rightPos) / 2.0;

        double wheelDiameter = 4.0;
        double wheelCircumference = wheelDiameter * M_PI;
        double positionInches = (avgDeg / 360.0) * wheelCircumference;

        error = inches - positionInches;

        if (fabs(error) < 6) {
            integral += error;
            if (integral > integralLimit) integral = integralLimit;
            if (integral < -integralLimit) integral = -integralLimit;
        } else {
            integral = 0;
        }

        derivative = error - prevError;
        double driveSpeed = (kP * error) + (kI * integral) + (kD * derivative);

        // clamp speed
        if (fabs(driveSpeed) < deadband) driveSpeed = 0;
        if (driveSpeed > maxSpeed) driveSpeed = maxSpeed;
        if (driveSpeed < -maxSpeed) driveSpeed = -maxSpeed;

        // heading correction
        double headingError = targetHeading - InertialSensor1.heading();
        double correction = headingError * headingKp;

        LeftMotors.spin(vex::directionType::fwd, driveSpeed + correction, vex::velocityUnits::pct);
        RightMotors.spin(vex::directionType::fwd, driveSpeed - correction, vex::velocityUnits::pct);

        prevError = error;

        // stop when close enough
        if (fabs(error) < 0.5 && fabs(derivative) < 0.3) break;
        if (t.time(vex::sec) > 3) break; // safety timeout

        vex::wait(20, vex::msec);
    }

    LeftMotors.stop(vex::brake);
    RightMotors.stop(vex::brake);
}