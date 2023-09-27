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
// Tread                motor         16              
// MotorGroup1          motor_group   14, 20          
// Drivetrain           drivetrain    17, 13, 15, 18, 12
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

#include "robot-config.h"

competition Competition;

int autonomousInt;

int treadSpeedSet = 75;
int liftSpeedSet = 100;
int y = 0;
int x = 0;

void pre_auton(){
  vexcodeInit();
}

void onScreenPressed() {
  if (Brain.Screen.xPosition() > 250) {
    if (Brain.Screen.yPosition() > 125) {
      // Blue Box Pressed
    }
    else {
      // Green Box Pressed
    }
  }
  else {
    if (Brain.Screen.yPosition() > 125) {
      // Red Box Pressed
    }
    else {
      // White Box Pressed
    }
  }
}


void autonomous(){
  //Calibrate
  MotorGroup1.setPosition(0, degrees);
  Drivetrain.setHeading(0, degrees);
  Drivetrain.setDriveVelocity(100, pct);
  MotorGroup1.setVelocity(100, pct);
  MotorGroup1.spinToPosition(-490, degrees);
  MotorGroup1.setStopping(hold);
  Drivetrain.driveFor(forward, 36, inches);
  Drivetrain.turnToHeading(65, degrees);
  Drivetrain.driveFor(forward, 16, inches);
  Drivetrain.turnToHeading(70, degrees);
  Drivetrain.driveFor(forward, 16, inches);        
  MotorGroup1.spinToPosition(-300, degrees);
  MotorGroup1.setStopping(hold);
  Drivetrain.driveFor(reverse, 20, inches);
  Tread.stop();
  Drivetrain.turnToHeading(0, degrees);
  Drivetrain.driveFor(reverse, 15, inches);
  //Go forward
  
}

int boosterSpeed(){
  if(Controller1.ButtonR1.pressing()){
    return -150;
  }
  else if(Controller1.ButtonR2.pressing()){
    return 150;
  }
  else{
    return 0;
    DriveBooster.setStopping(hold);
  }
}

void drive(){
  if(Controller1.ButtonR1.pressing() || Controller1.ButtonR2.pressing()){
  
  DriveBooster.spin(fwd, boosterSpeed(), pct);
  }else{
   
    DriveBooster.spin(fwd, boosterSpeed(), pct);
    DriveBooster.setStopping(hold);
  }
}

int treadSpeed(){
  if(Controller1.ButtonDown.pressing()){
    return (treadSpeedSet * -1);
  }
  else if(Controller1.ButtonUp.pressing()){
    return treadSpeedSet;
  }
  else{
    return 0;
  }
}

void tread(){
  Tread.spin(fwd, treadSpeed(), pct);
}

int liftSpeed(){
  if(Controller1.ButtonL1.pressing()){
    return liftSpeedSet;
  }
  else if(Controller1.ButtonL2.pressing()){
    return (liftSpeedSet * -1);
  }
  else{
    return 0;
  }
}

void lift(){
  MotorGroup1.spin(forward, liftSpeed(), pct);
}


void userControl(){
  vexcodeInit();
  MotorGroup1.setStopping(hold);
  while(true){
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  Brain.Screen.setFont(propXXL);
  wait(100, msec);
  drive();
  tread();
  lift();
  //flick();
  }
}

void printUI(void){
  Brain.Screen.setPenColor(white);
  Brain.Screen.setFillColor(white);
  Brain.Screen.drawRectangle(30, 10, 200, 50);
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(30, 125, 200, 100);
  Brain.Screen.setFillColor(green);
  Brain.Screen.drawRectangle(250, 10, 200, 100);
  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(250, 125, 200, 100);
}

int main(){
  Competition.autonomous(autonomous);
  Competition.drivercontrol(userControl);
  pre_auton();
  printUI();
  while (true) {
    Brain.Screen.pressed(onScreenPressed);
    wait(10, msec);
  }
}