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
// Controller1          controller                    
// leftIntakeMotor      motor         3               
// rightIntakeMotor     motor         4               
// intakeSpinner        motor         5               
// ejectionSpinner      motor         6               
// middleSpinner        motor         7               
// outtakeSpinner       motor         8               
// driveTrainLeft       motor         1               
// driveTrainRight      motor         2               
// VisionTwo            vision        10              
// OpticalSensor        optical       9               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

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
int rollerSpeed = 110;
int intakeSpeed = 100;
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
leftIntakeMotor.spin(directionType :: fwd, intakeSpeed , velocityUnits :: pct);
rightIntakeMotor.spin(directionType :: fwd, intakeSpeed , velocityUnits :: pct);
waitUntil(!Controller1.ButtonL1.pressing());
leftIntakeMotor.stop();
rightIntakeMotor.stop();
}
void reverseIntake() {
leftIntakeMotor.spin(directionType :: rev, intakeSpeed , velocityUnits :: pct);
rightIntakeMotor.spin(directionType :: rev, intakeSpeed , velocityUnits :: pct);
waitUntil(!Controller1.ButtonL2.pressing());
leftIntakeMotor.stop();
rightIntakeMotor.stop();
}
void bringBallUp(){
intakeSpinner.spin(directionType :: fwd, rollerSpeed , velocityUnits :: pct);
ejectionSpinner.spin(directionType :: fwd, rollerSpeed , velocityUnits :: pct);
middleSpinner.spin(directionType :: fwd, rollerSpeed , velocityUnits :: pct);
outtakeSpinner.spin(directionType :: fwd, rollerSpeed , velocityUnits :: pct);
waitUntil(!Controller1.ButtonR1.pressing());
intakeSpinner.stop();
ejectionSpinner.stop();
middleSpinner.stop();
outtakeSpinner.stop();
}
void bringBallDown(){
intakeSpinner.spin(directionType :: rev, rollerSpeed , velocityUnits :: pct);
ejectionSpinner.spin(directionType :: rev, rollerSpeed , velocityUnits :: pct);
middleSpinner.spin(directionType :: rev, rollerSpeed , velocityUnits :: pct);
outtakeSpinner.spin(directionType :: rev, rollerSpeed , velocityUnits :: pct);
waitUntil(!Controller1.ButtonR2.pressing());
intakeSpinner.stop();
ejectionSpinner.stop();
middleSpinner.stop();
outtakeSpinner.stop();
}
void reverseTopSpinner(){
outtakeSpinner.spin(directionType :: rev, rollerSpeed , velocityUnits :: pct);
waitUntil(!Controller1.ButtonB.pressing());
outtakeSpinner.stop();
}
void ejection(){
ejectionSpinner.spin(directionType :: rev, rollerSpeed , velocityUnits :: pct);
waitUntil(!Controller1.ButtonA.pressing());
ejectionSpinner.spin(directionType :: fwd, rollerSpeed , velocityUnits :: pct);
}
void cycleProgram(){
if(blueOrRed == 1){
while(Controller1.ButtonUp.pressing()){
OpticalSensor.setLightPower(100, percent); 
OpticalSensor.setLight(ledState::on);
intakeSpinner.spin(directionType :: fwd, rollerSpeed , velocityUnits :: pct);
ejectionSpinner.spin(directionType :: fwd, rollerSpeed , velocityUnits :: pct);
middleSpinner.spin(directionType :: fwd, rollerSpeed , velocityUnits :: pct);
outtakeSpinner.spin(directionType :: fwd, rollerSpeed , velocityUnits :: pct);
if(OpticalSensor.color() == vex::red){
  leftIntakeMotor.stop();
  rightIntakeMotor.stop();
intakeSpinner.stop();
middleSpinner.stop();
outtakeSpinner.stop();
while(OpticalSensor.color() == vex::red && (Controller1.ButtonUp.pressing())){
  intakeSpinner.spin(directionType :: fwd, 100 , velocityUnits :: pct);
ejectionSpinner.spin(directionType :: rev, 100 , velocityUnits :: pct);
middleSpinner.spin(directionType :: rev, 100 , velocityUnits :: pct);
}
wait(555, msec);
ejectionSpinner.stop();
}
}
if(!Controller1.ButtonUp.pressing()){
leftIntakeMotor.stop();
  rightIntakeMotor.stop();
intakeSpinner.stop();
ejectionSpinner.stop();
middleSpinner.stop();
outtakeSpinner.stop();
OpticalSensor.setLight(ledState::off);
}else if(Controller1.ButtonUp.pressing()){
intakeSpinner.spin(directionType :: fwd, rollerSpeed , velocityUnits :: pct);
ejectionSpinner.spin(directionType :: fwd, rollerSpeed , velocityUnits :: pct);
middleSpinner.spin(directionType :: fwd, rollerSpeed , velocityUnits :: pct);
outtakeSpinner.spin(directionType :: fwd, rollerSpeed , velocityUnits :: pct);
OpticalSensor.setLight(ledState::on);
}
}else if(blueOrRed == 2){
while(Controller1.ButtonUp.pressing()){
OpticalSensor.setLightPower(100, percent); 
OpticalSensor.setLight(ledState::on);
intakeSpinner.spin(directionType :: fwd, rollerSpeed , velocityUnits :: pct);
ejectionSpinner.spin(directionType :: fwd, rollerSpeed , velocityUnits :: pct);
middleSpinner.spin(directionType :: fwd, rollerSpeed , velocityUnits :: pct);
outtakeSpinner.spin(directionType :: fwd, rollerSpeed , velocityUnits :: pct);
if(OpticalSensor.color() == vex::blue){
  leftIntakeMotor.stop();
  rightIntakeMotor.stop();
intakeSpinner.stop();
middleSpinner.stop();
outtakeSpinner.stop();
while(OpticalSensor.color() == vex::blue && (Controller1.ButtonUp.pressing())){
intakeSpinner.spin(directionType :: fwd, 100 , velocityUnits :: pct);
ejectionSpinner.spin(directionType :: rev, 100 , velocityUnits :: pct);
middleSpinner.spin(directionType :: rev, 100 , velocityUnits :: pct);
}
wait(450, msec);
ejectionSpinner.stop();
}
}
if(!Controller1.ButtonUp.pressing()){
OpticalSensor.setLight(ledState::off);
leftIntakeMotor.stop();
  rightIntakeMotor.stop();
intakeSpinner.stop();
ejectionSpinner.stop();
middleSpinner.stop();
outtakeSpinner.stop();
}else if(Controller1.ButtonUp.pressing()){
intakeSpinner.spin(directionType :: fwd, rollerSpeed , velocityUnits :: pct);
ejectionSpinner.spin(directionType :: fwd, rollerSpeed , velocityUnits :: pct);
middleSpinner.spin(directionType :: fwd, rollerSpeed , velocityUnits :: pct);
outtakeSpinner.spin(directionType :: fwd, rollerSpeed , velocityUnits :: pct);
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
driveTrainLeft.setVelocity(Controller1.Axis3.position(), percent);
driveTrainRight.setVelocity(Controller1.Axis2.position(), percent);
driveTrainLeft.spin(forward);
driveTrainRight.spin(forward);

Controller1.ButtonL1.pressed(forwardIntake);
Controller1.ButtonL2.pressed(reverseIntake);
Controller1.ButtonR1.pressed(bringBallUp);
Controller1.ButtonR2.pressed(bringBallDown);
Controller1.ButtonB.pressed(reverseTopSpinner);
Controller1.ButtonA.pressed(ejection);
Controller1.ButtonUp.pressed(cycleProgram);

leftIntakeMotor.setStopping(hold);
rightIntakeMotor.setStopping(hold);
intakeSpinner.setStopping(hold);
ejectionSpinner.setStopping(hold);
middleSpinner.setStopping(hold);
outtakeSpinner.setStopping(hold);
}
}
//we blue in this one too:)
//follow the damn ball and score it
//like the name don't ya? *uwu*
void autonomous(void) {
vexcodeInit();
Brain.Screen.clearScreen();
//define blue/ red
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
leftIntakeMotor.spin(directionType :: rev, 100, velocityUnits :: pct);
rightIntakeMotor.spin(directionType :: rev, 100, velocityUnits :: pct);
intakeSpinner.spin(directionType :: rev, 100, velocityUnits :: pct);
wait(250, msec);
leftIntakeMotor.stop();
rightIntakeMotor.stop();
intakeSpinner.stop();

//pass out the preload
driveTrainLeft.spin(directionType :: fwd, 60 , velocityUnits :: pct);
driveTrainRight.spin(directionType :: fwd, 60 , velocityUnits :: pct);
leftIntakeMotor.spin(directionType :: fwd, 100, velocityUnits :: pct);
rightIntakeMotor.spin(directionType :: fwd, 100, velocityUnits :: pct);
wait(500, msec);
leftIntakeMotor.stop();
rightIntakeMotor.stop();
wait(350, msec);
driveTrainRight.stop();
driveTrainLeft.stop();
intakeSpinner.spin(directionType :: fwd, rollerSpeed , velocityUnits :: pct);
ejectionSpinner.spin(directionType :: fwd, rollerSpeed , velocityUnits :: pct);
middleSpinner.spin(directionType :: fwd, rollerSpeed , velocityUnits :: pct);
outtakeSpinner.spin(directionType :: fwd, 200 , velocityUnits :: pct);
wait(3700, msec);
driveTrainRight.stop();
driveTrainLeft.stop();
leftIntakeMotor.stop();
rightIntakeMotor.stop();
intakeSpinner.stop();
ejectionSpinner.stop();
middleSpinner.stop();
outtakeSpinner.stop();
wait(500, msec);
driveTrainLeft.spin(directionType :: rev, 75 , velocityUnits :: pct);
driveTrainRight.spin(directionType :: rev, 75 , velocityUnits :: pct);
wait(750, msec);
driveTrainLeft.stop();
driveTrainRight.stop();
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
