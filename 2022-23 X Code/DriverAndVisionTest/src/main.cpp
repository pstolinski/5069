/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\pstol                                            */
/*    Created:      Sat Oct 01 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LF                   motor         20              
// LB                   motor         19              
// RF                   motor         12              
// RB                   motor         15              
// flywheelBottom       motor         13              
// flywheelTop          motor         14              
// intakeMotor          motor         16              
// flywheelRotation     rotation      11              
// Controller1          controller                    
// GPS                  gps           17              
// triggerPneumatic     led           H               
// inertialSensor       inertial      18              
// flapPneumatic        led           G               
// VisionSensor         vision        1               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <algorithm>
#include <cmath>

using namespace vex;

competition Competition;

int intakeSpeed = 100;
int flywheelSpeed = 3000;

int launchMinimums = 100;
int flywheelCautionTemp = 80;
int flywheelCurveOffset = 5;

int centerFOV = 158;
int offsetX = 10;
int visionAlignTurnSpeed = 50;

// this is the speed deceleration profile, as the robot nears its selected
// heading it begins to slow down to avoid overshooting Edit these as necessary
// -Patrick Profile currently set to 30/20/10 degrees @ 0.75/0.50/0.20 %
double firstSpeedReductionDeg = 30;  // degrees till desired heading
double secondSpeedReductionDeg = 20; // degrees till desired heading
double thirdSpeedReductionDeg = 10;  // degrees till desired heading
double firstSpeedReduction = 0.75;   // (3/4) of the original speed
double secondSpeedReduction = 0.50;  // (1/2) of the original speed
double thirdSpeedReduction = 0.20;   // (1/5) of the original speed

bool intakeToggle = false;
bool flywheelToggle = false;
bool flickToggle = false;
bool intakeOverride = false;

float goalX1;
float goalY1;
float turnAngle1;

void toggleIntake(void) {
  if(!intakeOverride){
    if (intakeToggle && !intakeOverride) {
      intakeMotor.stop();
      intakeMotor.setStopping(hold);
      intakeToggle = false;
    } else if (!intakeToggle && !intakeOverride) {
      intakeMotor.spin(forward, intakeSpeed, pct);
      intakeToggle = true;
    }
  }
}

void toggleFlywheel(void) {

  if (flywheelToggle) {
    flywheelTop.stop();
    flywheelBottom.stop();
    flywheelTop.setStopping(coast);
    flywheelBottom.setStopping(coast);
    waitUntil(!Controller1.ButtonL1.pressing());
    flywheelToggle = false;
  } else {
    if ((flywheelTop.temperature(percent) ||
         flywheelBottom.temperature(percent)) >= flywheelCautionTemp) {
      Controller1.rumble(rumbleShort);
    }
    flywheelTop.spin(forward, flywheelSpeed, rpm);
    flywheelBottom.spin(forward, flywheelSpeed, rpm);
    waitUntil(!Controller1.ButtonL1.pressing());
    flywheelToggle = true;
  }
}

void discBoost(void) {
  if (flywheelRotation.velocity(rpm) > launchMinimums) {
    triggerPneumatic.off();
    wait(500, msec);
    triggerPneumatic.on();
  } else {
    Controller1.rumble(rumbleShort);
  }
}

void toggleFlick(void) {
  if (flickToggle) {
    wait(10, msec);
    flapPneumatic.off();
    flickToggle = false;
  } else if (!flickToggle) {
    flapPneumatic.on();
    wait(10, msec);
    flickToggle = true;
  }
}

void reverseIntake(void) {
  while(Controller1.ButtonB.pressing()){
    Controller1.rumble(rumbleShort);
    intakeToggle = false;
    intakeOverride = true;
    intakeMotor.spin(reverse, 100, pct);
  }
}

void visionAlign(void) {

  while (Controller1.ButtonDown.pressing()) {
    Controller1.rumble(rumbleShort);
    VisionSensor.takeSnapshot(VisionSensor__SIG_RED);
    if (VisionSensor.largestObject.exists && Controller1.ButtonLeft.pressing()) {
      if (VisionSensor.largestObject.centerX > centerFOV + offsetX) {
        // off to the right turn right
        RF.spin(directionType::rev, visionAlignTurnSpeed, pct);
        RB.spin(directionType::fwd, visionAlignTurnSpeed, pct);
        LF.spin(directionType::fwd, visionAlignTurnSpeed, pct);
        LB.spin(directionType::rev, visionAlignTurnSpeed, pct);

      } else if (VisionSensor.largestObject.centerX < centerFOV - offsetX) {
        // off to the left turn left
        RF.spin(directionType::fwd, visionAlignTurnSpeed, pct);
        RB.spin(directionType::rev, visionAlignTurnSpeed, pct);
        LF.spin(directionType::rev, visionAlignTurnSpeed, pct);
        LB.spin(directionType::fwd, visionAlignTurnSpeed, pct);
      } else {
        Controller1.rumble(rumbleLong);
        RF.stop();
        RB.stop();
        LF.stop();
        LB.stop();
        RF.setStopping(hold);
        RB.setStopping(hold);
        LF.setStopping(hold);
        LB.setStopping(hold);
      }
    }
    VisionSensor.takeSnapshot(VisionSensor__SIG_BLUE);
    if (VisionSensor.largestObject.exists && Controller1.ButtonRight.pressing()) {
      if (VisionSensor.largestObject.centerX > centerFOV + offsetX) {
        // off to the right turn right
        RF.spin(directionType::rev, visionAlignTurnSpeed, pct);
        RB.spin(directionType::fwd, visionAlignTurnSpeed, pct);
        LF.spin(directionType::fwd, visionAlignTurnSpeed, pct);
        LB.spin(directionType::rev, visionAlignTurnSpeed, pct);

      } else if (VisionSensor.largestObject.centerX < centerFOV - offsetX) {
        // off to the left turn left
        RF.spin(directionType::fwd, visionAlignTurnSpeed, pct);
        RB.spin(directionType::rev, visionAlignTurnSpeed, pct);
        LF.spin(directionType::rev, visionAlignTurnSpeed, pct);
        LB.spin(directionType::fwd, visionAlignTurnSpeed, pct);
      } else {
        Controller1.rumble(rumbleLong);
        RF.stop();
        RB.stop();
        LF.stop();
        LB.stop();
        RF.setStopping(hold);
        RB.setStopping(hold);
        LF.setStopping(hold);
        LB.setStopping(hold);
      }
    }
  }
  RF.stop();
  RB.stop();
  LF.stop();
  LB.stop();
  RF.setStopping(hold);
  RB.setStopping(hold);
  LF.setStopping(hold);
  LB.setStopping(hold);
}

// Game Positioning System
//--Goal (1340, 1340)

int checker = 1;
void printFlywheelRPM(void) {

  Brain.Screen.setCursor(1, 1);
  Brain.Screen.setFont(monoXL);
  Brain.Screen.print("Piper PA-46-350P Malibu Mirage");
  Brain.Screen.newLine();
  Brain.Screen.newLine();
  Brain.Screen.setFont(monoM);
  Brain.Screen.print("Flywheel System");
  Brain.Screen.newLine();
  Brain.Screen.print("Rotational Velocity:    ");
  Brain.Screen.print(flywheelRotation.velocity(rpm));
  Brain.Screen.print(" rpm");
  Brain.Screen.newLine();
  if ((flywheelTop.temperature(percent) ||
       flywheelBottom.temperature(percent)) >= flywheelCautionTemp) {
    Brain.Screen.setPenColor(red);
  }
  Brain.Screen.print("Temperature Top Motor: ");
  Brain.Screen.print(flywheelTop.temperature(percent));
  Brain.Screen.print(" pct");
  Brain.Screen.newLine();
  Brain.Screen.print("Temperature Bottom Motor: ");
  Brain.Screen.print(flywheelTop.temperature(percent));
  Brain.Screen.print(" pct");
  Brain.Screen.setPenColor(white);

  Brain.Screen.newLine();
  Brain.Screen.newLine();

  Brain.Screen.print("GPS System");
  Brain.Screen.newLine();
  Brain.Screen.setFont(monoM);
  Brain.Screen.print("Current Position: ");
  Brain.Screen.print("(X: ");
  Brain.Screen.print(GPS.xPosition(mm));
  Brain.Screen.print(" mm, Y: ");
  Brain.Screen.print(GPS.yPosition(mm));
  Brain.Screen.print(" mm)");
  Brain.Screen.newLine();
  Brain.Screen.print("Robot Heading: ");
  Brain.Screen.print(GPS.heading());
  Brain.Screen.print(" degrees");
  Brain.Screen.newLine();
  Brain.Screen.print("Turn To Angle: ");
  Brain.Screen.print(turnAngle1);
  Brain.Screen.newLine();
  Brain.Screen.print("GoalX: ");
  Brain.Screen.print(goalX1);
  Brain.Screen.print(" GoalY: ");
  Brain.Screen.print(goalY1);

  Controller1.Screen.setCursor(1, 1);
  if (flywheelRotation.velocity(rpm) == 0 && checker == 1) {
    Brain.Screen.clearScreen();
    Controller1.Screen.clearLine(1);
    checker = 0;
  } else if (flywheelRotation.velocity(rpm) > 10) {
    checker = 1;
  }

  if (flywheelRotation.velocity(rpm) > launchMinimums) {
    Controller1.Screen.print("Flywheel: ");
    Controller1.Screen.print(flywheelRotation.velocity(rpm));
    if ((flywheelTop.temperature(percent) ||
         flywheelBottom.temperature(percent)) >= flywheelCautionTemp) {
      Controller1.Screen.print(" TEMP");
    } else if ((flywheelTop.temperature(percent) ||
                flywheelBottom.temperature(percent)) < flywheelCautionTemp) {
      Controller1.Screen.print(" rpm");
    }
    wait(10, msec);
  } else {
    Controller1.Screen.print("Flywheel");
    if ((flywheelTop.temperature(percent) ||
         flywheelBottom.temperature(percent)) >= flywheelCautionTemp) {
      Controller1.Screen.print(" TEMP");
    } else if ((flywheelTop.temperature(percent) ||
                flywheelBottom.temperature(percent)) < flywheelCautionTemp) {
      Controller1.Screen.print(" Below Mins");
    }
  }
}

// DO NOT TOUCH -- TURN CODE (PIVOT) -Patrick
// GPS HEADING Methods (using inertial sensor)
void turn(double angle, double initSpeed) {
  double speed = initSpeed;

  // Right Turn
  if (GPS.heading() > angle && GPS.heading() < (angle + 180)) {
    RF.spin(directionType::fwd, speed,
            velocityUnits::pct); // this is updated for right turns
    RB.spin(directionType::rev, speed, velocityUnits::pct);
    LF.spin(directionType::rev, speed, velocityUnits::pct);
    LB.spin(directionType::fwd, speed, velocityUnits::pct);
  } else {
    RF.spin(directionType::rev, speed,
            velocityUnits::pct); // this is updated for right turns
    RB.spin(directionType::fwd, speed, velocityUnits::pct);
    LF.spin(directionType::fwd, speed, velocityUnits::pct);
    LB.spin(directionType::rev, speed, velocityUnits::pct);
  }
  waitUntil(GPS.heading() <= angle && GPS.heading() >= angle - 3);
  RF.stop();
  RB.stop();
  LF.stop();
  LB.stop();

  // Brake to a stop after completing either turn
  RF.stop();
  RB.stop();
  LF.stop();
  LB.stop();
  RF.setStopping(hold);
  RB.setStopping(hold);
  LF.setStopping(hold);
  LB.setStopping(hold);
}

void drive(void) {
  // Get the raw sums of the X and Y joystick axes
  double front_left = (double)(Controller1.Axis3.position(pct) +
                               Controller1.Axis4.position(pct));
  double back_left = (double)(Controller1.Axis3.position(pct) -
                              Controller1.Axis4.position(pct));
  double front_right = (double)(Controller1.Axis3.position(pct) -
                                Controller1.Axis4.position(pct));
  double back_right = (double)(Controller1.Axis3.position(pct) +
                               Controller1.Axis4.position(pct));

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
  LF.spin(fwd, front_left, velocityUnits::pct);
  LB.spin(reverse, back_left, velocityUnits::pct);
  RF.spin(fwd, front_right, velocityUnits::pct);
  RB.spin(reverse, back_right, velocityUnits::pct);

  LF.setStopping(hold);
  LB.setStopping(hold);
  RF.setStopping(hold);
  RB.setStopping(hold);
}
/**HOW TO USE THE NEW AUTONOMOUS METHODS
turn(<left, right>, <new heading, think of a compass>, <motor velocity in %>);
example: "turn(left, 270, 30);" turns to the left to a heading of 270, from any
starting orientation. Wherever the robot points at program start, that is 0 Deg
**/

// DO NOT TOUCH -- NEW MOVE CODE (LINEAR) -Patrick
void move(std::string direction, double amountDegrees, double speed) {
  if (direction == "forward") {
    RF.setVelocity(speed, percent);
    RB.setVelocity(speed, percent);
    LF.setVelocity(speed, percent);
    LB.setVelocity(speed, percent);
    RF.spinFor(directionType::fwd, amountDegrees, degrees, false);
    RB.spinFor(directionType::rev, amountDegrees, degrees, false);
    LF.spinFor(directionType::fwd, amountDegrees, degrees, false);
    LB.spinFor(directionType::rev, amountDegrees, degrees, true);
  }
  if (direction == "backward") {
    RF.setVelocity(speed, percent);
    RB.setVelocity(speed, percent);
    LF.setVelocity(speed, percent);
    LB.setVelocity(speed, percent);
    RF.spinFor(directionType::rev, amountDegrees, degrees, false);
    RB.spinFor(directionType::fwd, amountDegrees, degrees, false);
    LF.spinFor(directionType::rev, amountDegrees, degrees, false);
    LB.spinFor(directionType::fwd, amountDegrees, degrees, true);
  }
  if (direction == "left") {
    RF.setVelocity(speed, percent);
    RB.setVelocity(speed, percent);
    LF.setVelocity(speed, percent);
    LB.setVelocity(speed, percent);
    RF.spinFor(directionType::fwd, amountDegrees, degrees, false);
    RB.spinFor(directionType::fwd, amountDegrees, degrees, false);
    LF.spinFor(directionType::rev, amountDegrees, degrees, false);
    LB.spinFor(directionType::rev, amountDegrees, degrees, true);
  }
  if (direction == "right") {
    RF.setVelocity(speed, percent);
    RB.setVelocity(speed, percent);
    LF.setVelocity(speed, percent);
    LB.setVelocity(speed, percent);
    RF.spinFor(directionType::rev, amountDegrees, degrees, false);
    RB.spinFor(directionType::rev, amountDegrees, degrees, false);
    LF.spinFor(directionType::fwd, amountDegrees, degrees, false);
    LB.spinFor(directionType::fwd, amountDegrees, degrees, true);
  }
  // Brake to a stop after any direction move
  RF.stop();
  RB.stop();
  LF.stop();
  LB.stop();
  RF.setStopping(hold);
  RB.setStopping(hold);
  LF.setStopping(hold);
  LB.setStopping(hold);
  waitUntil(((RF.velocity(rpm)) && (RB.velocity(rpm)) && (LF.velocity(rpm)) &&
             (LB.velocity(rpm))) == 0);
}

// DO NOT TOUCH -- TURN CODE (PIVOT) -Patrick
// New Autonomous Methods (using inertial sensor)

void autoTurn(turnType dir, double angle, double initSpeed) {
  double speed = initSpeed;
  // Right Turn
  if (dir == right) {
    while (inertialSensor.rotation(degrees) < angle) {
      // while far away go at max speed
      if (inertialSensor.rotation(degrees) < angle - firstSpeedReductionDeg) {
        RF.spin(directionType::rev, speed,
                velocityUnits::pct); // this is updated for right turns
        RB.spin(directionType::fwd, speed, velocityUnits::pct);
        LF.spin(directionType::fwd, speed, velocityUnits::pct);
        LB.spin(directionType::rev, speed, velocityUnits::pct);
      }
      // first notch of slow
      if (inertialSensor.rotation(degrees) < angle - secondSpeedReductionDeg) {
        speed = initSpeed * firstSpeedReduction;
        RF.spin(directionType::rev, speed, velocityUnits::pct);
        RB.spin(directionType::fwd, speed, velocityUnits::pct);
        LF.spin(directionType::fwd, speed, velocityUnits::pct);
        LB.spin(directionType::rev, speed, velocityUnits::pct);
      }
      // second notch of slow
      if (inertialSensor.rotation(degrees) < angle - thirdSpeedReductionDeg)
        speed = initSpeed * secondSpeedReduction;
      RF.spin(directionType::rev, speed,
              velocityUnits::pct); // this is updated for right turns
      RB.spin(directionType::fwd, speed, velocityUnits::pct);
      LF.spin(directionType::fwd, speed, velocityUnits::pct);
      LB.spin(directionType::rev, speed, velocityUnits::pct);

      // third notch of slow
      if (inertialSensor.rotation(degrees) < angle - firstSpeedReductionDeg)
        speed = initSpeed * thirdSpeedReduction;
      RF.spin(directionType::rev, speed,
              velocityUnits::pct); // this is updated for right turns
      RB.spin(directionType::fwd, speed, velocityUnits::pct);
      LF.spin(directionType::fwd, speed, velocityUnits::pct);
      LB.spin(directionType::rev, speed, velocityUnits::pct);
    }
  }
  // Left Turn
  if (dir == right) {
    while (inertialSensor.rotation(degrees) < angle) {
      // while far away go at max speed
      if (inertialSensor.rotation(degrees) < angle - firstSpeedReductionDeg) {
        RF.spin(directionType::fwd, speed, velocityUnits::pct); // this is updated for left turns
        RB.spin(directionType::rev, speed, velocityUnits::pct);
        LF.spin(directionType::rev, speed, velocityUnits::pct);
        LB.spin(directionType::fwd, speed, velocityUnits::pct);
      }
      // first notch of slow
      if (inertialSensor.rotation(degrees) < angle - secondSpeedReductionDeg) {
        speed = initSpeed * firstSpeedReduction;
        RF.spin(directionType::fwd, speed, velocityUnits::pct); // this is updated for left turns
        RB.spin(directionType::rev, speed, velocityUnits::pct);
        LF.spin(directionType::rev, speed, velocityUnits::pct);
        LB.spin(directionType::fwd, speed, velocityUnits::pct);
      }
      // second notch of slow
      if (inertialSensor.rotation(degrees) < angle - thirdSpeedReductionDeg)
        speed = initSpeed * secondSpeedReduction;
      RF.spin(directionType::fwd, speed, velocityUnits::pct); // this is updated for left turns
        RB.spin(directionType::rev, speed, velocityUnits::pct);
        LF.spin(directionType::rev, speed, velocityUnits::pct);
        LB.spin(directionType::fwd, speed, velocityUnits::pct);

      // third notch of slow
      if (inertialSensor.rotation(degrees) < angle - firstSpeedReductionDeg)
        speed = initSpeed * thirdSpeedReduction;
      RF.spin(directionType::fwd, speed, velocityUnits::pct); // this is updated for left turns
        RB.spin(directionType::rev, speed, velocityUnits::pct);
        LF.spin(directionType::rev, speed, velocityUnits::pct);
        LB.spin(directionType::fwd, speed, velocityUnits::pct);
    }
  }
  // Brake to a stop after completing either turn
  RF.stop();
  RB.stop();
  LF.stop();
  LB.stop();
  RF.setStopping(hold);
  RB.setStopping(hold);
  LF.setStopping(hold);
  LB.setStopping(hold);
  waitUntil(((RF.velocity(rpm)) && (RB.velocity(rpm)) && (LF.velocity(rpm)) &&
             (LB.velocity(rpm))) == 0);
}

////////////////////////////////////////////////////////////////////
/**
For safety, do not set a turn velocity to greater than 50%. Doing so will risk
overshooting the turn. Up until the competition I placed a command to calibrate
the intertial sensor at the beginning of every autonomous run. This will let you
run your autonomous again and again without having to worry about the sensor
calibration. It will delay the robot movements for 3000 msecs to allow the
process to complete properly. For the competition this will be removed. Instead
to calibrate the sensor, you will PLACE the robot FIRST, start the PROGRAM, and
the sensor will calibrate during pre_aunton();

--------------------
HOW TO USE THE NEW AUTONOMOUS METHODS

move(<forward, backward, left, right>, <time in msec>, <motor velocity in %>);
example: "move(forward, 1250, 75);" moves forward, for 1250 msec, at 75% motor
velocity

autoTurn(<left, right>, <new heading, think of a compass>, <motor velocity in
%>); example: "turn(left, 270, 30);" turns to the left to a heading of 270, from
any starting orientation. Wherever the robot points at program start, that is 0
Deg

For your other actuators like ArmGroup, etc, just add in the basic
MotorGroup.spin() w/ a wait() statement after and MotorGroup.stop to control
those systems.
--------------------
**/


void flywheelController(int amountRPM){//essentially cruise control
  if(amountRPM == 0){
      flywheelBottom.stop();
      flywheelTop.stop();
      flywheelBottom.setStopping(coast);
      flywheelTop.setStopping(coast);
  }
  if(amountRPM > 0){
      flywheelBottom.setVelocity(amountRPM, rpm);
      flywheelTop.setVelocity(amountRPM, rpm);
      flywheelBottom.spin(forward);
      flywheelTop.spin(forward);
  }
}

void verifyLaunchIntegrity(int requiredRPM){
  waitUntil(flywheelRotation.velocity(rpm) >= requiredRPM);
  if(flywheelRotation.velocity(rpm) >= requiredRPM){//LAUNCH
    triggerPneumatic.off();
    wait(75, msec);
    triggerPneumatic.on();
    wait(75, msec);
  }
}



//autoTurn(left right, angle, initSpeed);
//move("direction", amountDegrees, speed);


// original autonomous method -- EDIT AUTO HERE
void autonomous(void) {
  intakeMotor.setVelocity(intakeSpeed, pct);
  inertialSensor.calibrate(); //-- we will do this during pre auton eventually -- HAVE
                        // PATRICK CHANGE THIS BEFORE COMPETITION
  wait(3000, msec); //REMOVE THIS REMOVE THIS
  //REMOVE REMOVE REMOVE - REMINDERS LIST


  //autoTurn(left, 1)

  /*move("left", 200, 100);
  move("right", 100, 100);
  move("left", 200, 100);
  move("right", 200, 100);
  autoTurn(right, 110, 100);
  intakeMotor.spin(forward);
  move("forward", 900, 100);
  wait(2000, msec);
  move("backward", 300, 100);
  autoTurn(left, 110, 100);
  flywheelController(2800);
  verifyLaunchIntegrity(2700);
  wait(1000, msec);
  verifyLaunchIntegrity(2700);
  wait(1000, msec);
  verifyLaunchIntegrity(2700);
  flywheelController(0);

  flywheelController(2800);
  autoTurn(left, 110, 100);
  verifyLaunchIntegrity(2700);
  flywheelController(0);*/


  // ArmGroup.spin(directionType::rev, 75, velocityUnits::pct);
  // wait(500, msec);
  // ArmGroup.stop();
  // move("backward", 500, 100);
}

// Driver Control

void usercontrol(void) {
  GPS.calibrate();
  while (true) {

    drive();

    float botX = 1800 + GPS.xPosition(mm);
    float botY = 1800 + GPS.yPosition(mm);
    float goalX = 3140 - botX;
    float goalY = 3140 - botY;

    goalX1 = goalX;
    goalY1 = goalY;

    float turnAngle = std::atan(goalX / goalY) * 57.2957795;

    turnAngle1 = turnAngle - flywheelCurveOffset;

    if (Controller1.ButtonUp.pressing()) {
      turn(turnAngle, 50);
      waitUntil(!Controller1.ButtonUp.pressing());
      wait(500, msec);
    }
    Controller1.ButtonB.pressed(reverseIntake);
    Controller1.ButtonDown.pressed(visionAlign);
    Controller1.ButtonR2.pressed(toggleFlick);
    Controller1.ButtonL1.pressed(toggleFlywheel);
    Controller1.ButtonL2.pressed(toggleIntake);
    Controller1.ButtonR1.pressed(discBoost);

    // © AntiJAM - Copyright 2022 Millard North Robotics Team
    if (intakeToggle && !intakeOverride) {
      if ((intakeMotor.velocity(percent) == 0) && intakeToggle && !intakeOverride) {
        intakeMotor.spin(reverse, 100, pct);
      } else if ((intakeMotor.velocity(percent) < -50) && intakeToggle && !intakeOverride) {
        intakeMotor.spin(forward, intakeSpeed, pct);
      }
    }

    //Cancel out intake reverse just in case
    if(intakeOverride && !Controller1.ButtonB.pressing()){
    intakeMotor.stop();
    intakeMotor.setStopping(coast);
    intakeOverride = false;
  }

    printFlywheelRPM();
  }
}

int main() {
  triggerPneumatic.on();
  flapPneumatic.on();
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  GPS.calibrate();
  // Set up callbacks for autonomous and driver control periods.
  // Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  Competition.autonomous(autonomous);

  // Run the pre-autonomous function.
  // pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {

    wait(10, msec);
  }
}
