#include "vex.h"
#include "Configure.h"
#include "Auton/AutonFunc/Odom/OdomTracking.h"
#include "InertialHeading.h"
#include "Auton/AutonFunc/Odom/AngWrap.h"
#include <cmath>

// Move to a target pose using odometry
void MoveToPoseOdom(double targetX, double targetY, double targetTheta, double maxSpeed, int timeout) {
    double kP_linear = 0.8;
    double kP_angular = 2.0;

    vex::timer t;
    t.reset();

    while(t.time(vex::msec) < timeout) {
        UpdateOdom(); // updates globalX, globalY, globalTheta

        // Distance and angle to target
        double deltaX = targetX - globalX;
        double deltaY = targetY - globalY;
        double distance = sqrt(deltaX*deltaX + deltaY*deltaY);
        double targetAngle = atan2(deltaY, deltaX) * 180.0 / M_PI;

        // Angular error relative to robot heading
        double errorHeading = angleWrap(targetAngle - globalTheta);
        double errorTheta = angleWrap(targetTheta - globalTheta);

        // Stop if close enough to pose
        if(distance < 1.0 && fabs(errorTheta) < 2.0) break;

        // PID outputs
        double forwardPower = kP_linear * distance;
        double turnPower = kP_angular * errorHeading;

        // Clamp speeds
        if(forwardPower > maxSpeed) forwardPower = maxSpeed;
        if(turnPower > maxSpeed) turnPower = maxSpeed;
        if(forwardPower < -maxSpeed) forwardPower = -maxSpeed;
        if(turnPower < -maxSpeed) turnPower = -maxSpeed;

        // Differential drive outputs
        double leftPower = forwardPower + turnPower;
        double rightPower = forwardPower - turnPower;

        // Normalize if needed
        double ratio = max(fabs(leftPower), fabs(rightPower)) / maxSpeed;
        if(ratio > 1.0) {
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
