#include "vex.h"
#include "configure.h"

double BotFacing(){
  double sum = 0;
  int count = 0;

  if (InertialSensor1.installed()) {
    sum += InertialSensor1.rotation();
    count++;
  }
  if (InertialSensor2.installed()) {
    sum += InertialSensor2.rotation();
    count++;
  }
  if (InertialSensor3.installed()) {
    sum += InertialSensor3.rotation();
    count++;
  }
  if (InertialSensor4.installed()) {
    sum += InertialSensor4.rotation();
    count++;
  }
  
  return sum / count;
}

//davin is stupid
void Turn(double targetAngle, double maxSpeed) {
  double kP = 0.6; //strength of reaction to error
  double kI = 0.002; // helps whit error calcuclation
  double kD = 0.4; //rate of slowing down as it gets closer to target

  double error; //how far off of the target angle
  double prevError = 0; //how far off it use to be from target angle
  double integral = 0; //sum of past error
  double derivative; //how quickly the robot changes it movement speed
   //the max speed the motors can be 

  vex::timer t;
  t.reset();   


  while (true) { //everything in this loop we constaly be running and calculating
    double currentAngle = BotFacing(); //sets cuurent angle to be equivent to botfacing
    error = targetAngle - currentAngle; // calculates how far it needs to turn to get closer to the angle

    // makes sure that it always travels the shortes distance; instead of 350deg it travels 10deg
    if (error > 180) error -= 360; 
    if (error < -180) error += 360;

    // adds up all the mistakes to help with over shooting but also doesn't bother adding up over 15deg of error
    if (fabs(error) < 15)
      integral += error;
    else
      integral = 0;

    derivative = error - prevError; // how fast it fixes error
    //even that it states prevError equals zero at the start after the first turn preErro starts equaling previous error
    //states it down in the loop prevError = error

    // claculates turn speed constantly so that it slows down as it gets closer
    double turnSpeed = (kP * error) + (kI * integral) + (kD * derivative);


    if (turnSpeed > maxSpeed) turnSpeed = maxSpeed; //these two lines limit speed to hundred percent which isn't 
    if (turnSpeed < -maxSpeed) turnSpeed = -maxSpeed;//necesary but if we ever lower max speed it will be necesary

    LeftMotors.spin(vex::forward, turnSpeed, vex::percent);// these two lines and the two above it help with speed and which 
    RightMotors.spin(vex::forward, -turnSpeed, vex::percent);// direction the motors spin

    prevError = error; //when the loop gets down here it sets the previous error to the error and then resets
    //the error after movement recalculates

    if ((fabs(error) < 1 && fabs(derivative) < 0.5) || t.time(vex::sec) > 3) {
      break;
    }// basically saying if it is off target by 1 degree and that it is taking longer than three seconds then the 
    //code ends and the turn will not
    vex::wait(20, vex::msec);
  }

  // when the turn is completed and error equals 0 with no problems then the turn ends and motors stop
  LeftMotors.stop(vex::brake);
  RightMotors.stop(vex::brake);
}

void DriveStraight(double distance, double speed){
  LeftMotors.resetPosition();
  RightMotors.resetPosition();
  Drivetrain1.setDriveVelocity(speed, vex::percent);
  Drivetrain1.driveFor(distance, vex::inches);
}

void IntakeSpin(double speed, vex::directionType dir){
  TopIntake.setVelocity(speed, vex::percent);
  BottomIntake.setVelocity(speed, vex::percent);
  TopIntake.spin(dir);
  BottomIntake.spin(dir);
}
