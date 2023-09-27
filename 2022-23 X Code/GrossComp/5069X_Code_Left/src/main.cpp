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
// intakeTwo            motor         10              
// expansionPneumaticF  led           F               
// expansionPneumaticL  led           E               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <algorithm>
#include <cmath>

using namespace vex;

competition Competition;

int intakeSpeed = 95;
int flywheelSpeed = 140;

int launchMinimums = 100;
int flywheelCautionTemp = 80;
int flywheelCurveOffset = 3;

int inertialCalibrationTolerance = 1;

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

/*void toggleIntake(void) {
  if (!intakeOverride) {
    if (intakeToggle && !intakeOverride) {
      intakeMotor.stop();
      intakeTwo.stop();
      intakeMotor.setStopping(hold);
      intakeTwo.setStopping(hold);
      intakeToggle = false;
    } else if (!intakeToggle && !intakeOverride) {
      intakeMotor.spin(forward, intakeSpeed, pct);
      intakeTwo.spin(forward, intakeSpeed, pct);
      intakeToggle = true;
    }
  }
}*/

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
  Brain.Screen.print(flywheelBottom.temperature(percent));
  Brain.Screen.print(" pct");
  Brain.Screen.setPenColor(white);

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
  Brain.Screen.print(" degrees (GPS)");
  Brain.Screen.newLine();
  Brain.Screen.print("Turn To Angle: ");
  Brain.Screen.print(turnAngle1);
  Brain.Screen.newLine();
  Brain.Screen.print("GoalX: ");
  Brain.Screen.print(goalX1);
  Brain.Screen.print(" GoalY: ");
  Brain.Screen.print(goalY1);
  Brain.Screen.newLine();
  Brain.Screen.print("Robot Heading: ");
  Brain.Screen.print(inertialSensor.heading());
  Brain.Screen.print(" degrees (INERTIAL)");

  Controller1.Screen.clearLine(1);
  Controller1.Screen.setCursor(1, 1);
  Controller1.Screen.print("ST: ");
  Controller1.Screen.print(flywheelSpeed);
  Controller1.Screen.print(" RPM: ");
  Controller1.Screen.print(flywheelRotation.velocity(rpm));
}

/*void toggleFlywheel(void) {
 if (flywheelToggle) {
   flywheelToggle = !flywheelToggle;
 } else if (!flywheelToggle){
   flywheelToggle = !flywheelToggle;
 }
 waitUntil(!Controller1.ButtonL1.pressing());
}*/

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
  if (!flickToggle) {
    wait(10, msec);
    flapPneumatic.off();
    flickToggle = true;
  } else if (flickToggle) {
    flapPneumatic.on();
    wait(10, msec);
    flickToggle = false;
  }
}

/*void reverseIntake(void) {
  while (Controller1.ButtonB.pressing()) {
    Controller1.rumble(rumbleShort);
    intakeToggle = false;
    intakeOverride = true;
    intakeMotor.spin(reverse, 100, pct);
    intakeTwo.spin(reverse, 100, pct);
  }
}*/

void visionAlign(void) {

  while (Controller1.ButtonDown.pressing()) {
    Controller1.rumble(rumbleShort);
    VisionSensor.takeSnapshot(VisionSensor__SIG_RED);
    if (VisionSensor.largestObject.exists &&
        Controller1.ButtonLeft.pressing()) {
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
    if (VisionSensor.largestObject.exists &&
        Controller1.ButtonRight.pressing()) {
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
  if (dir == left) {
    while (inertialSensor.rotation(degrees) > angle) {
      // while far away go at max speed
      if (inertialSensor.rotation(degrees) > angle + firstSpeedReductionDeg) {
        RF.spin(directionType::fwd, speed,
                velocityUnits::pct); // this is updated for left turns
        RB.spin(directionType::rev, speed, velocityUnits::pct);
        LF.spin(directionType::rev, speed, velocityUnits::pct);
        LB.spin(directionType::fwd, speed, velocityUnits::pct);
      }
      // first notch of slow
      if (inertialSensor.rotation(degrees) > angle + secondSpeedReductionDeg) {
        speed = initSpeed * firstSpeedReduction;
        RF.spin(directionType::fwd, speed,
                velocityUnits::pct); // this is updated for left turns
        RB.spin(directionType::rev, speed, velocityUnits::pct);
        LF.spin(directionType::rev, speed, velocityUnits::pct);
        LB.spin(directionType::fwd, speed, velocityUnits::pct);
      }
      // second notch of slow
      if (inertialSensor.rotation(degrees) > angle + thirdSpeedReductionDeg)
        speed = initSpeed * secondSpeedReduction;
      RF.spin(directionType::fwd, speed,
              velocityUnits::pct); // this is updated for left turns
      RB.spin(directionType::rev, speed, velocityUnits::pct);
      LF.spin(directionType::rev, speed, velocityUnits::pct);
      LB.spin(directionType::fwd, speed, velocityUnits::pct);

      // third notch of slow
      if (inertialSensor.rotation(degrees) > angle + firstSpeedReductionDeg)
        speed = initSpeed * thirdSpeedReduction;
      RF.spin(directionType::fwd, speed,
              velocityUnits::pct); // this is updated for left turns
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

void flywheelController(
    int amountRPM) { // essentially your flywheel rpm control, 0 is coast to
                     // stop, anything more is spool up
  if (amountRPM == 0) {
    flywheelBottom.stop();
    flywheelTop.stop();
    flywheelBottom.setStopping(coast);
    flywheelTop.setStopping(coast);
  }
  if (amountRPM > 0) {
    flywheelBottom.setVelocity(amountRPM, rpm);
    flywheelTop.setVelocity(amountRPM, rpm);
    flywheelBottom.spin(forward);
    flywheelTop.spin(forward);
  }
}

int flywheelTolerance = 15;

void verifyLaunchIntegrity(
    int requiredRPM) { // verify flywheel is of adequite revolutions per minute
                       // and then fire the pneumatic
  waitUntil(
      (flywheelRotation.velocity(rpm) >= requiredRPM - flywheelTolerance) &&
      (flywheelRotation.velocity(rpm) <= requiredRPM + flywheelTolerance));
  // LAUNCH
  triggerPneumatic.off();
  wait(75, msec);
  triggerPneumatic.on();
  wait(75, msec);
}

// autoTurn(left right, angle, initSpeed);
// move("direction", amountDegrees, speed);

// original autonomous method -- EDIT AUTO HERE
void autonomous(void) {
  // autoTurn(left, 1)
  // flapPneumatic.off();
  // autoTurn(left, -3, 75);
  autoTurn(left, -6, 75);
  flywheelController(160);
  verifyLaunchIntegrity(2750);
  verifyLaunchIntegrity(2750);
  flywheelController(0);
  autoTurn(left, -80, 50);
  move("left", 75, 30);
  move("forward", 375, 20);
  move("left", 900, 100);
  move("right", 150, 100);

  //autoTurn(right, -45, 75);
 
  

  // turn heading 90
  //

  // ArmGroup.spin(directionType::rev, 75, velocityUnits::pct);
  // wait(500, msec);
  // ArmGroup.stop();
  // move("backward", 500, 100);
}

void expand(void){
  if(Controller1.ButtonLeft.pressing() && Controller1.ButtonA.pressing()){
  expansionPneumaticF.off();
  expansionPneumaticL.off();
  waitUntil(!Controller1.ButtonLeft.pressing() && !Controller1.ButtonA.pressing());
  }
}

// Driver Control

int toggleSpeed(){
  while(true){
  if(Controller1.ButtonX.pressing())
    {
      flywheelSpeed = flywheelSpeed + 5;
      waitUntil(!Controller1.ButtonX.pressing());
    }      
    else if (Controller1.ButtonY.pressing()) 
    {
      flywheelSpeed = flywheelSpeed - 5;
      waitUntil(!Controller1.ButtonY.pressing());
    }
  }
    return 1;
}

int speedAdjust(){
  while(true){
  if(Controller1.ButtonX.pressing())
    {
      flywheelSpeed = flywheelSpeed + 5;
      waitUntil(!Controller1.ButtonX.pressing());
    }      
    else if (Controller1.ButtonY.pressing()) 
    {
      flywheelSpeed = flywheelSpeed - 5;
      waitUntil(!Controller1.ButtonY.pressing());
    }
  }
    return 1;
}

int toggleIntake(){
  while(true){
  if (!intakeOverride && Controller1.ButtonL2.pressing()) {
    if (intakeToggle && !intakeOverride) {
      intakeMotor.stop();
      intakeTwo.stop();
      intakeMotor.setStopping(hold);
      intakeTwo.setStopping(hold);
      intakeToggle = false;
    } else if (!intakeToggle && !intakeOverride && Controller1.ButtonL2.pressing()) {
      intakeMotor.spin(forward, intakeSpeed, pct);
      intakeTwo.spin(forward, intakeSpeed, pct);
      intakeToggle = true;
    }
    waitUntil(!Controller1.ButtonL2.pressing());
  }
  }
}

int reverseTheINtake(){
  while(true){
   while (Controller1.ButtonB.pressing()) {
    Controller1.rumble(rumbleShort);
    intakeToggle = false;
    intakeOverride = true;
    intakeMotor.spin(reverse, 100, pct);
    intakeTwo.spin(reverse, 100, pct);
  }
  if(!Controller1.ButtonB.pressing() && intakeOverride == true){
    intakeOverride = false;
    intakeToggle = false;
    break;
  }
  
  }
  return 1;
}

void usercontrol(void) {
  GPS.calibrate();
  task test(speedAdjust);
  task urmom(toggleIntake);
  //task ttt(reverseTheINtake);
  while (true) {

    // Controller1.ButtonL1.pressed(toggleFlywheel);
 Controller1.ButtonLeft.pressed(expand);
    drive();

    float botX = 1800 + GPS.xPosition(mm);
    float botY = 1800 + GPS.yPosition(mm);
    float goalX = 3140 - botX;
    float goalY = 3140 - botY;

    goalX1 = goalX;
    goalY1 = goalY;

    float turnAngle = (std::atan(goalX / goalY) * 57.2957795);

    turnAngle1 = turnAngle + flywheelCurveOffset;

    if (Controller1.ButtonUp.pressing()) {
      turn(turnAngle1, 50);
      waitUntil(!Controller1.ButtonUp.pressing());
      wait(500, msec);
    }

    

    //Controller1.ButtonB.pressed(reverseIntake);
    Controller1.ButtonDown.pressed(visionAlign);
    Controller1.ButtonR2.pressed(toggleFlick);

    //Controller1.ButtonL2.pressed(toggleIntake);
    Controller1.ButtonR1.pressed(discBoost);

    // © AntiJAM - Copyright 2022 Millard North Robotics Team
    if (intakeToggle && !intakeOverride) {
      if ((intakeMotor.velocity(percent) == 0) && intakeToggle &&
          !intakeOverride) {
        intakeMotor.spin(reverse, 100, pct);
        intakeTwo.spin(reverse, 100, pct);
      } else if ((intakeMotor.velocity(percent) < -50) && intakeToggle &&
                 !intakeOverride) {
        intakeMotor.spin(forward, intakeSpeed, pct);
        intakeTwo.spin(forward, intakeSpeed, pct);
      }
    }

    // Cancel out intake reverse just in case
    if (intakeOverride && !Controller1.ButtonB.pressing()) {
      intakeMotor.stop();
      intakeTwo.stop();
      intakeMotor.setStopping(coast);
      intakeTwo.setStopping(coast);
      intakeOverride = false;
    }

    if (flywheelToggle && Controller1.ButtonL1.pressing()) {
      flywheelToggle = !flywheelToggle;
      !Controller1.ButtonL1.pressing();
    } else if (!flywheelToggle && Controller1.ButtonL1.pressing()) {
      flywheelToggle = !flywheelToggle;
      !Controller1.ButtonL1.pressing();
    }

    if (!flywheelToggle) {
      flywheelTop.setVelocity(0, rpm);
      flywheelBottom.setVelocity(0, rpm);
      flywheelTop.stop();
      flywheelBottom.stop();
      flywheelTop.setStopping(coast);
      flywheelBottom.setStopping(coast);
    } else if (flywheelToggle) {
      if ((flywheelTop.temperature(percent) ||
           flywheelBottom.temperature(percent)) >= flywheelCautionTemp) {
        Controller1.rumble(rumbleShort);
      }
      flywheelTop.setVelocity(flywheelSpeed, rpm);
      flywheelBottom.setVelocity(flywheelSpeed, rpm);
    }
    flywheelTop.spin(forward);
    flywheelBottom.spin(forward);
    // printFlywheelRPM();
  }
}


int main() {
  triggerPneumatic.on();
  flapPneumatic.on();
  expansionPneumaticF.on();
  expansionPneumaticL.on();
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  
  

  Brain.Screen.setFont(monoM);
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Calibration needed. Place robot and");
  Brain.Screen.newLine();
  Brain.Screen.print("press \"A\" on controller to continue.");
  Brain.Screen.newLine();
  Brain.Screen.setPenColor(red);
  Brain.Screen.setFont(monoL);
  Brain.Screen.print("Do NOT plug into the tower.");
  Controller1.Screen.print("Press \"A\" to continue");
  while(true){
    Controller1.rumble(rumbleShort);
    if(Controller1.ButtonA.pressing()){
      Controller1.rumble(rumbleShort);
      break;
    }
  }


  GPS.calibrate();
  inertialSensor.calibrate();

  Brain.Screen.setFont(monoM);
  Brain.Screen.setPenColor(white);
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Calibrating Sensors... standby (3 seconds)");
  wait(1000, msec);
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Calibrating Sensors... standby (2 seconds)");
  wait(1000, msec);
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Calibrating Sensors... standby (1 second)");
  wait(1000, msec);

  Brain.Screen.setCursor(1, 1);

  if (!((inertialSensor.heading() >= 360 - inertialCalibrationTolerance && inertialSensor.heading() <= 360) || (inertialSensor.heading() >= 0 && inertialSensor.heading() < 0 + inertialCalibrationTolerance))) {
    Brain.Screen.clearScreen();
    Brain.Screen.setPenColor(red);
    Brain.Screen.setFont(monoXXL);
    Controller1.Screen.clearScreen();
    Controller1.Screen.print("Calibration Unsuccessful");
    
    while (true) {
      Controller1.rumble(rumbleLong);
      Brain.Screen.setCursor(1,1);
      Brain.Screen.print("Calibration");
      Brain.Screen.newLine();
      Brain.Screen.print("Unsuccessful");
      wait(1000, msec);
      Brain.Screen.clearScreen();
      wait(1000, msec);
    }
  }
  Brain.Screen.setPenColor(green);
  Brain.Screen.setFont(monoL);
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("Calibration Successful!");
  Brain.Screen.newLine();
  Brain.Screen.setFont(monoXL);
  Brain.Screen.print("Plug into the tower.");
  Controller1.Screen.clearLine(1);
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("Plug into tower");
  Controller1.rumble(rumblePulse);
  wait(5000, msec);
  Brain.Screen.clearScreen();
  Controller1.Screen.clearLine(1);


  // Set up callbacks for autonomous and driver control periods.
  // Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  Competition.autonomous(autonomous);

  // Run the pre-autonomous function.
  // pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    printFlywheelRPM();
    wait(75, msec);
  }
}
