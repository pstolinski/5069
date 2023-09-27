/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\pstolinski                                       */
/*    Created:      Tue Jun 21 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LF                   motor         16              
// LB                   motor         11              
// RF                   motor         10              
// RB                   motor         20              
// Flywheel             motor_group   3, 4            
// Pneumatic            led           A               
// GPS                  gps           15              
// Intake               motor_group   13, 12          
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <algorithm>
#include <cmath>

using namespace vex;

competition Competition;

int intakeSpeed = 25;
int flywheelSpeed = 75;

int launchMinimums = 50;
int flywheelCautionTemp = 60;

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

float goalX1;
float goalY1;
float turnAngle1;

void toggleIntake(void) {
  if (intakeToggle) {
    Intake.stop();
    Intake.setStopping(hold);
    intakeToggle = false;
  } else if (!intakeToggle) {
    Intake.spin(forward, intakeSpeed, pct);
    intakeToggle = true;
  }
}

void toggleFlywheel(void) {
  if (flywheelToggle) {
    Flywheel.stop();
    Flywheel.setStopping(coast);
    waitUntil(!Controller1.ButtonL1.pressing());
    flywheelToggle = false;
  } else {
    if (Flywheel.temperature(percent) >= flywheelCautionTemp) {
      Controller1.rumble(rumbleShort);
    }
    Flywheel.spin(forward, flywheelSpeed, pct);
    waitUntil(!Controller1.ButtonL1.pressing());
    flywheelToggle = true;
  }
}

void discBoost(void) {
  if (Flywheel.velocity(percent) > launchMinimums) {
    Pneumatic.off();
    wait(500, msec);
    Pneumatic.on();
  } else {
    Controller1.rumble(rumbleShort);
  }
}

// Game Positioning System
//--Goal (1340, 1340)

int checker = 1;
void printFlywheelRPM(void) {

  Brain.Screen.setCursor(1, 1);
  Brain.Screen.setFont(monoXL);
  Brain.Screen.print("Flywheel System");
  Brain.Screen.newLine();
  Brain.Screen.newLine();
  Brain.Screen.setFont(monoM);
  Brain.Screen.print("Velocity:    ");
  Brain.Screen.print(Flywheel.velocity(percent));
  Brain.Screen.print(" pct");
  Brain.Screen.newLine();
  Brain.Screen.print("Efficiency:  ");
  Brain.Screen.print(Flywheel.efficiency(percent));
  Brain.Screen.print(" pct");
  Brain.Screen.newLine();
  if (Flywheel.temperature(percent) >= flywheelCautionTemp) {
    Brain.Screen.setPenColor(red);
  }
  Brain.Screen.print("Temperature: ");
  Brain.Screen.print(Flywheel.temperature(percent));
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
  if (Flywheel.velocity(percent) == 0 && checker == 1) {
    Brain.Screen.clearScreen();
    Controller1.Screen.clearLine(1);
    checker = 0;
  } else if (Flywheel.velocity(percent) > 10) {
    checker = 1;
  }

  if (Flywheel.velocity(percent) > launchMinimums) {
    Controller1.Screen.print("Flywheel: ");
    Controller1.Screen.print(Flywheel.velocity(percent));
    if (Flywheel.temperature(percent) >= flywheelCautionTemp) {
      Controller1.Screen.print(" TEMP");
    } else if (Flywheel.temperature(percent) < flywheelCautionTemp) {
      Controller1.Screen.print(" pct");
    }
    wait(10, msec);
  } else {
    Controller1.Screen.print("Flywheel");
    if (Flywheel.temperature(percent) >= flywheelCautionTemp) {
      Controller1.Screen.print(" TEMP");
    } else if (Flywheel.temperature(percent) < flywheelCautionTemp) {
      Controller1.Screen.print(" Below Mins");
    }
  }
}

// DO NOT TOUCH -- TURN CODE (PIVOT) -Patrick
// New Autonomous Methods (using inertial sensor)
void turn(double angle, double initSpeed) {
  double speed = initSpeed;
  
  // Right Turn
    if(GPS.heading() > angle && GPS.heading() < (angle + 180)){
      RF.spin(directionType::fwd, speed, velocityUnits::pct); // this is updated for right turns
        RB.spin(directionType::rev, speed, velocityUnits::pct);
        LF.spin(directionType::rev, speed, velocityUnits::pct);
        LB.spin(directionType::fwd, speed, velocityUnits::pct);
    }else{
      RF.spin(directionType::rev, speed, velocityUnits::pct); // this is updated for right turns
        RB.spin(directionType::fwd, speed, velocityUnits::pct);
        LF.spin(directionType::fwd, speed, velocityUnits::pct);
        LB.spin(directionType::rev, speed, velocityUnits::pct);
    }
    waitUntil(GPS.heading()<= angle && GPS.heading() >= angle-3);
    RF.stop();
    RB.stop();
    LF.stop();
    LB.stop();
    
      
      /**
      // while far away go at max speed
      if (GPS.heading() < angle - firstSpeedReductionDeg) {
        RF.spin(directionType::rev, speed,
                velocityUnits::pct); // this is updated for right turns
        RB.spin(directionType::fwd, speed, velocityUnits::pct);
        LF.spin(directionType::fwd, speed, velocityUnits::pct);
        LB.spin(directionType::rev, speed, velocityUnits::pct);
      }
      // first notch of slow
      if (GPS.heading() < angle - secondSpeedReductionDeg) {
        speed = initSpeed * firstSpeedReduction;
        RF.spin(directionType::rev, speed,
                velocityUnits::pct); // this is updated for right turns
        RB.spin(directionType::fwd, speed, velocityUnits::pct);
        LF.spin(directionType::fwd, speed, velocityUnits::pct);
        LB.spin(directionType::rev, speed, velocityUnits::pct);
      }
      // second notch of slow
      if (GPS.heading() < angle - thirdSpeedReductionDeg)
        speed = initSpeed * secondSpeedReduction;
      RF.spin(directionType::rev, speed,
              velocityUnits::pct); // this is updated for right turns
      RB.spin(directionType::fwd, speed, velocityUnits::pct);
      LF.spin(directionType::fwd, speed, velocityUnits::pct);
      LB.spin(directionType::rev, speed, velocityUnits::pct);

      // third notch of slow
      if (GPS.heading() < angle - firstSpeedReductionDeg)
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
    while (GPS.heading() > angle) {
      // while far away go at max speed
      if (GPS.heading() > angle + firstSpeedReductionDeg) {
        RF.spin(directionType::fwd, speed,
                velocityUnits::pct); // this is updated for right turns
        RB.spin(directionType::rev, speed, velocityUnits::pct);
        LF.spin(directionType::rev, speed, velocityUnits::pct);
        LB.spin(directionType::fwd, speed, velocityUnits::pct);
      }
      // first notch of slow
      if (GPS.heading() > angle + secondSpeedReductionDeg) {
        speed = initSpeed * firstSpeedReduction;
        RF.spin(directionType::fwd, speed,
                velocityUnits::pct); // this is updated for right turns
        RB.spin(directionType::rev, speed, velocityUnits::pct);
        LF.spin(directionType::rev, speed, velocityUnits::pct);
        LB.spin(directionType::fwd, speed, velocityUnits::pct);
      }
      // second notch of slow
      if (GPS.heading() > angle + thirdSpeedReductionDeg) {
        speed = initSpeed * secondSpeedReduction;
        RF.spin(directionType::fwd, speed,
                velocityUnits::pct); // this is updated for right turns
        RB.spin(directionType::rev, speed, velocityUnits::pct);
        LF.spin(directionType::rev, speed, velocityUnits::pct);
        LB.spin(directionType::fwd, speed, velocityUnits::pct);
      }
      // third notch of slow
      if (GPS.heading() > angle + firstSpeedReductionDeg) {
        speed = initSpeed * thirdSpeedReduction;
        RF.spin(directionType::fwd, speed,
                velocityUnits::pct); // this is updated for right turns
        RB.spin(directionType::rev, speed, velocityUnits::pct);
        LF.spin(directionType::rev, speed, velocityUnits::pct);
        LB.spin(directionType::fwd, speed, velocityUnits::pct);
      }
    }**/
  
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

void drive(void){
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

    turnAngle1 = turnAngle;

    if (Controller1.ButtonUp.pressing()) {
      turn(turnAngle, 50);
      waitUntil(!Controller1.ButtonUp.pressing());
      wait(500, msec);
    }
    Controller1.ButtonL1.pressed(toggleFlywheel);
    Controller1.ButtonX.pressed(toggleIntake);
    Controller1.ButtonR1.pressed(discBoost);

    // © AntiJAM - Copyright 2022 Millard North Robotics Team
    if (intakeToggle) {
      if ((Intake.velocity(percent) == 0) && intakeToggle) {
        Intake.spin(reverse, 100, pct);
      } else if ((Intake.velocity(percent) < -50) && intakeToggle) {
        Intake.spin(forward, intakeSpeed, pct);
      }
    }

    printFlywheelRPM();
  }
}

int main() {
  Pneumatic.on();
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  GPS.calibrate();
  // Set up callbacks for autonomous and driver control periods.
  // Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  // pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {

    wait(10, msec);
  }
}
