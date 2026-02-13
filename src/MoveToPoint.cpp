#include "vex.h"
#include "Configure.h"
#include "InertialHeading.h"
#include "AutoInclude.h"
#include <cmath>
#include <algorithm>
#include <iostream>

void MoveToPoint(double targetX, double targetY, double maxSpeed, int timeout) {
    // Linear (forward)
    double kP_linear = 3.2;
    double kD_linear = 0.8;

    // Angular (turning)
    double kP_angular = 0.2;
    double kD_angular = 0.8;



    double error_linear = 0;
    double last_error_linear = 0;

    double error_angular = 0;
    double last_error_angular = 0;
    bool driveBackward = false;

    vex::timer t;
    t.reset();

    while (t.time(vex::msec) < timeout) {
        UpdateOdom();

        double deltaX = targetX - globalX;
        double deltaY = targetY - globalY;

        double distance = sqrt(deltaX*deltaX + deltaY*deltaY);
        double targetTheta = atan2(deltaX, deltaY) * 180.0 / M_PI;


        double headingRad = globalHeading * M_PI / 180.0;

        error_linear = deltaX * (-sin(headingRad)) + deltaY * (-cos(headingRad));

        double headingError = angleWrap(targetTheta - globalHeading);
        if (distance < 0.3) break;

        // Use hysteresis so reverse/forward mode does not chatter near 90 deg.
        if (!driveBackward && fabs(headingError) > 100.0) {
            driveBackward = true;
        } else if (driveBackward && fabs(headingError) < 80.0) {
            driveBackward = false;
        }

        error_angular = driveBackward ? angleWrap(headingError + 180.0) : headingError;
        if (driveBackward) {
            error_linear = -error_linear;
        }

double derivative_linear = error_linear - last_error_linear;
double derivative_angular = angleWrap(error_angular - last_error_angular);
        last_error_linear = error_linear;
        last_error_angular = error_angular;

        // PD output
        double forwardPower =
            (kP_linear * error_linear) +
            (kD_linear * derivative_linear);

        double turnPower =
            (kP_angular * error_angular) +
            (kD_angular * derivative_angular);
        double turnScale = clamp((distance - 0.6) / 2.0, 0.0, 1.0);
        turnPower *= turnScale;


        forwardPower = clamp(forwardPower, -maxSpeed, maxSpeed);
        turnPower = clamp(turnPower, -maxSpeed, maxSpeed);

        double leftPower = forwardPower + turnPower;
        double rightPower = forwardPower - turnPower;

        double ratio = std::max(fabs(leftPower), fabs(rightPower)) / maxSpeed;
        if (ratio > 1.0) {
            leftPower /= ratio;
            rightPower /= ratio;
        }

        LeftMotors.spin(vex::forward, -leftPower, vex::pct);
        RightMotors.spin(vex::forward, -rightPower, vex::pct);

        vex::task::sleep(10);
        std::cout << error_angular << " error angular  " << error_linear << " error Linear  " << "\n";
        std::cout << "y: " << globalY << " x: " << globalX << "\n";
    }
    std::cout << "Done\n";
    std::cout << "Done\n";
    std::cout << "Done\n";
    std::cout << "Done\n";
    std::cout << "Done\n";

    LeftMotors.stop(vex::brake);
    RightMotors.stop(vex::brake);

}
