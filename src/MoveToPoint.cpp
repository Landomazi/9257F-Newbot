#include "vex.h"
#include "Configure.h"
#include "InertialHeading.h"
#include "AutoInclude.h"
#include <cmath>
#include <algorithm>

// Simple PID move to point using odom
void MoveToPointOdom(double targetX, double targetY, double maxSpeed, int timeout) {
    double kP_linear = 0.8;
    double kP_angular = 2.0;

    double error_linear = 0;
    double error_angular = 0;
    double prevError_linear = 0;
    double prevError_angular = 0;

    vex::timer t;
    t.reset();

    while (t.time(vex::msec) < timeout) {
        UpdateOdom();

        double deltaX = targetX - globalX;
        double deltaY = targetY - globalY;

        // Distance and angle to target
        double distance = sqrt(deltaX*deltaX + deltaY*deltaY);
        double targetTheta = atan2(deltaY, deltaX) * 180.0 / M_PI;

        error_angular = angleWrap(targetTheta - globalTheta);
        error_linear = distance;

        if (distance < 1.0 && fabs(error_angular) < 2.0) break;

        double turnPower = clamp(kP_angular * error_angular, -maxSpeed, maxSpeed);
        double forwardPower = clamp(kP_linear * error_linear, -maxSpeed, maxSpeed);

        // Combine for differential drive
        double leftPower = forwardPower + turnPower;
        double rightPower = forwardPower - turnPower;

        // Normalize if over max
        double ratio = max(fabs(leftPower), fabs(rightPower)) / maxSpeed;
        if (ratio > 1.0) {
            leftPower /= ratio;
            rightPower /= ratio;
        }

        LeftMotors.spin(vex::forward, leftPower, vex::pct);
        RightMotors.spin(vex::forward, rightPower, vex::pct);

        vex::task::sleep(10);
    }

    LeftMotors.stop(vex::brake);
    RightMotors.stop(vex::brake);
}
