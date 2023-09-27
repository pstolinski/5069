/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Tue Oct 01 2019                                           */
/*    Description:  Clawbot Control                                           */
/*                  This program uses Controller events to drive the arm and  */
/*                  claw of the V5 Clawbot.                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// driveTrainLeft       motor         4               
// driveTrainRight      motor         3               
// ejectionSpinner      motor         2               
// armMotor             motor         1               
// Controller1          controller                    
// VisionSensor         vision        5               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int centerFOV = 158;
int offset = 50;

vision::signature SIG_RED (1, 5591, 8427, 7009, -1229, 299, -465, 1.600, 0);
vision::signature SIG_2 (2, 0, 0, 0, 0, 0, 0, 2.500, 0);
vision::signature SIG_3 (3, 0, 0, 0, 0, 0, 0, 2.500, 0);
vision::signature SIG_4 (4, 0, 0, 0, 0, 0, 0, 2.500, 0);
vision::signature SIG_5 (5, 0, 0, 0, 0, 0, 0, 2.500, 0);
vision::signature SIG_6 (6, 0, 0, 0, 0, 0, 0, 2.500, 0);
vision::signature SIG_7 (7, 0, 0, 0, 0, 0, 0, 2.500, 0);
vex::vision vision1 ( vex::PORT1, 50, SIG_RED, SIG_2, SIG_3, SIG_4, SIG_5, SIG_6, SIG_7 );

void whenDownArrowPressed(){
    ejectionSpinner.spin(forward);
    waitUntil(!Controller1.ButtonDown.pressing());
    ejectionSpinner.stop();
}


int main() {
  vexcodeInit();
  while (true) {

  driveTrainLeft.setVelocity(Controller1.Axis3.position(), percent);
  driveTrainRight.setVelocity(Controller1.Axis2.position(), percent);
  driveTrainLeft.spin(forward);
  driveTrainRight.spin(forward);

  Controller1.ButtonDown.pressed(whenDownArrowPressed);

  ejectionSpinner.setStopping(hold);

  ejectionSpinner.setVelocity(65, percent);

 Brain.Screen.clearLine();
VisionSensor.takeSnapshot(SIG_RED);
if(VisionSensor.largestObject.exists){
  if(VisionSensor.largestObject.centerX > centerFOV + offset){
    driveTrainRight.spin(directionType :: rev, 20 , velocityUnits :: pct);
    driveTrainLeft.spin(directionType :: fwd, 20 , velocityUnits :: pct);
  }
  else if(VisionSensor.largestObject.centerX < centerFOV - offset){
    driveTrainRight.spin(directionType :: fwd, 20 , velocityUnits :: pct);
    driveTrainLeft.spin(directionType :: rev, 20 , velocityUnits :: pct);
  }
  else{
    driveTrainRight.stop(brakeType :: brake);
    driveTrainLeft.stop(brakeType :: brake);
    driveTrainLeft.spin(directionType :: fwd, 75 , velocityUnits :: pct);
    driveTrainRight.spin(directionType :: fwd, 75 , velocityUnits :: pct);
  }
  }else{
    driveTrainRight.spin(directionType :: fwd, 20 , velocityUnits :: pct);
    driveTrainLeft.spin(directionType :: rev, 20 , velocityUnits :: pct);
  }
  wait(5, msec);
  }
}
