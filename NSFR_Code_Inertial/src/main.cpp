
/* */
/* Module: main.cpp */
/* Author: C:\Users\ */
/* Created:  */
/* Description: */
/* */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// DL1                  motor         1               
// DL2                  motor         13              
// DR1                  motor         10              
// DR2                  motor         19              
// Intake               motor         15              
// Controller1          controller                    
// Claw                 motor         12              
// ArmGroup             motor_group   20, 11          
// Pnuematic            led           C               
// Inertial             inertial      21              
// ---- END VEXCODE CONFIGURED DEVICES ----

// CHANGES: We want B to raise claw, down arrow to drop it.
#include "vex.h"

using namespace vex;

#include "robot-config.h"
#include <algorithm>
#include <cmath>

competition Competition;

// IGNORE

// int centerFOV = 158;
// int offset = 10;
// int rearRoller = 80;
// int frontRoller = 100;
// int intakeSpeed = 200;
// int driveSpeed = 135;
// if we are blue, set to 1, if we are red, set to two
// int blueOrRed = 0;
// bool origComplete = false;

// STOP IGNORING HERE
// Arm Group is 20 and 12
// change the drivetrain code ports

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

void EBreak() { Pnuematic.on(); }
void EBreakoff() { Pnuematic.off(); }

//this is the speed deceleration profile, as the robot nears its selected heading it begins to slow down to avoid overshooting
//Edit these as necessary -Patrick
//Profile currently set to 30/20/10 degrees @ 0.75/0.50/0.20 %
double firstSpeedReductionDeg = 30; // degrees till desired heading
double secondSpeedReductionDeg = 20; // degrees till desired heading
double thirdSpeedReductionDeg = 10; // degrees till desired heading
double firstSpeedReduction = 0.75; // (3/4) of the original speed
double secondSpeedReduction = 0.50; // (1/2) of the original speed
double thirdSpeedReduction = 0.20; // (1/5) of the original speed 


//DO NOT TOUCH -- NEW MOVE CODE (LINEAR) -Patrick
void move(std::string direction, double time, double speed){
  if(direction == "forward"){
    DR1.spin(directionType::fwd, speed, velocityUnits::pct);
    DR2.spin(directionType::rev, speed, velocityUnits::pct);
    DL1.spin(directionType::fwd, speed, velocityUnits::pct);
    DL2.spin(directionType::rev, speed, velocityUnits::pct);
    wait(time, msec);
  }
  if(direction == "backward"){
    DR1.spin(directionType::rev, speed, velocityUnits::pct);
    DR2.spin(directionType::fwd, speed, velocityUnits::pct);
    DL1.spin(directionType::rev, speed, velocityUnits::pct);
    DL2.spin(directionType::fwd, speed, velocityUnits::pct);
    wait(time, msec);
  }
  if(direction == "left"){
    DR1.spin(directionType::fwd, speed, velocityUnits::pct);
    DR2.spin(directionType::fwd, speed, velocityUnits::pct);
    DL1.spin(directionType::rev, speed, velocityUnits::pct);
    DL2.spin(directionType::rev, speed, velocityUnits::pct);
    wait(time, msec);
  }
  if(direction == "right"){
    DR1.spin(directionType::rev, speed, velocityUnits::pct);
    DR2.spin(directionType::rev, speed, velocityUnits::pct);
    DL1.spin(directionType::fwd, speed, velocityUnits::pct);
    DL2.spin(directionType::fwd, speed, velocityUnits::pct);
    wait(time, msec);
  }
  //Brake to a stop after any direction move
  DR1.stop();
  DR2.stop();
  DL1.stop();
  DL2.stop();
  DR1.setStopping(brake);
  DR2.setStopping(brake);
  DL1.setStopping(brake);
  DL2.setStopping(brake);
}

//DO NOT TOUCH -- TURN CODE (PIVOT) -Patrick
//New Autonomous Methods (using inertial sensor)
void turn(turnType dir, double angle, double initSpeed){
  double speed = initSpeed;
  //Right Turn
  if(dir == right){
    while(Inertial.rotation(degrees) < angle){
      //while far away go at max speed
      if(Inertial.rotation(degrees) < angle - firstSpeedReductionDeg){
        DR1.spin(directionType::rev, speed, velocityUnits::pct);//this is updated for right turns
        DR2.spin(directionType::fwd, speed, velocityUnits::pct);
        DL1.spin(directionType::fwd, speed, velocityUnits::pct);
        DL2.spin(directionType::rev, speed, velocityUnits::pct);
    }
    //first notch of slow
    if(Inertial.rotation(degrees) < angle - secondSpeedReductionDeg){
      speed = initSpeed * firstSpeedReduction;
      DR1.spin(directionType::rev, speed, velocityUnits::pct);
      DR2.spin(directionType::fwd, speed, velocityUnits::pct);
      DL1.spin(directionType::fwd, speed, velocityUnits::pct);
      DL2.spin(directionType::rev, speed, velocityUnits::pct);
    }
    //second notch of slow
    if(Inertial.rotation(degrees) < angle - thirdSpeedReductionDeg)
    speed = initSpeed * secondSpeedReduction;
      DR1.spin(directionType::rev, speed, velocityUnits::pct);
      DR2.spin(directionType::fwd, speed, velocityUnits::pct);
      DL1.spin(directionType::fwd, speed, velocityUnits::pct);
      DL2.spin(directionType::rev, speed, velocityUnits::pct);
    
    //third notch of slow
    if(Inertial.rotation(degrees) < angle - firstSpeedReductionDeg)
    speed = initSpeed * thirdSpeedReduction;
      DR1.spin(directionType::rev, speed, velocityUnits::pct);
      DR2.spin(directionType::fwd, speed, velocityUnits::pct);
      DL1.spin(directionType::fwd, speed, velocityUnits::pct);
      DL2.spin(directionType::rev, speed, velocityUnits::pct);
    }
  }
  //Left Turn
  if(dir == left){
    while(Inertial.rotation(degrees) > angle){
      //while far away go at max speed
      if(Inertial.rotation(degrees) > angle + firstSpeedReductionDeg){
        DR1.spin(directionType::fwd, speed, velocityUnits::pct);//this is updated for right turns
        DR2.spin(directionType::rev, speed, velocityUnits::pct);
        DL1.spin(directionType::rev, speed, velocityUnits::pct);
        DL2.spin(directionType::fwd, speed, velocityUnits::pct);
      }
    //first notch of slow
      if(Inertial.rotation(degrees) > angle + secondSpeedReductionDeg){
        speed = initSpeed * firstSpeedReduction;
        DR1.spin(directionType::fwd, speed, velocityUnits::pct);
        DR2.spin(directionType::rev, speed, velocityUnits::pct);
        DL1.spin(directionType::rev, speed, velocityUnits::pct);
        DL2.spin(directionType::fwd, speed, velocityUnits::pct);
      }
    //second notch of slow
      if(Inertial.rotation(degrees) > angle + thirdSpeedReductionDeg){
        speed = initSpeed * secondSpeedReduction;
        DR1.spin(directionType::fwd, speed, velocityUnits::pct);
        DR2.spin(directionType::rev, speed, velocityUnits::pct);
        DL1.spin(directionType::rev, speed, velocityUnits::pct);
        DL2.spin(directionType::fwd, speed, velocityUnits::pct);
      }
    //third notch of slow
      if(Inertial.rotation(degrees) > angle + firstSpeedReductionDeg){
        speed = initSpeed * thirdSpeedReduction;
        DR1.spin(directionType::fwd, speed, velocityUnits::pct);
        DR2.spin(directionType::rev, speed, velocityUnits::pct);
        DL1.spin(directionType::rev, speed, velocityUnits::pct);
        DL2.spin(directionType::fwd, speed, velocityUnits::pct);
      }
    }
  }
  //Brake to a stop after completing either turn
  DR1.stop();
  DR2.stop();
  DL1.stop();
  DL2.stop();
  DR1.setStopping(brake);
  DR2.setStopping(brake);
  DL1.setStopping(brake);
  DL2.setStopping(brake);
}

////////////////////////////////////////////////////////////////////
/**
For safety, do not set a turn velocity to greater than 50%. Doing so will risk overshooting the turn.
Up until the competition I placed a command to calibrate the intertial sensor at the beginning of every autonomous run. This will let you run your 
autonomous again and again without having to worry about the sensor calibration.
It will delay the robot movements for 3000 msecs to allow the process to complete properly. 
For the competition this will be removed. Instead to calibrate the sensor, you will PLACE the robot FIRST, start the PROGRAM, and the sensor will calibrate
during pre_aunton();

--------------------
HOW TO USE THE NEW AUTONOMOUS METHODS

move(<forward, backward, left, right>, <time in msec>, <motor velocity in %>);
example: "move(forward, 1250, 75);" moves forward, for 1250 msec, at 75% motor velocity

turn(<left, right>, <new heading, think of a compass>, <motor velocity in %>);
example: "turn(left, 270, 30);" turns to the left to a heading of 270, from any starting orientation. Wherever the robot points at program start, that is 0 Deg

For your other actuators like ArmGroup, etc, just add in the basic MotorGroup.spin() w/ a wait() statement after and MotorGroup.stop to control those systems.
--------------------
**/

//original autonomous method -- EDIT AUTO HERE
void Autonomous(void){
  Inertial.calibrate();//-- we will do this during pre auton eventually -- HAVE PATRICK CHANGE THIS BEFORE COMPETITION
  wait(3000, msec);//Do not remove this, it will add a 3 second delay at the start of the autonomous run BUT IS NECESSARY FOR THE SENSOR TO CALIBRATE PROPERLY
  //START AUTONOMOUS HERE
  turn(right, 90, 30);
  wait(500, msec);
  turn(left, 0, 30);
  wait(500, msec);
  move("forward", 500, 100);
  ArmGroup.spin(directionType::rev, 75, velocityUnits::pct);
  wait(500, msec);
  ArmGroup.stop();
  move("backward", 500, 100);
  wait(500, msec);
  move("left", 500, 100);
  wait(500, msec);
  move("right", 500, 100);  
 //the above was the test code I showed you during 5th hour
}
////////////////////////////////////////////////////////////////////

//I believe these are your driver control methods -- not touching them -Patrick
void GoalGrabDown() {
  Intake.spin(directionType::fwd, 75, velocityUnits::pct);
  waitUntil(!Controller1.ButtonR2.pressing());
  Intake.stop();
}
void GoalGrabUp() {
  Intake.spin(directionType::rev, 75, velocityUnits::pct);
  waitUntil(!Controller1.ButtonL2.pressing());
  Intake.stop();
}
void ArmUp() {
  ArmGroup.spin(directionType::rev, 75, velocityUnits::pct);
  waitUntil(!Controller1.ButtonB.pressing());
  ArmGroup.stop();
}
void ArmDown() {
  ArmGroup.spin(directionType::fwd, 75, velocityUnits::pct);
  waitUntil(!Controller1.ButtonDown.pressing());
  ArmGroup.stop();
}
void Flick() {
  ArmGroup.spin(directionType::rev, 75, velocityUnits::pct);
  wait(100, msec);
  Claw.spin(directionType::fwd, 75, velocityUnits::pct);
  wait(700, msec);
  ArmGroup.stop();
  Claw.stop();
}
void FlickNot() {
  ArmGroup.spin(directionType::fwd, 75, velocityUnits::pct);
  wait(100, msec);
  Claw.spin(directionType::rev, 75, velocityUnits::pct);
  wait(700, msec);
  ArmGroup.stop();
  Claw.stop();
}
void ClawOpen() {
  Claw.spin(directionType::fwd, 75, velocityUnits::pct);
  waitUntil(!Controller1.ButtonL1.pressing());
  Claw.stop();
}
void ClawClose() {
  Claw.spin(directionType::rev, 75, velocityUnits::pct);
  waitUntil(!Controller1.ButtonR1.pressing());
  Claw.stop();
}

//Drive Control Function -- do not touch this 
void usercontrol(void) {
  while (true) {
    vexcodeInit();
    // Get the raw sums of the X and Y joystick axes
    double front_left = (double)(Controller1.Axis3.position(pct) +
                                 Controller1.Axis4.position(pct));
    double back_left = (double)(Controller1.Axis3.position(pct) -
                                Controller1.Axis4.position(pct));
    double front_right = (double)(Controller1.Axis3.position(pct) -
                                  Controller1.Axis4.position(pct));
    double back_right = (double)(Controller1.Axis3.position(pct) +
                                 Controller1.Axis4.position(pct));
    if (Controller1.ButtonY.pressing())
      EBreak();
    if (Controller1.ButtonRight.pressing())
      EBreakoff();

    // Find the largest possible sum of X and Y
    double max_raw_sum = (double)(abs(Controller1.Axis3.position(pct)) +
                                  abs(Controller1.Axis4.position(pct)));

    // Find the largest joystick value
    double max_XYstick_value =
        (double)(std::max(abs(Controller1.Axis3.position(pct)),
                          abs(Controller1.Axis4.position(pct))));

    // The largest sum will be scaled down to the largest joystick value, and
    // the others will be scaled by the same amount to preserve directionality
    if (max_raw_sum != 0) {
      front_left = front_left / max_raw_sum * max_XYstick_value;
      back_left = back_left / max_raw_sum * max_XYstick_value;
      front_right = front_right / max_raw_sum * max_XYstick_value;
      back_right = back_right / max_raw_sum * max_XYstick_value;
    }

    // Now to consider rotation
    // Naively add the rotational axis
    front_left = front_left + Controller1.Axis1.position(pct);
    back_left = back_left + Controller1.Axis1.position(pct);
    front_right = front_right - Controller1.Axis1.position(pct);
    back_right = back_right - Controller1.Axis1.position(pct);

    // What is the largest sum, or is 100 larger?
    max_raw_sum =
        std::max(std::abs(front_left),
                 std::max(std::abs(back_left),
                          std::max(std::abs(front_right),
                                   std::max(std::abs(back_right), 100.0))));

    // Scale everything down by the factor that makes the largest only 100, if
    // it was over
    front_left = front_left / max_raw_sum * 100.0;
    back_left = back_left / max_raw_sum * 100.0;
    front_right = front_right / max_raw_sum * 100.0;
    back_right = back_right / max_raw_sum * 100.0;

    // Write the manipulated values out to the motors
    DL1.spin(fwd, front_left, velocityUnits::pct);
    DL2.spin(reverse, back_left, velocityUnits::pct);
    DR1.spin(fwd, front_right, velocityUnits::pct);
    DR2.spin(reverse, back_right, velocityUnits::pct);

    Controller1.ButtonR1.pressed(ClawClose);
    Controller1.ButtonL1.pressed(ClawOpen);
    Controller1.ButtonL2.pressed(GoalGrabUp);
    Controller1.ButtonR2.pressed(GoalGrabDown);
    Controller1.ButtonB.pressed(ArmUp);
    Controller1.ButtonDown.pressed(ArmDown);
    Controller1.ButtonX.pressed(Flick);
    Controller1.ButtonUp.pressed(FlickNot);

    Claw.setStopping(hold);
    Intake.setStopping(hold);
    ArmGroup.setStopping(hold);
  }
}

int main() {
  Intake.setStopping(hold);
  ArmGroup.setStopping(hold);
  Claw.setStopping(hold);
  Competition.autonomous(Autonomous);
  Competition.drivercontrol(usercontrol);
}