/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Patrick Stolinski                                         */
/*    Created:      Sat Jan 09 2020                                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// DRFront              motor         11              
// DRBack               motor         12              
// DLFront              motor         13              
// DLBack               motor         14              
// LIntake              motor         15              
// RIntake              motor         16              
// FRoller              motor         17              
// BRoller              motor         18              
// Controller1          controller                    
// OpticalSensor        optical       19              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
#include <algorithm>
#include <cmath>


competition Competition;
vision::signature SIG_BLUE (1, -2913, -1607, -2260, 7351, 11879, 9615, 1.000, 0);
vision::signature SIG_RED (2, 6127, 8429, 7278, -511, 505, -3, 2.200, 0);
vision::signature SIG_GREEN (3, -5851, -5359, -5605, -5923, -5481, -5702, 6.000, 0);
vision::signature SIG_4 (4, 0, 0, 0, 0, 0, 0, 3.000, 0);
vision::signature SIG_5 (5, 0, 0, 0, 0, 0, 0, 3.000, 0);
vision::signature SIG_6 (6, 0, 0, 0, 0, 0, 0, 2.500, 0);
vision::signature SIG_7 (7, 0, 0, 0, 0, 0, 0, 2.500, 0);
vex::vision vision1 ( vex::PORT1, 50, SIG_BLUE, SIG_RED, SIG_GREEN, SIG_4, SIG_5, SIG_6, SIG_7 );
int centerFOV = 158;
int offset = 10;
int rearRoller = 80;
int frontRoller = 100;
int intakeSpeed = 200;
int driveSpeed = 135;
//if we are blue, set to 1, if we are red, set to two
int blueOrRed = 0;
bool origComplete = false;

void pre_auton(void) {
// Initializing Robot Configuration. DO NOT REMOVE!
vexcodeInit();

// All activities that occur before the competition starts
// Example: clearing encoders, setting servo positions, ...
}
void forwardIntake() {
LIntake.spin(directionType :: fwd, intakeSpeed , velocityUnits :: pct);
RIntake.spin(directionType :: fwd, intakeSpeed , velocityUnits :: pct);
waitUntil(!Controller1.ButtonL1.pressing());
LIntake.stop();
RIntake.stop();
}
void reverseIntake() {
LIntake.spin(directionType :: rev, intakeSpeed , velocityUnits :: pct);
RIntake.spin(directionType :: rev, intakeSpeed , velocityUnits :: pct);
waitUntil(!Controller1.ButtonL2.pressing());
LIntake.stop();
RIntake.stop();
}
void bringBallUp(){
FRoller.spin(directionType :: fwd, frontRoller , velocityUnits :: pct);
BRoller.spin(directionType :: rev, rearRoller , velocityUnits :: pct);
waitUntil(!Controller1.ButtonR1.pressing());
FRoller.stop();
BRoller.stop();
}
void bringBallDown(){
FRoller.spin(directionType :: rev, frontRoller , velocityUnits :: pct);
BRoller.spin(directionType :: fwd, rearRoller , velocityUnits :: pct);
waitUntil(!Controller1.ButtonR2.pressing());
FRoller.stop();
BRoller.stop();
}
void ejection(){
BRoller.spin(directionType :: fwd, frontRoller , velocityUnits :: pct);
waitUntil(!Controller1.ButtonA.pressing());
BRoller.spin(directionType :: rev, rearRoller , velocityUnits :: pct);
}
void cycleProgram(){
if(blueOrRed == 1){
while(Controller1.ButtonUp.pressing()){
OpticalSensor.setLightPower(100, percent); 
OpticalSensor.setLight(ledState::on);
FRoller.spin(directionType :: fwd, frontRoller , velocityUnits :: pct);
BRoller.spin(directionType :: fwd, rearRoller , velocityUnits :: pct);
if(OpticalSensor.color() == vex::red){
  LIntake.stop();
  RIntake.stop();
FRoller.stop();
BRoller.stop();
while(OpticalSensor.color() == vex::red && (Controller1.ButtonUp.pressing())){
BRoller.spin(directionType :: rev, rearRoller , velocityUnits :: pct);
}
wait(555, msec);
BRoller.stop();
}
}
if(!Controller1.ButtonUp.pressing()){
LIntake.stop();
  RIntake.stop();
FRoller.stop();
BRoller.stop();
OpticalSensor.setLight(ledState::off);
}else if(Controller1.ButtonUp.pressing()){
FRoller.spin(directionType :: fwd, frontRoller , velocityUnits :: pct);
BRoller.spin(directionType :: fwd, rearRoller , velocityUnits :: pct);
OpticalSensor.setLight(ledState::on);
}
}else if(blueOrRed == 2){
while(Controller1.ButtonUp.pressing()){
OpticalSensor.setLightPower(100, percent); 
OpticalSensor.setLight(ledState::on);
FRoller.spin(directionType :: fwd, frontRoller , velocityUnits :: pct);
BRoller.spin(directionType :: fwd, rearRoller , velocityUnits :: pct);
if(OpticalSensor.color() == vex::blue){
  LIntake.stop();
  RIntake.stop();
FRoller.stop();
BRoller.stop();
while(OpticalSensor.color() == vex::blue && (Controller1.ButtonUp.pressing())){
BRoller.spin(directionType :: rev, rearRoller , velocityUnits :: pct);
}
wait(450, msec);
BRoller.stop();
}
}
if(!Controller1.ButtonUp.pressing()){
OpticalSensor.setLight(ledState::off);
LIntake.stop();
  RIntake.stop();
FRoller.stop();
BRoller.stop();
}else if(Controller1.ButtonUp.pressing()){
FRoller.spin(directionType :: fwd, frontRoller , velocityUnits :: pct);
BRoller.spin(directionType :: fwd, rearRoller , velocityUnits :: pct);
OpticalSensor.setLight(ledState::on);
}
}
}

void usercontrol(void) {
vexcodeInit();
while (true) {
  if(!origComplete){
OpticalSensor.setLightPower(100, percent); 
OpticalSensor.setLight(ledState::on);
if(OpticalSensor.color() == vex::blue){
Brain.Screen.print("TEAM 5069B IS BLUE");
blueOrRed = 1;
origComplete = true;
}
if(OpticalSensor.color() == vex::red){
Brain.Screen.print("TEAM 5069B IS RED");
blueOrRed = 2;
origComplete = true;
} 
}else if(origComplete){ 
OpticalSensor.setLight(ledState::off);
}
   //Get the raw sums of the X and Y joystick axes
        double front_left  = (double)(Controller1.Axis3.position(pct) + Controller1.Axis4.position(pct));
        double back_left   = (double)(Controller1.Axis3.position(pct) - Controller1.Axis4.position(pct));
        double front_right = (double)(Controller1.Axis3.position(pct) - Controller1.Axis4.position(pct));
        double back_right  = (double)(Controller1.Axis3.position(pct) + Controller1.Axis4.position(pct));
        
        //Find the largest possible sum of X and Y
        double max_raw_sum = (double)(abs(Controller1.Axis3.position(pct)) + abs(Controller1.Axis4.position(pct)));
        
        //Find the largest joystick value
        double max_XYstick_value = (double)(std::max(abs(Controller1.Axis3.position(pct)),abs(Controller1.Axis4.position(pct))));
        
        //The largest sum will be scaled down to the largest joystick value, and the others will be
        //scaled by the same amount to preserve directionality
        if (max_raw_sum != 0) {
            front_left  = front_left / max_raw_sum * max_XYstick_value;
            back_left   = back_left / max_raw_sum * max_XYstick_value;
            front_right = front_right / max_raw_sum * max_XYstick_value;
            back_right  = back_right / max_raw_sum * max_XYstick_value;
        }
        
        //Now to consider rotation
        //Naively add the rotational axis
        front_left  = front_left  + Controller1.Axis1.position(pct);
        back_left   = back_left   + Controller1.Axis1.position(pct);
        front_right = front_right - Controller1.Axis1.position(pct);
        back_right  = back_right  - Controller1.Axis1.position(pct);
        
        //What is the largest sum, or is 100 larger?
        max_raw_sum = std::max(std::abs(front_left),std::max(std::abs(back_left),std::max(std::abs(front_right),std::max(std::abs(back_right),100.0))));
        
        //Scale everything down by the factor that makes the largest only 100, if it was over
        front_left  = front_left  / max_raw_sum * 100.0;
        back_left   = back_left   / max_raw_sum * 100.0;
        front_right = front_right / max_raw_sum * 100.0;
        back_right  = back_right  / max_raw_sum * 100.0;
        
        //Write the manipulated values out to the motors
         DLFront.spin(fwd,front_left, velocityUnits::pct);
          DLBack.spin(reverse,back_left,  velocityUnits::pct);
        DRFront.spin(fwd,front_right,velocityUnits::pct);
         DRBack.spin(reverse,back_right, velocityUnits::pct);

Controller1.ButtonL1.pressed(forwardIntake);
Controller1.ButtonL2.pressed(reverseIntake);
Controller1.ButtonR1.pressed(bringBallUp);
Controller1.ButtonR2.pressed(bringBallDown);
Controller1.ButtonA.pressed(ejection);
Controller1.ButtonUp.pressed(cycleProgram);

LIntake.setStopping(hold);
RIntake.setStopping(hold);
FRoller.setStopping(hold);
BRoller.setStopping(hold);
}
}

void autonomous(void) {
vexcodeInit();
Brain.Screen.clearScreen();
if(!origComplete){
OpticalSensor.setLightPower(100, percent); 
OpticalSensor.setLight(ledState::on);
if(OpticalSensor.color() == vex::blue){
Brain.Screen.print("TEAM 5069B IS BLUE");
blueOrRed = 1;
origComplete = true;
}
if(OpticalSensor.color() == vex::red){
Brain.Screen.print("TEAM 5069B IS RED");
blueOrRed = 2;
origComplete = true;
} 
}else if(origComplete){ 
OpticalSensor.setLight(ledState::off);
}
}

int main() {
// Set up callbacks for autonomous and driver control periods.
Competition.autonomous(autonomous);
Competition.drivercontrol(usercontrol);

// Run the pre-autonomous function.
pre_auton();

// Prevent main from exiting with an infinite loop.
while (true) {
wait(100, msec);
}
}