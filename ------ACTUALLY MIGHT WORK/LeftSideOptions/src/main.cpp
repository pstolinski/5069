/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\pstolinski                                       */
/*    Created:      Mon Nov 15 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller
// DriveBooster         motor         19
// Tread                motor         13
// MotorGroup1          motor_group   14, 20
// Drivetrain           drivetrain    17, 13, 15, 18, 12
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

#include "robot-config.h"

competition Competition;

int autonomousInt =2;

int treadSpeedSet = 75;
int liftSpeedSet = 100;
int y = 0;
int x = 0;

void pre_auton() { vexcodeInit(); }

void onScreenPressed() {
  if (Brain.Screen.xPosition() > 250) {
    if (Brain.Screen.yPosition() > 125) {

      // blue
      autonomousInt = 1;
    } else {
      // green
      autonomousInt = 2;
    }
  } else {
    if (Brain.Screen.yPosition() > 125) {
      // Red Box Pressed
    } else {
      // White Box Pressed
    }
  }
}

void autonomous() {
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print(autonomousInt);
  if (autonomousInt == 1) {
    // priority middle
    MotorGroup1.setPosition(0, degrees);
    Drivetrain.setHeading(0, degrees);
    Drivetrain.setDriveVelocity(100, pct);
    MotorGroup1.setVelocity(100, pct);
    // do not change anything above

    // unfold arms
    MotorGroup1.spinToPosition(-490, degrees);
    MotorGroup1.setStopping(hold);

    // drive forward initially
    Drivetrain.driveFor(forward, 36, inches);
    // turn at left side neutral yellow goal
    Drivetrain.turnToHeading(13, degrees);
    // drive to the goal
    Drivetrain.driveFor(forward, 13, inches);
    // start the tread spinning
    Tread.spin(forward, 100, pct);

    // pick up the goal
    MotorGroup1.spinToPosition(-20, degrees);
    MotorGroup1.spinToPosition(-40, degrees);
    MotorGroup1.spinToPosition(-20, degrees);
    MotorGroup1.setStopping(hold);
    // goal should be in robot now, drive backwards into home zone
    Drivetrain.driveFor(reverse, 11, inches);
    wait(1500, msec);
    Tread.stop();
    // turn at MIDDLE mobile goal
    // lower arms again
    MotorGroup1.spinToPosition(-490, degrees);
    Drivetrain.turnToHeading(55, degrees);
    
    // drive at middle mobile goal
    Drivetrain.driveFor(forward, 5, inches);
    Drivetrain.turnToHeading(63, degrees);
    Drivetrain.driveFor(forward, 35, inches);
    // pick up middle mobile goal like a HALF inch off the ground -- we do NOT
    // WANT TO TAKE IT IN! Just move it into our home zone
    MotorGroup1.spinToPosition(-20, degrees);
    MotorGroup1.spinToPosition(-40, degrees);
    MotorGroup1.spinToPosition(-20, degrees);
    MotorGroup1.setStopping(hold);
    // MotorGroup1.spinToPosition(-300, degrees);
    // Back up into home zone
    Drivetrain.driveFor(reverse, 35, inches);
    Drivetrain.turnToHeading(0, degrees);
    Drivetrain.driveFor(reverse, 20, inches);
    // lower the mobile goal
    MotorGroup1.spinToPosition(-490, degrees);
  } else if (autonomousInt == 2) {
    MotorGroup1.setPosition(0, degrees);
    Drivetrain.setHeading(0, degrees);
    Drivetrain.setDriveVelocity(100, pct);
    MotorGroup1.setVelocity(100, pct);
    // do not touch anything above

    // lower arms
    MotorGroup1.spinToPosition(-490, degrees);
    MotorGroup1.setStopping(hold); 

    // move forward
    Drivetrain.driveFor(forward, 39, inches);
    // turn at MIDDLE MOBILE GOAL FIRST
    Drivetrain.turnToHeading(47, degrees);
    // drive AROUND THE OBSTRUCTING DONUTS
    Drivetrain.driveFor(forward, 1, inches);
    // FINAL TURN TO ALIGN WITH MIDDLE MOBILE GOAL
    Drivetrain.turnToHeading(62, degrees);
    // drive at middle mobile goal
    Drivetrain.driveFor(forward, 30, inches);
    Drivetrain.setDriveVelocity(40, percent);
    Drivetrain.driveFor(forward, 5, inches);
    // pick it up off the ground
    // pick it up off the ground
    MotorGroup1.setVelocity(25, percent);
    MotorGroup1.spinToPosition(-450, degrees);
    wait(1000, msec);
    Drivetrain.driveFor(forward, 3, inches);
    MotorGroup1.spinToPosition(-100, degrees);
    MotorGroup1.setStopping(hold);
    // back up
    Drivetrain.driveFor(reverse, 45, inches);
    Drivetrain.turnToHeading(0, degrees);
    Drivetrain.driveFor(reverse, 30, inches);
    // turn to place middle goal in our home zone, in front of our platform
    MotorGroup1.spin(forward, -490, pct);
  }
}

int boosterSpeed() {
  if (Controller1.ButtonR1.pressing()) {
    return -150;
  } else if (Controller1.ButtonR2.pressing()) {
    return 150;
  } else {
    return 0;
    DriveBooster.setStopping(hold);
  }
}

void drive() {
  if (Controller1.ButtonR1.pressing() || Controller1.ButtonR2.pressing()) {

    DriveBooster.spin(fwd, boosterSpeed(), pct);
  } else {

    DriveBooster.spin(fwd, boosterSpeed(), pct);
    DriveBooster.setStopping(hold);
  }
}

int treadSpeed() {
  if (Controller1.ButtonDown.pressing()) {
    return (treadSpeedSet * -1);
  } else if (Controller1.ButtonUp.pressing()) {
    return treadSpeedSet;
  } else {
    return 0;
  }
}

void tread() { Tread.spin(fwd, treadSpeed(), pct); }

int liftSpeed() {
  if (Controller1.ButtonL1.pressing()) {
    return liftSpeedSet;
  } else if (Controller1.ButtonL2.pressing()) {
    return (liftSpeedSet * -1);
  } else {
    return 0;
  }
}

void lift() { MotorGroup1.spin(forward, liftSpeed(), pct); }

void userControl() {
  vexcodeInit();
  MotorGroup1.setStopping(hold);
  while (true) {
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.setFont(propXXL);
    wait(100, msec);
    drive();
    tread();
    lift();
    // flick();
  }
}

void printUI(void) {
  Brain.Screen.setFillColor(yellow);
  Brain.Screen.drawRectangle(10, 30, 100, 100);
  Brain.Screen.drawRectangle(200, 30, 100, 100);
  Brain.Screen.setCursor(1, 10);
  Brain.Screen.setFont(propM);
  Brain.Screen.setPenColor(white);
  Brain.Screen.setFillColor(black);
  Brain.Screen.print("Select Neutral Mobile Goal Priority");
  Brain.Screen.setCursor(4, 5);
  Brain.Screen.setPenColor(black);
  Brain.Screen.setFillColor(yellow);
  Brain.Screen.print("Left");
  Brain.Screen.setCursor(4, 23);
  Brain.Screen.print("Middle");
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(userControl);
  pre_auton();
  printUI();
  while (true) {
    Brain.Screen.pressed(onScreenPressed);
    wait(10, msec);
  }
}