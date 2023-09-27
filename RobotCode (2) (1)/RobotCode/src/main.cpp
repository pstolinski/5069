/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\pstolinski790                                    */
/*    Created:      Tue Oct 12 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// FR                   motor         1               
// BR                   motor         2               
// FL                   motor         3               
// BL                   motor         4               
// ForkF                motor         5               
// ForkR                motor         6               
// SnowL                digital_out   B               
// SnowR                digital_out   C               
// ForkB                motor         7               
// ForkL                motor         8               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

#include "robot-config.h"

competition Competition;

int Y1 = 0;
int X1 = 0;
int X2 = 0;
int threshold = 10;
int p = 0;

int liftSpeed = 50;

bool toggleLeft = false;
bool toggleRight = false;

void precision() {
  if (p == 0) {
    p = 1;
  } else {
    p = 0;
  }
}



void forkliftFront() {
  if(Controller1.ButtonR1.pressing() and Controller1.ButtonUp.pressing()){
  ForkF.spin(directionType::fwd, liftSpeed, velocityUnits::pct);
  }
  waitUntil(!Controller1.ButtonR1.pressing());
  ForkF.setVelocity(0, percent);
  ForkF.setStopping(brake);
  if(Controller1.ButtonR2.pressing() and Controller1.ButtonUp.pressing()){
  ForkF.spin(directionType::rev, liftSpeed, velocityUnits::pct);
  }
  waitUntil(!Controller1.ButtonR2.pressing());
  ForkF.setVelocity(0, percent);
  ForkF.setStopping(brake);
}

void forkliftBack() {
  if(Controller1.ButtonR1.pressing() and Controller1.ButtonDown.pressing()){
  ForkB.spin(directionType::fwd, liftSpeed, velocityUnits::pct);
  }
  waitUntil(!Controller1.ButtonR1.pressing());
  ForkB.setVelocity(0, percent);
  ForkB.setStopping(brake);
  if(Controller1.ButtonR2.pressing() and Controller1.ButtonDown.pressing()){
  ForkB.spin(directionType::rev, liftSpeed, velocityUnits::pct);
  }
  waitUntil(!Controller1.ButtonR2.pressing());
  ForkB.setVelocity(0, percent);
  ForkB.setStopping(brake);
}

void forkliftLeft() {
  if(Controller1.ButtonR1.pressing() and Controller1.ButtonLeft.pressing()){
  ForkL.spin(directionType::fwd, liftSpeed, velocityUnits::pct);
  }
  waitUntil(!Controller1.ButtonR1.pressing());
  ForkL.setVelocity(0, percent);
  ForkL.setStopping(brake);
  if(Controller1.ButtonR2.pressing() and Controller1.ButtonLeft.pressing()){
  ForkL.spin(directionType::rev, liftSpeed, velocityUnits::pct);
  }
  waitUntil(!Controller1.ButtonR2.pressing());
  ForkL.setVelocity(0, percent);
  ForkL.setStopping(brake);
}

void forkliftRight() {
  if(Controller1.ButtonR1.pressing() and Controller1.ButtonRight.pressing()){
  ForkR.spin(directionType::fwd, liftSpeed, velocityUnits::pct);
  }
  waitUntil(!Controller1.ButtonR1.pressing());
  ForkR.setVelocity(0, percent);
  ForkR.setStopping(brake);
  if(Controller1.ButtonR2.pressing() and Controller1.ButtonRight.pressing()){
  ForkR.spin(directionType::rev, liftSpeed, velocityUnits::pct);
  }
  waitUntil(!Controller1.ButtonR2.pressing());
  ForkR.setVelocity(0, percent);
  ForkR.setStopping(brake);
}

void toggleLeftPlow() {
  if (!toggleLeft) {
    SnowL.set(true);
    toggleLeft = true;
  } else if (toggleLeft) {
    SnowL.set(false);
    toggleLeft = false;
  }
}

void toggleRightPlow() {
  if (!toggleRight) {
    SnowR.set(true);
    toggleRight = true;
  } else if (toggleRight) {
    SnowR.set(false);
    toggleRight = false;
  }
}

void userControl() {

  Controller1.ButtonUp.pressed(forkliftFront);
  Controller1.ButtonDown.pressed(forkliftBack);
  Controller1.ButtonLeft.pressed(forkliftLeft);
  Controller1.ButtonRight.pressed(forkliftRight);
  Controller1.ButtonL1.pressed(toggleLeftPlow);
  Controller1.ButtonL2.pressed(toggleRightPlow);

  //if (p == 0) {
  //  Controller1.Screen.clearScreen();
  //  Controller1.Screen.print("Precision: Off");
  //} else {
  //  Controller1.Screen.clearScreen();
  //  Controller1.Screen.print("Precision: On");
  //}

  while (1) {
    //Controller1.ButtonA.pressed(precision);

    float CH1 = Controller1.Axis1.position();
    float CH2 = Controller1.Axis2.position();
    // float CH3 = Controller1.Axis3.position(); //redundant
    float CH4 = Controller1.Axis4.position();

    if (fabs(CH2) >= threshold) {
      Y1 = CH2;
    } else {
      Y1 = 0;
    }
    if (fabs(CH1) >= threshold) {
      X1 = CH1;
    } else {
      X1 = 0;
    }
    if (fabs(CH4) >= threshold) {
      X2 = CH4;
    } else {
      X2 = 0;
    }

    if (p == 0) {
      FR.spin(fwd, Y1 - X2 - X1, pct);
      BR.spin(fwd, Y1 - X2 + X1, pct);
      FL.spin(fwd, Y1 + X2 + X1, pct);
      BL.spin(fwd, Y1 + X2 - X1, pct);
    } else {
      FR.spin(fwd, 0.5 * (Y1 - X2 - X1), pct);
      BR.spin(fwd, 0.5 * (Y1 - X2 + X1), pct);
      FL.spin(fwd, 0.5 * (Y1 + X2 + X1), pct);
      BL.spin(fwd, 0.5 * (Y1 + X2 - X1), pct);
    }
  }
}

int main() {
  vexcodeInit();
  Competition.drivercontrol(userControl);
  while (true) {
    userControl();
  }
}
