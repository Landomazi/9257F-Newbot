/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       autonRoutes.cpp                                           */
/*    Author:       Landon.kiely                                              */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "Configure.h"
#include "AutoInclude.h"
void AutonomousSkills()
{
DriveStraight(-10,50);
Intake.spin(vex::reverse);
DriveStraight(30,90);
DriveStraight(-40,80);
Turn(180,90);
ResetOdom();
MoveToPoseOdom(-10,20,-30,90,3000);
}

void AWP()
{

}

void AutonomousRight()
{
  
}

void AutonomousLeft()
{
 
}