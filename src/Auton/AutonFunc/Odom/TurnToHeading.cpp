#include "vex.h"
#include "Configure.h"
#include "OdomTracking.h"
#include "AngWrap.h"
#include <cmath>

// PID turn to an absolute heading
void TurnToHeadingOdom(double targetTheta, double maxSpeed, int timeout) {
    double kP = 2.0;
    double kI = 0.0;
    double kD = 0.2;

    double error = 0;
    double prevError = 0;
    double integral = 0;
    double derivative = 0;

    vex::timer t;
    t.reset();

    while (t.time(msec) < timeout) {
        UpdateOdom();  // update globalX, globalY, globalTheta

        error = angleWrap(targetTheta - globalTheta);

        if (fabs(error) < 1.0) break;  // exit if close enough

        integral += error;
        derivative = error - prevError;
        prevError = error;

        double motorPower = kP * error + kI * integral + kD * derivative;

        // clamp speed
        if (motorPower > maxSpeed) motorPower = maxSpeed;
        if (motorPower < -maxSpeed) motorPower = -maxSpeed;

        LeftMotors.spin(forward, motorPower, pct);
        RightMotors.spin(forward, -motorPower, pct);

        vex::task::sleep(10);
    }

    // stop drivetrain
    LeftMotors.stop(brake);
    RightMotors.stop(brake);
}
