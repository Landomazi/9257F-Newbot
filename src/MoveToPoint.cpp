#include "vex.h"
#include "Configure.h"
#include "InertialHeading.h"
#include "AutoInclude.h"
#include <cmath>
#include <algorithm>
#include <iostream>

void MoveToPoint(double targetX, double targetY, double maxSpeed, int timeout) {
    // Linear (forward)
    double kP_linear = 1.1;
    double kD_linear = 2.5;

    // Angular (turning)
    double kP_angular = 0.385;
    double kD_angular = 1.2;

    const double minDrivePower = 6.0;
    const double minTurnPower = 4.0;

    double error_linear = 0;
    double last_error_linear = 0;

    double error_angular = 0;
    double last_error_angular = 0;

    vex::timer t;
    t.reset();

    while (t.time(vex::msec) < timeout) {

        UpdateOdom();

        double deltaX = targetX - globalX;
        double deltaY = targetY - globalY;

        double distance = sqrt(deltaX * deltaX + deltaY * deltaY);

        // FIXED atan2 order
        double targetTheta = atan2(deltaX, deltaY) * 180.0 / M_PI;

        double headingError = angleWrap(targetTheta - globalHeading);

        if (distance < 0.6) break;

        // UPDATE ERRORS FIRST
        error_linear = distance;
        error_angular = headingError;

        double derivative_linear = (error_linear - last_error_linear);
        double derivative_angular = angleWrap(error_angular - last_error_angular);


        last_error_linear = error_linear;
        last_error_angular = error_angular;

        double forwardPower =
            (kP_linear * error_linear) +
            (kD_linear * derivative_linear);

        double turnPower =
            (kP_angular * error_angular) +
            (kD_angular * derivative_angular);

        // convert angular error to radians for cosine
        double errorAngularRad = error_angular * M_PI / 180.0;

        double headingScale = clamp(cos(errorAngularRad), 0.12, 1.0);
        forwardPower *= headingScale;

        if (fabs(error_angular) > 30.0) {
            double maxForwardWhileTurning = maxSpeed * 0.45;
            forwardPower = clamp(forwardPower,
                                 -maxForwardWhileTurning,
                                 maxForwardWhileTurning);
        }

        if (fabs(forwardPower) < minDrivePower && fabs(error_linear) > 1.0) {
            forwardPower = (forwardPower >= 0.0)
                ? minDrivePower : -minDrivePower;
        }

        if (fabs(turnPower) < minTurnPower && fabs(error_angular) > 2.0) {
            turnPower = (turnPower >= 0.0)
                ? minTurnPower : -minTurnPower;
        }

        forwardPower = clamp(forwardPower, -maxSpeed, maxSpeed);
        turnPower = clamp(turnPower, -maxSpeed * 0.9, maxSpeed * 0.9);

        double leftPower = forwardPower + turnPower;
        double rightPower = forwardPower - turnPower;

        double ratio =
            std::max(fabs(leftPower), fabs(rightPower)) / maxSpeed;

        if (ratio > 1.0) {
            leftPower /= ratio;
            rightPower /= ratio;
        }

        LeftMotors.spin(vex::forward, leftPower, vex::pct);
        RightMotors.spin(vex::forward, rightPower, vex::pct);

        vex::this_thread::sleep_for(10);
    }

    LeftMotors.stop(vex::brake);
    RightMotors.stop(vex::brake);
}