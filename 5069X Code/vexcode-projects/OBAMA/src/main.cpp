/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\pstol                                            */
/*    Created:      Wed Jun 30 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// L1Drive              motor         1               
// L2Drive              motor         2               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

void driveForward()
{
  L1Drive.spin(directionType :: fwd, 80 , velocityUnits :: pct);
  L2Drive.spin(directionType :: fwd, 80 , velocityUnits :: pct);
}

int main() 
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  while(true)
  {
    if(Controller1.ButtonUp.pressing())
    {
      driveForward();
    }
    else
    {
      L1Drive.stop();
      L2Drive.stop();
    }
  }
}
