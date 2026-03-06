#include "vex.h"
#include "Configure.h"
#include "InertialHeading.h"
#include "AutoInclude.h"
#include <cmath>
#include <algorithm>
#include <iostream>

void MoveToPoint(double targetY, double targetX, double maxSpeed, int timeout, bool DriveDirection) {
    //KP and KD
    
    double kP_linear = 2.1;
    double kD_linear = 2.7;

    //double kP_angular = .65;
    //double kD_angular = .907;
    double kP_angular = .38;
    double kD_angular = .6;


    const double minDrivePower = 1.0;
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

        double targetTheta = atan2(deltaY, deltaX) * 180.0 / M_PI;

        if (!DriveDirection) {
            targetTheta = angleWrap(targetTheta + 180.0);
        }

        double headingError = angleWrap(targetTheta - globalHeading);
        if (distance < .6 && fabs(error_angular) < 3.0) break;

        // UPDATE ERRORS FIRST
        error_linear = DriveDirection ? distance : -distance;
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
        // SLOW DOWN ZONE
        if (distance < 4.0) {

            // Scale max speed down as we approach target
            double slowCap = maxSpeed * (distance / 4.0);

            // Prevent it from getting too tiny
            slowCap = std::max(slowCap, 8.0);

            forwardPower = clamp(forwardPower, -slowCap, slowCap);
        }
        
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
        std::cout << "Global X: " << globalX 
                  << " GlobalY: " << globalY 
                  << " Global Heading: " << globalHeading 
                  << "\n";
    }

    LeftMotors.stop(vex::brake);
    RightMotors.stop(vex::brake);
}