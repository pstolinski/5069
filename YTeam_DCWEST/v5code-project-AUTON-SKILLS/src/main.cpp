/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\pvadd                                            */
/*    Created:      Fri Jan 06 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Motor17              motor         17              
// Motor18              motor         18              
// Motor15              motor         15              
// Motor16              motor         16              
// Pneu                 led           A               
// Drivetrain           drivetrain    13, 14, 2, 4    
// Controller1          controller                    
// VPneu                led           D               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

competition Competition;

void auton () {
  Pneu.on();
  VPneu.on();
  Motor15.setVelocity(50, percentUnits :: pct);
  Motor16.setVelocity(50, percentUnits :: pct);
  Motor17.setVelocity(100 , percentUnits :: pct);
  Motor18.setVelocity(100, percentUnits :: pct);
  Drivetrain.setDriveVelocity(40, percent);
  Drivetrain.setTurnVelocity(20, percent);
  //get a roller
  Drivetrain.driveFor(reverse, 3, inches);
  Motor15.spinFor(forward, 650, msec);
  //get second roller
  Drivetrain.setDriveVelocity(80, percent);
  Drivetrain.driveFor(forward, 13, inches);
  Drivetrain.setDriveVelocity(40, percent);
  //Drivetrain.driveFor(reverse, 4, inches);
  Drivetrain.turn(left);
  wait(1200, msec);
  Drivetrain.stop();
  Drivetrain.setDriveVelocity(80, percent);
  Drivetrain.driveFor(reverse, 14, inches);
  Motor15.spinFor(forward, 750, msec);
  Drivetrain.driveFor(forward, 4, inches);
  //expand
  Drivetrain.turn(right);
  wait(600, msec);
  Drivetrain.stop();
  Drivetrain.driveFor(forward, 70, inches);
  //Drivetrain.turn(right);
  //wait(500, msec);
  //Drivetrain.stop();
  Pneu.off();
  Drivetrain.driveFor(reverse, 60, inches);
  VPneu.off();

}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Competition.autonomous(auton);
}
