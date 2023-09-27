/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Patrick Stolinski                                         */
/*    Created:      Thu Jul 15 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LFrontDrive          motor         1               
// LRearDrive           motor         2               
// RFrontDrive          motor         3               
// RRearDrive           motor         4               
// LLift                motor         5               
// RLift                motor         6               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

competition Competition;

int liftSpeed = 75;
void liftUp(){
  Brain.Screen.print("hello");
  LLift.spin(directionType::fwd, liftSpeed, velocityUnits::pct);
  RLift.spin(directionType::fwd, liftSpeed, velocityUnits::pct);
  waitUntil(!Controller1.ButtonL1.pressing());
  LLift.stop();
  RLift.stop();
}
void liftDown(){
  LLift.spin(directionType::rev, liftSpeed, velocityUnits::pct);
  RLift.spin(directionType::rev, liftSpeed, velocityUnits::pct);
  waitUntil(!Controller1.ButtonR1.pressing());
  LLift.stop();
  RLift.stop();
}

void userControl(){
    LFrontDrive.spin(vex::directionType::fwd, Controller1.Axis3.value(), vex::velocityUnits::pct);
    LRearDrive.spin(vex::directionType::fwd, Controller1.Axis3.value(), vex::velocityUnits::pct);
    RFrontDrive.spin(vex::directionType::fwd, Controller1.Axis2.value(), vex::velocityUnits::pct);//(Axis3-Axis4)/2
    RRearDrive.spin(vex::directionType::fwd, Controller1.Axis2.value(), vex::velocityUnits::pct);//(Axis3-Axis4)/2

  Controller1.ButtonL1.pressed(liftUp);
  Controller1.ButtonR1.pressed(liftDown);

}


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Competition.drivercontrol(userControl);
  while(true){
    userControl();
  }
}
